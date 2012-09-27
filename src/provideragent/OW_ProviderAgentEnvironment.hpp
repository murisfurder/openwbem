/*******************************************************************************
* Copyright (C) 2001-2004 Vintela, Inc. All rights reserved.
* Copyright (C) 2004 Novell, Inc. All rights reserved.
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
 * @author Bart Whiteley
 * @author Dan Nuffer
 */

#ifndef OW_PROVIDERAGENTENVIRONMENT_HPP_INCLUDE_GUARD_
#define OW_PROVIDERAGENTENVIRONMENT_HPP_INCLUDE_GUARD_

#include "OW_config.h"
#include "OW_ServiceEnvironmentIFC.hpp"
#include "OW_ConfigFile.hpp"
#include "OW_AuthenticatorIFC.hpp"
#include "OW_Map.hpp"
#include "OW_ClientCIMOMHandleConnectionPool.hpp"
#include "OW_Cache.hpp"
#include "OW_CppProviderBaseIFC.hpp"
#include "OW_Reference.hpp"
#include "OW_ProviderAgentLockerIFC.hpp"
#include "OW_Array.hpp"

// The classes and functions defined in this file are not meant for general
// use, they are internal implementation details.  They may change at any time.

namespace OW_NAMESPACE
{

typedef std::pair<SelectableIFCRef, SelectableCallbackIFCRef> SelectablePair_t;

class ProviderAgentEnvironment : public ServiceEnvironmentIFC
{
public:
	enum EClassRetrievalFlag
	{
		E_DONT_RETRIEVE_CLASSES,
		E_RETRIEVE_CLASSES
	};

	enum EConnectionCredentialsUsageFlag
	{
		E_DONT_USE_CONNECTION_CREDENTIALS,
		E_USE_CONNECTION_CREDENTIALS
	};

	ProviderAgentEnvironment(const ConfigFile::ConfigMap& configMap,
		const Array<CppProviderBaseIFCRef>& providers,
		const Array<CIMClass>& cimClasses,
		const AuthenticatorIFCRef& authenticator,
		const Array<RequestHandlerIFCRef>& requestHandlers,
		const LoggerRef& logger,
        const String& callbackURL,
		const Reference<Array<SelectablePair_t> >& selectables,
		const ProviderAgentLockerIFCRef& locker);
	virtual ~ProviderAgentEnvironment();
	virtual bool authenticate(String &userName,
		const String &info, String &details, OperationContext& context) const;
	virtual void addSelectable(const SelectableIFCRef& obj,
		const SelectableCallbackIFCRef& cb);

	struct selectableFinder
	{
		selectableFinder(const SelectableIFCRef& obj) : m_obj(obj) {}
		template <typename T>
		bool operator()(const T& x)
		{
			return x.first == m_obj;
		}
		const SelectableIFCRef& m_obj;
	};

	virtual void removeSelectable(const SelectableIFCRef& obj);
	virtual String getConfigItem(const String &name, const String& defRetVal) const;
	virtual StringArray getMultiConfigItem(const String &itemName, 
		const StringArray& defRetVal, const char* tokenizeSeparator) const;
	virtual void setConfigItem(const String& item, const String& value, EOverwritePreviousFlag overwritePrevious);

	virtual RequestHandlerIFCRef getRequestHandler(const String& ct) const;
	virtual CIMOMHandleIFCRef getCIMOMHandle(OperationContext&,
		EBypassProvidersFlag bypassProviders,
		ELockingFlag locking) const;
	virtual LoggerRef getLogger() const;
	virtual LoggerRef getLogger(const String& componentName) const;

private:
	ConfigFile::ConfigMap m_configItems;
	AuthenticatorIFCRef m_authenticator;
	LoggerRef m_logger;
	String m_callbackURL;
	Array<RequestHandlerIFCRef> m_requestHandlers;
	Reference<Array<SelectablePair_t> > m_selectables;
	Map<String, CppProviderBaseIFCRef> m_assocProvs;
	Map<String, CppProviderBaseIFCRef> m_instProvs;
	Map<String, CppProviderBaseIFCRef> m_secondaryInstProvs;
	Map<String, CppProviderBaseIFCRef> m_methodProvs;
	// TODO Refactor me.  ProviderAgentCIMOMHandles get a reference
	// (&, not Reference) to m_cimClasses, and modify it.
	mutable Cache<CIMClass> m_cimClasses;
	ProviderAgentLockerIFCRef m_locker;
	EClassRetrievalFlag m_classRetrieval;
	mutable ClientCIMOMHandleConnectionPool m_connectionPool;
	ProviderAgentEnvironment::EConnectionCredentialsUsageFlag m_useConnectionCredentials;

};

} // end namespace OW_NAMESPACE

#endif // #ifndef OW_PROVIDERAGENTENVIRONMENT_HPP_INCLUDE_GUARD_
