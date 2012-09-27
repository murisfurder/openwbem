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
 * @author Jon Carey
 * @author Dan Nuffer
 */

#ifndef OW_NETWORK_TYPES_HPP_INCLUDE_GUARD_
#define OW_NETWORK_TYPES_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_Types.hpp"

extern "C"
{
#ifdef OW_HAVE_UNISTD_H
 #include <unistd.h>
#endif

#include <signal.h>

#ifdef OW_HAVE_SYS_SOCKET_H
 #include <sys/socket.h>
#endif

#ifdef OW_HAVE_NETINET_IN_H
 #include <netinet/in.h>
#endif

#ifdef OW_HAVE_SYS_UN_H
 #include <sys/un.h>
#endif

#if defined(OW_WIN32)
#include <winsock2.h>
#endif
}

#undef shutdown // On OpenUnix, sys/socket.h defines shutdown to be
				// _shutdown.  (which breaks HTTPServer, etc.)

namespace OW_NAMESPACE
{

// Platform specific socket address type
typedef sockaddr		SocketAddress_t;
// Platform specific inet socket address type
typedef sockaddr_in		InetSocketAddress_t;

#if !defined(OW_WIN32)
	// Platform specific unix socket address type
	typedef sockaddr_un		UnixSocketAddress_t;
#endif

// Platform specific socket address type
typedef in_addr		InetAddress_t;

#if defined (OW_WIN32)
// Platform specific socket fd type
typedef SOCKET			SocketHandle_t;
#else
// Platform specific socket fd type
typedef int 			SocketHandle_t;
#endif

} // end namespace OW_NAMESPACE

#if defined(OW_WIN32)
	typedef int socklen_t;
#else
	#ifndef OW_HAVE_SOCKLEN_T
		typedef unsigned socklen_t;
	#endif
#endif

#endif
