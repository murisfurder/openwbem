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
 * @author Dan Nuffer
 */

#include "OW_config.h"										
#include "OW_ClientCIMOMHandle.hpp"
#include "OW_CIMNameSpaceUtils.hpp"
#include "OW_URL.hpp"
#include "OW_CIMProtocolIFC.hpp"
#include "OW_HTTPClient.hpp"
#include "OW_BinaryCIMOMHandle.hpp"
#include "OW_CIMXMLCIMOMHandle.hpp"
#include "OW_HTTPChunkedIStream.hpp"
#include "OW_Enumeration.hpp"
#include "OW_HTTPDeflateIStream.hpp"

namespace OW_NAMESPACE
{

using namespace WBEMFlags;
#if !defined(OW_DISABLE_INSTANCE_MANIPULATION) && !defined(OW_DISABLE_NAMESPACE_MANIPULATION)
//////////////////////////////////////////////////////////////////////////////
void
ClientCIMOMHandle::createNameSpace(const String& ns)
{
	CIMNameSpaceUtils::create__Namespace(*this, ns);
}
//////////////////////////////////////////////////////////////////////////////
void
ClientCIMOMHandle::deleteNameSpace(const String& ns_)
{
	CIMNameSpaceUtils::delete__Namespace(*this, ns_);
}
#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION
//////////////////////////////////////////////////////////////////////////////
void
ClientCIMOMHandle::enumNameSpace(const String& ns_,
	StringResultHandlerIFC &result, EDeepFlag deep)
{
	CIMNameSpaceUtils::enum__Namespace(*this, ns_, result, deep);
}

//////////////////////////////////////////////////////////////////////////////
// static
ClientCIMOMHandleRef
ClientCIMOMHandle::createFromURL(const String& url, 
								 const ClientAuthCBIFCRef& authCb,
								 const SSLClientCtxRef& sslCtx)
{
	URL owurl(url);
	CIMProtocolIFCRef client(new HTTPClient(url, sslCtx));
	client->setLoginCallBack(authCb);

	if (owurl.scheme.startsWith(URL::OWBINARY)
		|| owurl.namespaceName.equals(URL::OWBINARY)) // the /owbinary is deprecated in 3.0.0 and may be removed!
	{
		return ClientCIMOMHandleRef(new BinaryCIMOMHandle(client));
	}
	else
	{
		return ClientCIMOMHandleRef(new CIMXMLCIMOMHandle(client));
	}
}

//////////////////////////////////////////////////////////////////////////////
void
ClientCIMOMHandle::getHTTPTrailers(const CIMProtocolIStreamIFCRef& istr_)
{
	m_trailers.clear();
	CIMProtocolIStreamIFCRef istr(istr_);
#ifdef OW_HAVE_ZLIB_H
	IntrusiveReference<HTTPDeflateIStream> defistr = istr_.cast_to<HTTPDeflateIStream>();
	if (defistr)
	{
		istr = defistr->getInputStreamOrig();
	}
#endif
	IntrusiveReference<HTTPChunkedIStream> chunkistr = istr.cast_to<HTTPChunkedIStream>();
	if (chunkistr)
	{
		m_trailers = chunkistr->getTrailers();
	}
}


} // end namespace OW_NAMESPACE

