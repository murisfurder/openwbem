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
#include "OW_config.h"
#include "OW_PerlIndicationProviderProxy.hpp"
#include "NPIExternal.hpp"
#include "OW_CIMException.hpp"
#include "OW_Format.hpp"
#include "OW_Logger.hpp"
#include "OW_NPIProviderIFCUtils.hpp"
#include "OW_WQLSelectStatement.hpp"

namespace OW_NAMESPACE
{

namespace
{
	const String COMPONENT_NAME("ow.provider.perlnpi.ifc");
}

/////////////////////////////////////////////////////////////////////////////
void
PerlIndicationProviderProxy::deActivateFilter(
	const ProviderEnvironmentIFCRef& env,
	const WQLSelectStatement& filter,
	const String& eventType,
	const String& nameSpace,
	const StringArray& classes)
{
	bool lastActivation = (--m_activationCount == 0);
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "deactivateFilter");
	if (m_ftable->fp_deActivateFilter != NULL)
	{
		::NPIHandle _npiHandle = { 0, 0, 0, 0, m_ftable->npicontext};

		NPIHandleFreer nhf(_npiHandle);
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "deactivateFilter");
		ProviderEnvironmentIFCRef env2(env);
		_npiHandle.thisObject = static_cast<void *>(&env2);
		//WQLSelectStatement mutableFilter(filter);
		//CIMObjectPath mutablePath(classes[0], nameSpace);
		//SelectExp exp = {&mutableFilter};
		//::CIMObjectPath cop = {&mutablePath};
		SelectExp exp;
		::CIMObjectPath cop;
		m_ftable->fp_deActivateFilter( &_npiHandle, exp, eventType.c_str(), cop, lastActivation);
		if (_npiHandle.errorOccurred)
		{
			OW_THROWCIMMSG(CIMException::FAILED,
			_npiHandle.providerError);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
void
PerlIndicationProviderProxy::activateFilter(
	const ProviderEnvironmentIFCRef& env,
	const WQLSelectStatement& filter,
	const String& eventType,
	const String& nameSpace,
	const StringArray& classes)
{
	bool firstActivation = (m_activationCount++ == 0);
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "activateFilter");
	if (m_ftable->fp_activateFilter != NULL)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "activateFilter2");
		::NPIHandle _npiHandle = { 0, 0, 0, 0, m_ftable->npicontext};
		NPIHandleFreer nhf(_npiHandle);
		ProviderEnvironmentIFCRef env2(env);
		_npiHandle.thisObject = static_cast<void *>(&env2);
		//WQLSelectStatement mutableFilter(filter);
		//CIMObjectPath mutablePath(classes[0], nameSpace);
		//SelectExp exp = {&mutableFilter};
		//::CIMObjectPath cop = {&mutablePath};
		SelectExp exp;
		::CIMObjectPath cop;
		m_ftable->fp_activateFilter( &_npiHandle, exp, eventType.c_str(), cop, firstActivation);
		if (_npiHandle.errorOccurred)
		{
			OW_THROWCIMMSG(CIMException::FAILED,
			_npiHandle.providerError);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
void
PerlIndicationProviderProxy::authorizeFilter(
	const ProviderEnvironmentIFCRef& env,
	const WQLSelectStatement& filter,
	const String& eventType,
	const String& nameSpace,
	const StringArray& classes,
	const String& owner)
{
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "authorizeFilter");
	if (m_ftable->fp_authorizeFilter != NULL)
	{
		::NPIHandle _npiHandle = { 0, 0, 0, 0, m_ftable->npicontext};

		NPIHandleFreer nhf(_npiHandle);
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "authorizeFilter2");
		ProviderEnvironmentIFCRef env2(env);
		_npiHandle.thisObject = static_cast<void *>(&env2);
		//WQLSelectStatement mutableFilter(filter);
		//CIMObjectPath mutablePath(classes[0], nameSpace);
		//SelectExp exp = {&mutableFilter};
		//::CIMObjectPath cop = {&mutablePath};
		SelectExp exp;
		::CIMObjectPath cop;
		m_ftable->fp_authorizeFilter( &_npiHandle, exp, eventType.c_str(), cop, owner.c_str());
		if (_npiHandle.errorOccurred)
		{
			OW_THROWCIMMSG(CIMException::FAILED,
			_npiHandle.providerError);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
int
PerlIndicationProviderProxy::mustPoll(
	const ProviderEnvironmentIFCRef& env,
	const WQLSelectStatement& filter,
	const String& eventType,
	const String& nameSpace,
	const StringArray& classes)
{
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "mustPoll");
	if (m_ftable->fp_mustPoll != NULL)
	{
		::NPIHandle _npiHandle = { 0, 0, 0, 0, m_ftable->npicontext};
		NPIHandleFreer nhf(_npiHandle);
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "mustPoll2");
		ProviderEnvironmentIFCRef env2(env);
		_npiHandle.thisObject = static_cast<void *>(&env2);
		//WQLSelectStatement mutableFilter(filter);
		//CIMObjectPath mutablePath(classes[0], nameSpace);
		//SelectExp exp = {&mutableFilter};
		//::CIMObjectPath cop = {&mutablePath};
		SelectExp exp;
		::CIMObjectPath cop;
		int rval = m_ftable->fp_mustPoll( &_npiHandle, exp, eventType.c_str(), cop);
		if (_npiHandle.errorOccurred)
		{
			OW_THROWCIMMSG(CIMException::FAILED,
			_npiHandle.providerError);
		}
		// Perl providers only return 0 or 1 for mustPoll.
		// OpenWBEM expects mustPoll to return the polling interval,
		// so we'll return a reasonable polling interval (5 mins.)
		if (rval > 0)
		{
			return 5 * 60;
		}
	}
	return 0;
}

} // end namespace OW_NAMESPACE

