/*******************************************************************************
* Copyright (C) 2003-2004 Vintela, Inc. All rights reserved.
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

#include "OW_CppProviderIncludes.hpp"
#include "OW_WQLSelectStatement.hpp"
#include "OW_Thread.hpp"
#include "OW_NonRecursiveMutex.hpp"
#include "OW_NonRecursiveMutexLock.hpp"
#include "OW_Condition.hpp"
#include "OW_WQLCompile.hpp"
#include "OW_Reference.hpp"

#include <algorithm>

#include <iostream>
#include <iterator> // debug

using namespace OpenWBEM;
using namespace WBEMFlags;

// anonymous namespace to prevent library symbol conflicts
namespace
{

const String COMPONENT_NAME("ow.test.IndicationProviderTest2");

// This is an example/test of a simple instance/indication provider.  It
// doesn't implement mustPoll.  The CIMOM will call the *Filter methods.
// We'll start up a separate thread to "watch" the instances we are
// instrumenting.  Really, we'll just change them once a second, so this
// provider has something to do.  A real indication provider should only
// use this model if it can block and wait for some sort of notification
// that something has happened.  There is no need to create a new thread
// if polling is needed, just create a combination indication/polled provider
// see (IndicationProviderTest3).  An indication provider with a separate
// thread is useful for waiting for external events which will notify the
// thread that something has happened.  How this notification happens is up
// to the provider.

// This example is bordering on the edge of complexity where it should be
// split up into a couple of source and header files...

class IndicationProviderTest2;

class TestProviderThread : public Thread
{
public:
	// joinable, so we can wait for it to stop before the library gets
	// unloaded.  NEVER start a detached thread from a provider.  As soon as
	// the provider library is unloaded, the CIMOM will crash if the thread
	// is still running.
	TestProviderThread(IndicationProviderTest2* pProv, const ProviderEnvironmentIFCRef& env)
		: Thread()
		, m_shuttingDown(false)
		, m_creationFilterCount(0)
		, m_modificationFilterCount(0)
		, m_deletionFilterCount(0)
		, m_pProv(pProv)
		, m_env(env)
	{
	}

	void shutdown()
	{
		NonRecursiveMutexLock l(m_guard);
		m_shuttingDown = true;
		m_cond.notifyAll(); // wake up run() so it will exit.
	}

	virtual void doCooperativeCancel()
	{
		shutdown();
	}

	void addCreationFilter()
	{
		NonRecursiveMutexLock l(m_guard);
		++m_creationFilterCount;
	}

	void addModificationFilter()
	{
		NonRecursiveMutexLock l(m_guard);
		++m_modificationFilterCount;
	}

	void addDeletionFilter()
	{
		NonRecursiveMutexLock l(m_guard);
		++m_deletionFilterCount;
	}

	void removeCreationFilter()
	{
		NonRecursiveMutexLock l(m_guard);
		--m_creationFilterCount;
	}

	void removeModificationFilter()
	{
		NonRecursiveMutexLock l(m_guard);
		--m_modificationFilterCount;
	}

	void removeDeletionFilter()
	{
		NonRecursiveMutexLock l(m_guard);
		--m_deletionFilterCount;
	}

protected:
	virtual Int32 run();

	NonRecursiveMutex m_guard;
	Condition m_cond;
	bool m_shuttingDown;
	int m_creationFilterCount;
	int m_modificationFilterCount;
	int m_deletionFilterCount;
	IndicationProviderTest2* m_pProv;
	ProviderEnvironmentIFCRef m_env;
};
	
class IndicationProviderTest2 : public CppIndicationProviderIFC, public CppInstanceProviderIFC
{
public:
	IndicationProviderTest2()
		: m_threadStarted(false)
		, m_theClass(CIMNULL)
	{
	}

	~IndicationProviderTest2()
	{
		std::cout << "IndicationProviderTest2::~IndicationProviderTest2()" << std::endl;
		do_cleanup();
	}

	// Indication provider methods
	virtual void activateFilter(
		const ProviderEnvironmentIFCRef& env,
		const WQLSelectStatement& filter,
		const String& eventType,
		const String& nameSpace,
		const StringArray& classes,
		bool firstActivation)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), Format("IndicationProviderTest2::activateFilter filter = %1, eventType = %2, nameSpace = %3, firstActivation = %4", filter.toString(), eventType, nameSpace, firstActivation));
		
		NonRecursiveMutexLock l(m_mtx);
		// create the thread now that someone is listening for our events.
		if (m_threadStarted == false && !m_thread)
		{
			OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::activateFilter creating helper thread");
			m_thread = new TestProviderThread(this, env->clone());
		}
		// eventType contains the name of the indication the listener subscribed to.
		// this will be one of the class names we indicated in getIndicationProviderInfo(IndicationProviderInfo& info)
		// so for this provider (and most other life cycle indication providers), it's got to be one of:
		// CIM_InstCreation, CIM_InstModification, or CIM_InstDeletion
		if (eventType.equalsIgnoreCase("CIM_InstCreation"))
		{
			m_thread->addCreationFilter();
		}
		else if (eventType.equalsIgnoreCase("CIM_InstModification"))
		{
			m_thread->addModificationFilter();
		}
		else if (eventType.equalsIgnoreCase("CIM_InstDeletion"))
		{
			m_thread->addDeletionFilter();
		}
		else if (eventType.equalsIgnoreCase("CIM_InstIndication") || eventType.equalsIgnoreCase("CIM_Indication"))
		{
			m_thread->addCreationFilter();
			m_thread->addModificationFilter();
			m_thread->addDeletionFilter();
		}
		else
		{
			// this isn't really necessary in a normal provider, but since this is a test, we do it to make sure the indication server is working all right
			OW_THROWCIMMSG(CIMException::FAILED, "BIG PROBLEM! eventType is incorrect!");
		}
		// classes should either be empty (meaning the filter didn't contain an ISA clause), or contain a IndicationProviderTest2 classname
		// (this is the case if the filter contains "SourceInstance ISA IndicationProviderTest2")
		if (!classes.empty() && std::find(classes.begin(), classes.end(), "OW_IndicationProviderTest2") == classes.end())
		{
			// this isn't really necessary in a normal provider, but since this is a test, we do it to make sure the indication server is working all right
			OW_THROWCIMMSG(CIMException::FAILED, "BIG PROBLEM! classPath is incorrect!");
		}

		WQLCompile comp(filter);
		// do something with comp

		// start the thread now that someone is listening for our events.
		if (m_threadStarted == false)
		{
			OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::activateFilter starting helper thread");
			m_thread->start();
			m_threadStarted = true;
		}
	}
	
	virtual void deActivateFilter(
		const ProviderEnvironmentIFCRef& env,
		const WQLSelectStatement& filter,
		const String& eventType,
		const String& nameSpace,
		const StringArray& classes,
		bool lastActivation)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), Format("IndicationProviderTest2::deActivateFilter filter = %1, eventType = %2, nameSpace = %3, lastActivation = %4", filter.toString(), eventType, nameSpace, lastActivation));
		
		NonRecursiveMutexLock l(m_mtx);
		// terminate the thread if no one is listening for our events.
		if (lastActivation && m_thread && m_threadStarted == true)
		{
			OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::deActivateFilter stopping helper thread");
			m_thread->shutdown();
			m_thread->join();
			m_thread = 0;
			m_threadStarted = false;
			OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::deActivateFilter helper thread stopped");
			return;
		}

		// eventType contains the name of the indication the listener subscribed to.
		// this will be one of the class names we indicated in getIndicationProviderInfo(IndicationProviderInfo& info)
		// so for this provider (and most other life cycle indication providers), it's got to be one of:
		// CIM_InstCreation, CIM_InstModification, or CIM_InstDeletion
		if (eventType.equalsIgnoreCase("CIM_InstCreation"))
		{
			m_thread->removeCreationFilter();
		}
		else if (eventType.equalsIgnoreCase("CIM_InstModification"))
		{
			m_thread->removeModificationFilter();
		}
		else if (eventType.equalsIgnoreCase("CIM_InstDeletion"))
		{
			m_thread->removeDeletionFilter();
		}
		else if (eventType.equalsIgnoreCase("CIM_InstIndication") || eventType.equalsIgnoreCase("CIM_Indication"))
		{
			m_thread->removeCreationFilter();
			m_thread->removeModificationFilter();
			m_thread->removeDeletionFilter();
		}
		else
		{
			// this isn't really necessary in a normal provider, but since this is a test, we do it to make sure the indication server is working all right
			OW_THROWCIMMSG(CIMException::FAILED, "BIG PROBLEM! eventType is incorrect!");
		}
		// classes should either be empty (meaning the filter didn't contain an ISA clause), or contain a IndicationProviderTest2 classname
		// (this is the case if the filter contains "SourceInstance ISA IndicationProviderTest2")
		if (!classes.empty() && std::find(classes.begin(), classes.end(), "OW_IndicationProviderTest2") == classes.end())
		{
			// this isn't really necessary in a normal provider, but since this is a test, we do it to make sure the indication server is working all right
			OW_THROWCIMMSG(CIMException::FAILED, "BIG PROBLEM! classPath is incorrect!");
		}

		WQLCompile comp(filter);
		// do something with comp
		
	}

	/**
	 * A provider should override this method to report which classes in
	 * which namespaces it instruments.
	 * It should insert an entry for each class it is responsible for.
	 *  The entry consists of the class name and an optional list of namespaces.
	 *  If the namespace list is empty, all namespaces are implied.
	 * If the method does nothing, then the provider's class must have a
	 * provider qualifier that identifies the provider.  This old behavior is
	 * deprecated and will be removed sometime in the future.  This method
	 * has a default implementation that does nothing, to allow old providers
	 * to be migrated forward with little or no change, but once the old
	 * provider location method is removed, this member function will be pure
	 * virtual.
	 */
	virtual void getIndicationProviderInfo(IndicationProviderInfo& info)
	{
		// Add the class(es) we are monitoring for lifecycle indications. We only need to add the most derived classes to this array.
		const char* theMonitoredClasses[] =
			{
				"OW_IndicationProviderTest2",
				0
			};

		// all the life-cycle indications that may be generated by this provider. We have to add all the base classes to this array.
		const char* instanceLifeCycleIndicationClassNames[] =
			{
				"CIM_InstCreation",
				"CIM_InstModification",
				"CIM_InstDeletion",
				"CIM_InstIndication",
				"CIM_Indication",
				0
			};

		for (const char** pIndicationClassName = instanceLifeCycleIndicationClassNames;
			  *pIndicationClassName != 0;
			  ++pIndicationClassName)
		{
			const char* indicationClassName = *pIndicationClassName;
			IndicationProviderInfoEntry e(indicationClassName);
			for (const char** pClassName = theMonitoredClasses;
				  *pClassName != 0;
				  ++pClassName)
			{
				const char* className = *pClassName;
				e.classes.push_back(className);
			}
			info.addInstrumentedClass(e);

		}
	}

	// These are the instance provider methods.
	virtual void getInstanceProviderInfo(InstanceProviderInfo& info)
	{
		// The class we are instrumenting
		info.addInstrumentedClass("OW_IndicationProviderTest2");
	}

	virtual void deleteInstance(const ProviderEnvironmentIFCRef &, const String &, const CIMObjectPath &)
	{
		OW_THROWCIMMSG(CIMException::FAILED, "Delete not supported");
	}

	virtual CIMObjectPath createInstance(const ProviderEnvironmentIFCRef &, const String &, const CIMInstance &)
	{
		OW_THROWCIMMSG(CIMException::FAILED, "Create not supported");
	}
	
	virtual CIMInstance getInstance(
		const ProviderEnvironmentIFCRef &env,
		const String &ns,
		const CIMObjectPath &instanceName,
		ELocalOnlyFlag localOnly,
		EIncludeQualifiersFlag includeQualifiers,
		EIncludeClassOriginFlag includeClassOrigin,
		const StringArray *propertyList,
		const CIMClass &cimClass)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::getInstance");
		Int32 id = 0;
		try
		{
			id = instanceName.getKeyT("DeviceID").getValueT().toString().toInt32();
		}
		catch (Exception& e)
		{
			OW_THROWCIMMSG_SUBEX(CIMException::NOT_FOUND, "Invalid DeviceID property", e);
		}

		// m_insts could be accessed from multiple threads
		NonRecursiveMutexLock l(m_guard);
		if (id < 0 || UInt32(id) >= m_insts.size())
		{
			OW_THROWCIMMSG(CIMException::NOT_FOUND, Format("Invalid DeviceID property: %1", id).c_str());
		}
		return m_insts[id].clone(localOnly, includeQualifiers, includeClassOrigin, propertyList);
	}

	virtual void enumInstances(
		const ProviderEnvironmentIFCRef &env,
		const String &ns,
		const String &className,
		CIMInstanceResultHandlerIFC &result,
		ELocalOnlyFlag localOnly,
		EDeepFlag deep,
		EIncludeQualifiersFlag includeQualifiers,
		EIncludeClassOriginFlag includeClassOrigin,
		const StringArray *propertyList,
		const CIMClass &requestedClass,
		const CIMClass &cimClass)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::enumInstances");
		// m_insts could be accessed from multiple threads
		NonRecursiveMutexLock l(m_guard);
		for (size_t i = 0; i < m_insts.size(); ++i)
		{
			result.handle(m_insts[i].clone(localOnly, deep, includeQualifiers, includeClassOrigin, propertyList, requestedClass, cimClass));
		}
	}
	
	virtual void enumInstanceNames(
		const ProviderEnvironmentIFCRef &env,
		const String &ns,
		const String &className,
		CIMObjectPathResultHandlerIFC &result,
		const CIMClass &cimClass)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::enumInstanceNames");
		// m_insts could be accessed from multiple threads
		NonRecursiveMutexLock l(m_guard);
		for (size_t i = 0; i < m_insts.size(); ++i)
		{
			result.handle(CIMObjectPath(ns, m_insts[i]));
		}
	}
	
	virtual void modifyInstance(
		const ProviderEnvironmentIFCRef& env,
		const String& ns,
		const CIMInstance& modifiedInstance,
		const CIMInstance& previousInstance,
		EIncludeQualifiersFlag includeQualifiers,
		const StringArray* propertyList,
		const CIMClass& theClass)
	{
		OW_THROWCIMMSG(CIMException::FAILED, "Modify not supported");
	}

	virtual void initialize(const ProviderEnvironmentIFCRef& env)
	{
		OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "IndicationProviderTest2::initialize - creating the thread");
		NonRecursiveMutexLock l(m_mtx);
		m_threadStarted = false;
	}

	void do_cleanup()
	{
		using std::cout;
		using std::endl;
		// we've got to stop the thread we started
		cout << "IndicationProviderTest2::do_cleanup" << endl;
		NonRecursiveMutexLock l(m_mtx);
		if (m_threadStarted && m_thread)
		{
			cout << "IndicationProviderTest2::do_cleanup - stopping thread" << endl;
			m_thread->shutdown();
			m_thread->join();
			cout << "IndicationProviderTest2::do_cleanup - thread stopped" << endl;
		}
		m_thread = 0;
	}

	void updateInstancesAndSendIndications(const CIMOMHandleIFCRef& hdl, int creat, int mod, int del)
	{
		std::cout << "IndicationProviderTest2::updateInstancesAndSendIndications create = " << creat << " mod = " << mod << " del = " << del << std::endl;
		if (!m_theClass)
		{
			m_theClass = hdl->getClass("root/testsuite", "OW_IndicationProviderTest2");
		}

		// m_insts could be accessed from multiple threads
		NonRecursiveMutexLock l(m_guard);

		if (m_insts.size() == 5)
		{
			if (del > 0)
			{
				// send out CIM_InstDeletion indications
				for (size_t i = 0; i < m_insts.size(); ++i)
				{
					CIMInstance expInst;
					expInst.setClassName("CIM_InstDeletion");
					expInst.setProperty("SourceInstance", CIMValue(m_insts[i]));
					expInst.setProperty("IndicationTime", CIMValue(CIMDateTime(DateTime::getCurrent())));
					hdl->exportIndication(expInst, "root/testsuite");
				}
			}
			m_insts.clear();
		}
		else
		{
			// add an instance
			CIMInstance iToAdd(m_theClass.newInstance());
			iToAdd.setProperty("SystemCreationClassName", CIMValue("CIM_System"));
			iToAdd.setProperty("SystemName", CIMValue("localhost"));
			iToAdd.setProperty("CreationClassName", CIMValue("OW_IndicationProviderTest2"));
			iToAdd.setProperty("DeviceID", CIMValue(String(UInt32(m_insts.size()))));
			// PowerOnHours is our property that will be modified
			iToAdd.setProperty("PowerOnHours", CIMValue(UInt64(m_insts.size())));
			if (creat > 0)
			{
				// send out CIM_InstCreation indications
				CIMInstance expInst;
				expInst.setClassName("CIM_InstCreation");
				expInst.setProperty("SourceInstance", CIMValue(iToAdd));
				expInst.setProperty("IndicationTime", CIMValue(CIMDateTime(DateTime::getCurrent())));
				hdl->exportIndication(expInst, "root/testsuite");
			}
			m_insts.push_back(iToAdd);

			// now modify the first instance's PowerOnHours property
			CIMInstance prevInst = m_insts[0];
			UInt64 oldPowerOnHours = prevInst.getPropertyT("PowerOnHours").getValueT().toUInt64();
			m_insts[0].setProperty("PowerOnHours", CIMValue(UInt64(oldPowerOnHours + 1)));

			if (mod > 0)
			{
				// send out CIM_InstModification indications
				CIMInstance expInst;
				expInst.setClassName("CIM_InstModification");
				expInst.setProperty("PreviousInstance", CIMValue(prevInst));
				expInst.setProperty("SourceInstance", CIMValue(m_insts[0]));
				expInst.setProperty("IndicationTime", CIMValue(CIMDateTime(DateTime::getCurrent())));
				hdl->exportIndication(expInst, "root/testsuite");
			}
		}
	}

private:
	CIMInstanceArray m_insts;

	// this is a reference so we can pass in a cimom handle to it's constructor.  We can't get a cimom handle in our constructor, so we have to wait until initialize is called.
	Reference<TestProviderThread> m_thread;
	bool m_threadStarted;
	NonRecursiveMutex m_mtx;
	NonRecursiveMutex m_guard;
	CIMClass m_theClass;
};


Int32 TestProviderThread::run()
{
	NonRecursiveMutexLock l(m_guard);
	while (!m_shuttingDown)
	{
		OperationContext context;
		m_pProv->updateInstancesAndSendIndications(m_env->getCIMOMHandle(), m_creationFilterCount, m_modificationFilterCount, m_deletionFilterCount);
		// wait one second.  If this were a real provider we would wait on some IPC mechanism.  This has to be done carefully so that we don't block forever.  The provider needs
		// to be able to stop the thread when the cimom shuts down or restarts.
		m_cond.timedWait(l, 1);
	}
	return 0;
}


} // end anonymous namespace


OW_PROVIDERFACTORY(IndicationProviderTest2, indicationtest2)


