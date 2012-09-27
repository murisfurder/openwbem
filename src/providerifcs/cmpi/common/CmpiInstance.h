
/*
 *
 * CmpiInstance.h
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
 * Description: CMPI C++ Instance wrapper
 *
 */

#ifndef _CmpiInstance_h_
#define _CmpiInstance_h_
#include "OW_config.h"

#include "cmpidt.h"
#include "cmpift.h"

/*#include "CmpiImpl.h" */

#include "CmpiObject.h"
#include "CmpiObjectPath.h"
#include "CmpiData.h"
#include "CmpiProviderBase.h"

class CmpiObjectPath;

/** This class represents the instance of a CIM class. It is used manipulate
    instances and their parts.
*/

class CmpiInstance : public CmpiObject {
   friend class CmpiBroker;
   friend class CmpiResult;
   friend class CmpiInstanceMI;
   friend class CmpiMethodMI;
   friend class CmpiData;

  public:

   /** Protected constructor used by MIDrivers to encapsulate CMPIInstance.
   */
   inline CmpiInstance(const CMPIInstance* enc)
      { this->enc=(void*)enc; }

   /** Gets the encapsulated CMPIInstance.
   */
   inline CMPIInstance *getEnc() const
      { return (CMPIInstance*)enc; }
//   private:

   /** Constructor - Should not be called
   */
   CmpiInstance() {}

   /** Internal make function
   */
   void *makeInstance(CMPIBroker *mb, const CmpiObjectPath& cop);
   CmpiBoolean doInstanceIsA(CMPIBroker *mb, const char *className);

//  public:
    /**	Constructor - Creates an Instance object with the classname
	from the input parameter.
	@param op defining classname and namespace
	@return The new Instance object
    */
   inline CmpiInstance(const CmpiObjectPath& op) {
      enc=makeInstance(CmpiProviderBase::getBroker(),op);
   }

    /**	instanceIsA - Tests whether this CIM Instance is of type <className>.
	@param className CIM classname to be tested for.
	@return True or False
    */
   inline CmpiBoolean instanceIsA(const char *className) {
      return doInstanceIsA(CmpiProviderBase::getBroker(),className);
   }

    /**	getPropertyCount - Gets the number of Properties
	defined for this Instance.
	@return	Number of Properties of this instance.
    */
   unsigned int getPropertyCount();

    /**	getProperty - Gets the CmpiData object representing the value
        associated with the property name
	@param name Property name.
	@return CmpiData value object associated with the property.
    */
   CmpiData getProperty(const char* name);

    /**	getProperty - Gets the CmpiData object defined
	by the input index parameter.
	@param index Index into the Property array.
	@param name Optional output parameter returning the property name.
	@return CmpiData value object corresponding to the index.
    */
   CmpiData getProperty(const int index, CmpiString *name=NULL);

    /**	setProperty - adds/replaces a property value defined by the input
	parameter to the Instance
	@param name Property name.
	@param data Type and Value to be added.
    */
   void setProperty(const char* name, const CmpiData data);

    /**	getObjectPath - generates an ObjectPath out of the namespace, classname and
	key propeties of this Instance
	@return the generated ObjectPath.
    */
   CmpiObjectPath getObjectPath();
};

#endif
