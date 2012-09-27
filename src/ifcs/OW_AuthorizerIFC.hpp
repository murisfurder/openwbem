/*******************************************************************************
* Copyright (C) 2004 Vintela, Inc. All rights reserved.
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

#ifndef OW_AUTHORIZER_IFC_HPP_INCLUDE_GUARD_
#define OW_AUTHORIZER_IFC_HPP_INCLUDE_GUARD_

#include "OW_config.h"
#include "OW_RepositoryIFC.hpp"

namespace OW_NAMESPACE
{

class OW_COMMON_API AuthorizerIFC : public RepositoryIFC
{
public:
	virtual ~AuthorizerIFC();

	virtual AuthorizerIFC* clone() const = 0;
	virtual void setSubRepositoryIFC(const RepositoryIFCRef& rep) = 0;
	virtual void init(const ServiceEnvironmentIFCRef& env);
	virtual void shutdown();

};

}

#if !defined(OW_STATIC_SERVICES)
#define OW_AUTHORIZER_FACTORY(derived, authorizerName) \
extern "C" OW_EXPORT OW_NAMESPACE::AuthorizerIFC* \
createAuthorizer() \
{ \
	return new derived; \
} \
extern "C" OW_EXPORT const char* \
getOWVersion() \
{ \
	return OW_VERSION; \
}
#else
#define OW_AUTHORIZER_FACTORY(derived, authorizerName) \
extern "C" OW_NAMESPACE::AuthorizerIFC* \
createAuthorizer_##authorizerName() \
{ \
	return new derived; \
}
#endif /* !defined(OW_STATIC_SERVICES) */

#endif
