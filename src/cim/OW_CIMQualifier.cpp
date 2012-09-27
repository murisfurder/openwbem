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
#include "OW_CIMQualifier.hpp"
#include "OW_StringBuffer.hpp"
#include "OW_Assertion.hpp"
#include "OW_BinarySerialization.hpp"
#include "OW_StrictWeakOrdering.hpp"
#include "OW_NULLValueException.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMQualifierType.hpp"
#include "OW_CIMFlavor.hpp"
#include "OW_COWIntrusiveCountableBase.hpp"

namespace OW_NAMESPACE
{

using std::istream;
using std::ostream;
//////////////////////////////////////////////////////////////////////////////
struct CIMQualifier::QUALData : public COWIntrusiveCountableBase
{
	QUALData() 
		: m_qualifierValue(CIMNULL)
		, m_propagated(false) 
	{}
	CIMName m_name;
	CIMValue m_qualifierValue;
	CIMQualifierType m_qualifierType;
	Bool m_propagated;
	CIMFlavorArray m_flavors;
	String m_language;
	QUALData* clone() const { return new QUALData(*this); }
};
//////////////////////////////////////////////////////////////////////////////
bool operator<(const CIMQualifier::QUALData& x, const CIMQualifier::QUALData& y)
{
	return StrictWeakOrdering(
		x.m_name, y.m_name,
		x.m_language, y.m_language,
		x.m_qualifierValue, y.m_qualifierValue,
		x.m_qualifierType, y.m_qualifierType,
		x.m_propagated, y.m_propagated,
		x.m_flavors, y.m_flavors);
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::CIMQualifier() :
	CIMElement(), m_pdata(new QUALData)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::CIMQualifier(CIMNULL_t) :
	CIMElement(), m_pdata(0)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::CIMQualifier(const CIMName& name) :
	CIMElement(), m_pdata(new QUALData)
{
	m_pdata->m_name = name;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::CIMQualifier(const char* name) :
	CIMElement(), m_pdata(new QUALData)
{
	m_pdata->m_name = name;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::CIMQualifier(const CIMQualifierType& cgt) :
	CIMElement(), m_pdata(new QUALData)
{
	m_pdata->m_name = cgt.getName();
	m_pdata->m_qualifierType = cgt;
	m_pdata->m_qualifierValue = cgt.getDefaultValue();
	m_pdata->m_flavors = cgt.getFlavors();
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::CIMQualifier(const CIMQualifier& x) :
	CIMElement(), m_pdata(x.m_pdata)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier::~CIMQualifier()
{
}
//////////////////////////////////////////////////////////////////////////////
void
CIMQualifier::setNull()
{
	m_pdata = NULL;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier&
CIMQualifier::operator= (const CIMQualifier& x)
{
	m_pdata = x.m_pdata;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMQualifier::isKeyQualifier() const
{
	return m_pdata->m_name == CIMQualifier::CIM_QUAL_KEY;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMQualifier::isAssociationQualifier() const
{
	return m_pdata->m_name == CIMQualifier::CIM_QUAL_ASSOCIATION;
}
//////////////////////////////////////////////////////////////////////////////
CIMValue
CIMQualifier::getValue() const
{
	return m_pdata->m_qualifierValue;
}
//////////////////////////////////////////////////////////////////////////////
CIMValue
CIMQualifier::getValueT() const
{
	if (!m_pdata->m_qualifierValue)
	{
		OW_THROW(NULLValueException, "");
	}
	return m_pdata->m_qualifierValue;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier&
CIMQualifier::setValue(const CIMValue& value)
{
	m_pdata->m_qualifierValue = value;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier&
CIMQualifier::setDefaults(const CIMQualifierType& qtype)
{
	m_pdata->m_qualifierType = qtype;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifierType
CIMQualifier::getDefaults() const
{
	return m_pdata->m_qualifierType;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMQualifier::hasFlavor(const CIMFlavor& flavor) const
{
	if (flavor)
	{
		size_t tsize = m_pdata->m_flavors.size();
		for (size_t i = 0; i < tsize; i++)
		{
			if (m_pdata->m_flavors[i].getFlavor() == flavor.getFlavor())
			{
				return true;
			}
		}
	}
	return(false);
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier&
CIMQualifier::addFlavor(const CIMFlavor& flavor)
{
	if (flavor)
	{
		Int32 flavorValue = flavor.getFlavor();
		//
		// Don't add it if its already present
		//
		size_t tsize = m_pdata->m_flavors.size();
		for (size_t i = 0; i < tsize; i++)
		{
			if (m_pdata->m_flavors[i].getFlavor() == flavorValue)
			{
				return *this;
			}
		}
		switch (flavorValue)
		{
			case CIMFlavor::ENABLEOVERRIDE:
				removeFlavor(CIMFlavor::DISABLEOVERRIDE);
				break;
			case CIMFlavor::DISABLEOVERRIDE:
				removeFlavor(CIMFlavor::ENABLEOVERRIDE);
				break;
			case CIMFlavor::RESTRICTED:
				removeFlavor(CIMFlavor::TOSUBCLASS);
				break;
			case CIMFlavor::TOSUBCLASS:
				removeFlavor(CIMFlavor::RESTRICTED);
				break;
		}
		m_pdata->m_flavors.append(flavor);
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier&
CIMQualifier::removeFlavor(Int32 flavor)
{
	size_t i = 0;
	while (i < m_pdata->m_flavors.size())
	{
		if (m_pdata->m_flavors[i].getFlavor() == flavor)
		{
			m_pdata->m_flavors.remove(i);
		}
		else
		{
			++i;
		}
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMQualifier::hasValue() const
{
	return (m_pdata->m_qualifierValue) ? true : false;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMQualifier::equals(const CIMQualifier& arg) const
{
	return m_pdata->m_name == arg.getName();
}
//////////////////////////////////////////////////////////////////////////////
CIMFlavorArray
CIMQualifier::getFlavor() const
{
	return m_pdata->m_flavors;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier&
CIMQualifier::setPropagated(bool propagated)
{
	m_pdata->m_propagated = propagated;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMQualifier::getPropagated() const
{
	return m_pdata->m_propagated;
}
//////////////////////////////////////////////////////////////////////////////
CIMQualifier& 
CIMQualifier::setLanguage(const String& language)
{
	OW_ASSERT(hasFlavor(CIMFlavor::TRANSLATE));
	m_pdata->m_language = language;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
String
CIMQualifier::getLanguage() const
{
	return m_pdata->m_language;
}
//////////////////////////////////////////////////////////////////////////////
String
CIMQualifier::getName() const
{
	return m_pdata->m_name.toString();
}
//////////////////////////////////////////////////////////////////////////////
void
CIMQualifier::setName(const CIMName& name)
{
	m_pdata->m_name = name;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMQualifier::readObject(istream &istrm)
{
	CIMName name;
	CIMValue qualifierValue(CIMNULL);
	CIMQualifierType qualifierType(CIMNULL);
	Bool propagated;
	CIMFlavorArray flavors;
	Bool isValue;
	String language;

	UInt32 version = CIMBase::readSig( istrm, OW_CIMQUALIFIERSIG, OW_CIMQUALIFIERSIG_V, CIMQualifier::SERIALIZATION_VERSION );

	name.readObject(istrm);
	isValue.readObject(istrm);
	if (isValue)
	{
		qualifierValue.readObject(istrm);
	}
	qualifierType.readObject(istrm);
	propagated.readObject(istrm);
	BinarySerialization::readArray(istrm, flavors);

	// language was added in version 1
	if (version > 0)
	{
		language.readObject(istrm);
	}

	if (!m_pdata)
	{
		m_pdata = new QUALData;
	}
	m_pdata->m_name = name;
	m_pdata->m_qualifierValue = qualifierValue;
	m_pdata->m_qualifierType = qualifierType;
	m_pdata->m_propagated = propagated;
	m_pdata->m_flavors = flavors;
	m_pdata->m_language = language;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMQualifier::writeObject(ostream &ostrm) const
{
	CIMBase::writeSig(ostrm, OW_CIMQUALIFIERSIG_V, CIMQualifier::SERIALIZATION_VERSION);

	m_pdata->m_name.writeObject(ostrm);
	CIMValue qv = m_pdata->m_qualifierValue;
	if (!qv && m_pdata->m_qualifierType)
	{
		qv = m_pdata->m_qualifierType.getDefaultValue();
	}
	if (m_pdata->m_qualifierValue)
	{
		Bool(true).writeObject(ostrm);
		qv.writeObject(ostrm);
	}
	else
	{
		Bool(false).writeObject(ostrm);
	}
	m_pdata->m_qualifierType.writeObject(ostrm);
	m_pdata->m_propagated.writeObject(ostrm);
	BinarySerialization::writeArray(ostrm, m_pdata->m_flavors);
	m_pdata->m_language.writeObject(ostrm);
}
//////////////////////////////////////////////////////////////////////////////
String
CIMQualifier::toMOF() const
{
	StringBuffer rv;
	rv += m_pdata->m_name.toString();
	
	if (!m_pdata->m_language.empty())
	{
		rv += '_';
		rv += m_pdata->m_language;
	}

	if (m_pdata->m_qualifierValue 
		&& m_pdata->m_name != CIMName("Association")
		&& m_pdata->m_name != CIMName("Indication"))
	{
		if (!m_pdata->m_qualifierValue.isArray())
		{
			rv += '(';
		}
		rv += m_pdata->m_qualifierValue.toMOF();
		if (!m_pdata->m_qualifierValue.isArray())
		{
			rv += ')';
		}
	}
	
	return rv.releaseString();
}
//////////////////////////////////////////////////////////////////////////////
String
CIMQualifier::toString() const
{
	StringBuffer rv("CIMQualifier(");
	rv += m_pdata->m_name.toString();
	if (!m_pdata->m_language.empty())
	{
		rv += '_';
		rv += m_pdata->m_language;
	}
	rv += ')';
	return rv.releaseString();
}
//////////////////////////////////////////////////////////////////////////////
// STATIC
CIMQualifier
CIMQualifier::createKeyQualifier()
{
	CIMQualifier cq(CIMQualifier::CIM_QUAL_KEY);
	cq.setValue(CIMValue(Bool(true)));
	return cq;
}
//////////////////////////////////////////////////////////////////////////////
bool operator<(const CIMQualifier& x, const CIMQualifier& y)
{
	return *x.m_pdata < *y.m_pdata;
}
// Meta qualifiers
const char* const CIMQualifier::CIM_QUAL_ASSOCIATION	= "Association";
const char* const CIMQualifier::CIM_QUAL_INDICATION		= "Indication";
// Standard qualifiers
const char* const CIMQualifier::CIM_QUAL_ABSTRACT 		= "Abstract";
const char* const CIMQualifier::CIM_QUAL_AGGREGATE 		= "Aggregate";
const char* const CIMQualifier::CIM_QUAL_AGGREGATION 	= "Aggregation";
const char* const CIMQualifier::CIM_QUAL_ALIAS 			= "Alias";
const char* const CIMQualifier::CIM_QUAL_ARRAYTYPE 		= "ArrayType";
const char* const CIMQualifier::CIM_QUAL_BITMAP 		= "BitMap";
const char* const CIMQualifier::CIM_QUAL_BITVALUES 		= "BitValues";
const char* const CIMQualifier::CIM_QUAL_COMPOSITION    = "Composition";
const char* const CIMQualifier::CIM_QUAL_COUNTER 		= "Counter";
const char* const CIMQualifier::CIM_QUAL_DELETE         = "Delete";
const char* const CIMQualifier::CIM_QUAL_DEPRECATED     = "Deprecated";
const char* const CIMQualifier::CIM_QUAL_DESCRIPTION 	= "Description";
const char* const CIMQualifier::CIM_QUAL_DISPLAYNAME 	= "DisplayName";
const char* const CIMQualifier::CIM_QUAL_DN             = "DN";
const char* const CIMQualifier::CIM_QUAL_EMBEDDEDOBJECT = "EmbeddedObject";
const char* const CIMQualifier::CIM_QUAL_EXCEPTION      = "Exception";
const char* const CIMQualifier::CIM_QUAL_EXPENSIVE      = "Expensive";
const char* const CIMQualifier::CIM_QUAL_EXPERIMENTAL   = "Experimental";
const char* const CIMQualifier::CIM_QUAL_GAUGE 			= "Gauge";
const char* const CIMQualifier::CIM_QUAL_IFDELETED      = "Ifdeleted";
const char* const CIMQualifier::CIM_QUAL_IN             = "In";
const char* const CIMQualifier::CIM_QUAL_INVISIBLE      = "Invisible";
const char* const CIMQualifier::CIM_QUAL_KEY            = "Key";
const char* const CIMQualifier::CIM_QUAL_LARGE          = "Large";
const char* const CIMQualifier::CIM_QUAL_MAPPINGSTRINGS	= "MappingStrings";
const char* const CIMQualifier::CIM_QUAL_MAX 			= "Max";
const char* const CIMQualifier::CIM_QUAL_MAXLEN         = "MaxLen";
const char* const CIMQualifier::CIM_QUAL_MAXVALUE 		= "MaxValue";
const char* const CIMQualifier::CIM_QUAL_MIN 			= "Min";
const char* const CIMQualifier::CIM_QUAL_MINLEN         = "MinLen";
const char* const CIMQualifier::CIM_QUAL_MINVALUE 		= "MinValue";
const char* const CIMQualifier::CIM_QUAL_MODELCORRESPONDENCE = "ModelCorrespondence";
const char* const CIMQualifier::CIM_QUAL_NONLOCAL 		= "Nonlocal";
const char* const CIMQualifier::CIM_QUAL_NONLOCALTYPE 	= "NonlocalType";
const char* const CIMQualifier::CIM_QUAL_NULLVALUE 		= "NullValue";
const char* const CIMQualifier::CIM_QUAL_OCTETSTRING    = "Octetstring";
const char* const CIMQualifier::CIM_QUAL_OUT 			= "Out";
const char* const CIMQualifier::CIM_QUAL_OVERRIDE 		= "Override";
const char* const CIMQualifier::CIM_QUAL_PROPAGATED 	= "Propagated";
const char* const CIMQualifier::CIM_QUAL_PROPERTYUSAGE  = "PropertyUsage";
const char* const CIMQualifier::CIM_QUAL_PROVIDER       = "Provider";
const char* const CIMQualifier::CIM_QUAL_READ 			= "Read";
const char* const CIMQualifier::CIM_QUAL_REQUIRED 		= "Required";
const char* const CIMQualifier::CIM_QUAL_REVISION 		= "Revision";
const char* const CIMQualifier::CIM_QUAL_SCHEMA         = "Schema";
const char* const CIMQualifier::CIM_QUAL_SOURCE         = "Source";
const char* const CIMQualifier::CIM_QUAL_SOURCETYPE     = "SourceType";
const char* const CIMQualifier::CIM_QUAL_STATIC         = "Static";
const char* const CIMQualifier::CIM_QUAL_SYNTAX         = "Syntax";
const char* const CIMQualifier::CIM_QUAL_SYNTAXTYPE     = "SyntaxType";
const char* const CIMQualifier::CIM_QUAL_TERMINAL 		= "Terminal";
const char* const CIMQualifier::CIM_QUAL_TRIGGERTYPE    = "TriggerType";
const char* const CIMQualifier::CIM_QUAL_UNITS 			= "Units";
const char* const CIMQualifier::CIM_QUAL_UNKNOWNVALUES  = "UnknownValues";
const char* const CIMQualifier::CIM_QUAL_UNSUPPORTEDVALUES = "UnsupportedValues";
const char* const CIMQualifier::CIM_QUAL_VALUEMAP 		= "ValueMap";
const char* const CIMQualifier::CIM_QUAL_VALUES         = "Values";
const char* const CIMQualifier::CIM_QUAL_VERSION 		= "Version";
const char* const CIMQualifier::CIM_QUAL_WEAK 			= "Weak";
const char* const CIMQualifier::CIM_QUAL_WRITE 			= "Write";

} // end namespace OW_NAMESPACE

