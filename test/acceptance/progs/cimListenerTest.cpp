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
#include "OW_HTTPXMLCIMListener.hpp"
#include "OW_Semaphore.hpp"
#include "OW_String.hpp"
#include "OW_Array.hpp"
#include "OW_ClientCIMOMHandle.hpp"
#include "OW_CIMClass.hpp"
#include "OW_CIMQualifier.hpp"
#include "OW_CIMQualifierType.hpp"
#include "OW_CIMProperty.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMNameSpace.hpp"
#include "OW_CIMException.hpp"
#include "OW_CIMInstanceEnumeration.hpp"
#include "OW_MutexLock.hpp"
#include "OW_Bool.hpp"
#include "OW_SocketBaseImpl.hpp"
#include "OW_CerrLogger.hpp"

#include <iostream> // for cout and cerr

using std::cout;
using std::endl;
using std::cerr;
using namespace OpenWBEM;

OW_DECLARE_EXCEPTION(ListenerTest);
OW_DEFINE_EXCEPTION(ListenerTest);

Semaphore sem(0);
Semaphore test1sem(0);
Semaphore test2sem(0);
Mutex coutMutex;
#define PRINT(arg) do {MutexLock lock(coutMutex); std::cout << arg << std::flush;} while (0)

class myCallBack : public CIMListenerCallback
{
public:
	myCallBack() : m_count(0) {}
protected:
	virtual void doIndicationOccurred(CIMInstance &ci,
		const String &listenerPath)
	{
		// remove time property so output will always look alike (and allow
		// a diff in the acceptance script).
		ci.removeProperty("IndicationTime");
		{
		MutexLock lock(coutMutex);
		++m_count;
		cout << "\nmyCallBack::doIndicationOccurred: Got indication: " << m_count << "\n";
		cout << ci.toString() << "\n" << std::flush;
		}
		sem.signal();
	}
private:
	int m_count;
};

class test1CallBack : public CIMListenerCallback
{
protected:
	virtual void doIndicationOccurred(CIMInstance &ci,
		const String &listenerPath)
	{
		// remove time property so output will always look alike (and allow
		// a diff in the acceptance script).
		ci.removeProperty("IndicationTime");
		{
		MutexLock lock(coutMutex);
		cout << "\ntest1CallBack::doIndicationOccurred: Got indication:\n";
		cout << ci.toString() << "\n" << std::flush;
		}
		test1sem.signal();
	}
};

class test2CallBack : public CIMListenerCallback
{
protected:
	virtual void doIndicationOccurred(CIMInstance &ci,
		const String &listenerPath)
	{
		// remove time property so output will always look alike (and allow
		// a diff in the acceptance script).
		ci.removeProperty("IndicationTime");
		{
		MutexLock lock(coutMutex);
		cout << "\ntest2CallBack::doIndicationOccurred: Got indication:\n";
		cout << ci.toString() << "\n" << std::flush;
		}
		test2sem.signal();
	}
};



void createClass(CIMOMHandleIFC& hdl)
{
	CIMQualifierType cqt = hdl.getQualifierType("root/testsuite", "Key");
	CIMQualifier cimQualifierKey(cqt);
	cimQualifierKey.setValue(CIMValue(Bool(true)));

	CIMClass cimClass;
	cimClass.setName("EXP_IndicationTestComputerSystem");
	cimClass.setSuperClass("CIM_System");

	Array<String> zargs;
	zargs.push_back("CreationClassName");
	zargs.push_back("string");
	zargs.push_back("true");
	zargs.push_back("Name");
	zargs.push_back("string");
	zargs.push_back("true");
	zargs.push_back("OptionalArg");
	zargs.push_back("boolean");
	zargs.push_back("false");

	String name;
	String type;
	String isKey;

	for (size_t i = 0; i < zargs.size(); i += 3)
	{
		name = zargs[i];
		type = zargs[i + 1];
		isKey = zargs[i + 2];
		CIMProperty cimProp;
		if (type.equals("string"))
		{
			cimProp.setDataType(CIMDataType::STRING);
		}
		else if (type.equals("uint16"))
		{
			cimProp.setDataType(CIMDataType::UINT16);
		}
		else if (type.equals("boolean"))
		{
			cimProp.setDataType(CIMDataType::BOOLEAN);
		}
		else if (type.equals("datatime"))
		{
			cimProp.setDataType(CIMDataType::DATETIME);
		}
		else cimProp.setDataType(CIMDataType::STRING);

		cimProp.setName(name);
		if (isKey.equals("true"))
		{
			cimProp.addQualifier(cimQualifierKey);
		}
		cimClass.addProperty(cimProp);
	}

	hdl.createClass("root/testsuite", cimClass);
}


void modifyClass(CIMOMHandleIFC& hdl)
{
	CIMClass cimClass = hdl.getClass("root/testsuite",
		"EXP_IndicationTestComputerSystem");
	CIMProperty cimProp;
	cimProp.setDataType(CIMDataType::STRING);
	cimProp.setName("BrandNewProperty");
	cimClass.addProperty(cimProp);
	hdl.modifyClass("root/testsuite", cimClass);
}


void createInstance(CIMOMHandleIFC& hdl, const String& newInstance)
{
	String fromClass = "EXP_IndicationTestComputerSystem";

	CIMClass cimClass = hdl.getClass("root/testsuite", fromClass);

	CIMInstance newInst = cimClass.newInstance();

	newInst.setProperty(CIMProperty::NAME_PROPERTY,
							  CIMValue(newInstance));
	newInst.setProperty("CreationClassName",
							  CIMValue(fromClass));

	hdl.createInstance("root/testsuite", newInst);
}


void getInstance(CIMOMHandleIFC& hdl, const String& theInstance)
{
	String ofClass = "EXP_IndicationTestComputerSystem";
	CIMObjectPath cop(ofClass);
	cop.setKeyValue("CreationClassName", CIMValue(ofClass));
	cop.setKeyValue("Name", CIMValue(theInstance));

	CIMInstance in = hdl.getInstance("root/testsuite", cop);
	//cout << in.toMOF();
}

void modifyInstance(CIMOMHandleIFC& hdl, const String& theInstance)
{
	String ofClass = "EXP_IndicationTestComputerSystem";
	CIMObjectPath cop(ofClass);
	cop.setKeyValue("CreationClassName", CIMValue(ofClass));
	cop.setKeyValue("Name", CIMValue(theInstance));

	CIMInstance in = hdl.getInstance("root/testsuite", cop);

	in.setProperty(CIMProperty("BrandNewProperty",
											CIMValue(Bool(true))));

	// getInstance with includeQualifiers = false doesn't have any keys, so
	// we'll have to set them so modifyInstance will work.
	in.setKeys(cop.getKeys());

	hdl.modifyInstance("root/testsuite", in);
}

void deleteInstance(CIMOMHandleIFC& hdl, const String& theInstance)
{
	String ofClass = "EXP_IndicationTestComputerSystem";
	CIMObjectPath cop(ofClass, "root/testsuite");
	cop.setKeyValue("CreationClassName", CIMValue(ofClass));
	cop.setKeyValue("Name", CIMValue(theInstance));
	hdl.deleteInstance("root/testsuite", cop);
}


void deleteClass(CIMOMHandleIFC& hdl)
{
	String delClass = "EXP_IndicationTestComputerSystem";
	hdl.deleteClass("root/testsuite", delClass);
}

int main(int argc, char* argv[])
{
	// these need to be out of the try, so that a potential deadlock won't happen
	// the problem is that Exception has a mutex, and the HTTPXMLCIMListener
	// destructor shouldn't run when the Exception mutex is locked.
	LoggerRef logger(new CerrLogger);

	HTTPXMLCIMListener hxcl(logger);

	try
	{
		if (argc < 2 || argc > 3)
		{
			cerr << "Usage: " << argv[0] << " <URL> [dump file prefix]" << endl;
			return 1;
		}

		String url(argv[1]);

		if (argc == 3)
		{
			String sockDumpOut = argv[2];
			String sockDumpIn = argv[2];
			sockDumpOut += "SockDumpOut";
			sockDumpIn += "SockDumpIn";
			cerr << "argc = " << argc << " sockDumpOut = " << sockDumpOut << endl;
			SocketBaseImpl::setDumpFiles(sockDumpIn.c_str(),
				sockDumpOut.c_str());
		}

		String ns("/root/testsuite");

		CIMOMHandleIFCRef chRef = ClientCIMOMHandle::createFromURL(url);
		CIMOMHandleIFC& rch = *chRef;

		rch.execQueryE("/root/testsuite", "delete from CIM_IndicationSubscription", "wql2");


		Array<String> registrationHandles;
		String handle;

		CIMListenerCallbackRef mcb(new myCallBack);
		CIMListenerCallbackRef test1cb(new test1CallBack);
		CIMListenerCallbackRef test2cb(new test2CallBack);

		if (getenv("OWLONGTEST"))
		{
			// TODO: Add tests here for alert indications

			handle = hxcl.registerForIndication(url, ns,
				"select * from CIM_Indication where SourceInstance ISA "
				"OW_IndicationProviderTest1", "wql1", "root/testsuite", test1cb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns,
				"select * from CIM_InstModification where SourceInstance ISA "
				"\"OW_IndicationProviderTest2\" and SourceInstance.SystemName = \"localhost\"", "wql1",
				"root/testsuite", test2cb);
			registrationHandles.append(handle);
			sleep(1);

			// Now wait for our test trigger providers to send out their indications.
			// we'll wait for 5 TestIndication1 indications.
			for (size_t i = 0; i < 5; ++i)
			{
				if (!test1sem.timedWait(25))
				{
					OW_THROW(ListenerTestException, "semaphore 1 timed out");
				}
			}
			// we'll wait for 5 TestIndication2 indications.
			for (size_t i = 0; i < 5; ++i)
			{
				if (!test2sem.timedWait(25))
				{
					OW_THROW(ListenerTestException, "semaphore 2 timed out");
				}
			}

			// now deregister
			PRINT("Now deregistering\n");

			for (size_t i = 0; i < registrationHandles.size(); ++i)
			{
				hxcl.deregisterForIndication(registrationHandles[i]);
			}
			registrationHandles.clear();

		}
		
		// now let's register for all the intrinsic method indications.


		try
		{
			deleteInstance(rch, "MyInstance");
		}
		catch(CIMException& e)
		{
			PRINT(e.getMessage() << endl);
		}
		try
		{
			deleteClass(rch);
		}
		catch(CIMException& e)
		{
			PRINT(e.getMessage() << endl);
		}

		for (size_t i = 0; i < 3; ++i)
		{
			registrationHandles.clear();

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_ClassIndication", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_ClassCreation", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_ClassDeletion", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_ClassModification", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_InstModification", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_InstDeletion", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_InstRead", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_InstCreation", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);

			handle = hxcl.registerForIndication(url, ns, "select * from CIM_InstIndication", "wql1", "root/testsuite", mcb);
			registrationHandles.append(handle);
			sleep(1);


			//handle = hxcl.registerForIndication(url, ns, "select * from CIM_InstMethodCall", "wql1", "root/testsuite", mcb);
			//registrationHandles.append(handle);


			PRINT("Executing createClass()\n");
			createClass(rch);

			PRINT("Executing createInstance()\n");
			createInstance(rch, "MyInstance");

			PRINT("Executing modifyInstance()\n");
			modifyInstance(rch, "MyInstance");

			PRINT("Executing getInstance()\n");
			getInstance(rch, "MyInstance");

			PRINT("Executing deleteInstance()\n");
			deleteInstance(rch, "MyInstance");

			PRINT("Executing modifyClass()\n");
			modifyClass(rch);

			PRINT("Executing deleteClass()\n");
			deleteClass(rch);

			PRINT("Done running intrinsic methods.\n");
			//invokeMethod(rch, 2); // TODO

			//cout << "Now waiting for intrinsic method indications" << endl;
			for (size_t i = 0; i < 10; ++i)
			{
				if (!sem.timedWait(25))
				{
					OW_THROW(ListenerTestException, "timeout on semaphore");
				}
				PRINT(i << endl);
			}

			PRINT("Now deregistering...\n");

			for (size_t i = 0; i < registrationHandles.size() - 1; ++i)
			{
				hxcl.deregisterForIndication(registrationHandles[i]);
			}
		}

		PRINT("Now shutting down...\n");

		hxcl.shutdownHttpServer();
		for (size_t i = 0; i < registrationHandles.size(); ++i)
		{
			hxcl.deregisterForIndication(registrationHandles[i]);
		}

		// The acceptance script greps for "Success" in the output to tell
		// whether the test worked or not.
		PRINT("Success!\n");
		return 0;
	}
	catch(Exception& e)
	{
		cerr << e << endl;
	}
	catch(std::exception& e)
	{
		cerr << e.what() << endl;
	}
	catch(...)
	{
		cerr << "Caught unknown exception in main" << endl;
	}
	return 1;
}

