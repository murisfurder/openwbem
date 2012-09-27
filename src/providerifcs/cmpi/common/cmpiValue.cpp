
/*
 *
 * cmpiValue.cpp
 *
 * Copyright (c) 2002, International Business Machines
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE COMMON PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Common Public License from
 * http://oss.software.ibm.com/developerworks/opensource/license-cpl.html
 *
 * Author:        Adrian Schuur <schuur@de.ibm.com>
 *
 * Contributor:   Markus Mueller <sedgewick_de@yahoo.de>
 *
 * Description: value to CMPIdata and CMPIType converters
 *
 */


#include <iostream>
#include "cmpisrv.h"
#include "OW_Char16.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMDateTime.hpp"

#define CopyToArray(pt,ct) { pt##Array ar(aSize); \
   for (int i=0; i<aSize; i++) ar[i]=pt(aData[i].value.ct); \
   v.set(OpenWBEM::CIMValue(ar)); }

#define CopyToStringArray(pt,ct) { OpenWBEM::Array<pt> ar(aSize); \
   for (int i=0; i<aSize; i++) ar[i]=OpenWBEM::String(((char*)aData[i].value)->ct); \
   v.set(OpenWBEM::CIMValue(ar)); }

#define CopyToEncArray(pt,ct) { OpenWBEM::Array<pt> ar(aSize); \
   for (int i=0; i<aSize; i++) ar[i]=*((pt*)aData[i].value.ct->hdl); \
   v.set(OpenWBEM::CIMValue(ar)); }


OpenWBEM::CIMValue value2CIMValue(const CMPIValue* data, const CMPIType type, CMPIrc *rc)
{
	OpenWBEM::CIMValue v(OpenWBEM::CIMNULL);
	if(rc)
	{
		*rc = CMPI_RC_OK;
	}

	if (data == NULL)
	{
	  return v;
	}
	
	if(type & CMPI_ARRAY)
	{
		CMPIArray *ar=data->array;
		CMPIData *aData=(CMPIData*)ar->hdl;
		CMPIType aType=aData->type;

		if(aType & CMPI_ARRAY)
		{
			aType ^= CMPI_ARRAY;
		}

		int aSize=aData->value.sint32;
		aData++;

		if((aType & (CMPI_UINT|CMPI_SINT)) == CMPI_SINT)
		{
			switch(aType)
			{
				case CMPI_sint32: CopyToArray(OpenWBEM::Int32,sint32); break;
				case CMPI_sint16: CopyToArray(OpenWBEM::Int16,sint16); break;
				case CMPI_sint8:  CopyToArray(OpenWBEM::Int8,sint8);   break;
				case CMPI_sint64: CopyToArray(OpenWBEM::Int64,sint64); break;
				default: ;
			}
		}

		//else if (aType==CMPI_chars)  CopyToStringArray(OpenWBEM::String,chars)
		//else if (aType==CMPI_string) CopyToStringArray(OpenWBEM::String,string->hdl)
		else if(aType == CMPI_charsA || aType == CMPI_chars)
		{
			OpenWBEM::Array<OpenWBEM::String> helper(aSize); 
			for(int i = 0; i < aSize; i++)
			{
				helper[i] = OpenWBEM::String( (char *)(aData[i].value.chars));
			}
			v.set(OpenWBEM::CIMValue(helper));
		}

		else if(aType == CMPI_string)
		{
			OpenWBEM::Array<OpenWBEM::String> helper(aSize); 
			for(int i = 0; i < aSize; i++)
			{
				helper[i]=OpenWBEM::String((char *)(aData[i].value.string->hdl));
			}

			v.set(OpenWBEM::CIMValue(helper));
		}

		else if((aType & (CMPI_UINT|CMPI_SINT)) == CMPI_UINT)
		{
			switch(aType)
			{
				case CMPI_uint32: CopyToArray(OpenWBEM::UInt32,uint32); break;
				case CMPI_uint16: CopyToArray(OpenWBEM::UInt16,uint16); break;
				case CMPI_uint8:  CopyToArray(OpenWBEM::UInt8,uint8);   break;
				case CMPI_uint64: CopyToArray(OpenWBEM::UInt64,uint64); break;
				default: ;
			}
		}

		else switch(aType)
			{
				case CMPI_ref:      CopyToEncArray(OpenWBEM::CIMObjectPath,ref); break;
				case CMPI_dateTime: CopyToEncArray(OpenWBEM::CIMDateTime,dateTime); break;
				case CMPI_boolean:  CopyToArray(OpenWBEM::Bool,boolean); break;
				case CMPI_char16:   CopyToArray(OpenWBEM::Char16,char16); break;
				case CMPI_real32:   CopyToArray(OpenWBEM::Real32,real32); break;
				case CMPI_real64:   CopyToArray(OpenWBEM::Real64,real64); break;
				default:
					if(rc)
					{
						*rc=CMPI_RC_ERR_NOT_SUPPORTED;
					}
			}
		return OpenWBEM::CIMValue(v);
	} // end of array processing
	else if((type & (CMPI_UINT|CMPI_SINT)) == CMPI_SINT)
	{
		switch(type)
		{
			//case CMPI_sint32: v.set(OpenWBEM::CIMValue((OpenWBEM::Int32)data->sint32)); break;
			//case CMPI_sint16: v.set(OpenWBEM::CIMValue((OpenWBEM::Int16)data->sint16)); break;
			//case CMPI_sint8:  v.set(OpenWBEM::CIMValue((OpenWBEM::Int8)data->sint8));   break;
			//case CMPI_sint64: v.set(OpenWBEM::CIMValue((OpenWBEM::Int64)data->sint64)); break;
			case CMPI_sint32: v.set(OpenWBEM::CIMValue((OpenWBEM::Int32)data->sint32)); break;
			case CMPI_sint16: v.set(OpenWBEM::CIMValue((OpenWBEM::Int16)data->sint16)); break;
			case CMPI_sint8:  v.set(OpenWBEM::CIMValue((OpenWBEM::Int8)data->sint8));   break;
			case CMPI_sint64: v.set(OpenWBEM::CIMValue((OpenWBEM::Int64)data->sint64)); break;
			default: ;
		}
	}

	//else if (type==CMPI_chars)  v.set(OpenWBEM::CIMValue(OpenWBEM::String(data->chars)));
	else if(type == CMPI_string)
	{
		v.set(OpenWBEM::CIMValue(OpenWBEM::String((char*)data->string->hdl)));
	}
	else if(type == CMPI_chars)
	{
		// Apparently everyone who uses the cmpi interface assumes that
		// a pointer to a CMPIValue is the same thing as a pointer to a
		// Null terminated character string. Since CMPIValue is a union,
		// a pointer to a CMPIValue that has the type of CMPI_chars would be
		// a pointer to a char pointer. But that is not the way it is being
		// used, So I'm coding this to treat it as a straight char*.
		//v.set(OpenWBEM::CIMValue(OpenWBEM::String(data->chars)));
		v.set(OpenWBEM::CIMValue(OpenWBEM::String((const char*)data)));
	}
	else if(((type & (CMPI_UINT|CMPI_SINT)) == CMPI_UINT)  && type != CMPI_boolean)
	{
		switch(type)
		{
			case CMPI_uint32:
				v.set(OpenWBEM::CIMValue((OpenWBEM::UInt32)data->sint32));
				break;
			case CMPI_uint16:
				v.set(OpenWBEM::CIMValue((OpenWBEM::UInt16)data->sint16));
				break;
			case CMPI_uint8:
				v.set(OpenWBEM::CIMValue((OpenWBEM::UInt8)data->sint8));
				break;
			case CMPI_uint64:
				v.set(OpenWBEM::CIMValue((OpenWBEM::UInt64)data->sint64));
				break;
			default: ;
		}
	}
	else
	{
		switch(type)
		{
			case CMPI_ref:
				v.set(OpenWBEM::CIMValue(*((OpenWBEM::CIMObjectPath*)data->ref->hdl)));
				break;
			case CMPI_dateTime:
				v.set(OpenWBEM::CIMValue(*((OpenWBEM::CIMDateTime*)data->dateTime->hdl)));
				break;
			case CMPI_boolean:
				v.set(OpenWBEM::CIMValue((OpenWBEM::Bool)data->boolean));
				break;
			case CMPI_char16:
				v.set(OpenWBEM::CIMValue((OpenWBEM::Char16)data->char16));
				break;
			case CMPI_real32:
				v.set(OpenWBEM::CIMValue((OpenWBEM::Real32)data->real32));
				break;
			case CMPI_real64:
				v.set(OpenWBEM::CIMValue((OpenWBEM::Real64)data->real64));
				break;
			default:
				if(rc)
				{
					*rc = CMPI_RC_ERR_NOT_SUPPORTED;
				}
		}
	}

	//return OpenWBEM::CIMValue(v);
	return v;
}



#define CopyFromArray(pt,ct,dt) { OpenWBEM::Array<pt> ar; \
   v.get(ar); \
   for (int i=0; i<aSize; i++){ \
       aData[i].value.ct=ar[i]; \
       aData[i].state = 0; \
       aData[i].type = dt; } }

#define CopyFromStringArray(pt,ct) { OpenWBEM::Array<pt> ar; \
   v.get(ar); \
   for (int i=0; i<aSize; i++) { \
	  aData[i].value.ct=(CMPIString*)new CMPI_Object(ar[i]); \
      aData[i].state = 0; \
      aData[i].type = CMPI_string; } }

#define CopyFromEncArray(pt,ct,cn,dt) { OpenWBEM::Array<pt> ar; \
   v.get(ar); \
   for (int i=0; i<aSize; i++) { \
	 aData[i].value.cn=(ct*)new CMPI_Object(new pt(ar[i])); \
     aData[i].state = 0; \
     aData[i].type = dt; } }


CMPIrc value2CMPIData(const OpenWBEM::CIMValue& v, CMPIType t, CMPIData *data)
{
	data->type=t;
	data->state=0;

	if(t & CMPI_ARRAY)
	{
		int aSize = v.getArraySize();
		CMPIType aType = t & (~CMPI_ARRAY);
		CMPIData *aData = new CMPIData[aSize+1];
		aData->type = aType;
		aData->value.sint32 = aSize;
		aData++;

		if((aType & (CMPI_UINT | CMPI_SINT)) == CMPI_SINT)
		{
			switch(aType)
			{
				case CMPI_sint32: CopyFromArray(OpenWBEM::Int32,sint32,CMPI_sint32); break;
				case CMPI_sint16: CopyFromArray(OpenWBEM::Int16,sint16,CMPI_sint16); break;
				case CMPI_sint8:  CopyFromArray(OpenWBEM::Int8,sint8,CMPI_sint8);   break;
				case CMPI_sint64: CopyFromArray(OpenWBEM::Int64,sint64,CMPI_sint64); break;
				default: ;
			}
		}
		else if(aType == CMPI_string)
		{
			CopyFromStringArray(OpenWBEM::String,string)
		}
		else if((aType & (CMPI_UINT | CMPI_SINT)) == CMPI_UINT)
		{
			switch(aType)
			{
				case CMPI_uint32: CopyFromArray(OpenWBEM::UInt32,uint32,CMPI_uint32); break;
				case CMPI_uint16: CopyFromArray(OpenWBEM::UInt16,uint16,CMPI_uint16); break;
				case CMPI_uint8:  CopyFromArray(OpenWBEM::UInt8,uint8,CMPI_uint8);   break;
 				case CMPI_uint64: CopyFromArray(OpenWBEM::UInt64,uint64,CMPI_uint64); break;
				default: ;
			}
		}
		else
		{
			switch(aType)
			{
				case CMPI_ref:      CopyFromEncArray(OpenWBEM::CIMObjectPath,CMPIObjectPath,ref,CMPI_ref); break;
				case CMPI_instance: CopyFromEncArray(OpenWBEM::CIMInstance,CMPIInstance,inst,CMPI_instance); break;
				case CMPI_dateTime: CopyFromEncArray(OpenWBEM::CIMDateTime,CMPIDateTime,dateTime,CMPI_dateTime); break;
				case CMPI_boolean:  CopyFromArray(OpenWBEM::Bool,boolean,CMPI_boolean); break;
				case CMPI_char16:   CopyFromArray(OpenWBEM::Char16,char16,CMPI_char16); break;
				case CMPI_real32:   CopyFromArray(OpenWBEM::Real32,real32,CMPI_real32); break;
				case CMPI_real64:   CopyFromArray(OpenWBEM::Real64,real64,CMPI_real64); break;
				default:
					return CMPI_RC_ERR_NOT_SUPPORTED;
			}
		}

		data->value.array=(CMPIArray*)new CMPI_Object(aData-1);
	}  // end of array porocessing

	else if((t & (CMPI_UINT | CMPI_SINT)) == CMPI_SINT)
	{
		switch(t)
		{
			case CMPI_sint32:
			{
				OpenWBEM::Int32 iv;
				v.get(iv);
				data->value.sint32 = (CMPISint32)iv;
				break;
			}
			case CMPI_sint16: v.get((OpenWBEM::Int16&)data->value.sint16); break;
			case CMPI_sint8:  v.get((OpenWBEM::Int8&)data->value.sint8);   break;
			case CMPI_sint64: v.get((OpenWBEM::Int64&)data->value.sint64); break;
			default: ;
		}
	}
   
	else if((t & (CMPI_UINT | CMPI_SINT)) == CMPI_UINT)
	{
		switch(t)
		{
			case CMPI_uint32:
			{
				OpenWBEM::UInt32 uv;
				v.get(uv);
				data->value.uint32 = (CMPIUint32)uv;
				break;
			}
			case CMPI_uint16: v.get((OpenWBEM::UInt16&)data->value.uint16); break;
			case CMPI_uint8:  v.get((OpenWBEM::UInt8&)data->value.uint8);   break;
			case CMPI_uint64: v.get((OpenWBEM::UInt64&)data->value.uint64); break;
			default: ;
		}
	}

	else if(t == CMPI_string)
	{
		OpenWBEM::String str;
		v.get(str);
//std::cout << " string is " << v << std::endl;
		data->value.string=string2CMPIString(str);
	}


	else
	{
		switch(t)
		{
			case CMPI_ref:
				{
					OpenWBEM::CIMObjectPath ref;
					v.get(ref);
					data->value.ref =(CMPIObjectPath*)new CMPI_Object(
						new OpenWBEM::CIMObjectPath(ref));
				}
				break;

			//case CMPI_class:
				// There is no CMPIClass!

			case CMPI_instance:
				{
				    OpenWBEM::CIMInstance inst;
				    v.get(inst);
				    data->value.inst =(CMPIInstance*)new CMPI_Object(
						new OpenWBEM::CIMInstance(inst));
				}
				break;

			case CMPI_dateTime:
				{
					OpenWBEM::CIMDateTime dt;
					v.get(dt);
					data->value.dateTime=(CMPIDateTime*)new CMPI_Object(
						new OpenWBEM::CIMDateTime(dt));
				}
				break;

			case CMPI_boolean:      v.get((OpenWBEM::Bool&)data->value.boolean); break;
			case CMPI_char16:       v.get((OpenWBEM::Char16&)data->value.char16); break;
			case CMPI_real32:       v.get((OpenWBEM::Real32&)data->value.real32); break;
			case CMPI_real64:       v.get((OpenWBEM::Real64&)data->value.real64); break;
			default:
				return CMPI_RC_ERR_NOT_SUPPORTED;
		}
	}
	return CMPI_RC_OK;
}

CMPIType type2CMPIType(OpenWBEM::CIMDataType pt, int array)
{
	static CMPIType types[] = {
		CMPI_uint8,	 // NULL,
		CMPI_uint8,		 // UINT8,
		CMPI_sint8,		 // SINT8,
		CMPI_uint16,	 // UINT16,
		CMPI_sint16,	 // SINT16,
		CMPI_uint32,	 // UINT32,
		CMPI_sint32,	 // SINT32,
		CMPI_uint64,	 // UINT64,
		CMPI_sint64,	 // SINT64,
		CMPI_string,	 // STRING,
		CMPI_boolean,	 // BOOLEAN,
		CMPI_real32,	 // REAL32,
		CMPI_real64,	 // REAL64,
		CMPI_dateTime,	 // DATETIME,
		CMPI_char16,	 // CHAR16,
		CMPI_ref,		 // REFERENCE
    		CMPI_class, 	 // Embedded Class
    		CMPI_instance	 // Embedded Instance
	};

	int t = types[pt.getType()];

	if(array)
	{
		t |= CMPI_ARRAY;
	}

	return (CMPIType)t;
}

CMPIrc key2CMPIData(const OpenWBEM::String& v, OpenWBEM::CIMDataType t, CMPIData *data)
{
	data->state = CMPI_keyValue;

	//case KeyBinding::NUMERIC: {
	if(t.isNumericType())
	{
		const char *vp = v.c_str();
		data->value.sint64 = OpenWBEM::String(vp).toInt64();
		data->type = CMPI_sint64;
		//delete vp;
	}
	//case KeyBinding::STRING:
	else if(t.getType() == OpenWBEM::CIMDataType::STRING)
	{
		data->value.string = string2CMPIString(v);
		data->type = CMPI_string;
	}
	//case KeyBinding::BOOLEAN:
	else if(t.getType() == OpenWBEM::CIMDataType::BOOLEAN)
	{
		data->value.boolean = (v.compareToIgnoreCase("true"));
		data->type=CMPI_boolean;
	}
	//case KeyBinding::REFERENCE:
	else if(t.getType() == OpenWBEM::CIMDataType::BOOLEAN)
	{
		data->value.ref = (CMPIObjectPath*)new CMPI_Object(new OpenWBEM::CIMObjectPath(v));
		data->type = CMPI_ref;
	}
	else
	{
		return CMPI_RC_ERR_NOT_SUPPORTED;
	}

	return CMPI_RC_OK;
}
