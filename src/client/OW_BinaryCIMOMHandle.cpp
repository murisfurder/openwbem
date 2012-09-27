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

#include "OW_config.h"										
#include "OW_BinaryCIMOMHandle.hpp"
#include "OW_Format.hpp"
#include "OW_CIMNameSpace.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMProperty.hpp"
#include "OW_CIMParameter.hpp"
#include "OW_CIMMethod.hpp"
#include "OW_CIMUrl.hpp"
#include "OW_CIMObjectPath.hpp"
#include "OW_BinarySerialization.hpp"
#include "OW_IOException.hpp"
#include "OW_CIMParamValue.hpp"
#include "OW_CIMInstanceEnumeration.hpp"
#include "OW_CIMNameSpaceUtils.hpp"
#include "OW_CIMException.hpp"
#include "OW_HTTPClient.hpp"
#include "OW_HTTPChunkedIStream.hpp"

#if defined(OW_HAVE_ISTREAM) && defined(OW_HAVE_OSTREAM)
#include <istream>
#include <ostream>
#else
#include <iostream>
#endif

namespace OW_NAMESPACE
{

using std::ostream;
using std::iostream;
using std::istream;
using namespace WBEMFlags;
namespace // anonymous
{
void
_getHTTPTrailers(const CIMProtocolIStreamIFCRef& istr_, Map<String,String>& trailers)
{
	IntrusiveReference<HTTPChunkedIStream> istr = 
		istr_.cast_to<HTTPChunkedIStream>();
	if (istr)
	{
		Map<String,String> itrailers = istr->getTrailers();
		Map<String,String>::iterator it = itrailers.begin();
		while (it != itrailers.end())
		{
			trailers[it->first] = it->second;
			it++;
		}
	}
}

inline void
checkError(std::istream& istrm)
{
	UInt8 rc;
	BinarySerialization::read(istrm, rc);
	if (rc != BIN_OK)
	{
		switch (rc)
		{
			case BIN_ERROR:
			{
				String msg;
				BinarySerialization::read(istrm, msg);
				OW_THROW(IOException, msg.c_str());
			}
			case BIN_EXCEPTION:
			{
				UInt16 cimerrno;
				String cimMsg;
				BinarySerialization::read(istrm, cimerrno);
				BinarySerialization::read(istrm, cimMsg);
				OW_THROWCIMMSG(CIMException::ErrNoType(cimerrno), cimMsg.c_str());
			}
			default:
				OW_THROW(IOException,
					"Unexpected value received from server.");
		}
	}
}
inline void
checkError(const CIMProtocolIStreamIFCRef& istr, Map<String,String>& trailers)
{
	try
	{
		checkError(*istr);
	}
	catch (IOException& e)
	{
		while (*istr) 
		{
			istr->get();
		}
		_getHTTPTrailers(istr, trailers);
		istr->checkForError();
		throw e;
	}
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMClass& cc)
{
	cc = BinarySerialization::readClass(*istr);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMClassResultHandlerIFC& result)
{
	BinarySerialization::readClassEnum(*istr, result);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMInstance& ci)
{
	ci = BinarySerialization::readInstance(*istr);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMObjectPath& cop)
{
	cop = BinarySerialization::readObjectPath(*istr);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMObjectPathResultHandlerIFC& result)
{
	BinarySerialization::readObjectPathEnum(*istr, result);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMInstanceResultHandlerIFC& result)
{
	BinarySerialization::readInstanceEnum(*istr, result);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMQualifierType& arg)
{
	arg = BinarySerialization::readQualType(*istr);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, CIMQualifierTypeResultHandlerIFC& result)
{
	BinarySerialization::readQualifierTypeEnum(*istr, result);
}
inline void
readCIMObject(CIMProtocolIStreamIFCRef& istr, StringResultHandlerIFC& result)
{
	BinarySerialization::readStringEnum(*istr, result);
}
template<class T>
inline T
readCIMObject(CIMProtocolIStreamIFCRef& istr, Map<String,String>& trailers)
{
	T rval;
	try
	{
		checkError(istr, trailers);
		readCIMObject(istr, rval);
	}
	catch (IOException& e)
	{
		while (*istr) 
		{
			istr->get();
		}
		_getHTTPTrailers(istr, trailers);
		istr->checkForError();
		throw e;
	}
	while (*istr) 
	{
		istr->get();
	}
	_getHTTPTrailers(istr, trailers);
	istr->checkForError();
	return rval;
}

template<class T>
inline void
readAndDeliver(CIMProtocolIStreamIFCRef& istr, T& result,
	Map<String,String>& trailers)
{
	try
	{
		checkError(istr, trailers);
		readCIMObject(istr,result);
	}
	catch (IOException& e)
	{
		while (*istr) 
		{
			istr->get();
		}
		_getHTTPTrailers(istr, trailers);
		istr->checkForError();
		throw e;
	}
	while (*istr) 
	{
		istr->get();
	}
	_getHTTPTrailers(istr, trailers);
	istr->checkForError();
}

// We always send the lowest possible version. If 1.0 and 1.1 are the same, we send 1.0 so that 1.0 only clients will accept the request.
// If we're using a 1.1 only feature, then we have to send 1.1.
const String PROTOCOL_VERSION_1_0("1.0");
const String PROTOCOL_VERSION_1_1("1.1");

} // end anonymous namespace
//////////////////////////////////////////////////////////////////////////////
BinaryCIMOMHandle::BinaryCIMOMHandle(const CIMProtocolIFCRef& prot)
: ClientCIMOMHandle(), m_protocol(prot)
{
	m_protocol->setContentType("application/x-owbinary");
}

//////////////////////////////////////////////////////////////////////////////
CIMProtocolIFCRef
BinaryCIMOMHandle::getWBEMProtocolHandler() const
{
	return m_protocol;
}

//////////////////////////////////////////////////////////////////////////////
void BinaryCIMOMHandle::close() 
{
	m_protocol->close();
}

//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::enumClassNames(
	const String& ns_,
	const String& className,
	StringResultHandlerIFC& result,
	EDeepFlag deep)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"EnumerateClassNames", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ENUMCLSNAMES);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, className);
	BinarySerialization::writeBool(strm, deep);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"EnumerateClassNames", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::enumClass(const String& ns_,
	const String& className,
	CIMClassResultHandlerIFC& result,
	EDeepFlag deep,
	ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"EnumerateClasses", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ENUMCLSS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, className);
	BinarySerialization::writeBool(strm, deep);
	BinarySerialization::writeBool(strm, localOnly);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"EnumerateClasses", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::enumInstanceNames(
	const String& ns_,
	const String& className,
	CIMObjectPathResultHandlerIFC& result)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"EnumerateInstanceNames", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ENUMINSTNAMES);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, className);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"EnumerateInstanceNames", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::enumInstances(
	const String& ns_,
	const String& className,
	CIMInstanceResultHandlerIFC& result, EDeepFlag deep,
	ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"EnumerateInstances", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ENUMINSTS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, className);
	BinarySerialization::writeBool(strm, deep);
	BinarySerialization::writeBool(strm, localOnly);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"EnumerateInstances", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
CIMClass
BinaryCIMOMHandle::getClass(
	const String& ns_,
	const String& className,
	ELocalOnlyFlag localOnly,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"GetClass", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_GETCLS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, className);
	BinarySerialization::writeBool(strm, localOnly);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"GetClass", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	return readCIMObject<CIMClass>(in, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
CIMInstance
BinaryCIMOMHandle::getInstance(
	const String& ns_,
	const CIMObjectPath& instanceName,
	ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"GetInstance", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_GETINST);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, instanceName);
	BinarySerialization::writeBool(strm, localOnly);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"GetInstance", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	return readCIMObject<CIMInstance>(in, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
CIMValue
BinaryCIMOMHandle::invokeMethod(
	const String& ns_,
	const CIMObjectPath& path,
	const String& methodName,
	const CIMParamValueArray& inParams,
	CIMParamValueArray& outParams)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		methodName, ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_INVMETH);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, methodName);
	BinarySerialization::write(strm, BINSIG_PARAMVALUEARRAY);
	BinarySerialization::writeArray(strm, inParams);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		methodName, ns + ":" + path.modelPath(), CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	CIMValue cv(CIMNULL);
	try
	{
		Bool isrv(BinarySerialization::readBool(*in));
		if (isrv)
		{
			cv = BinarySerialization::readValue(*in);
		}
		BinarySerialization::verifySignature(*in, BINSIG_PARAMVALUEARRAY);
		BinarySerialization::readArray(*in, outParams);
	}
	catch(IOException& e)
	{
		while (*in) 
		{
			in->get();
		}
		_getHTTPTrailers(in, m_trailers);
		in->checkForError();
		throw e;
	}
	_getHTTPTrailers(in, m_trailers);
	return cv;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifierType
BinaryCIMOMHandle::getQualifierType(const String& ns_,
		const String& qualifierName)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"GetQualifier", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_GETQUAL);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, qualifierName);
	
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"GetQualifier", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	return readCIMObject<CIMQualifierType>(in, m_trailers);
}
#ifndef OW_DISABLE_QUALIFIER_DECLARATION
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::setQualifierType(const String& ns_,
		const CIMQualifierType& qt)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"SetQualifier", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_SETQUAL);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeQualType(strm, qt);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"SetQualifier", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::enumQualifierTypes(
	const String& ns_,
	CIMQualifierTypeResultHandlerIFC& result)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"EnumerateQualifiers", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ENUMQUALS);
	BinarySerialization::writeString(strm, ns);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"EnumerateQualifiers", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::deleteQualifierType(const String& ns_, const String& qualName)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"DeleteQualifier", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_DELETEQUAL);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, qualName);
	checkError(m_protocol->endRequest(strmRef, "DeleteQualifier", ns,
		CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0), m_trailers);
}
#endif // #ifndef OW_DISABLE_QUALIFIER_DECLARATION
#ifndef OW_DISABLE_SCHEMA_MANIPULATION
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::modifyClass(const String &ns_,
		const CIMClass& cc)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"ModifyClass", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_MODIFYCLS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeClass(strm, cc);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"ModifyClass", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::createClass(const String& ns_,
		const CIMClass& cc)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"CreateClass", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_CREATECLS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeClass(strm, cc);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"CreateClass", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::deleteClass(const String& ns_, const String& className)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"DeleteClass", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_DELETECLS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, className);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"DeleteClass", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
#endif // #ifndef OW_DISABLE_SCHEMA_MANIPULATION
#ifndef OW_DISABLE_INSTANCE_MANIPULATION
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::modifyInstance(
	const String& ns_,
	const CIMInstance& modifiedInstance,
	EIncludeQualifiersFlag includeQualifiers,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"ModifyInstance", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_MODIFYINST);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeInstance(strm, modifiedInstance);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeStringArray(strm, propertyList);
	
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"ModifyInstance", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_1);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
CIMObjectPath
BinaryCIMOMHandle::createInstance(const String& ns_,
	const CIMInstance& ci)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"CreateInstance", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_CREATEINST);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeInstance(strm, ci);
	
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"CreateInstance", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	CIMObjectPath rval = readCIMObject<CIMObjectPath>(in, m_trailers);
	rval.setNameSpace(ns);
	return rval;
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::deleteInstance(const String& ns_, const CIMObjectPath& inst)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"DeleteInstance", ns);;
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_DELETEINST);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, inst);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef, "DeleteInstance", ns,
		CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
#if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::setProperty(
	const String& ns_,
	const CIMObjectPath& path,
	const String& propName,
	const CIMValue& cv)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"SetProperty", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_SETPROP);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, propName);
	Bool isValue = (cv) ? true : false;
	BinarySerialization::writeBool(strm, isValue);
	if (isValue)
	{
		BinarySerialization::writeValue(strm, cv);
	}
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"SetProperty", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	_getHTTPTrailers(in, m_trailers);
}
#endif // #if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION
#if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
//////////////////////////////////////////////////////////////////////////////
CIMValue
BinaryCIMOMHandle::getProperty(
	const String& ns_,
	const CIMObjectPath& path,
	const String& propName)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"GetProperty", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_GETPROP);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, propName);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"GetProperty", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	checkError(in, m_trailers);
	CIMValue cv(CIMNULL);
	try
	{
		Bool isValue(BinarySerialization::readBool(*in));
		if (isValue)
		{
			cv = BinarySerialization::readValue(*in);
		}
	}
	catch (IOException& e)
	{
		while (*in) 
		{
			in->get();
		}
		_getHTTPTrailers(in, m_trailers);
		in->checkForError();
		throw e;
	}
	_getHTTPTrailers(in, m_trailers);
	return cv;
}
#endif // #if !defined(OW_DISABLE_PROPERTY_OPERATIONS)
#ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::associatorNames(
	const String& ns_,
	const CIMObjectPath& path,
	CIMObjectPathResultHandlerIFC& result,
	const String& assocClass, const String& resultClass,
	const String& role, const String& resultRole)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"AssociatorNames", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ASSOCNAMES);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, assocClass);
	BinarySerialization::writeString(strm, resultClass);
	BinarySerialization::writeString(strm, role);
	BinarySerialization::writeString(strm, resultRole);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"AssociatorNames", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::associators(
	const String& ns_,
	const CIMObjectPath& path,
	CIMInstanceResultHandlerIFC& result,
	const String& assocClass, const String& resultClass,
	const String& role, const String& resultRole,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	if (!path.isInstancePath())
	{
		OW_THROWCIMMSG(CIMException::INVALID_PARAMETER,
			"associators requires an instance path not a class path");
	}
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"Associators", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ASSOCIATORS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, assocClass);
	BinarySerialization::writeString(strm, resultClass);
	BinarySerialization::writeString(strm, role);
	BinarySerialization::writeString(strm, resultRole);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"Associators", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::associatorsClasses(
	const String& ns_,
	const CIMObjectPath& path,
	CIMClassResultHandlerIFC& result,
	const String& assocClass, const String& resultClass,
	const String& role, const String& resultRole,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	if (!path.isClassPath())
	{
		OW_THROWCIMMSG(CIMException::INVALID_PARAMETER,
			"associatorsClasses requires a class path not an instance path");
	}
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"Associators", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_ASSOCIATORS);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, assocClass);
	BinarySerialization::writeString(strm, resultClass);
	BinarySerialization::writeString(strm, role);
	BinarySerialization::writeString(strm, resultRole);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"Associators", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::referenceNames(
	const String& ns_,
	const CIMObjectPath& path,
	CIMObjectPathResultHandlerIFC& result,
	const String& resultClass,
	const String& role)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"ReferenceNames", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_REFNAMES);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, resultClass);
	BinarySerialization::writeString(strm, role);
	
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"ReferenceNames", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::references(
	const String& ns_,
	const CIMObjectPath& path,
	CIMInstanceResultHandlerIFC& result,
	const String& resultClass, const String& role,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	if (!path.isInstancePath())
	{
		OW_THROWCIMMSG(CIMException::INVALID_PARAMETER,
			"references requires an instance path not a class path");
	}
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"ReferenceNames", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_REFERENCES);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, resultClass);
	BinarySerialization::writeString(strm, role);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"ReferenceNames", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::referencesClasses(
	const String& ns_,
	const CIMObjectPath& path,
	CIMClassResultHandlerIFC& result,
	const String& resultClass, const String& role,
	EIncludeQualifiersFlag includeQualifiers, EIncludeClassOriginFlag includeClassOrigin,
	const StringArray* propertyList)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	if (!path.isClassPath())
	{
		OW_THROWCIMMSG(CIMException::INVALID_PARAMETER,
			"referencesClasses requires a class path not an instance path");
	}
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"ReferenceNames", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_REFERENCES);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeObjectPath(strm, path);
	BinarySerialization::writeString(strm, resultClass);
	BinarySerialization::writeString(strm, role);
	BinarySerialization::writeBool(strm, includeQualifiers);
	BinarySerialization::writeBool(strm, includeClassOrigin);
	BinarySerialization::writeStringArray(strm, propertyList);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"ReferenceNames", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}
#endif // #ifndef OW_DISABLE_ASSOCIATION_TRAVERSAL
//////////////////////////////////////////////////////////////////////////////
CIMInstanceEnumeration
BinaryCIMOMHandle::execQuery(
	const String& ns,
	const String& query, int wqlLevel)
{
	m_trailers.clear();

	// Not sure what to do with trailers here ????

	return CIMOMHandleIFC::execQueryE(ns, query,
		String("WQL") + String(wqlLevel));
}
//////////////////////////////////////////////////////////////////////////////
void
BinaryCIMOMHandle::execQuery(
	const String& ns_,
	CIMInstanceResultHandlerIFC& result,
	const String& query, const String& queryLanguage)
{
	m_trailers.clear();
	String ns(CIMNameSpaceUtils::prepareNamespace(ns_));
	Reference<std::iostream> strmRef = m_protocol->beginRequest(
		"ExecQuery", ns);
	std::iostream& strm = *strmRef;
	BinarySerialization::write(strm, BinaryProtocolVersion);
	BinarySerialization::write(strm, BIN_EXECQUERY);
	BinarySerialization::writeString(strm, ns);
	BinarySerialization::writeString(strm, query);
	BinarySerialization::writeString(strm, queryLanguage);
	CIMProtocolIStreamIFCRef in = m_protocol->endRequest(strmRef,
		"ExecQuery", ns, CIMProtocolIFC::E_CIM_OPERATION_REQUEST, PROTOCOL_VERSION_1_0);
	readAndDeliver(in, result, m_trailers);
}

//////////////////////////////////////////////////////////////////////////////
bool 
BinaryCIMOMHandle::setHTTPRequestHeader(const String& hdrName,
	const String& hdrValue)
{
	bool cc = false;
	IntrusiveReference<HTTPClient> httpClient = 
		m_protocol.cast_to<HTTPClient>();
	if (httpClient)
	{
		httpClient->addCustomHeader(hdrName, hdrValue);
		cc = true;
	}
	return cc;
}

//////////////////////////////////////////////////////////////////////////////
bool 
BinaryCIMOMHandle::getHTTPResponseHeader(const String& hdrName,
	String& valueOut) const
{
	bool cc = false;
	IntrusiveReference<HTTPClient> httpClient = 
		m_protocol.cast_to<HTTPClient>();
	if (httpClient)
	{
		if (!(cc = httpClient->getResponseHeader(hdrName, valueOut)))
		{
			if (HTTPUtils::headerHasKey(m_trailers, hdrName))
			{
				cc = true;
				valueOut = HTTPUtils::getHeaderValue(m_trailers, hdrName);
			}
		}
	}
	return cc;
}

//////////////////////////////////////////////////////////////////////////////
CIMFeatures
BinaryCIMOMHandle::getServerFeatures()
{
	return m_protocol->getFeatures();
}
//////////////////////////////////////////////////////////////////////////////

} // end namespace OW_NAMESPACE

