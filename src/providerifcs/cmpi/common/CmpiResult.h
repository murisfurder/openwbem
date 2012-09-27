
/*
 *
 * CmpiResult.h
 *
 * (C) Copyright IBM Corp. 2003
 * 
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE COMMON PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Common Public License from
 * http://oss.software.ibm.com/developerworks/opensource/license-cpl.html
 *
 * Author:        Adrian Schuur <schuur@de.ibm.com>
 * Contributors:
 *
 * Description: CMPI C++ result wrapper
 *
 */

#ifndef _CmpiResult_h_
#define _CmpiResult_h_
#include "OW_config.h"

#include "cmpidt.h"
#include "cmpift.h"

#include "CmpiObject.h"
#include "CmpiData.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"


/** This class acts as a container to hold values returned by provider functions.
*/

class CmpiResult : public CmpiObject{
   friend class CmpiInstanceMI;
   friend class CmpiAssociationMI;
   friend class CmpiMethodMI;
   friend class CmpiPropertyMI;
   friend class CmpiIndicationMI;
 private:

   /** Constructor - Should not be called
   */
   CmpiResult() {}
  protected:

   /** Protected constructor used by MIDrivers to encapsulate CMPIResult.
   */
   CmpiResult(CMPIResult* r)
      : CmpiObject((void*)r) {}

   /** getEnc - Gets the encapsulated CMPIResult.
   */
   inline CMPIResult *getEnc() const
      { return (CMPIResult*)enc; }
  public:

   /** returnData - Return a CmpiData instance.
   */
   void returnData(const CmpiData& d);

   /** returnData - Return a CmpiInstance object.
   */
   void returnData(const CmpiInstance& d);

   /** returnData - Return a CmpiObjectPath object.
   */
   void returnData(const CmpiObjectPath& d);
 
   /** returnDone - Indicate all data returned.
   */
   void returnDone();
};

#endif


