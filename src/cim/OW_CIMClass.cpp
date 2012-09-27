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
#include "OW_CIMClass.hpp"
#include "OW_StringBuffer.hpp"
#include "OW_Assertion.hpp"
#include "OW_CIMQualifier.hpp"
#include "OW_CIMQualifierType.hpp"
#include "OW_CIMProperty.hpp"
#include "OW_CIMMethod.hpp"
#include "OW_CIMInstance.hpp"
#include "OW_CIMUrl.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMName.hpp"
#include "OW_BinarySerialization.hpp"
#include "OW_StrictWeakOrdering.hpp"
#include "OW_COWIntrusiveCountableBase.hpp"

#include <algorithm>

namespace OW_NAMESPACE
{

using std::istream;
using std::ostream;
using namespace WBEMFlags;

//////////////////////////////////////////////////////////////////////////////
struct CIMClass::CLSData : public COWIntrusiveCountableBase
{
	CLSData() :
		m_associationFlag(false), m_isKeyed(false){  }
	CIMName m_name;
	CIMName m_parentClassName;
	CIMQualifierArray m_qualifiers;
	CIMPropertyArray m_properties;
	CIMMethodArray m_methods;
	Bool m_associationFlag;
	Bool m_isKeyed;
	CLSData* clone() const { return new CLSData(*this); }
};
//////////////////////////////////////////////////////////////////////////////
bool operator<(const CIMClass::CLSData& x, const CIMClass::CLSData& y)
{
	return StrictWeakOrdering(x.m_name, y.m_name, 
		x.m_parentClassName, y.m_parentClassName,
		x.m_qualifiers, y.m_qualifiers,
		x.m_properties, y.m_properties,
		x.m_methods, y.m_methods);
}
//////////////////////////////////////////////////////////////////////////////
bool operator==(const CIMClass::CLSData& x, const CIMClass::CLSData& y)
{
	return x.m_name == y.m_name && 
		x.m_parentClassName == y.m_parentClassName &&
		x.m_qualifiers == y.m_qualifiers &&
		x.m_properties == y.m_properties &&
		x.m_methods == y.m_methods;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass::CIMClass() :
	m_pdata(new CLSData)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMClass::CIMClass(CIMNULL_t) :
	m_pdata(0)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMClass::CIMClass(const char* name) :
	m_pdata(new CLSData)
{
	m_pdata->m_name = name;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass::CIMClass(const CIMName& name) :
	m_pdata(new CLSData)
{
	m_pdata->m_name = name;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMClass::setName(const CIMName& name)
{
	m_pdata->m_name = name;
}
//////////////////////////////////////////////////////////////////////////////
String
CIMClass::getSuperClass() const
{
	return m_pdata->m_parentClassName.toString();
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setSuperClass(const CIMName& pname)
{
	m_pdata->m_parentClassName = pname;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMClass::isKeyed() const
{
	return m_pdata->m_isKeyed;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setIsKeyed(bool isKeyedParm)
{
	m_pdata->m_isKeyed = isKeyedParm;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMPropertyArray
CIMClass::getKeys() const
{
	CIMPropertyArray v;
	for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
	{
		const CIMProperty& p = m_pdata->m_properties[i];
		if (p.isKey())
		{
			v.append(p);
		}
	}
	return v;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier
CIMClass::getQualifier(const CIMName& name) const
{
	for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
	{
		CIMQualifier q = m_pdata->m_qualifiers[i];
		if (q.getName() == name)
		{
			return q;
		}
	}
	return CIMQualifier(CIMNULL);
}
//////////////////////////////////////////////////////////////////////////////
CIMProperty
CIMClass::getProperty(const CIMName& prpName) const
{
	return getProperty(prpName, "");
}
//////////////////////////////////////////////////////////////////////////////
CIMProperty
CIMClass::getProperty(const CIMName& name,
	const CIMName& originClass) const
{
	//
	// See if property name is in the form originClass.propName
	// and if it is, work to find real origin class
	//
	if (originClass != "")
	{
		for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
		{
			CIMProperty cp = m_pdata->m_properties[i];
			if (cp.getOriginClass() == originClass && cp.getName() == name)
			{
				return cp;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
		{
			CIMProperty cp = m_pdata->m_properties[i];
			if (cp.getName() == name)
			{
				return(cp);
			}
		}
	}
	return CIMProperty(CIMNULL);
}
//////////////////////////////////////////////////////////////////////////////
CIMMethod
CIMClass::getMethod(const CIMName& name) const
{
	return getMethod(name, "");
}
//////////////////////////////////////////////////////////////////////////////
CIMMethod
CIMClass::getMethod(const CIMName& name,
	const CIMName& originClass) const
{
	//
	// See if method name is in the form originClass.propName
	// and if it is, work to find real origin class
	//
	if (originClass != "")
	{
		int tsize = m_pdata->m_methods.size();
		for (int i = 0; i < tsize; i++)
		{
			CIMMethod q = m_pdata->m_methods[i];
			if (q.getOriginClass() == originClass && (q.getName() == name))
			{
				return q;
			}
		}
	}
	else
	{
		int tsize = m_pdata->m_methods.size();
		for (int i = 0; i < tsize; i++)
		{
			CIMMethod q = m_pdata->m_methods[i];
			if (q.getName() == name)
			{
				return q;
			}
		}
	}
	return CIMMethod(CIMNULL);
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMClass::isAssociation() const
{
	return m_pdata->m_associationFlag;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setIsAssociation(bool isAssocFlag)
{
	m_pdata->m_associationFlag = isAssocFlag;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifierArray
CIMClass::getQualifiers() const
{
	return m_pdata->m_qualifiers;
}
//////////////////////////////////////////////////////////////////////////////
CIMPropertyArray
CIMClass::getAllProperties() const
{
	return m_pdata->m_properties;
}
//////////////////////////////////////////////////////////////////////////////
String
CIMClass::getKeyClass() const
{
	for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
	{
		CIMProperty p = m_pdata->m_properties[i];
		if (p.isKey())
		{
			return p.getOriginClass();
		}
	}
	return String();
}
//////////////////////////////////////////////////////////////////////////////
CIMPropertyArray
CIMClass::getProperties() const
{
	CIMPropertyArray prop;
	for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
	{
		CIMProperty cp = m_pdata->m_properties[i];
		if (!cp.hasTrueQualifier(CIMQualifier::CIM_QUAL_OVERRIDE))
		{
			prop.append(cp);
		}
	}
	return(prop);
}
//////////////////////////////////////////////////////////////////////////////
CIMMethodArray
CIMClass::getAllMethods() const
{
	return m_pdata->m_methods;
}
//////////////////////////////////////////////////////////////////////////////
CIMMethodArray
CIMClass::getMethods() const
{
	CIMMethodArray meth;
	int tsize = m_pdata->m_methods.size();
	for (int i = 0; i < tsize; i++)
	{
		CIMMethod cm = m_pdata->m_methods[i];
		if (cm.getQualifier(CIMQualifier::CIM_QUAL_OVERRIDE))
		{
			meth.append(cm);
		}
	}
	return meth;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::addProperty(const CIMProperty& prop)
{
	if (prop)
	{
		m_pdata->m_properties.append(prop);
		if (prop.isKey())
		{
			m_pdata->m_isKeyed = true;
		}
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
int
CIMClass::numberOfProperties() const
{
	return m_pdata->m_properties.size();
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setProperties(const CIMPropertyArray& props)
{
	m_pdata->m_properties = props;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setProperty(const CIMProperty& prop)
{
	CIMName argName = prop.getName();
	for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
	{
		if (argName == m_pdata->m_properties[i].getName())
		{
			m_pdata->m_properties[i] = prop;
			return *this;
		}
	}
	m_pdata->m_properties.append(prop);
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setMethod(const CIMMethod& meth)
{
	CIMName argName = meth.getName();
	for (size_t i = 0; i < m_pdata->m_methods.size(); i++)
	{
		if (argName == m_pdata->m_methods[i].getName())
		{
			m_pdata->m_methods[i] = meth;
			return *this;
		}
	}
	m_pdata->m_methods.append(meth);
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::addQualifier(const CIMQualifier& qual)
{
	if (!qual)
	{
		return *this;
	}
	//
	// See if qualifier already present
	//
	for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
	{
		if (m_pdata->m_qualifiers[i].equals(qual))
		{
			m_pdata->m_qualifiers.remove(i);
			break;
		}
	}
	if (qual.getName().equalsIgnoreCase(CIMQualifier::CIM_QUAL_ASSOCIATION))
	{
		CIMValue v = qual.getValue();
		if (v && v.getType() == CIMDataType::BOOLEAN)
		{
			Bool b;
			qual.getValue().get(b);
			m_pdata->m_associationFlag = b;
		}
		else
		{
			m_pdata->m_associationFlag = false;
		}
	}
	m_pdata->m_qualifiers.append(qual);
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMClass::hasQualifier(const CIMQualifier& qual) const
{
	if (qual)
	{
		for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
		{
			if (m_pdata->m_qualifiers[i].equals(qual))
			{
				return true;
			}
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////
int
CIMClass::numberOfQualifiers() const
{
	return m_pdata->m_qualifiers.size();
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMClass::removeQualifier(const CIMQualifier& qual)
{
	bool cc = false;
	if (qual)
	{
		for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
		{
			CIMQualifier cq = m_pdata->m_qualifiers[i];
			if (cq.equals(qual))
			{
				m_pdata->m_qualifiers.remove(i);
				cc = true;
				break;
			}
		}
	}
	return cc;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMClass::removeQualifier(const CIMName& name)
{
	bool cc = false;
	for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
	{
		CIMQualifier cq = m_pdata->m_qualifiers[i];
		if (cq.getName() == name)
		{
			m_pdata->m_qualifiers.remove(i);
			cc = true;
			break;
		}
	}
	return cc;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMClass::removeProperty(const CIMName& name)
{
	bool cc = false;
	for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
	{
		CIMProperty prop = m_pdata->m_properties[i];
		if (prop.getName() == name)
		{
			m_pdata->m_properties.remove(i);
			cc = true;
			break;
		}
	}
	return cc;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setQualifiers(const CIMQualifierArray& quals)
{
	m_pdata->m_qualifiers = quals;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setQualifier(const CIMQualifier& qual)
{
	if (qual)
	{
		bool found = false;
		for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
		{
			CIMQualifier cq = m_pdata->m_qualifiers[i];
			if (cq.equals(qual))
			{
				m_pdata->m_qualifiers[i] = qual;
				found = true;
				break;
			}
		}
		if (!found)
		{
			m_pdata->m_qualifiers.append(qual);
		}
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::addMethod(const CIMMethod& meth)
{
	if (meth)
	{
		m_pdata->m_methods.append(meth);
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass&
CIMClass::setMethods(const CIMMethodArray& meths)
{
	m_pdata->m_methods = meths;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMInstance
CIMClass::newInstance() const
{
	CIMInstance cInstance;
	cInstance.syncWithClass(*this, E_INCLUDE_QUALIFIERS);
	cInstance.setClassName(m_pdata->m_name);
	return cInstance;
}
//////////////////////////////////////////////////////////////////////////////
CIMClass
CIMClass::filterProperties(const StringArray& propertyList,
	EIncludeQualifiersFlag includeQualifiers,
	EIncludeClassOriginFlag includeClassOrigin) const
{
	return clone(E_NOT_LOCAL_ONLY, includeQualifiers, includeClassOrigin,
		propertyList, false);
}
//////////////////////////////////////////////////////////////////////////////
CIMClass
CIMClass::clone(ELocalOnlyFlag localOnly, EIncludeQualifiersFlag includeQualifiers,
	EIncludeClassOriginFlag includeClassOrigin, const StringArray& propertyList,
	bool noProps) const
{
	if (!m_pdata)
	{
		return CIMClass(CIMNULL);
	}
	CIMClass theClass;
	theClass.m_pdata->m_name = m_pdata->m_name;
	theClass.m_pdata->m_parentClassName = m_pdata->m_parentClassName;
	theClass.m_pdata->m_associationFlag = m_pdata->m_associationFlag;
	theClass.m_pdata->m_isKeyed = m_pdata->m_isKeyed;
	//
	// Process qualifiers
	//
	if (includeQualifiers)
	{
		CIMQualifierArray qra;
		for (size_t i = 0; i < m_pdata->m_qualifiers.size(); i++)
		{
			CIMQualifier cq = m_pdata->m_qualifiers[i];
			if (localOnly && cq.getPropagated() == true)
			{
				continue;
			}
			qra.append(cq);
		}
		theClass.m_pdata->m_qualifiers = qra;
	}
	if (!noProps)
	{
		CIMPropertyArray pra;
		for (size_t i = 0; i < m_pdata->m_properties.size(); i++)
		{
			CIMProperty prop = m_pdata->m_properties[i];
			if (localOnly && prop.getPropagated() == true)
			{
				continue;
			}
			// If the given property list has any elements, then ensure this
			// property name is in the property list before including it
			if (propertyList.size() > 0)
			{
				CIMName pName = prop.getName();
				for (size_t j = 0; j < propertyList.size(); j++)
				{
					if (pName == propertyList[j])
					{
						pra.append(prop.clone(includeQualifiers,
							includeClassOrigin));
						break;
					}
				}
			}
			else
			{
				pra.append(prop.clone(includeQualifiers,
					includeClassOrigin));
			}
		}
		theClass.m_pdata->m_properties = pra;
	}
	// Process methods
	CIMMethodArray mra;
	for (size_t i = 0; i < m_pdata->m_methods.size(); i++)
	{
		CIMMethod meth = m_pdata->m_methods[i];
		if (localOnly && meth.getPropagated() == true)
		{
			continue;
		}
		mra.append(meth.clone(includeQualifiers, includeClassOrigin));
	}
	theClass.m_pdata->m_methods = mra;
	return theClass;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMClass::readObject(istream &istrm)
{
	CIMName name;
	CIMName pcName;
	CIMQualifierArray qra;
	CIMPropertyArray pra;
	CIMMethodArray mra;
	Bool isAssocFlag;
	Bool isK;

	UInt32 version = CIMBase::readSig(istrm, OW_CIMCLASSSIG, OW_CIMCLASSSIG_V, CIMClass::SERIALIZATION_VERSION);
	name.readObject(istrm);
	pcName.readObject(istrm);
	isAssocFlag.readObject(istrm);
	isK.readObject(istrm);
	BinarySerialization::readArray(istrm, qra);
	BinarySerialization::readArray(istrm, pra);
	BinarySerialization::readArray(istrm, mra);
	// If dealing with version 1 format, then read language (it was removed in version 2)
	// TODO: This was only present in CVS builds and never released.  Remove it right before the release.
	if (version == 1)
	{
		String language;
		language.readObject(istrm);
	}
	if (!m_pdata)
	{
		m_pdata = new CLSData;
	}
	m_pdata->m_name = name;
	m_pdata->m_parentClassName = pcName;
	m_pdata->m_associationFlag = isAssocFlag;
	m_pdata->m_isKeyed = isK;
	m_pdata->m_qualifiers = qra;
	m_pdata->m_properties = pra;
	m_pdata->m_methods = mra;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMClass::writeObject(ostream &ostrm) const
{
	// ATTENTION: There is a bad hack in MetaRepository::_getClassNameFromNode which relies on the format of a CIMClass.
	// If you update/change this function, make sure you update it too!

	// Since version 2 is the same a version 0, we're just using version 0 here, since it's more efficient.
	// When/if the version changes to 3, uncomment the next line.
	//CIMBase::writeSig(ostrm, OW_CIMCLASSSIG_V, VERSION);
	CIMBase::writeSig(ostrm, OW_CIMCLASSSIG);
	m_pdata->m_name.writeObject(ostrm);
	m_pdata->m_parentClassName.writeObject(ostrm);
	m_pdata->m_associationFlag.writeObject(ostrm);
	m_pdata->m_isKeyed.writeObject(ostrm);
	BinarySerialization::writeArray(ostrm, m_pdata->m_qualifiers);
	BinarySerialization::writeArray(ostrm, m_pdata->m_properties);
	BinarySerialization::writeArray(ostrm, m_pdata->m_methods);
}
//////////////////////////////////////////////////////////////////////////////
String
CIMClass::toMOF() const
{
	size_t i;
	StringBuffer rv;
	if (m_pdata->m_qualifiers.size() != 0)// || m_pdata->m_associationFlag)
	{
		rv += "[";
		CIMQualifierArray qra = m_pdata->m_qualifiers;
		/*
		 * The association needs to be at the beginning according to
		 * the MOF grammar.
		 */
		CIMQualifierArray::iterator iter = std::find(
			qra.begin(), qra.end(),
			CIMQualifier(CIMQualifier::CIM_QUAL_ASSOCIATION));
		if (iter != qra.end())
		{
			if (iter != qra.begin())
			{
				//std::swap(*iter, *qra.begin());
				CIMQualifier tmp = *iter;
				qra.erase(iter);
				qra.insert(qra.begin(), tmp);
			}
		}
		else
		{
//             if (m_pdata->m_associationFlag)
//             {
//                 CIMQualifierType cqt(CIMQualifier::CIM_QUAL_ASSOCIATION);
//                 cqt.setDataType(CIMDataType(CIMDataType::BOOLEAN));
//                 CIMQualifier cq(cqt);
//                 cq.setValue(CIMValue(Bool(true)));
//                 qra.insert(qra.begin(), cq);
//             }
		}
		iter = std::find( qra.begin(), qra.end(),
			CIMQualifier(CIMQualifier::CIM_QUAL_INDICATION));
		if (iter != qra.end())
		{
			std::swap(*iter, *qra.begin());
		}
		for (i = 0; i < qra.size(); i++)
		{
			if (i > 0)
			{
				rv += ",\n ";
			}
			rv += qra[i].toMOF();
		}
		rv += "]\n";
	}
	rv += "class ";
	rv += getName();
	if (m_pdata->m_parentClassName != "")
	{
		rv += ':';
		rv += m_pdata->m_parentClassName.toString();
	}
	rv += "\n{\n";
	for (i = 0; i < m_pdata->m_properties.size(); i++)
	{
		rv += m_pdata->m_properties[i].toMOF();
// TODO:		rv += '\n';
	}
	for (i = 0; i < m_pdata->m_methods.size(); i++)
	{
		rv += m_pdata->m_methods[i].toMOF();
// TODO:		rv += '\n';
	}
	rv += "};\n";
	return rv.releaseString();
}
//////////////////////////////////////////////////////////////////////////////
String
CIMClass::toString() const
{
	return toMOF();
}
//////////////////////////////////////////////////////////////////////////////
CIMClass::~CIMClass()
{
}
//////////////////////////////////////////////////////////////////////////////
CIMClass::CIMClass(const CIMClass& x)
	: CIMElement(x)
	, m_pdata(x.m_pdata)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMClass& CIMClass::operator=(const CIMClass& x)
{
	m_pdata = x.m_pdata;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMClass::setNull()
{
	m_pdata = NULL;
}
//////////////////////////////////////////////////////////////////////////////
String
CIMClass::getName() const
{
	return m_pdata->m_name.toString();
}
//////////////////////////////////////////////////////////////////////////////
bool operator<(const CIMClass& x, const CIMClass& y)
{
	return *x.m_pdata < *y.m_pdata;
}

//////////////////////////////////////////////////////////////////////////////
bool operator==(const CIMClass& x, const CIMClass& y)
{
	return *x.m_pdata == *y.m_pdata;
}

//////////////////////////////////////////////////////////////////////////////
bool operator<=(const CIMClass& x, const CIMClass& y)
{
    return !(y < x);
}

//////////////////////////////////////////////////////////////////////////////
bool operator>(const CIMClass& x, const CIMClass& y)
{
    return y < x;
}

//////////////////////////////////////////////////////////////////////////////
bool operator>=(const CIMClass& x, const CIMClass& y)
{
    return !(x < y);
}

//////////////////////////////////////////////////////////////////////////////
bool operator!=(const CIMClass& x, const CIMClass& y)
{
	return !(x == y);
}

//////////////////////////////////////////////////////////////////////////////
const char* const CIMClass::NAMESPACECLASS = "__Namespace";
//////////////////////////////////////////////////////////////////////////////
StringArray
CIMClass::getCloneProps(ELocalOnlyFlag localOnly, EDeepFlag deep,
	const StringArray* propertyList,
	const CIMClass& requestedClass) const
{
	if (propertyList && propertyList->size() == 0)
	{
		return StringArray();
	}
	StringArray rv = this->getCloneProps(E_NOT_LOCAL_ONLY, propertyList);
	// do processing of deep & localOnly
	// don't filter anything if (deep == E_DEEP && localOnly == E_NOT_LOCAL_ONLY)
	if (deep != E_DEEP || localOnly != E_NOT_LOCAL_ONLY)
	{
		CIMPropertyArray props = this->getAllProperties();
		CIMName requestedClassName = requestedClass.getName();
		for (size_t i = 0; i < props.size(); ++i)
		{
			CIMProperty p = props[i];
			CIMProperty clsp = requestedClass.getProperty(p.getName());
			if (clsp)
			{
				if (clsp.getOriginClass() == requestedClassName)
				{
					rv.push_back(p.getName());
					continue;
				}
			}
			if (deep == E_DEEP)
			{
				if (!clsp || p.getOriginClass() != clsp.getOriginClass())
				{
					// the property is from a derived class
					rv.push_back(p.getName());
					continue;
				}
			}
			if (localOnly == E_NOT_LOCAL_ONLY)
			{
				if (clsp)
				{
					// the property has to be from a superclass
					rv.push_back(p.getName());
					continue;
				}
			}
		}
	}
	return rv;
}
//////////////////////////////////////////////////////////////////////////////
StringArray
CIMClass::getCloneProps(ELocalOnlyFlag localOnly,
	const StringArray* propertyList) const
{
	StringArray props;
	if (propertyList && propertyList->size() == 0)
	{
		return props;
	}
	for (size_t i = 0; i < this->getAllProperties().size(); i++)
	{
		CIMProperty prop = this->getAllProperties()[i];
		if (localOnly && prop.getPropagated())
		{
			continue;
		}
		//
		// If propertyList is not NULL then check this is a request property
		//
		if (propertyList)
		{
			CIMName pName = prop.getName();
			for (size_t j = 0; j < propertyList->size(); j++)
			{
				if (pName == (*propertyList)[j])
				{
					props.push_back(prop.getName());
					break;
				}
			}
		}
		else
		{
			props.append(prop.getName());
		}
	}
	return props;
}

} // end namespace OW_NAMESPACE

