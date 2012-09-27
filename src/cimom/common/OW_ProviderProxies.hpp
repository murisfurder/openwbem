/*******************************************************************************
* Copyright (C) 2004 Novell, Inc., Vintela, Inc. All rights reserved.
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
*  - Neither the name of Novell nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL Novell, Inc OR THE CONTRIBUTORS
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
 */

#ifndef OW_PROVIDERPROXIES_HPP_INCLUDE_GUARD_
#define OW_PROVIDERPROXIES_HPP_INCLUDE_GUARD_

#ifdef OW_THREADS_RUN_AS_USER

#include "OW_config.h"
#include "OW_InstanceProviderIFC.hpp"
#include "OW_AssociatorProviderIFC.hpp"
#include "OW_MethodProviderIFC.hpp"
#include "OW_SecondaryInstanceProviderIFC.hpp"
#ifdef OW_NETWARE
#include "OW_NetwareIdentity.hpp"
#endif
#include <sys/types.h>
#include <unistd.h>

namespace OW_NAMESPACE
{

class OW_CIMOMCOMMON_API InstanceProviderProxy : public InstanceProviderIFC
{
public:
	InstanceProviderProxy(InstanceProviderIFCRef pProv,
		const ProviderEnvironmentIFCRef& env);

	virtual void enumInstanceNames(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const String& className,
			CIMObjectPathResultHandlerIFC& result,
			const CIMClass& cimClass );

	virtual void enumInstances(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const String& className,
			CIMInstanceResultHandlerIFC& result,
			WBEMFlags::ELocalOnlyFlag localOnly, 
			WBEMFlags::EDeepFlag deep, 
			WBEMFlags::EIncludeQualifiersFlag includeQualifiers, 
			WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
			const StringArray* propertyList,
			const CIMClass& requestedClass,
			const CIMClass& cimClass );

	virtual CIMInstance getInstance(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const CIMObjectPath& instanceName,
			WBEMFlags::ELocalOnlyFlag localOnly,
			WBEMFlags::EIncludeQualifiersFlag includeQualifiers, 
			WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
			const StringArray* propertyList, 
			const CIMClass& cimClass );

#ifndef OW_DISABLE_INSTANCE_MANIPULATION

	virtual CIMObjectPath createInstance(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const CIMInstance& cimInstance );

	virtual void modifyInstance(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const CIMInstance& modifiedInstance,
			const CIMInstance& previousInstance,
			WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
			const StringArray* propertyList,
			const CIMClass& theClass);

	virtual void deleteInstance(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const CIMObjectPath& cop);

#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION
	
private:
	InstanceProviderIFCRef m_pProv;
#if defined(OW_GNU_LINUX)
	uid_t m_cimomuid;
	uid_t m_useruid;
#elif defined(OW_NETWARE)
	NetwareIdentityRef m_nwi; 
#endif
};

class OW_CIMOMCOMMON_API SecondaryInstanceProviderProxy : public SecondaryInstanceProviderIFC
{
public:
	SecondaryInstanceProviderProxy(SecondaryInstanceProviderIFCRef pProv,
		const ProviderEnvironmentIFCRef& env);
	virtual void filterInstances(const ProviderEnvironmentIFCRef &env, const String &ns, const String &className, CIMInstanceArray &instances, WBEMFlags:: ELocalOnlyFlag localOnly, WBEMFlags:: EDeepFlag deep, WBEMFlags:: EIncludeQualifiersFlag includeQualifiers, WBEMFlags:: EIncludeClassOriginFlag includeClassOrigin, const StringArray *propertyList, const CIMClass &requestedClass, const CIMClass &cimClass);
#ifndef OW_DISABLE_INSTANCE_MANIPULATION
	virtual void createInstance(const ProviderEnvironmentIFCRef &env, const String &ns, const CIMInstance &cimInstance);
	virtual void modifyInstance(const ProviderEnvironmentIFCRef &env, const String &ns, const CIMInstance &modifiedInstance, const CIMInstance &previousInstance, WBEMFlags:: EIncludeQualifiersFlag includeQualifiers, const StringArray *propertyList, const CIMClass &theClass);
	virtual void deleteInstance(const ProviderEnvironmentIFCRef &env, const String &ns, const CIMObjectPath &cop);
#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION

private:
	SecondaryInstanceProviderIFCRef m_pProv;
#if defined(OW_GNU_LINUX)
	uid_t m_cimomuid;
	uid_t m_useruid;
#elif defined(OW_NETWARE)
	NetwareIdentityRef m_nwi; 
#endif
};

class OW_CIMOMCOMMON_API MethodProviderProxy : public MethodProviderIFC
{
public:
	MethodProviderProxy(MethodProviderIFCRef pProv,
		const ProviderEnvironmentIFCRef& env);

	virtual CIMValue invokeMethod(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const CIMObjectPath& path,
			const String& methodName,
			const CIMParamValueArray& in,
			CIMParamValueArray& out );

private:
	MethodProviderIFCRef m_pProv;
#if defined(OW_GNU_LINUX)
	uid_t m_cimomuid;
	uid_t m_useruid;
#elif defined(OW_NETWARE)
	NetwareIdentityRef m_nwi; 
#endif
};

#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
class OW_CIMOMCOMMON_API AssociatorProviderProxy : public AssociatorProviderIFC
{
public:
	AssociatorProviderProxy(AssociatorProviderIFCRef pProv,
		const ProviderEnvironmentIFCRef& env);

		virtual void associators(
				const ProviderEnvironmentIFCRef& env,
				CIMInstanceResultHandlerIFC& result,
				const String& ns,
				const CIMObjectPath& objectName,
				const String& assocClass,
				const String& resultClass,
				const String& role,
				const String& resultRole,
				WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
				WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
				const StringArray* propertyList);

		virtual void associatorNames(
				const ProviderEnvironmentIFCRef& env,
				CIMObjectPathResultHandlerIFC& result,
				const String& ns,
				const CIMObjectPath& objectName,
				const String& assocClass,
				const String& resultClass,
				const String& role,
				const String& resultRole );

		virtual void references(
				const ProviderEnvironmentIFCRef& env,
				CIMInstanceResultHandlerIFC& result,
				const String& ns,
				const CIMObjectPath& objectName,
				const String& resultClass,
				const String& role,
				WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
				WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
				const StringArray* propertyList);

		virtual void referenceNames(
				const ProviderEnvironmentIFCRef& env,
				CIMObjectPathResultHandlerIFC& result,
				const String& ns,
				const CIMObjectPath& objectName,
				const String& resultClass,
				const String& role );
private:

	AssociatorProviderIFCRef m_pProv;
#if defined(OW_GNU_LINUX)
	uid_t m_cimomuid;
	uid_t m_useruid;
#elif defined(OW_NETWARE)
	NetwareIdentityRef m_nwi; 
#endif
};
#endif	// OW_DISABLE_ASSOCIATION_TRAVERSAL

}	// end namespace OW_NAMESPACE

#endif // OW_THREADS_RUN_AS_USER

#endif
