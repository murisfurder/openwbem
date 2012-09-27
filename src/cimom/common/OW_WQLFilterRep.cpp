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
#include "OW_WQLFilterRep.hpp"
#include "OW_CIMException.hpp"
#include "OW_CIMQualifierType.hpp"
#include "OW_Array.hpp"
#include "OW_CIMClass.hpp"
#include "OW_CIMServer.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMObjectPath.hpp"
#include "OW_ServiceIFCNames.hpp"

namespace OW_NAMESPACE
{

using namespace WBEMFlags;
///////////////////////////////////////////////////////////////////////////////
WQLFilterRep::WQLFilterRep(const CIMInstance& inst,
	const RepositoryIFCRef& cimServer)
	: RepositoryIFC()
	, m_inst(inst)
	, m_pCIMServer(cimServer)
{
}
///////////////////////////////////////////////////////////////////////////////
String
WQLFilterRep::getName() const
{
	return ServiceIFCNames::WQLFilterRep;
}
///////////////////////////////////////////////////////////////////////////////
ServiceEnvironmentIFCRef
WQLFilterRep::getEnvironment() const
{
	return m_pCIMServer->getEnvironment();
}
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::enumNameSpace(
	StringResultHandlerIFC&,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#if !defined(OW_DISABLE_INSTANCE_MANIPULATION) && !defined(OW_DISABLE_NAMESPACE_MANIPULATION)
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::createNameSpace(const String& /*ns*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::deleteNameSpace(const String& /*ns*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION
///////////////////////////////////////////////////////////////////////////////
CIMQualifierType
WQLFilterRep::getQualifierType(const String&,
	const String&,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#ifndef OW_DISABLE_QUALIFIER_DECLARATION
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::setQualifierType(const String &/*ns*/,
	const CIMQualifierType &/*qt*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::enumQualifierTypes(
	const String&,
	CIMQualifierTypeResultHandlerIFC&, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::deleteQualifierType(const String& /*ns*/, const String& /*qualName*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#endif // #ifndef OW_DISABLE_QUALIFIER_DECLARATION
#ifndef OW_DISABLE_SCHEMA_MANIPULATION
///////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::createClass(const String &/*path*/,
	const CIMClass &/*cimClass*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
CIMClass
WQLFilterRep::modifyClass(const String &/*name*/,
	const CIMClass &/*cc*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
CIMClass
WQLFilterRep::deleteClass(const String& /*ns*/, const String& /*className*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#endif // #ifndef OW_DISABLE_SCHEMA_MANIPULATION
//////////////////////////////////////////////////////////////////////////////
CIMClass
WQLFilterRep::getClass(
	const String& ns,
	const String& className,
	ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers,
	EIncludeClassOriginFlag includeClassOrigin, const StringArray* propertyList,
	OperationContext& context)
{
	return m_pCIMServer->getClass(ns, className, localOnly, includeQualifiers, includeClassOrigin, propertyList,
		context);
}
//////////////////////////////////////////////////////////////////////////////
CIMInstance
WQLFilterRep::getInstance(const String&, const CIMObjectPath&,
	ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers,
	EIncludeClassOriginFlag includeClassOrigin, const StringArray* propertyList,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::enumClasses(const String& ns,
	const String& className,
	CIMClassResultHandlerIFC& result,
	EDeepFlag deep,
	ELocalOnlyFlag localOnly,
	EIncludeQualifiersFlag includeQualifiers,
	EIncludeClassOriginFlag includeClassOrigin, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::enumClassNames(
	const String&,
	const String&,
	StringResultHandlerIFC&,
	EDeepFlag /*deep*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::enumInstances(
	const String& ns,
	const String& className,
	CIMInstanceResultHandlerIFC& result,
	EDeepFlag deep,
	ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList, EEnumSubclassesFlag enumSubclasses, OperationContext& context)
{
	CIMName superClassName = m_inst.getClassName();
	while (superClassName != CIMName())
	{
		if (superClassName == className)
		{
			// Don't need to do correct localOnly & deep processing.
			//result.handleInstance(m_inst.clone(localOnly, includeQualifiers,
			//	includeClassOrigin, propertyList));
			// This is more efficient
			result.handle(m_inst);
			break;
		}
		
		superClassName = m_pCIMServer->getClass(ns, superClassName.toString(),
			E_NOT_LOCAL_ONLY, E_INCLUDE_QUALIFIERS, E_INCLUDE_CLASS_ORIGIN,
			NULL, context).getSuperClass();
	}
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::enumInstanceNames(
	const String&,
	const String&,
	CIMObjectPathResultHandlerIFC&,
	EDeepFlag,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#ifndef OW_DISABLE_INSTANCE_MANIPULATION
//////////////////////////////////////////////////////////////////////////////
CIMObjectPath
WQLFilterRep::createInstance(const String&,
	const CIMInstance &/*ci*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
CIMInstance
WQLFilterRep::modifyInstance(
	const String& ns,
	const CIMInstance& modifiedInstance,
	EIncludeQualifiersFlag includeQualifiers,
	const StringArray* propertyList,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
CIMInstance
WQLFilterRep::deleteInstance(const String& /*ns*/, const CIMObjectPath &/*cop*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::setProperty(
	const String&,
	const CIMObjectPath &/*name*/,
	const String& /*propertyName*/, const CIMValue &/*cv*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#endif // #if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION
#if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
//////////////////////////////////////////////////////////////////////////////
CIMValue
WQLFilterRep::getProperty(
	const String&,
	const CIMObjectPath &/*name*/,
	const String &/*propertyName*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#endif // #if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
//////////////////////////////////////////////////////////////////////////////
CIMValue
WQLFilterRep::invokeMethod(const String&, const CIMObjectPath &/*name*/,
	const String &/*methodName*/, const CIMParamValueArray &/*inParams*/,
	CIMParamValueArray &/*outParams*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::associators(
	const String& ns,
	const CIMObjectPath &path,
	CIMInstanceResultHandlerIFC& result,
	const String &assocClass, const String &resultClass,
	const String &role, const String &resultRole,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray *propertyList, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::associatorsClasses(
	const String& ns,
	const CIMObjectPath &path,
	CIMClassResultHandlerIFC& result,
	const String &assocClass, const String &resultClass,
	const String &role, const String &resultRole,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray *propertyList, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::referenceNames(
	const String&,
	const CIMObjectPath &/*path*/,
	CIMObjectPathResultHandlerIFC&,
	const String &/*resultClass*/,
	const String &/*role*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::associatorNames(
	const String&,
	const CIMObjectPath &/*path*/,
	CIMObjectPathResultHandlerIFC&,
	const String &/*assocClass*/,
	const String &/*resultClass*/, const String &/*role*/,
	const String &/*resultRole*/, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::references(
	const String& ns,
	const CIMObjectPath &path,
	CIMInstanceResultHandlerIFC& result,
	const String &resultClass, const String &role,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray *propertyList, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::referencesClasses(
	const String& ns,
	const CIMObjectPath &path,
	CIMClassResultHandlerIFC& result,
	const String &resultClass, const String &role,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray *propertyList, OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
#endif // #ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::execQuery(const String& /*ns*/,
	CIMInstanceResultHandlerIFC&,
	const String &/*query*/, const String &/*queryLanguage*/,
	OperationContext&)
{
	OW_THROWCIMMSG(CIMException::INVALID_QUERY, "Only EnumInstances() "
		"is supported in the WQLCIMOMHandle.");
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::beginOperation(WBEMFlags::EOperationFlag, OperationContext&)
{
}
//////////////////////////////////////////////////////////////////////////////
void
WQLFilterRep::endOperation(WBEMFlags::EOperationFlag, OperationContext&, WBEMFlags::EOperationResultFlag result)
{
}

} // end namespace OW_NAMESPACE

