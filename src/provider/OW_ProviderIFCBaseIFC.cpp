/*******************************************************************************
* Copyright (C) 2003-2004 Vintela, Inc. All rights reserved.
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
#include "OW_ProviderIFCBaseIFC.hpp"
#include "OW_NoSuchProviderException.hpp"

namespace OW_NAMESPACE
{

///////////////////////////////////////////////////////////////////////////////
ProviderIFCBaseIFC::ProviderIFCBaseIFC()
: signature(0xABCDEFA0)
{
}
///////////////////////////////////////////////////////////////////////////////
ProviderIFCBaseIFC::~ProviderIFCBaseIFC()
{
}
///////////////////////////////////////////////////////////////////////////////
void
ProviderIFCBaseIFC::init(const ProviderEnvironmentIFCRef& env,
	InstanceProviderInfoArray& i,
	SecondaryInstanceProviderInfoArray& si,
#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
	AssociatorProviderInfoArray& a,
#endif
	MethodProviderInfoArray& m,
	IndicationProviderInfoArray& ind)
{
	doInit(env, i,
		si,
#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
		a,
#endif
		m,
		ind);
}
///////////////////////////////////////////////////////////////////////////////
InstanceProviderIFCRef
ProviderIFCBaseIFC::getInstanceProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	return doGetInstanceProvider(env, provIdString);
}
///////////////////////////////////////////////////////////////////////////////
SecondaryInstanceProviderIFCRef
ProviderIFCBaseIFC::getSecondaryInstanceProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	return doGetSecondaryInstanceProvider(env, provIdString);
}
///////////////////////////////////////////////////////////////////////////////
MethodProviderIFCRef
ProviderIFCBaseIFC::getMethodProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	return doGetMethodProvider(env, provIdString);
}
#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
///////////////////////////////////////////////////////////////////////////////
AssociatorProviderIFCRef
ProviderIFCBaseIFC::getAssociatorProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	return  doGetAssociatorProvider(env, provIdString);
}
#endif
///////////////////////////////////////////////////////////////////////////////
IndicationExportProviderIFCRefArray
ProviderIFCBaseIFC::getIndicationExportProviders(
	const ProviderEnvironmentIFCRef& env
	)
{
	return doGetIndicationExportProviders(env);
}
///////////////////////////////////////////////////////////////////////////////
PolledProviderIFCRefArray
ProviderIFCBaseIFC::getPolledProviders(const ProviderEnvironmentIFCRef& env
	)
{
	return doGetPolledProviders(env);
}
///////////////////////////////////////////////////////////////////////////////
void
ProviderIFCBaseIFC::unloadProviders(const ProviderEnvironmentIFCRef& env)
{
	doUnloadProviders(env);
}
///////////////////////////////////////////////////////////////////////////////
IndicationProviderIFCRef
ProviderIFCBaseIFC::getIndicationProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	return  doGetIndicationProvider(env, provIdString);
}
///////////////////////////////////////////////////////////////////////////////
void ProviderIFCBaseIFC::shuttingDown(const ProviderEnvironmentIFCRef& env)
{
	doShuttingDown(env);
}

///////////////////////////////////////////////////////////////////////////////
InstanceProviderIFCRef
ProviderIFCBaseIFC::doGetInstanceProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	OW_THROW(NoSuchProviderException, "INTERNAL ERROR! Provider IFC didn't override ProviderIFCBaseIFC::doGetInstanceProvider()");
}
///////////////////////////////////////////////////////////////////////////////
SecondaryInstanceProviderIFCRef
ProviderIFCBaseIFC::doGetSecondaryInstanceProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	OW_THROW(NoSuchProviderException, "INTERNAL ERROR! Provider IFC didn't override ProviderIFCBaseIFC::doGetSecondaryInstanceProvider()");
}
///////////////////////////////////////////////////////////////////////////////
MethodProviderIFCRef
ProviderIFCBaseIFC::doGetMethodProvider(const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	OW_THROW(NoSuchProviderException, "INTERNAL ERROR! Provider IFC didn't override ProviderIFCBaseIFC::doGetMethodProvider()");
}
#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
///////////////////////////////////////////////////////////////////////////////
AssociatorProviderIFCRef
ProviderIFCBaseIFC::doGetAssociatorProvider(
	const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	OW_THROW(NoSuchProviderException, "INTERNAL ERROR! Provider IFC didn't override ProviderIFCBaseIFC::doGetAssociatorProvider()");
}
#endif
///////////////////////////////////////////////////////////////////////////////
IndicationExportProviderIFCRefArray
ProviderIFCBaseIFC::doGetIndicationExportProviders(
	const ProviderEnvironmentIFCRef& env
	)
{
	return IndicationExportProviderIFCRefArray();
}
///////////////////////////////////////////////////////////////////////////////
PolledProviderIFCRefArray
ProviderIFCBaseIFC::doGetPolledProviders(
	const ProviderEnvironmentIFCRef& env
	)
{
	return PolledProviderIFCRefArray();
}
///////////////////////////////////////////////////////////////////////////////
IndicationProviderIFCRef
ProviderIFCBaseIFC::doGetIndicationProvider(
	const ProviderEnvironmentIFCRef& env,
	const char* provIdString)
{
	OW_THROW(NoSuchProviderException, "INTERNAL ERROR! Provider IFC didn't override ProviderIFCBaseIFC::doGetIndicationProvider()");
}
///////////////////////////////////////////////////////////////////////////////
void
ProviderIFCBaseIFC::doUnloadProviders(const ProviderEnvironmentIFCRef& env)
{
}

///////////////////////////////////////////////////////////////////////////////
void ProviderIFCBaseIFC::doShuttingDown(const ProviderEnvironmentIFCRef& env)
{
}

} // end namespace OW_NAMESPACE

