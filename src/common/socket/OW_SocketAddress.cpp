/*******************************************************************************
* Copyright (C) 2001-2004 Vintela, Inc. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of source code must retain the above copyright notice,
*	this list of conditions and the following disclaimer.
*
*  - Redistributions in binary form must reproduce the above copyright notice,
*	this list of conditions and the following disclaimer in the documentation
*	and/or other materials provided with the distribution.
*
*  - Neither the name of Vintela, Inc. nor the names of its
*	contributors may be used to endorse or promote products derived from this
*	software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL Vintela, Inc. OR THE CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/**
 * @author Bart Whiteley
 * @author Dan Nuffer
 */

#include "OW_config.h"
#include "OW_SocketAddress.hpp"
#include "OW_ByteSwap.hpp"
#include "OW_Assertion.hpp"
#include "OW_Mutex.hpp"
#include "OW_MutexLock.hpp"
#include "OW_ExceptionIds.hpp"

extern "C"
{
#if !defined(OW_WIN32)
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include <sys/utsname.h>
#include <unistd.h>
#endif

#include <errno.h>
}

namespace OW_NAMESPACE
{

OW_DEFINE_EXCEPTION_WITH_ID(UnknownHost);
OW_DEFINE_EXCEPTION_WITH_ID(SocketAddress);

const char* const SocketAddress::ALL_LOCAL_ADDRESSES = "0.0.0.0";

#if !defined(OW_WIN32)
//////////////////////////////////////////////////////////////////////////////
//static
SocketAddress
SocketAddress::getUDS(const String& filename)
{
	SocketAddress rval;
	rval.m_type = UDS;
	rval.m_name = filename;
	rval.m_address = "localhost";
	memset(&rval.m_UDSNativeAddress, 0, sizeof(rval.m_UDSNativeAddress));
	rval.m_UDSNativeAddress.sun_family = AF_UNIX;
	strncpy(rval.m_UDSNativeAddress.sun_path, filename.c_str(),
		sizeof(rval.m_UDSNativeAddress.sun_path) - 1);
#ifdef OW_SOLARIS
	rval.m_nativeSize = ::strlen(rval.m_UDSNativeAddress.sun_path) +
		offsetof(struct sockaddr_un, sun_path);
#elif defined OW_OPENUNIX
	rval.m_UDSNativeAddress.sun_len = sizeof(rval.m_UDSNativeAddress);
	rval.m_nativeSize = ::strlen(rval.m_UDSNativeAddress.sun_path) +
		offsetof(struct sockaddr_un, sun_path);
#elif defined OW_AIX || defined OW_DARWIN
	// AIX requires the NULL terminator to be included in the sizes.
	rval.m_UDSNativeAddress.sun_len = filename.length() + 1;
	rval.m_nativeSize = ::strlen(rval.m_UDSNativeAddress.sun_path) +
		offsetof(struct sockaddr_un, sun_path) + 1;	
#elif defined OW_FREEBSD
	rval.m_nativeSize = ::strlen(rval.m_UDSNativeAddress.sun_path)
		+ sizeof(rval.m_UDSNativeAddress.sun_len)
		+ sizeof(rval.m_UDSNativeAddress.sun_family);
#else
	rval.m_nativeSize = sizeof(rval.m_UDSNativeAddress.sun_family) +
		 ::strlen(rval.m_UDSNativeAddress.sun_path);
#endif
	return rval;
}

#endif	// #if !defined(OW_WIN32)

//////////////////////////////////////////////////////////////////////////////
SocketAddress::SocketAddress()
	: m_nativeSize(0) , m_type(UNSET)
{
}

#ifndef OW_HAVE_GETHOSTBYNAME_R
Mutex gethostbynameMutex;
#endif

//////////////////////////////////////////////////////////////////////////////
//static
SocketAddress
SocketAddress::getByName(const String& hostName, UInt16 port)
{
#if defined(OW_HAVE_GETHOSTBYNAME_R) && defined(OW_GETHOSTBYNAME_R_ARGUMENTS)
	hostent hostbuf;
	hostent* host = &hostbuf;
#if (OW_GETHOSTBYNAME_R_ARGUMENTS == 6)
	char buf[2048];
	int h_err = 0;
	if (gethostbyname_r(hostName.c_str(), &hostbuf, buf, sizeof(buf),
						&host, &h_err) == -1)
	{
		host = NULL;
	}
#elif (OW_GETHOSTBYNAME_R_ARGUMENTS == 5)

	char buf[2048];
	int h_err(0);
	// returns NULL if not successful
	host = gethostbyname_r(hostName.c_str(), &hostbuf, buf, sizeof(buf), &h_err);

#elif (OW_GETHOSTBYNAME_R_ARGUMENTS == 3)
	hostent_data hostdata;
	if (gethostbyname_r(hostName.c_str(), &hostbuf, &hostdata) != 0)
	{
		host = NULL;
	}

#else
#error Not yet supported: gethostbyname_r() with other argument counts.
#endif /* OW_GETHOSTBYNAME_R_ARGUMENTS */
#else
	MutexLock mlock(gethostbynameMutex);
	hostent* host = gethostbyname(hostName.c_str());
#endif /* defined(OW_HAVE_GETHOSTBYNAME_R) && defined(OW_GETHOSTBYNAME_R_ARGUMENTS) */

	if (!host)
	{
		OW_THROW(UnknownHostException, String("Unknown host: ").concat(hostName).c_str());
	}
	in_addr addr;
	memcpy(&addr, host->h_addr_list[0], sizeof(addr));
	return getFromNativeForm(addr, port, host->h_name);
}

//////////////////////////////////////////////////////////////////////////////
//static
SocketAddress
SocketAddress::getFromNativeForm( const InetSocketAddress_t& nativeForm)
{
	return SocketAddress(nativeForm);
}

#if !defined(OW_WIN32)
//////////////////////////////////////////////////////////////////////////////
//static
SocketAddress
SocketAddress::getFromNativeForm( const UnixSocketAddress_t& nativeForm)
{
	return SocketAddress(nativeForm);
}
#endif	// !defined(OW_WIN32)

//////////////////////////////////////////////////////////////////////////////
//static
SocketAddress
SocketAddress::getFromNativeForm( const InetAddress_t& nativeForm,
		UInt16 nativePort, const String& hostName)
{
	InetSocketAddress_t addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = hton16(nativePort);
	addr.sin_addr = nativeForm;
	SocketAddress p = SocketAddress(addr);
	p.m_type = INET;
	p.m_name = hostName;
	return p;
}
//////////////////////////////////////////////////////////////////////////////
const SocketAddress_t* SocketAddress::getNativeForm() const
{
	if (m_type == INET)
	{
		return reinterpret_cast<const sockaddr*>(&m_inetNativeAddress);
	}

#if !defined(OW_WIN32)
	else if (m_type == UDS)
	{
		return reinterpret_cast<const sockaddr*>(&m_UDSNativeAddress);
	}
#endif

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
const InetSocketAddress_t* SocketAddress::getInetAddress() const
{
	return &m_inetNativeAddress;
}

#if !defined(OW_WIN32)
//////////////////////////////////////////////////////////////////////////////
// Get a pointer to the UnixSocketAddress_t
// precondition: getType() == UDS
const UnixSocketAddress_t* SocketAddress::getUnixAddress() const
{
	return &m_UDSNativeAddress;
}
#endif

//////////////////////////////////////////////////////////////////////////////
SocketAddress
SocketAddress::getAnyLocalHost(UInt16 port)
{
	struct in_addr addr;
	addr.s_addr = hton32(INADDR_ANY);
	SocketAddress rval = getFromNativeForm(addr, port, "localhost");
	char buf[256];
	gethostname(buf, sizeof(buf));
	String hname(buf);
	if (hname.indexOf('.') == String::npos)
	{
#if defined(OW_HAVE_GETHOSTBYNAME_R) && defined(OW_GETHOSTBYNAME_R_ARGUMENTS)
		hostent hostbuf;
		hostent* hent = &hostbuf;
#if (OW_GETHOSTBYNAME_R_ARGUMENTS == 6)
		char local_buf[2048];
		int h_err = 0;
		if (gethostbyname_r(buf, &hostbuf, local_buf, sizeof(local_buf),
							&hent, &h_err) == -1)
		{
			hent = NULL;
		}
#elif (OW_GETHOSTBYNAME_R_ARGUMENTS == 5)

		char local_buf[2048];
		int h_err(0);
		// returns NULL if not successful
		hent = gethostbyname_r(buf, &hostbuf, local_buf, sizeof(local_buf), &h_err);

#elif (OW_GETHOSTBYNAME_R_ARGUMENTS == 3)
		hostent_data hostdata;
		if (gethostbyname_r(buf, &hostbuf, &hostdata) != 0)
		{
			hent = NULL;
		}

#else
#error Not yet supported: gethostbyname_r() with other argument counts.
#endif /* OW_GETHOSTBYNAME_R_ARGUMENTS */
#else	
		MutexLock mlock(gethostbynameMutex);
		hostent* hent = gethostbyname(buf);
#endif
		if (hent && hent->h_name && (strlen(hent->h_name) > 0))
		{
			hname = String(hent->h_name);
		}
	}
	rval.m_name = hname;
	return rval;
}

//////////////////////////////////////////////////////////////////////////////
void SocketAddress::assignFromNativeForm(
	const InetSocketAddress_t* address, size_t /*size*/)
{
	char    buf[INET6_ADDRSTRLEN];
	m_type = INET;
	memcpy(&m_inetNativeAddress, address, sizeof(m_inetNativeAddress));
	m_address = inet_ntop(address->sin_family, &(address->sin_addr), buf, 
                sizeof(buf));
	m_nativeSize = sizeof(m_inetNativeAddress);
}

#if !defined(OW_WIN32)
//////////////////////////////////////////////////////////////////////////////
void SocketAddress::assignFromNativeForm(
	const UnixSocketAddress_t* address, size_t /*size*/)
{
	m_type = UDS;
	memcpy(&m_UDSNativeAddress, address, sizeof(m_UDSNativeAddress));
	m_address = "localhost";
	m_name = m_UDSNativeAddress.sun_path;
	m_nativeSize = sizeof(m_UDSNativeAddress);
}
#endif	// !defined(OW_WIN32)

//////////////////////////////////////////////////////////////////////////////
UInt16 SocketAddress::getPort() const
{
	OW_ASSERT(m_type == INET);
	return ntoh16(m_inetNativeAddress.sin_port);
}

#if !defined(OW_WIN32)
//////////////////////////////////////////////////////////////////////////////
SocketAddress::SocketAddress(const UnixSocketAddress_t& nativeForm)
	: m_nativeSize(0), m_type(UDS)
{
	assignFromNativeForm(&nativeForm, sizeof(nativeForm));
}
#endif	// !defined(OW_WIN32)

//////////////////////////////////////////////////////////////////////////////
SocketAddress::SocketAddress(const InetSocketAddress_t& nativeForm)
	: m_nativeSize(0), m_type(INET)
{
	assignFromNativeForm(&nativeForm, sizeof(nativeForm));
}
//////////////////////////////////////////////////////////////////////////////
const String SocketAddress::getName() const
{
	return m_name;
}
//////////////////////////////////////////////////////////////////////////////
const String SocketAddress::getAddress() const
{
	return m_address;
}
//////////////////////////////////////////////////////////////////////////////
size_t SocketAddress::getNativeFormSize() const
{
	return m_nativeSize;
}
//////////////////////////////////////////////////////////////////////////////
SocketAddress SocketAddress::allocEmptyAddress(AddressType type)
{
	if (type == INET)
	{
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		return SocketAddress(SocketAddress::getFromNativeForm(addr));
	}
#if !defined(OW_WIN32)
	else if (type == UDS)
	{
		sockaddr_un addr;
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		return SocketAddress(SocketAddress::getFromNativeForm(addr));
	}
#endif

	OW_THROW(SocketAddressException, "Bad Address Type");
}
//////////////////////////////////////////////////////////////////////////////
const String
SocketAddress::toString() const
{
	OW_ASSERT(m_type != UNSET);
	String rval;
	if (m_type == INET)
	{
		rval = getAddress() + ":" + String(UInt32(getPort()));
	}
	else
	{
		rval = this->m_name;
	}
	return rval;
}

} // end namespace OW_NAMESPACE

