/*
 *
 * cmpiResult.cpp
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
 * Description: CMPIObjectPath support
 *
 */

#include <iostream>
#include "cmpisrv.h"
#include "OW_CIMException.hpp"
#include "CmpiProviderBase.h"

static CMPIStatus resultReturnData(const CMPIResult* eRes, const CMPIValue* data,
	const CMPIType type)
{
	CMPIrc rc;
	OpenWBEM::CIMValue v=value2CIMValue(data,type,&rc);
	if(eRes->ft==CMPI_ResultMethOnStack_Ftab)
	{
		CMPIValueValueResultHandler* res=(CMPIValueValueResultHandler*)eRes->hdl;
		if(((CMPI_Result*)eRes)->flags & RESULT_set==0)
		{
			((CMPI_Result*)eRes)->flags|=RESULT_set;
		}
		res->handle(v);
	}
	else
	{
		CMPIValueValueResultHandler* res=(CMPIValueValueResultHandler*)eRes->hdl;
		if(((CMPI_Result*)eRes)->flags & RESULT_set==0)
		{
			((CMPI_Result*)eRes)->flags|=RESULT_set;
		}
		res->handle(v);
	}
	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnInstance(const CMPIResult* eRes, const CMPIInstance* eInst)
{
	OpenWBEM::CIMInstanceResultHandlerIFC * res =
		static_cast<OpenWBEM::CIMInstanceResultHandlerIFC *> (eRes->hdl);
//	const OpenWBEM::CIMInstance& inst =
//		* (static_cast<OpenWBEM::CIMInstance *>(eInst->hdl));
	try
   {
      CMPIStatus rc;
      CMPIContext *ctx=CMPI_ThreadContext::getContext();
      CMPIFlags flgs = ctx->ft->getEntry(ctx,const_cast<char*>(CMPIInvocationFlags),&rc).value.uint32;
      OpenWBEM::CIMInstance* in = (static_cast<OpenWBEM::CIMInstance *>(eInst->hdl));
      OpenWBEM::CIMInstance ci(
         in->clone((flgs & CMPI_FLAG_LocalOnly         )? OpenWBEM::WBEMFlags::E_LOCAL_ONLY          : OpenWBEM::WBEMFlags::E_NOT_LOCAL_ONLY,
                   (flgs & CMPI_FLAG_IncludeQualifiers )? OpenWBEM::WBEMFlags::E_INCLUDE_QUALIFIERS  : OpenWBEM::WBEMFlags::E_EXCLUDE_QUALIFIERS,
                   (flgs & CMPI_FLAG_IncludeClassOrigin)? OpenWBEM::WBEMFlags::E_INCLUDE_CLASS_ORIGIN: OpenWBEM::WBEMFlags::E_EXCLUDE_CLASS_ORIGIN));
      res->handle(ci);
   }
	catch(const OpenWBEM::CIMException& e)
	{
		//CMReturnWithChars(CmpiProviderBase::getBroker(),
		//		  (_CMPIrc)e.getErrNo(), e.getMessage());
		CMReturn((_CMPIrc)e.getErrNo());
	}
	catch(...)
	{
		CMReturn(CMPI_RC_ERROR);
	}
	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnObject(const CMPIResult* eRes, const CMPIInstance* eInst)
{
	OpenWBEM::CIMInstanceResultHandlerIFC * res =
		static_cast<OpenWBEM::CIMInstanceResultHandlerIFC *> (eRes->hdl);
	const OpenWBEM::CIMInstance& inst =
		* (static_cast<OpenWBEM::CIMInstance *>(eInst->hdl));

	try
	{
		//std::cout << "inst to handle " << inst.toMOF() << std::endl;
		// TODO - turn instance into object
		res->handle(inst);

	}
	catch(const OpenWBEM::CIMException& e)
	{
		CMReturn((_CMPIrc)e.getErrNo());
	}
	catch(...)
	{
		CMReturn(CMPI_RC_ERROR);
	}
	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnObjectPath(const CMPIResult* eRes,
	const CMPIObjectPath* eRef)
{
	OpenWBEM::CIMObjectPathResultHandlerIFC * res =
		static_cast<OpenWBEM::CIMObjectPathResultHandlerIFC *>(eRes->hdl);

	const OpenWBEM::CIMObjectPath& cop =
		* (static_cast<OpenWBEM::CIMObjectPath *>(eRef->hdl));

	try
	{
		//std::cout << "cop to handle " << cop.toMOF() << std::endl;
		res->handle(cop);
	}
	catch(const OpenWBEM::CIMException& e)
	{
		CMReturn((_CMPIrc)e.getErrNo());
	}
	catch(...)
	{
		CMReturn(CMPI_RC_ERROR);
	}

	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnInstDone(const CMPIResult* eRes) 
{
	(void) eRes;
	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnRefDone(const CMPIResult* eRes)
{
	(void) eRes;
	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnDataDone(const CMPIResult* eRes)
{
	(void) eRes;
	CMReturn(CMPI_RC_OK);
}

static CMPIStatus resultReturnMethDone(const CMPIResult* eRes)
{
	(void) eRes;
	CMReturn(CMPI_RC_OK);
}
static CMPIStatus resultReturnObjDone(const CMPIResult* eRes)
{
	(void) eRes;
	CMReturn(CMPI_RC_OK);
}


static CMPIStatus resultBadReturnData(const CMPIResult* eRes,
	const CMPIValue* data, CMPIType type)
{
	(void) eRes;
	(void) data;
	(void) type;
	CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus resultBadReturnInstance(const CMPIResult* eRes,
	const CMPIInstance* eInst)
{
	(void) eRes;
	(void) eInst;
	CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus resultBadReturnObjectPath(const CMPIResult* eRes,
	const CMPIObjectPath* eRef)
{
	(void) eRes;
	(void) eRef;
	CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIResultFT resultMethOnStack_FT={
	CMPICurrentVersion,
	NULL,
	NULL,
	resultReturnData,
	resultBadReturnInstance,
	resultBadReturnObjectPath,
	resultReturnMethDone,
};

static CMPIResultFT resultObjOnStack_FT={
	CMPICurrentVersion,
	NULL,
	NULL,
	resultBadReturnData,
	resultReturnObject,
	resultBadReturnObjectPath,
	resultReturnObjDone,
};

static CMPIResultFT resultData_FT={
	CMPICurrentVersion,
	NULL,
	NULL,
	resultReturnData,
	resultBadReturnInstance,
	resultBadReturnObjectPath,
	resultReturnDataDone,
};

static CMPIResultFT resultInstOnStack_FT={
	CMPICurrentVersion,
	NULL,
	NULL,
	resultBadReturnData,
	resultReturnInstance,
	resultBadReturnObjectPath,
	resultReturnInstDone,
};

static CMPIResultFT resultResponseOnStack_FT={
	CMPICurrentVersion,
	NULL,
	NULL,
	resultReturnData,
	resultBadReturnInstance,
	resultBadReturnObjectPath,
	resultReturnDataDone,
};

static CMPIResultFT resultRefOnStack_FT={
	CMPICurrentVersion,
	NULL,
	NULL,
	resultBadReturnData,
	resultBadReturnInstance,
	resultReturnObjectPath,
	resultReturnRefDone,
};


CMPIResultFT *CMPI_ResultMeth_Ftab=&resultMethOnStack_FT;
CMPIResultFT *CMPI_ResultData_Ftab=&resultData_FT;
CMPIResultFT *CMPI_ResultMethOnStack_Ftab=&resultMethOnStack_FT;
CMPIResultFT *CMPI_ResultInstOnStack_Ftab=&resultInstOnStack_FT;
CMPIResultFT *CMPI_ResultObjOnStack_Ftab=&resultObjOnStack_FT;
CMPIResultFT *CMPI_ResultRefOnStack_Ftab=&resultRefOnStack_FT;
CMPIResultFT *CMPI_ResultResponseOnStack_Ftab=&resultResponseOnStack_FT;


CMPI_ResultOnStack::CMPI_ResultOnStack(
	const OpenWBEM::CIMObjectPathResultHandlerIFC & handler)
{
	hdl = (void *)(&handler);
	ft = CMPI_ResultRefOnStack_Ftab;
	flags = RESULT_ObjectPath;
}

CMPI_ResultOnStack::CMPI_ResultOnStack(
	const OpenWBEM::CIMInstanceResultHandlerIFC & handler)
{
	hdl = (void *)(&handler);
	ft = CMPI_ResultInstOnStack_Ftab;
	flags = RESULT_Instance;
}

#if 0
// ObjectResponseHandler
CMPI_ResultOnStack::CMPI_ResultOnStack(
	const OpenWBEM::CIMInstanceResultHandlerIFC & handler)
{
	hdl= (void *)(&handler);
	ft=CMPI_ResultInstOnStack_Ftab;
	flags=RESULT_Instance;
}

CMPI_ResultOnStack::CMPI_ResultOnStack(
	const OpenWBEM::MethodResultResultHandlerIFC & handler)
{
	hdl= (void *)(&handler);
	ft=CMPI_ResultMethOnStack_Ftab;
	flags=RESULT_Method;
}
#endif

CMPI_ResultOnStack::CMPI_ResultOnStack(const
	CMPIObjectPathValueResultHandler& handler)
{
	hdl = (void *)&handler;
	ft = CMPI_ResultResponseOnStack_Ftab;
	flags = RESULT_Response;
}

CMPI_ResultOnStack::CMPI_ResultOnStack(
	const CMPIValueValueResultHandler& handler)
{
	hdl = (void *)&handler;
	ft = CMPI_ResultResponseOnStack_Ftab;
	flags = RESULT_Response;
}

CMPI_ResultOnStack::CMPI_ResultOnStack()
{
	//hdl= static_cast<void* >(&handler);
	ft=CMPI_ResultResponseOnStack_Ftab;
	flags=RESULT_Response;
}

CMPI_ResultOnStack::~CMPI_ResultOnStack()
{
	//std::cout << "--- ~CMPI_ResultOnStack()" << std::endl;
	//if (flags & RESULT_set==0)  ((ResponseHandler*)hdl)->processing();
	//if (flags & RESULT_done==0) ((ResponseHandler*)hdl)->complete();
}

