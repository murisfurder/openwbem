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
 * @author Bart Whiteley
 */

#include "OW_config.h"
#include "OW_CIMOMEnvironment.hpp"
#include "OW_ConfigOpts.hpp"
#include "OW_Platform.hpp"
#include "OW_PlatformSignal.hpp"
#include "OW_Assertion.hpp"
#include "OW_Format.hpp"
#include "OW_Logger.hpp"
#include "OW_CerrLogger.hpp"
#include "OW_CmdLineParser.hpp"

#include <exception>
#include <iostream> // for cout
#include <new> // for new handler stuff

#ifdef OW_USE_DL
#include "OW_dlSharedLibrary.hpp"
#endif

using namespace OpenWBEM;


namespace
{
	enum
	{
		E_HELP_OPT,
		E_VERSION_OPT,
		E_LIBRARY_VERSION_OPT,
		E_DEBUG_MODE_OPT,
		E_CONFIG_FILE_OPT
	};
	const CmdLineParser::Option g_options[] =
		{
			{E_HELP_OPT, 'h', "help", CmdLineParser::E_NO_ARG, 0, "Show help about options and exit"},
			{E_VERSION_OPT, 'v', "version", CmdLineParser::E_NO_ARG, 0, "Show version information and exit"},
			{E_LIBRARY_VERSION_OPT, 'l', "libversion", CmdLineParser::E_NO_ARG, 0, "Show the required OpenWBEM library version and exit"},
			{E_DEBUG_MODE_OPT, 'd', "debug", CmdLineParser::E_NO_ARG, 0, "Use debug mode (does not detach from terminal)"},
			{E_CONFIG_FILE_OPT, 'c', "config", CmdLineParser::E_REQUIRED_ARG, 0, "Use <arg> instead of the default config file"},
			{0, 0, 0, CmdLineParser::E_NO_ARG, 0, 0}
		};

	// Process the command line, setting appropriate options in the cimom environment.
	void processCommandLine(int argc, char* argv[],	CIMOMEnvironmentRef env);
	void printUsage(std::ostream& ostrm);

	const String COMPONENT_NAME("ow.owcimomd");
}

void owcimomd_new_handler();

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    int rval = 0;
	CIMOMEnvironmentRef env = CIMOMEnvironment::instance();

	// until the config file is read and parsed, just use a logger that prints everything to stderr.
	LoggerRef logger(new CerrLogger());

	try
	{
		processCommandLine(argc, argv, env);
		// Initilize the cimom environment object
		env->init();

		// debug mode can be activated by -d or by the config file, so check both. The config file is loaded by env->init().
		bool debugMode = env->getConfigItem(ConfigOpts::DEBUGFLAG_opt, OW_DEFAULT_DEBUGFLAG).equalsIgnoreCase("true");

		// logger's not set up according to the config file until after init()
		logger = env->getLogger(COMPONENT_NAME);
		OW_LOG_INFO(logger, "owcimomd (" OW_VERSION ") beginning startup");

#ifdef OW_USE_DL
		if (env->getConfigItem("owcimomd.dont_call_dlclose", "false").equalsIgnoreCase("true"))
		{
			dlSharedLibrary::setCallDlclose(false);
		}
#endif

		// Call platform specific code to become a daemon/service
		try
		{
			Platform::daemonize(debugMode, OW_DAEMON_NAME, env);
		}
		catch (const DaemonException& e)
		{
			OW_LOG_FATAL_ERROR(logger, e.getMessage());
			OW_LOG_FATAL_ERROR(logger, "owcimomd failed to initialize. Aborting...");
			return 1;
		}
		// Start all of the cimom services
		env->startServices();
		OW_LOG_INFO(logger, "owcimomd is now running!");

		// Do this after initialization to prevent an infinite loop.
		std::unexpected_handler oldUnexpectedHandler = 0;
		std::terminate_handler oldTerminateHandler = 0;
		std::new_handler oldNewHandler = std::set_new_handler(owcimomd_new_handler);

		if (env->getConfigItem(ConfigOpts::RESTART_ON_ERROR_opt, OW_DEFAULT_RESTART_ON_ERROR).equalsIgnoreCase("true"))
		{
			const char* const restartDisabledMessage =
				"WARNING: even though the owcimomd.restart_on_error config option = true, it\n"
				"is not enabled. Possible reasons are that OpenWBEM is built in debug mode,\n"
				"owcimomd is running in debug mode (-d), or owcimomd was not run using an\n"
				"absolute path (argv[0][0] != '/')";

			// only do this in production mode. During development we want it to crash!
#if !defined(OW_DEBUG)
			if ((debugMode == false) && argv[0][0] == '/') // if argv[0][0] != '/' the restart will not be predictable
			{
				Platform::installFatalSignalHandlers();
				oldUnexpectedHandler = std::set_unexpected(Platform::rerunDaemon);
				oldTerminateHandler = std::set_terminate(Platform::rerunDaemon);
			}
			else
			{
				OW_LOG_INFO(logger, restartDisabledMessage);
			}
#else
			OW_LOG_INFO(logger, restartDisabledMessage);
#endif
		}

		int sig;
		bool shuttingDown(false);

		Platform::sendDaemonizeStatus(Platform::DAEMONIZE_SUCCESS);
		while (!shuttingDown)
		{
			// runSelectEngine will only return once something has been put into
			// the signal pipe or an error has happened
			env->runSelectEngine();
			Platform::Signal::SignalInformation signalInfo;

			sig = Platform::popSig(signalInfo);
			switch (sig)
			{
				case Platform::SHUTDOWN:

					OW_LOG_INFO(logger, "owcimomd received shutdown notification."
						" Initiating shutdown");
					OW_LOG_INFO(logger, Format("signal details:\n%1", signalInfo));
					shuttingDown = true;


#if !defined(OW_DEBUG)
					// need to remove them so we don't restart while shutting down.
					Platform::removeFatalSignalHandlers();
					if (oldUnexpectedHandler)
					{
						std::set_unexpected(oldUnexpectedHandler);
					}
					if (oldTerminateHandler)
					{
						std::set_terminate(oldTerminateHandler);
					}
#endif

					env->shutdown();
					break;
				case Platform::REINIT:
					OW_LOG_INFO(logger, "owcimomd received restart notification."
						" Initiating restart");
					OW_LOG_INFO(logger, Format("signal details: %1", signalInfo));
					env->shutdown();
					env->clearConfigItems();
					env = CIMOMEnvironment::instance() = 0;
					// don't try to catch the DeamonException, because if it's thrown, stuff is so whacked, we should just exit!
					Platform::rerunDaemon();

					// typically on *nix, restartDaemon() doesn't return, however to account for environments where
					// it won't we'll leave this code here to re-initialize.
					env = CIMOMEnvironment::instance() = new CIMOMEnvironment;
					processCommandLine(argc, argv, env);
					env->init();
					env->startServices();
					break;
				default:
					OW_LOG_INFO(logger, Format("Ignoring signal. Details: %1", signalInfo));
					break;
			}
		}
	}
	catch (Exception& e)
	{
		OW_LOG_FATAL_ERROR(logger, "* EXCEPTION CAUGHT IN owcimomd MAIN!");
		OW_LOG_FATAL_ERROR(logger, Format("* %1", e));
		Platform::sendDaemonizeStatus(Platform::DAEMONIZE_FAIL);
		rval = 1;
	}
	catch (std::exception& se)
	{
		OW_LOG_FATAL_ERROR(logger, "* std::exception CAUGHT IN owcimomd MAIN!");
		OW_LOG_FATAL_ERROR(logger, Format("* Message: %1", se.what()));
		Platform::sendDaemonizeStatus(Platform::DAEMONIZE_FAIL);
		rval = 1;
	}
	catch(...)
	{
		OW_LOG_FATAL_ERROR(logger, "* UNKNOWN EXCEPTION CAUGHT owcimomd MAIN!");
		Platform::sendDaemonizeStatus(Platform::DAEMONIZE_FAIL);
		rval = 1;
	}
	// Call platform specific shutdown routine
	Platform::daemonShutdown(OW_DAEMON_NAME, env);

	CIMOMEnvironment::instance() = env = 0;
	
	OW_LOG_INFO(logger, "owcimomd has shutdown");
	return rval;
}

namespace
{

//////////////////////////////////////////////////////////////////////////////
void
processCommandLine(int argc, char* argv[], CIMOMEnvironmentRef env)
{
	// Give store a copy of the initial arguments for later use (should we need
	// to restart).
	Platform::daemonInit(argc, argv);

	try
	{
		CmdLineParser parser(argc, argv, g_options, CmdLineParser::E_NON_OPTION_ARGS_INVALID);

		//
		// Options that will cause the cimom to exit.
		//
		if (parser.isSet(E_HELP_OPT))
		{
			printUsage(std::cout);
			exit(0);
		}
		else if (parser.isSet(E_VERSION_OPT))
		{
			std::cout << OW_DAEMON_NAME " from " OW_PACKAGE_STRING << std::endl;
			exit(0);
		}
		else if (parser.isSet(E_LIBRARY_VERSION_OPT))
		{
#define STRINGIFY_ARGUMENT(x) #x
#define STRINGIFY_DEFINITION_VALUE(x) STRINGIFY_ARGUMENT(x)
			std::cout << STRINGIFY_DEFINITION_VALUE(OW_OPENWBEM_LIBRARY_VERSION) << std::endl;
#undef STRINGIFY_ARGUMENT
#undef STRINGIFY_DEFINITION_VALUE
			exit(0);
		}

		//
		// Options that will change the behavior of the CIMOM
		//
		if (parser.isSet(E_DEBUG_MODE_OPT))
		{
			env->setConfigItem(ConfigOpts::DEBUGFLAG_opt, "true", ServiceEnvironmentIFC::E_PRESERVE_PREVIOUS);
			env->setConfigItem(ConfigOpts::LOG_LEVEL_opt, "debug");
		}
		if (parser.isSet(E_CONFIG_FILE_OPT))
		{
			env->setConfigItem(ConfigOpts::CONFIG_FILE_opt, parser.getOptionValue(E_CONFIG_FILE_OPT));
		}
	}
	catch (const CmdLineParserException& e)
	{
		switch (e.getErrorCode())
		{
			case CmdLineParser::E_INVALID_OPTION:
				std::cerr << "Invalid option: " << e.getMessage() << std::endl;
				break;
			case CmdLineParser::E_MISSING_ARGUMENT:
				std::cerr << "Argument not specified for option: " << e.getMessage() << std::endl;
				break;
		}
		printUsage(std::cerr);
		exit(1);
	}
}

//////////////////////////////////////////////////////////////////////////////
void
printUsage(std::ostream& ostrm)
{
	ostrm << OW_DAEMON_NAME << " [OPTIONS]..." << std::endl;
	ostrm << CmdLineParser::getUsage(g_options) << std::endl;
}

} // end unnamed namespace
//////////////////////////////////////////////////////////////////////////////
void owcimomd_new_handler()
{
#if defined (OW_DEBUG)  || defined (OW_NETWARE)
	abort();
#endif

	Platform::restartDaemon();
	throw std::bad_alloc();
}

