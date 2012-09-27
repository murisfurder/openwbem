/*******************************************************************************
* Copyright (C) 2003-2004 Vintela, Inc., IBM Corp. All rights reserved.
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
*
* Author:        Markus Mueller <sedgewick_de@yahoo.de>
*
*******************************************************************************/
#include "OW_config.h"
#include "OW_CMPIIndicationProviderProxy.hpp"
#include "OW_CIMException.hpp"
#include "OW_Format.hpp"
#include "OW_CMPIProviderIFCUtils.hpp"
#include "OW_WQLSelectStatement.hpp"
#include "OW_Logger.hpp"
#include "cmpisrv.h"

#define CMPI_POLLING_INTERVAL (5*60)

namespace OW_NAMESPACE
{

namespace
{
	const String COMPONENT_NAME("ow.provider.cmpi.ifc");
}

/////////////////////////////////////////////////////////////////////////////
void
CMPIIndicationProviderProxy::deActivateFilter(
	const ProviderEnvironmentIFCRef &env,
	const WQLSelectStatement &filter,
	const String &eventType,
	const String& nameSpace,
	const StringArray& classes)
{
	bool lastActivation = (--m_activationCount == 0);
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "deactivateFilter");
	m_ftable->lastAccessTime.setToCurrent();
	if (m_ftable->miVector.indMI->ft->deActivateFilter != NULL)
	{
		CMPIStatus rc = {CMPI_RC_OK, NULL};
		::CMPIOperationContext context;
		ProviderEnvironmentIFCRef env2(env);
		::CMPI_Broker localBroker(m_ftable->broker);
		localBroker.hdl = static_cast<void *>(&env2);
		CMPI_ContextOnStack eCtx(context);
		CMPI_ThreadContext thr(&localBroker, &eCtx);
		WQLSelectStatement mutableFilter(filter);
		CIMObjectPath mutablePath;
		mutablePath.setNameSpace(nameSpace);

		if (!classes.empty())
			mutablePath.setClassName(classes[0]);

		CMPI_ObjectPathOnStack eRef(mutablePath);
		CMPISelectExp exp; // = {&mutableFilter};
		//CMPIFlags flgs = 0;
		CMPIPrepareContext(env, eCtx);
		::CMPIIndicationMI *mi = m_ftable->miVector.indMI;
		char* _eventType = const_cast<char*>(eventType.c_str());
		rc = m_ftable->miVector.indMI->ft->deActivateFilter(mi, &eCtx,
			&exp, _eventType, &eRef, lastActivation);

		if (rc.rc != CMPI_RC_OK)
		{
			OW_THROWCIMMSG(CIMException::ErrNoType(rc.rc), rc.msg ? CMGetCharPtr(rc.msg) : "");
		}
	}
	else
	{
		OW_THROWCIMMSG(CIMException::FAILED,
			"Provider does not support deactivateFilter");
	}
}
/////////////////////////////////////////////////////////////////////////////
void
CMPIIndicationProviderProxy::activateFilter(
	const ProviderEnvironmentIFCRef &env,
	const WQLSelectStatement &filter,
	const String &eventType,
	const String& nameSpace,
	const StringArray& classes)
{
	bool firstActivation = (m_activationCount++ == 0);
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "activateFilter");
	m_ftable->lastAccessTime.setToCurrent();
	if (m_ftable->miVector.indMI->ft->activateFilter != NULL)
	{
		CMPIStatus rc = {CMPI_RC_OK, NULL};
		::CMPIOperationContext context;
		ProviderEnvironmentIFCRef env2(env);
		::CMPI_Broker localBroker(m_ftable->broker);
		localBroker.hdl = static_cast<void *>(&env2);
		CMPI_ContextOnStack eCtx(context);
		CMPI_ThreadContext thr(&localBroker, &eCtx);
		WQLSelectStatement mutableFilter(filter);
		CIMObjectPath mutablePath;
		mutablePath.setNameSpace(nameSpace);

		if (!classes.empty())
			mutablePath.setClassName(classes[0]);

		CMPI_ObjectPathOnStack eRef(mutablePath);
		CMPISelectExp exp; // = {&mutableFilter};
		//CMPIFlags flgs = 0;
		::CMPIIndicationMI * mi = m_ftable->miVector.indMI;
		char* _eventType = const_cast<char*>(eventType.c_str());
		CMPIPrepareContext(env, eCtx);

		rc = m_ftable->miVector.indMI->ft->activateFilter(mi, &eCtx, 
			&exp, _eventType, &eRef, firstActivation);

		if (rc.rc != CMPI_RC_OK)
		{
			OW_THROWCIMMSG(CIMException::ErrNoType(rc.rc), rc.msg ? CMGetCharPtr(rc.msg) : "");
		}
	}
	else
	{
		OW_THROWCIMMSG(CIMException::FAILED,
			"Provider does not support activateFilter");
	}
}
/////////////////////////////////////////////////////////////////////////////
void
CMPIIndicationProviderProxy::authorizeFilter(
	const ProviderEnvironmentIFCRef &env,
	const WQLSelectStatement &filter,
	const String &eventType,
	const String &nameSpace,
	const StringArray &classes,
	const String &owner)
{
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "authorizeFilter");
	m_ftable->lastAccessTime.setToCurrent();
	if (m_ftable->miVector.indMI->ft->authorizeFilter != NULL)
	{
		CMPIStatus rc = {CMPI_RC_OK, NULL};
		::CMPIOperationContext context;
		ProviderEnvironmentIFCRef env2(env);
		::CMPI_Broker localBroker(m_ftable->broker);
		localBroker.hdl = static_cast<void *>(&env2);
		CMPI_ContextOnStack eCtx(context);
		CMPI_ThreadContext thr(&localBroker, &eCtx);
		WQLSelectStatement mutableFilter(filter);
		CIMObjectPath mutablePath;
		mutablePath.setNameSpace(nameSpace);

		if (!classes.empty())
			mutablePath.setClassName(classes[0]);

		CMPI_ObjectPathOnStack eRef(mutablePath);
		CMPISelectExp exp; // = {&mutableFilter};
		//CMPIFlags flgs = 0;
		::CMPIIndicationMI * mi = m_ftable->miVector.indMI;
		char* _eventType = const_cast<char*>(eventType.c_str());
		char* _owner = const_cast<char*>(owner.c_str());
		CMPIPrepareContext(env, eCtx);
		rc = m_ftable->miVector.indMI->ft->authorizeFilter(mi, &eCtx, 
			&exp, _eventType, &eRef, _owner);
		if (rc.rc != CMPI_RC_OK)
		{
			OW_THROWCIMMSG(CIMException::ErrNoType(rc.rc), rc.msg ? CMGetCharPtr(rc.msg) : "");
		}
	}
	else
	{
		OW_THROWCIMMSG(CIMException::FAILED,
			"Provider does not support authorizeFilter");
	}
}
/////////////////////////////////////////////////////////////////////////////
int
CMPIIndicationProviderProxy::mustPoll(
	const ProviderEnvironmentIFCRef &env,
	const WQLSelectStatement &filter,
	const String &eventType,
	const String &nameSpace,
	const StringArray &classes)
{
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "mustPoll");
	m_ftable->lastAccessTime.setToCurrent();
	if (m_ftable->miVector.indMI->ft->mustPoll != NULL)
	{
		CMPIStatus rc = {CMPI_RC_OK, NULL};
		::CMPIOperationContext context;
		ProviderEnvironmentIFCRef env2(env);
		::CMPI_Broker localBroker(m_ftable->broker);
		localBroker.hdl = static_cast<void *>(&env2);
		CMPI_ContextOnStack eCtx(context);
		CMPI_ThreadContext thr(&localBroker, &eCtx);
		WQLSelectStatement mutableFilter(filter);
		CIMObjectPath mutablePath;
		mutablePath.setNameSpace(nameSpace);
		if (!classes.empty())
			mutablePath.setClassName(classes[0]);
		CMPI_ObjectPathOnStack eRef(mutablePath);
		CMPISelectExp exp; // = {&mutableFilter};
		//CMPIFlags flgs = 0;
		::CMPIIndicationMI * mi = m_ftable->miVector.indMI;
		char* _eventType = const_cast<char*>(eventType.c_str());
		CMPIPrepareContext(env, eCtx);
		rc = m_ftable->miVector.indMI->ft->mustPoll(mi, &eCtx, 
			&exp, _eventType, &eRef);

		if (rc.rc != CMPI_RC_OK)
		{
			OW_THROWCIMMSG(CIMException::ErrNoType(rc.rc), rc.msg ? CMGetCharPtr(rc.msg) : "");
		}
	}
	else
	{
		OW_THROWCIMMSG(CIMException::FAILED,
			"Provider does not support mustPoll");
	}

	return CMPI_POLLING_INTERVAL;
}

} // end namespace OW_NAMESPACE

