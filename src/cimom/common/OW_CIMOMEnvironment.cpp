/*******************************************************************************
* Copyright (C) 2001-2004 Vintela, Inc. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of source code must retain the above copyright notice,
*	this list of conditions and the following disclaimer.
*
*  - Redistributions in binary form must reproduce the above copyright notice,
*	this list of conditions and the following disclaimer in the documentation
*	and/or other materials provided with the distribution.
*
*  - Neither the name of Vintela, Inc. nor the names of its
*	contributors may be used to endorse or promote products derived from this
*	software without specific prior written permission.
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
#include "OW_CIMOMEnvironment.hpp"
#include "OW_ConfigOpts.hpp"
#include "OW_ConfigException.hpp"
#include "OW_Format.hpp"
#include "OW_FileSystem.hpp"
#include "OW_SafeLibCreate.hpp"
#include "OW_SelectEngine.hpp"
#include "OW_CIMServer.hpp"
#include "OW_CIMRepository.hpp"
#include "OW_CIMInstance.hpp"
#include "OW_CIMNameSpace.hpp"
#include "OW_ServiceIFC.hpp"
#include "OW_RequestHandlerIFC.hpp"
#include "OW_IndicationServer.hpp"
#include "OW_PollingManager.hpp"
#include "OW_Assertion.hpp"
#include "OW_AuthManager.hpp"
#include "OW_LocalCIMOMHandle.hpp"
#include "OW_WQLFilterRep.hpp"
#include "OW_IndicationRepLayer.hpp"
#include "OW_Platform.hpp"
#include "OW_WQLIFC.hpp"
#include "OW_SharedLibraryRepository.hpp"
#include "OW_IndicationRepLayerMediator.hpp"
#include "OW_OperationContext.hpp"
#include "OW_Authorizer2IFC.hpp"
#include "OW_ExceptionIds.hpp"
#include "OW_CIMObjectPath.hpp"
#include "OW_AuthorizerManager.hpp"
#include "OW_AuthorizerIFC.hpp"
#include "OW_Socket.hpp"
#include "OW_LogAppender.hpp"
#include "OW_AppenderLogger.hpp"
#include "OW_CerrLogger.hpp"
#include "OW_ProviderEnvironmentIFC.hpp"
#include "OW_ProviderManager.hpp"

#include <iostream>
#include <map>
#include <set>

namespace OW_NAMESPACE
{

OW_DECLARE_EXCEPTION(CIMOMEnvironment)
OW_DEFINE_EXCEPTION_WITH_ID(CIMOMEnvironment)

using std::cerr;
using std::endl;

namespace
{
// the one and only
CIMOMEnvironmentRef theCimomEnvironment;
}

CIMOMEnvironmentRef&
CIMOMEnvironment::instance()
{
	if (!theCimomEnvironment)
	{
		theCimomEnvironment = CIMOMEnvironmentRef(new CIMOMEnvironment);
	}
	return theCimomEnvironment;
}

String CIMOMEnvironment::COMPONENT_NAME("ow.owcimomd");

namespace
{
	class CIMOMProviderEnvironment : public ProviderEnvironmentIFC
	{
	public:
		CIMOMProviderEnvironment(CIMOMEnvironmentRef pCenv)
			: m_pCenv(pCenv)
			, m_context()
		{}
		virtual String getConfigItem(const String &name, const String& defRetVal="") const
		{
			return m_pCenv->getConfigItem(name, defRetVal);
		}
		virtual StringArray getMultiConfigItem(const String &itemName, 
			const StringArray& defRetVal, const char* tokenizeSeparator) const
		{
			return m_pCenv->getMultiConfigItem(itemName, defRetVal, tokenizeSeparator);
		}
		virtual CIMOMHandleIFCRef getCIMOMHandle() const
		{
			OW_ASSERT("Cannot call CIMOMProviderEnvironment::getCIMOMHandle()" == 0);
			return CIMOMHandleIFCRef();
		}
		
		virtual CIMOMHandleIFCRef getRepositoryCIMOMHandle() const
		{
			OW_ASSERT("Cannot call CIMOMProviderEnvironment::getRepositoryCIMOMHandle()" == 0);
			return CIMOMHandleIFCRef();
		}
		
		virtual RepositoryIFCRef getRepository() const
		{
			return m_pCenv->getRepository();
		}
		virtual LoggerRef getLogger() const
		{
			return m_pCenv->getLogger();
		}
		virtual LoggerRef getLogger(const String& componentName) const
		{
			return m_pCenv->getLogger(componentName);
		}
		virtual String getUserName() const
		{
			return Platform::getCurrentUserName();
		}
		virtual OperationContext& getOperationContext()
		{
			return m_context;
		}
		virtual ProviderEnvironmentIFCRef clone() const
		{
			return ProviderEnvironmentIFCRef(new CIMOMProviderEnvironment(m_pCenv));
		}
	private:
		CIMOMEnvironmentRef m_pCenv;
		OperationContext m_context;
	};
	ProviderEnvironmentIFCRef createProvEnvRef(const CIMOMEnvironmentRef& pcenv)
	{
		return ProviderEnvironmentIFCRef(new CIMOMProviderEnvironment(pcenv));
	}
} // end anonymous namespace
//////////////////////////////////////////////////////////////////////////////
// We don't initialize everything here, since startServices() and shutdown() manage the lifecycle.
// We start off with a dumb logger and an empty config map.
CIMOMEnvironment::CIMOMEnvironment()
	: m_Logger(new CerrLogger)
	, m_configItems(new ConfigMap)
	, m_indicationsDisabled(true)
	, m_indicationRepLayerDisabled(false)
	, m_state(E_STATE_INVALID)
	, m_indicationRepLayerMediatorRef(new IndicationRepLayerMediator)
{
}
//////////////////////////////////////////////////////////////////////////////
CIMOMEnvironment::~CIMOMEnvironment()
{
	try
	{
		try
		{
			if (isLoaded(m_state))
			{
				shutdown();
			}
		}
		catch(Exception& e)
		{
			cerr << e << endl;
		}
		m_configItems = 0;
		m_state = E_STATE_INVALID; // just for the heck of it.
	}
	catch (Exception& e)
	{
		OW_LOG_ERROR(m_Logger, Format("Caught exception in CIMOMEnvironment::~CIMOMEnvironment(): %1", e));
	}
	catch (...)
	{
		// don't let exceptions escape!
	}
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::init()
{
	// init() is called from a single-threaded state
	_clearSelectables();

	// The config file config item may be set by main before init() is called.
	_loadConfigItemsFromFile(getConfigItem(ConfigOpts::CONFIG_FILE_opt, OW_DEFAULT_CONFIG_FILE));

	// logger is treated special, so it goes in init() not startServices()
	_createLogger();
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::startServices()
{
	// Split up into 3 sections:
	// 1. load
	// 2. init, initialized
	// 3. start, started

	// We start out single-threaded.  The start phase is when threads enter the picture.

	// This is a global thing, so handle it here.
	Socket::createShutDownMechanism();

	// load
	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment loading services");

	m_authorizerManager = new AuthorizerManager;
	m_services.push_back(ServiceIFCRef(SharedLibraryRef(), m_authorizerManager));

	m_providerManager = new ProviderManager;
	m_providerManager->load(ProviderIFCLoader::createProviderIFCLoader(
		this), this);
	m_services.push_back(ServiceIFCRef(SharedLibraryRef(), m_providerManager));

	m_cimRepository = new CIMRepository;
	m_services.push_back(ServiceIFCRef(SharedLibraryRef(), m_cimRepository));

	m_cimServer = RepositoryIFCRef(new CIMServer(this,
		m_providerManager, m_cimRepository, m_authorizerManager));
	m_services.push_back(ServiceIFCRef(SharedLibraryRef(), m_cimServer));

	_loadAuthorizer();  // old stuff
	_createAuthorizerManager();  // new stuff
	_createAuthManager();
	_loadRequestHandlers();
	_loadServices();
	if (!getConfigItem(ConfigOpts::HTTP_SERVER_SINGLE_THREAD_opt).equalsIgnoreCase("true"))
	{
		_createPollingManager();
		_createIndicationServer();
	}

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment finished loading services");

	_sortServicesForDependencies();

	// init

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment initializing services");

	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_INITIALIZING;
	}

	for (size_t i = 0; i < m_services.size(); i++)
	{
		OW_LOG_DEBUG(m_Logger, Format("CIMOM initializing service: %1", m_services[i]->getName()));
		m_services[i]->init(this);
	}
	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_INITIALIZED;
	}
	
	for (size_t i = 0; i < m_services.size(); i++)
	{
		OW_LOG_DEBUG(m_Logger, Format("CIMOM calling initialized() for service: %1", m_services[i]->getName()));
		m_services[i]->initialized();
	}

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment finished initializing services");

	// start
	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment starting services");
	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_STARTING;
	}

	for (size_t i = 0; i < m_services.size(); i++)
	{
		OW_LOG_DEBUG(m_Logger, Format("CIMOM starting service: %1", m_services[i]->getName()));
		m_services[i]->start();
	}
	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_STARTED;
	}

	for (size_t i = 0; i < m_services.size(); i++)
	{
		OW_LOG_DEBUG(m_Logger, Format("CIMOM calling started() for service: %1", m_services[i]->getName()));
		m_services[i]->started();
	}

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment finished starting services");
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::shutdown()
{

	// notify all services of impending shutdown.
	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment notifying services of shutdown");
	// Do this in reverse order because of dependencies
	for (int i = int(m_services.size())-1; i >= 0; i--)
	{
		try
		{
			OW_LOG_DEBUG(m_Logger, Format("CIMOMEnvironment notifying service: %1", m_services[i]->getName()));
			m_services[i]->shuttingDown();
		}
		catch (Exception& e)
		{
			OW_LOG_ERROR(m_Logger, Format("Caught exception while calling shuttingDown(): %1", e));
		}
		catch (...)
		{
		}
	}

	// PHASE 1: SHUTDOWNS
	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment beginning shutdown process");
	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_SHUTTING_DOWN;
	}

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment shutting down sockets");
	// this is a global thing, so do it here
	Socket::shutdownAllSockets();

	// Shutdown all services
	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment shutting down services");
	// Do this in reverse order because of dependencies
	for (int i = int(m_services.size())-1; i >= 0; i--)
	{
		try
		{
			OW_LOG_DEBUG(m_Logger, Format("CIMOMEnvironment shutting down service: %1", m_services[i]->getName()));
			m_services[i]->shutdown();
		}
		catch (Exception& e)
		{
			OW_LOG_ERROR(m_Logger, Format("Caught exception while calling shutdown(): %1", e));
		}
		catch (...)
		{
		}
	}

	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_SHUTDOWN;
	}

	// PHASE 2: unload/delete

	// get this lock here so that we delete everything atomically
	MutexLock ml(m_monitor);

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment unloading and deleting services");

	m_pollingManager = 0;
	
	// Clear selectable objects
	try
	{
		_clearSelectables();
	}
	catch (Exception& e)
	{
		OW_LOG_ERROR(m_Logger, Format("Caught exception while calling _clearSelectables(): %1", e));
	}
	catch(...)
	{
	}

	// We need to unload these in the opposite order that
	// they were loaded because of bugs in shared library
	// handling on certain OSes.
	for (int i = int(m_services.size())-1; i >= 0; i--)
	{
		m_services[i].setNull();
	}
	m_services.clear();
	// Unload all request handlers
	m_reqHandlers.clear();
	// Unload the wql library if loaded
	m_wqlLib = 0;
	// Shutdown indication processing
	if (m_indicationServer)
	{
		m_indicationServer.setNull();
		m_indicationRepLayerLib = 0;
	}
	// Delete the authentication manager
	m_authManager = 0;
	// Delete the cim server
	m_cimServer = 0;
	// Delete the cim repository
	m_cimRepository = 0;
	// Delete the authorization manager
	m_authorizerManager = 0;
	// Delete the provider manager
	m_providerManager = 0;

	{
		MutexLock l(m_stateGuard);
		m_state = E_STATE_UNLOADED;
	}

	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment has shut down");
}
//////////////////////////////////////////////////////////////////////////////
ProviderManagerRef
CIMOMEnvironment::getProviderManager() const
{
	{
		MutexLock l(m_stateGuard);
		if (!isLoaded(m_state))
		{
			OW_THROW(CIMOMEnvironmentException, "CIMOMEnvironment::getProviderManager() called when state is not constructed");
		}
	}
	OW_ASSERT(m_providerManager);
	return m_providerManager;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_createAuthManager()
{
	m_authManager = AuthManagerRef(new AuthManager);
	m_services.push_back(ServiceIFCRef(SharedLibraryRef(), m_authManager));
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_createPollingManager()
{
	m_pollingManager = PollingManagerRef(new PollingManager(m_providerManager));
	m_services.push_back(ServiceIFCRef(SharedLibraryRef(), m_pollingManager));
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_createIndicationServer()
{
	// Determine if user has disabled indication exportation
	m_indicationsDisabled = getConfigItem(
		ConfigOpts::DISABLE_INDICATIONS_opt, OW_DEFAULT_DISABLE_INDICATIONS).equalsIgnoreCase("true");
	if (!m_indicationsDisabled)
	{
		// load the indication server library
		String indicationLib = getConfigItem(ConfigOpts::OWLIBDIR_opt, OW_DEFAULT_OWLIBDIR);
		if (!indicationLib.endsWith(OW_FILENAME_SEPARATOR))
		{
			indicationLib += OW_FILENAME_SEPARATOR;
		}
		indicationLib += "libowindicationserver"OW_SHAREDLIB_EXTENSION;
		m_indicationServer = SafeLibCreate<IndicationServer>::loadAndCreateObject(
				indicationLib, "createIndicationServer", getLogger(COMPONENT_NAME));
		if (!m_indicationServer)
		{

			OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM Failed to load indication server"
				" from library %1. Indication are currently DISABLED!",
				indicationLib));
			OW_THROW(CIMOMEnvironmentException, "Failed to load indication server");
		}
		m_services.push_back(m_indicationServer);
	}
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_loadRequestHandlers()
{
	m_reqHandlers.clear();
	int reqHandlerCount = 0;
	const StringArray libPaths = getMultiConfigItem(
		ConfigOpts::REQUEST_HANDLER_PATH_opt, 
		String(OW_DEFAULT_REQUEST_HANDLER_PATH).tokenize(OW_PATHNAME_SEPARATOR),
		OW_PATHNAME_SEPARATOR);
	for (size_t i = 0; i < libPaths.size(); ++i)
	{
		String libPath(libPaths[i]);
		if (!libPath.endsWith(OW_FILENAME_SEPARATOR))
		{
			libPath += OW_FILENAME_SEPARATOR;
		}
		OW_LOG_INFO(m_Logger, Format("CIMOM loading request handlers from"
			" directory %1", libPath));
		StringArray dirEntries;
		if (!FileSystem::getDirectoryContents(libPath, dirEntries))
		{
			OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM failed getting the contents of the"
				" request handler directory: %1", libPath));
			OW_THROW(CIMOMEnvironmentException, "No RequestHandlers");
		}
		for (size_t i = 0; i < dirEntries.size(); i++)
		{
			if (!dirEntries[i].endsWith(OW_SHAREDLIB_EXTENSION))
			{
				continue;
			}
#ifdef OW_DARWIN
					if (dirEntries[i].indexOf(OW_VERSION) != String::npos)
					{
							continue;
					}
#endif // OW_DARWIN
			String libName = libPath;
			libName += dirEntries[i];
			RequestHandlerIFCRef rh =
				SafeLibCreate<RequestHandlerIFC>::loadAndCreateObject(
					libName, "createRequestHandler", getLogger(COMPONENT_NAME));
			if (rh)
			{
				++reqHandlerCount;
				rh->setEnvironment(this);
				StringArray supportedContentTypes = rh->getSupportedContentTypes();
				OW_LOG_INFO(m_Logger, Format("CIMOM loaded request handler from file: %1",
					libName));
	
				ReqHandlerDataRef rqData(new ReqHandlerData);
				rqData->filename = libName;
				rqData->rqIFCRef = rh;
				rqData->dt.setToCurrent();
				for (StringArray::const_iterator iter = supportedContentTypes.begin();
					  iter != supportedContentTypes.end(); iter++)
				{
					MutexLock ml(m_reqHandlersLock);
					m_reqHandlers[(*iter)] = rqData;
					ml.release();
					OW_LOG_INFO(m_Logger, Format(
						"CIMOM associating Content-Type %1 with Request Handler %2",
						*iter, libName));
				}
				m_services.push_back(rh);
			}
			else
			{
				OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM failed to load request handler from file:"
					" %1", libName));
				OW_THROW(CIMOMEnvironmentException, "Invalid request handler");
			}
		}
	}
	OW_LOG_INFO(m_Logger, Format("CIMOM: Handling %1 Content-Types from %2 Request Handlers",
		m_reqHandlers.size(), reqHandlerCount));
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_loadServices()
{
	const StringArray libPaths = getMultiConfigItem(
		ConfigOpts::SERVICES_PATH_opt, String(OW_DEFAULT_SERVICES_PATH).tokenize(OW_PATHNAME_SEPARATOR), OW_PATHNAME_SEPARATOR);
	for (size_t i = 0; i < libPaths.size(); ++i)
	{
		String libPath(libPaths[i]);
		if (!libPath.endsWith(OW_FILENAME_SEPARATOR))
		{
			libPath += OW_FILENAME_SEPARATOR;
		}
		OW_LOG_INFO(m_Logger, Format("CIMOM loading services from directory %1",
			libPath));
		StringArray dirEntries;
		if (!FileSystem::getDirectoryContents(libPath, dirEntries))
		{
			OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM failed getting the contents of the"
				" services directory: %1", libPath));
			OW_THROW(CIMOMEnvironmentException, "No Services");
		}
		for (size_t i = 0; i < dirEntries.size(); i++)
		{
			if (!dirEntries[i].endsWith(OW_SHAREDLIB_EXTENSION))
			{
				continue;
			}
	#ifdef OW_DARWIN
			if (dirEntries[i].indexOf(OW_VERSION) != String::npos)
			{
					continue;
			}
	#endif // OW_DARWIN
			String libName = libPath;
			libName += dirEntries[i];
			ServiceIFCRef srv =
				SafeLibCreate<ServiceIFC>::loadAndCreateObject(libName,
					"createService", getLogger(COMPONENT_NAME));
			if (srv)
			{
				m_services.push_back(srv);
				OW_LOG_INFO(m_Logger, Format("CIMOM loaded service from file: %1", libName));
			}
			else
			{
				OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM failed to load service from library: %1",
					libName));
				OW_THROW(CIMOMEnvironmentException, "Invalid service");
			}
		}
	}
	OW_LOG_INFO(m_Logger, Format("CIMOM: Number of services loaded: %1",
		m_services.size()));
}

//////////////////////////////////////////////////////////////////////////////
namespace
{
LogAppender::ConfigMap getAppenderConfig(const ConfigFile::ConfigMap& configItems)
{
	LogAppender::ConfigMap appenderConfig;
	for (ConfigFile::ConfigMap::const_iterator iter = configItems.begin(); iter != configItems.end(); ++iter)
	{
		if (iter->first.startsWith("log") && iter->second.size() > 0)
		{
			appenderConfig[iter->first] = iter->second.back().value;
		}
	}
	return appenderConfig;
}

} // end anonymous namespace
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_createLogger()
{
	using namespace ConfigOpts;
	Array<LogAppenderRef> appenders;
	
	StringArray additionalLogs = getMultiConfigItem(ADDITIONAL_LOGS_opt, StringArray(), " \t");

	// this also gets set if owcimomd is run with -d
	bool debugFlag = getConfigItem(DEBUGFLAG_opt, OW_DEFAULT_DEBUGFLAG).equalsIgnoreCase("true");
	if ( debugFlag )
	{
		// stick it at the beginning as a possible slight logging performance optimization
		additionalLogs.insert(additionalLogs.begin(), LOG_DEBUG_LOG_NAME);
	}

	for (size_t i = 0; i < additionalLogs.size(); ++i)
	{
		const String& logName(additionalLogs[i]);

		String logMainType = getConfigItem(Format(LOG_1_TYPE_opt, logName), OW_DEFAULT_LOG_1_TYPE);
		String logMainComponents = getConfigItem(Format(LOG_1_COMPONENTS_opt, logName), OW_DEFAULT_LOG_1_COMPONENTS);
		String logMainCategories = getConfigItem(Format(LOG_1_CATEGORIES_opt, logName));
		if (logMainCategories.empty())
		{
			// convert level into categories
			String logMainLevel = getConfigItem(Format(LOG_1_LEVEL_opt, logName), OW_DEFAULT_LOG_1_LEVEL);
			if (logMainLevel.equalsIgnoreCase(Logger::STR_DEBUG_CATEGORY))
			{
				logMainCategories = Logger::STR_DEBUG_CATEGORY + " " + Logger::STR_INFO_CATEGORY + " " + Logger::STR_ERROR_CATEGORY + " " + Logger::STR_FATAL_CATEGORY;
			}
			else if (logMainLevel.equalsIgnoreCase(Logger::STR_INFO_CATEGORY))
			{
				logMainCategories = Logger::STR_INFO_CATEGORY + " " + Logger::STR_ERROR_CATEGORY + " " + Logger::STR_FATAL_CATEGORY;
			}
			else if (logMainLevel.equalsIgnoreCase(Logger::STR_ERROR_CATEGORY))
			{
				logMainCategories = Logger::STR_ERROR_CATEGORY + " " + Logger::STR_FATAL_CATEGORY;
			}
			else if (logMainLevel.equalsIgnoreCase(Logger::STR_FATAL_CATEGORY))
			{
				logMainCategories = Logger::STR_FATAL_CATEGORY;
			}
		}
		String logMainFormat = getConfigItem(Format(LOG_1_FORMAT_opt, logName), OW_DEFAULT_LOG_1_FORMAT);

		appenders.push_back(LogAppender::createLogAppender(logName, logMainComponents.tokenize(), logMainCategories.tokenize(),
			logMainFormat, logMainType, getAppenderConfig(*m_configItems)));
	}


	// This one will eventually be handled the same as all other logs by just sticking "main" in the additionalLogs array
	// but we need to handle deprecated options for now, so it needs special treatment.
	String logName(LOG_MAIN_LOG_NAME);
	String logMainType = getConfigItem(Format(LOG_1_TYPE_opt, logName));
	String logMainComponents = getConfigItem(Format(LOG_1_COMPONENTS_opt, logName), OW_DEFAULT_LOG_1_COMPONENTS);
	String logMainCategories = getConfigItem(Format(LOG_1_CATEGORIES_opt, logName));
	String logMainLevel = getConfigItem(Format(LOG_1_LEVEL_opt, logName));
	String logMainFormat = getConfigItem(Format(LOG_1_FORMAT_opt, logName), OW_DEFAULT_LOG_1_FORMAT);

	// map the old log_location onto log.main.type and log.main.location if necessary
	if (logMainType.empty())
	{
		String deprecatedLogLocation = getConfigItem(ConfigOpts::LOG_LOCATION_opt, OW_DEFAULT_LOG_LOCATION);
		if (deprecatedLogLocation.empty() || deprecatedLogLocation.equalsIgnoreCase("syslog"))
		{
			logMainType = "syslog";
		}
		else if (deprecatedLogLocation.equalsIgnoreCase("null"))
		{
			logMainType = "null";
		}
		else
		{
			logMainType = "file";
			setConfigItem(Format(LOG_1_LOCATION_opt, logName), deprecatedLogLocation);
		}
	}

	// map the old log_level onto log.main.level if necessary
	if (logMainCategories.empty() && logMainLevel.empty())
	{
		String deprecatedLogLevel = getConfigItem(ConfigOpts::LOG_LEVEL_opt);
		if (deprecatedLogLevel.empty())
		{
			logMainLevel = OW_DEFAULT_LOG_1_LEVEL;
		}
		else
		{
			// old used "fatalerror", now we just use FATAL
			if (deprecatedLogLevel.equalsIgnoreCase("fatalerror"))
			{
				logMainLevel = Logger::STR_FATAL_CATEGORY;
			}
			else
			{
				deprecatedLogLevel.toUpperCase();
				logMainLevel = deprecatedLogLevel;
			}
		}
	}
	
	// convert level into categories
	if (logMainCategories.empty())
	{
		// convert level into categories
		String logMainLevel = getConfigItem(Format(LOG_1_LEVEL_opt, logName), OW_DEFAULT_LOG_1_LEVEL);
		if (logMainLevel.equalsIgnoreCase(Logger::STR_DEBUG_CATEGORY))
		{
			logMainCategories = Logger::STR_DEBUG_CATEGORY + " " + Logger::STR_INFO_CATEGORY + " " + Logger::STR_ERROR_CATEGORY + " " + Logger::STR_FATAL_CATEGORY;
		}
		else if (logMainLevel.equalsIgnoreCase(Logger::STR_INFO_CATEGORY))
		{
			logMainCategories = Logger::STR_INFO_CATEGORY + " " + Logger::STR_ERROR_CATEGORY + " " + Logger::STR_FATAL_CATEGORY;
		}
		else if (logMainLevel.equalsIgnoreCase(Logger::STR_ERROR_CATEGORY))
		{
			logMainCategories = Logger::STR_ERROR_CATEGORY + " " + Logger::STR_FATAL_CATEGORY;
		}
		else if (logMainLevel.equalsIgnoreCase(Logger::STR_FATAL_CATEGORY))
		{
			logMainCategories = Logger::STR_FATAL_CATEGORY;
		}
	}

	appenders.push_back(LogAppender::createLogAppender(logName, logMainComponents.tokenize(), logMainCategories.tokenize(),
		logMainFormat, logMainType, getAppenderConfig(*m_configItems)));


	m_Logger = new AppenderLogger(COMPONENT_NAME, appenders);
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_loadConfigItemsFromFile(const String& filename)
{
	OW_LOG_DEBUG(m_Logger, "\nUsing config file: " + filename);
	ConfigFile::loadConfigFile(filename, *m_configItems);
	StringArray configDirs = ConfigFile::getMultiConfigItem(*m_configItems, 
		ConfigOpts::ADDITIONAL_CONFIG_FILES_DIRS_opt, 
		String(OW_DEFAULT_ADDITIONAL_CONFIG_FILES_DIRS).tokenize(OW_PATHNAME_SEPARATOR), 
		OW_PATHNAME_SEPARATOR);
	for (size_t i = 0; i < configDirs.size(); ++i)
	{
		String const & dir = configDirs[i];
		StringArray dir_entries;
		bool ok = FileSystem::getDirectoryContents(dir, dir_entries);
		if (!ok)
		{
			OW_THROW(ConfigException, Format("Unable to read additional config directory: %1", dir).c_str());
		}
		for (size_t j = 0; j < dir_entries.size(); ++j)
		{
			String const & fname = dir_entries[j];
			if (fname.endsWith(".conf"))
			{
				ConfigFile::loadConfigFile(dir + "/" + fname, *m_configItems);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
bool
CIMOMEnvironment::authenticate(String &userName, const String &info,
	String &details, OperationContext& context) const
{
	{
		MutexLock l(m_stateGuard);
		if (!isInitialized(m_state))
		{
			return false;
		}
	}
	MutexLock ml(m_monitor);
	OW_ASSERT(m_authManager);
	return m_authManager->authenticate(userName, info, details, context);
}
//////////////////////////////////////////////////////////////////////////////
String
CIMOMEnvironment::getConfigItem(const String &name, const String& defRetVal) const
{
	return ConfigFile::getConfigItem(*m_configItems, name, defRetVal);
}

//////////////////////////////////////////////////////////////////////////////
StringArray
CIMOMEnvironment::getMultiConfigItem(const String &itemName, 
	const StringArray& defRetVal, const char* tokenizeSeparator) const
{
	return ConfigFile::getMultiConfigItem(*m_configItems, itemName, defRetVal, tokenizeSeparator);
}

//////////////////////////////////////////////////////////////////////////////
CIMOMHandleIFCRef
CIMOMEnvironment::getWQLFilterCIMOMHandle(const CIMInstance& inst,
		OperationContext& context) const
{
	{
		MutexLock l(m_stateGuard);
		if (!isLoaded(m_state))
		{
			OW_THROW(CIMOMEnvironmentException, "CIMOMEnvironment::getWQLFilterCIMOMHandle() called when state is not initialized");
		}
	}
	OW_ASSERT(m_cimServer);
	return CIMOMHandleIFCRef(new LocalCIMOMHandle(
		const_cast<CIMOMEnvironment *>(this),
		RepositoryIFCRef(new WQLFilterRep(inst, m_cimServer)), context));
}

//////////////////////////////////////////////////////////////////////////////
CIMOMHandleIFCRef
CIMOMEnvironment::getCIMOMHandle(OperationContext& context,
	EBypassProvidersFlag bypassProviders,
	ELockingFlag locking) const
{
	return getCIMOMHandle(context, E_SEND_INDICATIONS, bypassProviders, locking);
}

//////////////////////////////////////////////////////////////////////////////
CIMOMHandleIFCRef
CIMOMEnvironment::getCIMOMHandle(OperationContext& context,
	ESendIndicationsFlag sendIndications,
	EBypassProvidersFlag bypassProviders,
	ELockingFlag locking) const
{
	{
		MutexLock l(m_stateGuard);
		if (!isLoaded(m_state))
		{
			OW_THROW(CIMOMEnvironmentException, "CIMOMEnvironment::getCIMOMHandle() called when state is not loaded.");
		}
	}
	MutexLock ml(m_monitor);
	OW_ASSERT(m_cimServer);

	// Here we construct a pipeline.  Currently it looks like:
	// LocalCIMOMHandle -> [ Authorizer -> ] [Indication Rep Layer -> ] [ CIM Server -> ] CIM Repository

	RepositoryIFCRef rref;
	if (bypassProviders == E_BYPASS_PROVIDERS)
	{
		rref = m_cimRepository;
	}
	else
	{
		rref = m_cimServer;
	}

	if (sendIndications == E_SEND_INDICATIONS && m_indicationServer && !m_indicationsDisabled)
	{
		SharedLibraryRepositoryIFCRef irl = _getIndicationRepLayer(rref);
		if (irl)
		{
			rref = RepositoryIFCRef(new SharedLibraryRepository(irl));
		}
	}
	if (m_authorizer)
	{
		AuthorizerIFC* p = m_authorizer->clone();
		p->setSubRepositoryIFC(rref);
		rref = RepositoryIFCRef(new SharedLibraryRepository(SharedLibraryRepositoryIFCRef(m_authorizer.getLibRef(), RepositoryIFCRef(p))));
	}

	return CIMOMHandleIFCRef(new LocalCIMOMHandle(const_cast<CIMOMEnvironment*>(this), rref,
		context, locking == E_LOCKING ? LocalCIMOMHandle::E_LOCKING : LocalCIMOMHandle::E_NO_LOCKING));
}
//////////////////////////////////////////////////////////////////////////////
WQLIFCRef
CIMOMEnvironment::getWQLRef() const
{
	{
		MutexLock l(m_stateGuard);
		if (!isLoaded(m_state))
		{
			OW_THROW(CIMOMEnvironmentException, "CIMOMEnvironment::getWQLRef() called when state is not loaded");
		}
	}
	MutexLock ml(m_monitor);
	if (!m_wqlLib)
	{
		String libname = getConfigItem(ConfigOpts::WQL_LIB_opt, OW_DEFAULT_WQL_LIB);
		OW_LOG_DEBUG(m_Logger, Format("CIMOM loading wql library %1", libname));
		SharedLibraryLoaderRef sll =
			SharedLibraryLoader::createSharedLibraryLoader();
		m_wqlLib = sll->loadSharedLibrary(libname, m_Logger);
		if (!m_wqlLib)
		{
			OW_LOG_ERROR(m_Logger, Format("CIMOM Failed to load WQL Libary: %1", libname));
			return WQLIFCRef();
		}
	}
	return  WQLIFCRef(m_wqlLib, SafeLibCreate<WQLIFC>::create(
		m_wqlLib, "createWQL", m_Logger));
}
//////////////////////////////////////////////////////////////////////////////
SharedLibraryRepositoryIFCRef
CIMOMEnvironment::_getIndicationRepLayer(const RepositoryIFCRef& rref) const
{
	SharedLibraryRepositoryIFCRef retref;
	if (!m_indicationRepLayerDisabled)
	{
		MutexLock ml(m_indicationLock);
		if (!m_indicationRepLayerLib)
		{
			const String libPath = getConfigItem(ConfigOpts::OWLIBDIR_opt, OW_DEFAULT_OWLIBDIR) + OW_FILENAME_SEPARATOR;
			const String libBase = "libowindicationreplayer";
			String libname = libPath + libBase + OW_SHAREDLIB_EXTENSION;
			OW_LOG_DEBUG(m_Logger, Format("CIMOM loading indication libary %1",
				libname));
			SharedLibraryLoaderRef sll =
				SharedLibraryLoader::createSharedLibraryLoader();

			if (!sll)
			{
				m_indicationRepLayerDisabled = true;
				OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM failed to create SharedLibraryLoader"
					" library %1", libname));
				return retref;
			}
			m_indicationRepLayerLib = sll->loadSharedLibrary(libname, m_Logger);
			if (!m_indicationRepLayerLib)
			{
				m_indicationRepLayerDisabled = true;
				OW_LOG_FATAL_ERROR(m_Logger, Format("CIMOM failed to load indication rep layer"
					" library %1", libname));
				return retref;
			}
		}
		IndicationRepLayer* pirep =
			SafeLibCreate<IndicationRepLayer>::create(
				m_indicationRepLayerLib, "createIndicationRepLayer", m_Logger);
		if (pirep)
		{
			retref = SharedLibraryRepositoryIFCRef(m_indicationRepLayerLib,
				RepositoryIFCRef(pirep));
			pirep->setCIMServer(rref);
		}
		else
		{
			m_indicationRepLayerDisabled = true;
			m_indicationRepLayerLib = 0;
		}
	}
	return retref;
}

//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_loadAuthorizer()
{
	OW_ASSERT(!m_authorizer);
	String libname = getConfigItem(ConfigOpts::AUTHORIZATION_LIB_opt);

	// no authorization requested
	if (libname.empty())
	{
		return;
	}

	OW_LOG_DEBUG(m_Logger, Format("CIMOM loading authorization libary %1",
					libname));
	SharedLibraryLoaderRef sll =
		SharedLibraryLoader::createSharedLibraryLoader();
	if (!sll)
	{
		String msg = Format("CIMOM failed to create SharedLibraryLoader."
							" library %1", libname);
		OW_LOG_FATAL_ERROR(m_Logger, msg);
		OW_THROW(CIMOMEnvironmentException, msg.c_str());
	}
	SharedLibraryRef authorizerLib = sll->loadSharedLibrary(libname, m_Logger);
	if (!authorizerLib)
	{
		String msg = Format("CIMOM failed to load authorization"
							" library %1", libname);
		OW_LOG_FATAL_ERROR(m_Logger, msg);
		OW_THROW(CIMOMEnvironmentException, msg.c_str());
	}
	AuthorizerIFC* p =
		SafeLibCreate<AuthorizerIFC>::create(
			authorizerLib, "createAuthorizer", m_Logger);
	if (!p)
	{
		String msg = Format("CIMOM failed to load authorization"
							" library %1", libname);
		OW_LOG_FATAL_ERROR(m_Logger, msg);
		OW_THROW(CIMOMEnvironmentException, msg.c_str());
	}
	m_authorizer = AuthorizerIFCRef(authorizerLib,
									AuthorizerIFCRef::element_type(p));

	m_services.push_back(m_authorizer);
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_createAuthorizerManager()
{
	// m_authorizerManager should actually be a valid AuthorizerManager
	// already, but it doesn't have a authorizer loaded yet.
	// It is also already added to the m_services array.

	String libname = getConfigItem(ConfigOpts::AUTHORIZATION2_LIB_opt);

	// no authorization requested
	if (libname.empty())
	{
		return;
	}

	OW_LOG_DEBUG(m_Logger, Format("CIMOM loading authorization libary %1", libname));

	SharedLibraryLoaderRef sll =
		SharedLibraryLoader::createSharedLibraryLoader();
	if (!sll)
	{
		String msg = Format("CIMOM failed to create SharedLibraryLoader."
			" library %1", libname);
		OW_LOG_FATAL_ERROR(m_Logger, msg);
		OW_THROW(CIMOMEnvironmentException, msg.c_str());
	}
	SharedLibraryRef authorizerLib = sll->loadSharedLibrary(libname, m_Logger);
	if (!authorizerLib)
	{
		String msg = Format("CIMOM failed to load authorization"
			" library %1", libname);
		OW_LOG_FATAL_ERROR(m_Logger, msg);
		OW_THROW(CIMOMEnvironmentException, msg.c_str());
	}
	Authorizer2IFC* p =
		SafeLibCreate<Authorizer2IFC>::create(
			authorizerLib, "createAuthorizer2", m_Logger);
	if (!p)
	{
		String msg = Format("CIMOM failed to load authorization"
			" library %1", libname);
		OW_LOG_FATAL_ERROR(m_Logger, msg);
		OW_THROW(CIMOMEnvironmentException, msg.c_str());
	}

	m_authorizerManager->setAuthorizer(
		Authorizer2IFCRef(authorizerLib,Authorizer2IFCRef::element_type(p)));
}
//////////////////////////////////////////////////////////////////////////////
RequestHandlerIFCRef
CIMOMEnvironment::getRequestHandler(const String &id) const
{
	RequestHandlerIFCRef ref;
	{
		MutexLock l(m_stateGuard);
		if (!isInitialized(m_state))
		{
			return ref;
		}
	}
	MutexLock ml(m_reqHandlersLock);
	ReqHandlerMap::iterator iter =
			m_reqHandlers.find(id);
	if (iter != m_reqHandlers.end())
	{
		if (!iter->second->rqIFCRef)
		{
			iter->second->rqIFCRef =
				SafeLibCreate<RequestHandlerIFC>::loadAndCreateObject(
					iter->second->filename, "createRequestHandler", getLogger(COMPONENT_NAME));

			iter->second->rqIFCRef->setEnvironment(const_cast<CIMOMEnvironment*>(this));
			iter->second->rqIFCRef->init(const_cast<CIMOMEnvironment*>(this));
			
			// re-add it to m_services and resort them.
			m_services.push_back(iter->second->rqIFCRef);
			const_cast<CIMOMEnvironment*>(this)->_sortServicesForDependencies();
		}
		if (iter->second->rqIFCRef)
		{
			ref = RequestHandlerIFCRef(iter->second->rqIFCRef.getLibRef(),
				iter->second->rqIFCRef->clone());
			iter->second->dt.setToCurrent();
			ref->setEnvironment(const_cast<CIMOMEnvironment*>(this));
			OW_LOG_DEBUG(m_Logger, Format("Request Handler %1 handling request for content type %2",
				iter->second->filename, id));
		}
		else
		{
			OW_LOG_ERROR(m_Logger, Format(
				"Error loading request handler library %1 for content type %2",
				iter->second->filename, id));
		}
	}
	return ref;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::unloadReqHandlers()
{
	//OW_LOG_DEBUG(m_Logger, "Running unloadReqHandlers()");
	Int32 ttl = 0;
	try
	{
		ttl = getConfigItem(ConfigOpts::REQUEST_HANDLER_TTL_opt, OW_DEFAULT_REQUEST_HANDLER_TTL).toInt32();
	}
	catch (const StringConversionException&)
	{
		OW_LOG_ERROR(m_Logger, Format("Invalid value (%1) for %2 config item.",
			getConfigItem(ConfigOpts::REQUEST_HANDLER_TTL_opt, OW_DEFAULT_REQUEST_HANDLER_TTL),
			ConfigOpts::REQUEST_HANDLER_TTL_opt));
	}
	if (ttl < 0)
	{
		OW_LOG_DEBUG(m_Logger, "Non-Positive TTL for Request Handlers: OpenWBEM will not unload request handlers.");
		return;
	}
	DateTime dt;
	dt.setToCurrent();
	MutexLock ml(m_reqHandlersLock);
	for (ReqHandlerMap::iterator iter = m_reqHandlers.begin();
		  iter != m_reqHandlers.end(); ++iter)
	{
		if (iter->second->rqIFCRef)
		{
			DateTime rqDT = iter->second->dt;
			rqDT.addMinutes(ttl);
			if (rqDT < dt)
			{
				// remove it from m_services
				for (size_t i = 0; i < m_services.size(); ++i)
				{
					if (m_services[i].get() == iter->second->rqIFCRef.get())
					{
						m_services.remove(i);
						break;
					}
				}
				iter->second->rqIFCRef.setNull();
				OW_LOG_DEBUG(m_Logger, Format("Unloaded request handler lib %1 for content type %2",
					iter->second->filename, iter->first));
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
LoggerRef
CIMOMEnvironment::getLogger() const
{
	OW_ASSERT(m_Logger);
	return m_Logger->clone();
}
//////////////////////////////////////////////////////////////////////////////
LoggerRef
CIMOMEnvironment::getLogger(const String& componentName) const
{
	OW_ASSERT(m_Logger);
	LoggerRef rv(m_Logger->clone());
	rv->setDefaultComponent(componentName);
	return rv;
}
//////////////////////////////////////////////////////////////////////////////
IndicationServerRef
CIMOMEnvironment::getIndicationServer() const
{
	return m_indicationServer;
}
//////////////////////////////////////////////////////////////////////////////
PollingManagerRef
CIMOMEnvironment::getPollingManager() const
{
	return m_pollingManager;
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::clearConfigItems()
{
	m_configItems->clear();
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::setConfigItem(const String &item,
	const String &value, EOverwritePreviousFlag overwritePrevious)
{
	ConfigFile::setConfigItem(*m_configItems, item, value, 
		overwritePrevious == E_OVERWRITE_PREVIOUS ? ConfigFile::E_OVERWRITE_PREVIOUS : ConfigFile::E_PRESERVE_PREVIOUS);
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::runSelectEngine() const
{
	OW_ASSERT(m_selectables.size() == m_selectableCallbacks.size());
	SelectEngine engine;
	// Insure the signal pipe is at the front of the select list
	engine.addSelectableObject(Platform::getSigSelectable(),
		SelectableCallbackIFCRef(new SelectEngineStopper(engine)));
	
	for (size_t i = 0; i < m_selectables.size(); ++i)
	{
		engine.addSelectableObject(m_selectables[i], m_selectableCallbacks[i]);
	}
	engine.go();
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_clearSelectables()
{
	MutexLock ml(m_selectableLock);
	m_selectables.clear();
	m_selectableCallbacks.clear();
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::addSelectable(const SelectableIFCRef& obj,
	const SelectableCallbackIFCRef& cb)
{
	MutexLock ml(m_selectableLock);
	m_selectables.push_back(obj);
	m_selectableCallbacks.push_back(cb);
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::removeSelectable(const SelectableIFCRef& obj)
{
	MutexLock ml(m_selectableLock);
    for (size_t i = 0; i < m_selectables.size(); i++)
    {
        if (obj == m_selectables[i])
        {
            m_selectables.remove(i);
            m_selectableCallbacks.remove(i);
            --i;
            continue;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::exportIndication(const CIMInstance& instance,
	const String& instNS)
{
	OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment::exportIndication");
	if (m_indicationServer && !m_indicationsDisabled)
	{
		OW_LOG_DEBUG(m_Logger, "CIMOMEnvironment::exportIndication - calling indication"
			" server");
		m_indicationServer->processIndication(instance, instNS);
	}
}
//////////////////////////////////////////////////////////////////////////////
IndicationRepLayerMediatorRef
CIMOMEnvironment::getIndicationRepLayerMediator() const
{
	return m_indicationRepLayerMediatorRef;
}
//////////////////////////////////////////////////////////////////////////////
RepositoryIFCRef
CIMOMEnvironment::getRepository() const
{
	return m_cimRepository;
}
//////////////////////////////////////////////////////////////////////////////
AuthorizerManagerRef
CIMOMEnvironment::getAuthorizerManager() const
{
	return m_authorizerManager;
}

//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::unloadProviders()
{
	m_providerManager->unloadProviders(createProvEnvRef(this));
}

namespace
{

//////////////////////////////////////////////////////////////////////////////
struct Node
{
	Node(const String& name_, size_t index_ = ~0)
		: name(name_)
		, index(index_)
	{}

	String name;
	size_t index;
};

//////////////////////////////////////////////////////////////////////////////
bool operator!=(const Node& x, const Node& y)
{
	return x.name != y.name;
}

//////////////////////////////////////////////////////////////////////////////
bool operator<(const Node& x, const Node& y)
{
	return x.name < y.name;
}

//////////////////////////////////////////////////////////////////////////////
Node INVALID_NODE("", ~0);

//////////////////////////////////////////////////////////////////////////////
class ServiceDependencyGraph
{
public:
	// returns false if serviceName has already been inserted, true otherwise
	bool addNode(const String& serviceName, size_t index);
	// returns false if serviceName already has a dependency on dependentServiceName, true otherwise
	// precondition: a node for serviceName has already been added via addNode()
	bool addDependency(const String& serviceName, const String& dependentServiceName);
	Node findIndependentNode() const;
	void removeNode(const String& serviceName);
	bool empty() const;
	Array<Node> getNodes() const;

private:
	typedef std::map<Node, std::set<String> > deps_t;
	deps_t m_deps;
};

//////////////////////////////////////////////////////////////////////////////
bool
ServiceDependencyGraph::addNode(const String& serviceName, size_t index)
{
	return m_deps.insert(std::make_pair(Node(serviceName, index), deps_t::mapped_type())).second;
}

//////////////////////////////////////////////////////////////////////////////
bool
ServiceDependencyGraph::addDependency(const String& serviceName, const String& dependentServiceName)
{
	return m_deps.find(serviceName)->second.insert(dependentServiceName).second;
}

//////////////////////////////////////////////////////////////////////////////
Node
ServiceDependencyGraph::findIndependentNode() const
{
	for (deps_t::const_iterator nodeiter(m_deps.begin()); nodeiter != m_deps.end(); ++nodeiter)
	{
		if (nodeiter->second.empty())
		{
			return nodeiter->first;
		}
	}
	
	// didn't find any :-(
	return INVALID_NODE;
}

//////////////////////////////////////////////////////////////////////////////
void
ServiceDependencyGraph::removeNode(const String& serviceName)
{
	// remove it from all dependency lists
	for (deps_t::iterator nodeiter(m_deps.begin()); nodeiter != m_deps.end(); ++nodeiter)
	{
		nodeiter->second.erase(serviceName);
	}
	m_deps.erase(serviceName);
}

//////////////////////////////////////////////////////////////////////////////
bool
ServiceDependencyGraph::empty() const
{
	return m_deps.empty();
}

//////////////////////////////////////////////////////////////////////////////
Array<Node>
ServiceDependencyGraph::getNodes() const
{
	Array<Node> rv;
	rv.reserve(m_deps.size());
	for (deps_t::const_iterator nodeiter(m_deps.begin()); nodeiter != m_deps.end(); ++nodeiter)
	{
		rv.push_back(nodeiter->first);
	}
	return rv;
}

} // end anonymous namespace

//////////////////////////////////////////////////////////////////////////////
void
CIMOMEnvironment::_sortServicesForDependencies()
{
	// All services can specify a name and dependencies. If a service has an empty name, it can't be specified
	// as a dependency, and our algorithm requires that each service has a name, so if any have an empty name,
	// they'll just be put at the beginning of the list.

	// We need to make sure that a service is initialized before any other services which depend on it.
	// The depedencies reported by the services make a graph.  If it's not a DAG (i.e. contains cycles), we
	// can't turn it into a list of what to do, and we'll detect that and throw an exception. Doing a topological
	// sort on the graph will yield the order we need.
	//
	// The process is quite simple conceptually:
	// while (the graph has a node with no antecedents)
	//    remove one such node from the graph and add it to the list
	//
	// if (the graph is not empty)
	//    the graph contains a cycle
	// else
	//    success
	
	Array<ServiceIFCRef> sortedServices;

	// first build the graph
	ServiceDependencyGraph depGraph;
	// step 1 insert all the nodes and handle the no-names.
	for (size_t i = 0; i < m_services.size(); ++i)
	{
		String name = m_services[i]->getName();
		if (name == "")
		{
			// no name == no depedency tracking, just do it at the beginning.
			sortedServices.push_back(m_services[i]);
			OW_LOG_DEBUG(m_Logger, "Found service with no name, adding to sortedServices");
		}
		else
		{
			OW_LOG_DEBUG(m_Logger, Format("Adding node for service %1", name));
			if (!depGraph.addNode(name, i))
			{
				OW_THROW(CIMOMEnvironmentException, Format("Invalid: 2 services with the same name: %1", name).c_str());
			}
			
		}
	}

	// step 2 insert all the dependencies
	for (size_t i = 0; i < m_services.size(); ++i)
	{
		String name = m_services[i]->getName();
		if (name != "")
		{
			StringArray deps(m_services[i]->getDependencies());
			for (size_t j = 0; j < deps.size(); ++j)
			{
				OW_LOG_DEBUG(m_Logger, Format("Adding dependency for service %1->%2", name, deps[j]));
				if (!depGraph.addDependency(name, deps[j]))
				{
					OW_THROW(CIMOMEnvironmentException, Format("Invalid: service %1 has duplicate dependencies: %2", name, deps[j]).c_str());
				}
			}

			// these are just the opposite direction than the dependencies
			StringArray dependentServices(m_services[i]->getDependentServices());
			for (size_t j = 0; j < dependentServices.size(); ++j)
			{
				OW_LOG_DEBUG(m_Logger, Format("Adding dependency for service %1->%2", dependentServices[j], name));
				if (!depGraph.addDependency(dependentServices[j], name))
				{
					OW_THROW(CIMOMEnvironmentException, Format("Invalid: service %1 has duplicate dependencies: %2", dependentServices[j], name).c_str());
				}
			}
		}
	}

	// now do the topological sort
	Node curNode = depGraph.findIndependentNode();
	while (curNode != INVALID_NODE)
	{
		OW_LOG_DEBUG(m_Logger, Format("Found service with satisfied dependencies: %1", curNode.name));
		sortedServices.push_back(m_services[curNode.index]);
		depGraph.removeNode(curNode.name);
		curNode = depGraph.findIndependentNode();
	}

	if (!depGraph.empty())
	{
		OW_LOG_FATAL_ERROR(m_Logger, "Service dependency graph contains a cycle:");
		Array<Node> nodes(depGraph.getNodes());
		for (size_t i = 0; i < nodes.size(); ++i)
		{
			OW_LOG_FATAL_ERROR(m_Logger, Format("Service: %1", nodes[i].name));
		}
		OW_THROW(CIMOMEnvironmentException, "Service dependency graph contains a cycle");
	}

	m_services = sortedServices;
}

} // end namespace OW_NAMESPACE

