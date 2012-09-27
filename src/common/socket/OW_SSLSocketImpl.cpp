/*******************************************************************************
* Copyright (C) 2001-2004 Vintela, Inc. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
*  - Neither the name of Vintela, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
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
 * @name		OW_SSLSocketImpl.cpp
 * @author	J. Bart Whiteley
 * @author Dan Nuffer
 *
 * @description
 *		Implementation file for the SSLSocketImpl class.
 */

#include "OW_config.h"
#include "OW_SSLSocketImpl.hpp"
#include "OW_Format.hpp"
#include "OW_Assertion.hpp"
#ifdef OW_HAVE_OPENSSL
#include <openssl/err.h>
#include <OW_Format.hpp>
#include <OW_SocketUtils.hpp>


namespace OW_NAMESPACE
{
//////////////////////////////////////////////////////////////////////////////
SSLSocketImpl::SSLSocketImpl(SSLClientCtxRef sslCtx) 
	: SocketBaseImpl()
	, m_ssl(0)
	, m_sslCtx(sslCtx)
{
}

namespace
{

void sslWaitForIO(SocketBaseImpl& s, int type)
{
	if(type == SSL_ERROR_WANT_READ)
	{
		s.waitForInput();
	}
	else
	{
		s.waitForOutput();
	}
}

void shutdownSSL(SSL* ssl)
{
	OW_ASSERT(ssl != 0);
	if (SSL_shutdown(ssl) == -1)
	{
		// do nothing, since we're probably cleaning up.  If we had a logger we should log the reason why this failed....
	}
	// we're not going to reuse the SSL context, so we do a 
	// unidirectional shutdown, and don't need to call it twice
}

void connectWithSSL(SSL* ssl, SocketBaseImpl& s)
{
	OW_ASSERT(ssl != 0);
	int retries = 0;
	ERR_clear_error();
	int cc = SSL_connect(ssl);
	cc = SSL_get_error(ssl, cc);
	while((cc == SSL_ERROR_WANT_READ 
		|| cc == SSL_ERROR_WANT_WRITE)
		&& retries < OW_SSL_RETRY_LIMIT)
	{
		sslWaitForIO(s, cc);
		ERR_clear_error();
		cc = SSL_connect(ssl);
		cc = SSL_get_error(ssl, cc);
		retries++;
	}

	if (cc != SSL_ERROR_NONE)
	{
		OW_THROW(SSLException, Format("SSL connect error: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}
}

int acceptSSL(SSL* ssl, SocketBaseImpl& s, String& errorDescription)
{
	OW_ASSERT(ssl != 0);
	int retries = 0;
	int cc = SSL_ERROR_WANT_READ;
	while((cc == SSL_ERROR_WANT_READ || cc == SSL_ERROR_WANT_WRITE)
		&& retries < OW_SSL_RETRY_LIMIT)
	{
		sslWaitForIO(s, cc);
		ERR_clear_error();
		cc = SSL_accept(ssl);
		cc = SSL_get_error(ssl, cc);
		retries++;
	}
	if (cc == SSL_ERROR_NONE)
	{
		return 0;
	}
	else
	{
		errorDescription = SSLCtxMgr::getOpenSSLErrorDescription();
		return -1;
	}
}

}	// End of unnamed namespace

//////////////////////////////////////////////////////////////////////////////
SSLSocketImpl::SSLSocketImpl() 
	: SocketBaseImpl()
	, m_ssl(0)
	, m_sbio(0)
{
}
//////////////////////////////////////////////////////////////////////////////
SSLSocketImpl::SSLSocketImpl(SocketHandle_t fd, 
	SocketAddress::AddressType addrType, const SSLServerCtxRef& sslCtx) 
	: SocketBaseImpl(fd, addrType)
{
	OW_ASSERT(sslCtx);
	ERR_clear_error();
	m_ssl = SSL_new(sslCtx->getSSLCtx());
	if (!m_ssl)
	{
		OW_THROW(SSLException, Format("SSL_new failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}

	if (SSL_set_ex_data(m_ssl, SSLServerCtx::SSL_DATA_INDEX, &m_owctx) == 0)
	{
		OW_THROW(SSLException, Format("SSL_set_ex_data failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}

	BIO* bio = BIO_new_socket(fd, BIO_NOCLOSE);
	if (!bio)
	{
		SSL_free(m_ssl);
		OW_THROW(SSLException, Format("BIO_new_socket failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}
		
	SSL_set_bio(m_ssl, bio, bio);
	String errorDescription;
	if (acceptSSL(m_ssl, *this, errorDescription) != 0)
	{
		shutdownSSL(m_ssl);
		SSL_free(m_ssl);
		ERR_remove_state(0); // cleanup memory SSL may have allocated
		OW_THROW(SSLException, Format("SSLSocketImpl ctor: SSL accept error while connecting to %1: %2", m_peerAddress.toString(), errorDescription).c_str());
	}
	if (!SSLCtxMgr::checkClientCert(m_ssl, m_peerAddress.getName()))
	{
		shutdownSSL(m_ssl);
		SSL_free(m_ssl);
		ERR_remove_state(0); // cleanup memory SSL may have allocated
		OW_THROW(SSLException, "SSL failed to authenticate client");
	}
}

// TODO Get rid of this one later. 
//////////////////////////////////////////////////////////////////////////////
SSLSocketImpl::SSLSocketImpl(SocketHandle_t fd, 
	SocketAddress::AddressType addrType) 
	: SocketBaseImpl(fd, addrType)
{
	ERR_clear_error();
	m_ssl = SSL_new(SSLCtxMgr::getSSLCtxServer());
	if (!m_ssl)
	{
		OW_THROW(SSLException, Format("SSL_new failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}

	m_sbio = BIO_new_socket(fd, BIO_NOCLOSE);
	if (!m_sbio)
	{
		SSL_free(m_ssl);
		OW_THROW(SSLException, Format("BIO_new_socket failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}
		
	SSL_set_bio(m_ssl, m_sbio, m_sbio);
	String errorDescription;
	if (acceptSSL(m_ssl, *this, errorDescription) != 0)
	{
		shutdownSSL(m_ssl);
		SSL_free(m_ssl);
		ERR_remove_state(0); // cleanup memory SSL may have allocated
		OW_THROW(SSLException, Format("SSLSocketImpl ctor: SSL accept error while connecting to %1: %2", m_peerAddress.toString(), errorDescription).c_str());
	}
	if (!SSLCtxMgr::checkClientCert(m_ssl, m_peerAddress.getName()))
	{
		shutdownSSL(m_ssl);
		SSL_free(m_ssl);
		ERR_remove_state(0); // cleanup memory SSL may have allocated
		OW_THROW(SSLException, "SSL failed to authenticate client");
	}
}
//////////////////////////////////////////////////////////////////////////////
SSLSocketImpl::SSLSocketImpl(const SocketAddress& addr) 
	: SocketBaseImpl(addr)
{
	connectSSL();
}
//////////////////////////////////////////////////////////////////////////////
SSLSocketImpl::~SSLSocketImpl()
{
	try
	{
		disconnect(); 
		if (m_ssl)
		{
			SSL_free(m_ssl);
			m_ssl = 0; 
		}
		ERR_remove_state(0); // cleanup memory SSL may have allocated
	}
	catch (...)
	{
		// no exceptions allowed out of destructors.
	}
}
//////////////////////////////////////////////////////////////////////////////
Select_t
SSLSocketImpl::getSelectObj() const
{
#if defined(OW_WIN32)
	Select_t st;
	st.event = m_event;
	st.sockfd = m_sockfd;
	st.networkevents = FD_READ | FD_WRITE;
	st.doreset = true;
	return st;
#else
	return m_sockfd;
#endif
}
//////////////////////////////////////////////////////////////////////////////
void 
SSLSocketImpl::connect(const SocketAddress& addr)
{
	SocketBaseImpl::connect(addr);
	connectSSL();
}
//////////////////////////////////////////////////////////////////////////////
void 
SSLSocketImpl::connectSSL()
{
	m_isConnected = false;
	OW_ASSERT(m_sslCtx); 
	if (m_ssl)
	{
		SSL_free(m_ssl); 
		m_ssl = 0;
	}
	ERR_clear_error();
	m_ssl = SSL_new(m_sslCtx->getSSLCtx()); 
	
	if (!m_ssl)
	{
		OW_THROW(SSLException, Format("SSL_new failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}
	m_sbio = BIO_new_socket(m_sockfd, BIO_NOCLOSE);
	if (!m_sbio)
	{
		SSL_free(m_ssl);
		OW_THROW(SSLException, Format("BIO_new_socket failed: %1", SSLCtxMgr::getOpenSSLErrorDescription()).c_str());
	}
	SSL_set_bio(m_ssl, m_sbio, m_sbio);

	connectWithSSL(m_ssl, *this);

	if (!SSLCtxMgr::checkServerCert(m_ssl, m_peerAddress.getName()))
	{
		OW_THROW(SSLException, "Failed to validate peer certificate");
	}
	m_isConnected = true;
}
//////////////////////////////////////////////////////////////////////////////
void
SSLSocketImpl::disconnect()
{
#if defined(OW_WIN32)
	if (m_sockfd != INVALID_SOCKET && m_isConnected)
#else
	if (m_sockfd != -1 && m_isConnected)
#endif
	{
		if (m_ssl)
		{
			shutdownSSL(m_ssl);
		}
	}
	SocketBaseImpl::disconnect();
}
//////////////////////////////////////////////////////////////////////////////
int 
SSLSocketImpl::writeAux(const void* dataOut, int dataOutLen)
{
	return SSLCtxMgr::sslWrite(m_ssl, static_cast<const char*>(dataOut), 
			dataOutLen);
}
//////////////////////////////////////////////////////////////////////////////
int 
SSLSocketImpl::readAux(void* dataIn, int dataInLen)
{
	return SSLCtxMgr::sslRead(m_ssl, static_cast<char*>(dataIn), 
			dataInLen);
}
//////////////////////////////////////////////////////////////////////////////
SSL*
SSLSocketImpl::getSSL() const
{
	return m_ssl; 
}

//////////////////////////////////////////////////////////////////////////////
bool
SSLSocketImpl::peerCertVerified() const
{
    return (m_owctx.peerCertPassedVerify == OWSSLContext::VERIFY_PASS); 
}

//////////////////////////////////////////////////////////////////////////////
// SSL buffer can contain the data therefore select
// does not work without checking SSL_pending() first.
bool
SSLSocketImpl::waitForInput(int timeOutSecs)
{
   // SSL buffer contains data -> read them
   if (SSL_pending(m_ssl))
   {
	   return false;
   }
   return SocketBaseImpl::waitForInput(timeOutSecs);
}
//////////////////////////////////////////////////////////////////////////////

} // end namespace OW_NAMESPACE

//////////////////////////////////////////////////////////////////////////////
#endif // #ifdef OW_HAVE_OPENSSL

