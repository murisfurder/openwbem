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
#include "OW_Platform.hpp"
#include "OW_ConfigOpts.hpp"
#include "OW_Format.hpp"
#include "OW_PidFile.hpp"
#include "OW_ExceptionIds.hpp"
#include "OW_PlatformSignal.hpp"
#include "OW_ServiceEnvironmentIFC.hpp"
#include "OW_Logger.hpp"

#ifdef OW_NETWARE
#include "OW_Condition.hpp"
#include "OW_NonRecursiveMutex.hpp"
#include "OW_NonRecursiveMutexLock.hpp"
#endif

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#if defined(OW_HAVE_GETOPT_H) && !defined(OW_GETOPT_AND_UNISTD_CONFLICT)
#include <getopt.h>
#else
#include <stdlib.h> // for getopt on Solaris
#endif
#ifdef WIN32
#include <process.h>
#define getpid _getpid
#else
#include <unistd.h> // for getpid, getuid, etc.
#endif
#include <signal.h>
#include <fcntl.h>
#if defined (OW_HAVE_PWD_H)
#include <pwd.h>
#endif
#if defined (OW_HAVE_SYS_RESOURCE_H)
#include <sys/resource.h>
#endif
#if defined(OW_HAVE_GRP_H)
#include <grp.h>
#endif

#ifdef OW_NETWARE
#include <nks/vm.h>
#include <nks/netware.h>
#include <netware.h>
#include <event.h>
#include <library.h>
#endif
}
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

namespace OW_NAMESPACE
{

using std::ostream;
using std::endl;

OW_DEFINE_EXCEPTION_WITH_ID(Daemon);

namespace Platform
{

extern "C" {
static void theSigHandler(int sig, siginfo_t* info, void* context);
}

namespace
{
const String COMPONENT_NAME("ow.owcimomd");

const int DAEMONIZE_PIPE_TIMEOUT = 25;

void handleSignal(int sig);
void setupSigHandler(bool dbgFlg);

UnnamedPipeRef plat_upipe;

UnnamedPipeRef daemonize_upipe;

char** g_argv = 0;

#ifdef OW_NETWARE
Condition g_shutdownCond;
bool g_shutDown = false;
NonRecursiveMutex g_shutdownGuard;
void* WarnFuncRef = NULL;
rtag_t EventRTag;
event_handle_t DownEvent;
bool FromEventHandler = false;
#endif

}

//////////////////////////////////////////////////////////////////////////////
void
daemonInit( int argc, char* argv[] )
{
	g_argv = argv;
}
/**
 * daemonize() - detach process from user and disappear into the background
 * Throws DaemonException on error.
 */
void
daemonize(bool dbgFlg, const String& daemonName, const ServiceEnvironmentIFCRef& env)
{
#ifndef WIN32
#ifdef OW_NETWARE
	{
		NonRecursiveMutexLock l(g_shutdownGuard);
		g_shutDown = false;
	}
#endif
	initDaemonizePipe();

	// If we're running as root and owcimomd.drop_root_privileges != "false", then try to switch users/groups to owcimomd/owcimomd
	if (geteuid() == 0 && !env->getConfigItem(ConfigOpts::DROP_ROOT_PRIVILEGES_opt, OW_DEFAULT_DROP_ROOT_PRIVILEGES).equalsIgnoreCase("false"))
	{
		const char OWCIMOMD_USER[] = "owcimomd";
		// dont need to worry about thread safety here, the threads won't start until later.
		struct passwd* owcimomdInfo = ::getpwnam(OWCIMOMD_USER);
		if (!owcimomdInfo)
		{
			OW_THROW_ERRNO_MSG(DaemonException, "Platform::daemonize(): getpwnam(\"owcimomd\")");
		}
		if (::setgid(owcimomdInfo->pw_gid) != 0)
		{
			OW_THROW_ERRNO_MSG(DaemonException, "Platform::daemonize(): setgid");
		}
		if (::initgroups(owcimomdInfo->pw_name, owcimomdInfo->pw_gid) != 0)
		{
			OW_THROW_ERRNO_MSG(DaemonException, "Platform::daemonize(): initgroups");
		}
		if (::setuid(owcimomdInfo->pw_uid) != 0)
		{
			OW_THROW_ERRNO_MSG(DaemonException, "Platform::daemonize(): setuid");
		}
	}


	int pid = -1;
#if !defined(OW_NETWARE)
	String pidFile(env->getConfigItem(ConfigOpts::PIDFILE_opt, OW_DEFAULT_PIDFILE));
	pid = PidFile::checkPid(pidFile.c_str());
	// Is there already another instance of the cimom running?
	if (pid != -1)
	{
		OW_THROW(DaemonException,
			Format("Another instance of %1 is already running [%2]",
				daemonName, pid).c_str());
	}
#endif
	if (!dbgFlg)
	{
#if !defined(OW_NETWARE) && !defined(WIN32)
		pid = fork();
		switch (pid)
		{
			case 0:
				break;
			case -1:
				OW_THROW_ERRNO_MSG(DaemonException,
					"FAILED TO DETACH FROM THE TERMINAL - First fork");
			default:
				int status = DAEMONIZE_FAIL;
				if (daemonize_upipe->readInt(&status) < 1
						|| status != DAEMONIZE_SUCCESS)
				{
					cerr << "Error starting CIMOM.  Check the log files." << endl;
					_exit(1);
				}
				_exit(0); // exit the original process
		}
		if (setsid() < 0)					  // shoudn't fail on linux
		{
			OW_THROW(DaemonException,
				"FAILED TO DETACH FROM THE TERMINAL - setsid failed");
		}
		pid = fork();
		switch (pid)
		{
			case 0:
				break;
			case -1:
				{
					// Save the error number, since the sendDaemonizeStatus function can cause it to change.
					int saved_errno = errno;
					sendDaemonizeStatus(DAEMONIZE_FAIL);
					// Restore the real error number.
					errno = saved_errno;
					OW_THROW_ERRNO_MSG(DaemonException,
						"FAILED TO DETACH FROM THE TERMINAL - Second fork");
					exit(1);
				}
			default:
				_exit(0);
		}
#endif
		chdir("/");
		close(0);
		close(1);
		close(2);
		open("/dev/null", O_RDONLY);
		open("/dev/null", O_WRONLY);
		dup(1);
	}
	else
	{
		pid = getpid();
	}
	umask(0077); // ensure all files we create are only accessible by us.
#if !defined(OW_NETWARE)
	if (PidFile::writePid(pidFile.c_str()) == -1)
	{
		// Save the error number, since the sendDaemonizeStatus function can cause it to change.
		int saved_errno = errno;
		sendDaemonizeStatus(DAEMONIZE_FAIL);
		// Restore the real error number.
		errno = saved_errno;
		OW_THROW_ERRNO_MSG(DaemonException,
			Format("Failed to write the pid file (%1)", pidFile).c_str());
	}
#endif
	OW_LOG_INFO(env->getLogger(COMPONENT_NAME), Format("Platform::daemonize() pid = %1", ::getpid()));
#endif
	initSig();
#ifndef WIN32
	setupSigHandler(dbgFlg);
#endif

#ifdef OW_HAVE_PTHREAD_ATFORK
	// this registers shutdownSig to be run in the child whenever a fork() happens. 
	// This will prevent a child process from writing to the signal pipe and shutting down the parent.
	::pthread_atfork(NULL, NULL, &shutdownSig);
#endif
}
//////////////////////////////////////////////////////////////////////////////
int
daemonShutdown(const String& daemonName, const ServiceEnvironmentIFCRef& env)
{
#ifndef WIN32
#if defined(OW_NETWARE)
	(void)daemonName;
	{
		NonRecursiveMutexLock l(g_shutdownGuard);
		g_shutDown = true;
		g_shutdownCond.notifyAll();
		pthread_yield();
	}
	if(!FromEventHandler)
	{
		UnRegisterEventNotification(DownEvent);
	}
#else
	String pidFile(env->getConfigItem(ConfigOpts::PIDFILE_opt, OW_DEFAULT_PIDFILE));
	PidFile::removePid(pidFile.c_str());
#endif
#endif
	shutdownSig();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void rerunDaemon()
{
#ifndef WIN32
#ifdef OW_HAVE_PTHREAD_KILL_OTHER_THREADS_NP
	// do this, since it seems that on some distros (debian sarge for instance)
	// it doesn't happen when calling execv(), and it shouldn't hurt if it's
	// called twice.
	pthread_kill_other_threads_np();
#endif

#ifdef OW_DARWIN
	// On Darwin, execv() fails with a ENOTIMP if any threads are running.
	// The only way we have to really get rid of all the threads is to call fork() and exit() the parent.
	// Note that we don't do this on other platforms because fork() isn't safe to call from a signal handler, and isn't necessary.
	if (::fork() != 0)
	{
		_exit(1); // if fork fails or we're the parent, just exit.
	}
	// child continues.
#endif

	// On Linux pthreads will kill off all the threads when we call
	// execv().  If we close all the fds, then that breaks pthreads and
	// execv() will just hang.
	// Instead set the close on exec flag so all file descriptors are closed
	// by the kernel when we evecv() and we won't leak them.
	rlimit rl;
	int i = sysconf(_SC_OPEN_MAX);
	if (getrlimit(RLIMIT_NOFILE, &rl) != -1)
	{
	  if ( i < 0 )
	  {
		i = rl.rlim_max;
	  }
	  else
	  {
		i = std::min<int>(rl.rlim_max, i);
	  }
	}

	struct flock lck;
	::memset (&lck, '\0', sizeof (lck));
	lck.l_type = F_UNLCK;       // unlock
	lck.l_whence = 0;           // 0 offset for l_start
	lck.l_start = 0L;           // lock starts at BOF
	lck.l_len = 0L;             // extent is entire file

	while (i > 2)
	{
		// clear any file locks - this shouldn't technically be necessary, but it seems on some systems, even though we restart, the locks persist,
		// either because of bugs in the kernel or somehow things still hang around...
		::fcntl(i, F_SETLK, &lck);

		// set it for close on exec
		::fcntl(i, F_SETFD, FD_CLOEXEC);
		i--;
	}

	// reset the signal mask, since that is inherited by an exec()'d process, and if
	// this was called from a signal handler, the signal being handled (e.g. SIGSEGV) will be blocked.
	// some platforms make macros for sigemptyset, so we can't use ::
	sigset_t emptymask;
	sigemptyset(&emptymask);
	::sigprocmask(SIG_SETMASK, &emptymask, 0);
#endif

	// This doesn't return. execv() will replace the current process with a
	// new copy of g_argv[0] (owcimomd).
	::execv(g_argv[0], g_argv);

	// If we get here we're pretty much hosed.
	OW_THROW_ERRNO_MSG(DaemonException, "execv() failed");
}

//////////////////////////////////////////////////////////////////////////////
void restartDaemon()
{
#ifdef WIN32
	rerunDaemon();
#else
	::kill(::getpid(), SIGHUP);
#endif
}

#ifndef WIN32

namespace
{

//////////////////////////////////////////////////////////////////////////////
#if !defined(OW_HAVE_SIGHANDLER_T)
typedef void (*sighandler_t)(int);
#endif

void
handleSignalAux(int sig, sighandler_t handler)
{
	struct sigaction temp;
	memset(&temp, '\0', sizeof(temp));
	sigaction(sig, 0, &temp);
	temp.sa_handler = handler;
	sigemptyset(&temp.sa_mask);
	/* Here's a note from the glibc documentation:
	 * When you don't specify with `sigaction' or `siginterrupt' what a
	 * particular handler should do, it uses a default choice.  The default
	 * choice in the GNU library depends on the feature test macros you have
	 * defined.  If you define `_BSD_SOURCE' or `_GNU_SOURCE' before calling
	 * `signal', the default is to resume primitives; otherwise, the default
	 * is to make them fail with `EINTR'.  (The library contains alternate
	 * versions of the `signal' function, and the feature test macros
	 * determine which one you really call.)
	 *
	 * We want the EINTR behavior, so we can cancel threads and shutdown
	 * or restart if the occasion arises, so we set flags to 0.
	 *
	 * This also clears the SA_SIGINFO flag so that the sa_handler member
	 * may be safely used.
	 */
	temp.sa_flags = 0;
	sigaction(sig, &temp, NULL);
}

// This typedef is not required to be defined anywhere in the header files,
// but POSIX does show the signature of the function.
// See http://www.opengroup.org/onlinepubs/009695399/functions/sigaction.html
typedef void (*full_sighandler_t)(int,siginfo_t*,void*);

// A signal handler installer for a full sigaction handler.  This is
// different from the normal sighandler type only by the flags in the
// handler and the field used in the sigaction struct
// (sa_sigaction/sa_handler).
void
handleSignalAux(int sig, full_sighandler_t handler)
{
	struct sigaction temp;
	memset(&temp, '\0', sizeof(temp));
	sigaction(sig, 0, &temp);
	temp.sa_sigaction = handler;
	sigemptyset(&temp.sa_mask);
	/* Here's a note from the glibc documentation:
	 * When you don't specify with `sigaction' or `siginterrupt' what a
	 * particular handler should do, it uses a default choice.  The default
	 * choice in the GNU library depends on the feature test macros you have
	 * defined.  If you define `_BSD_SOURCE' or `_GNU_SOURCE' before calling
	 * `signal', the default is to resume primitives; otherwise, the default
	 * is to make them fail with `EINTR'.  (The library contains alternate
	 * versions of the `signal' function, and the feature test macros
	 * determine which one you really call.)
	 *
	 * We want the EINTR behavior, so we can cancel threads and shutdown
	 * or restart if the occasion arises, so we set flags to 0.
	 *
	 * We also want to use the sa_sigaction field, so we set SA_SIGINFO flag.
	 */
	temp.sa_flags = SA_SIGINFO;
	sigaction(sig, &temp, NULL);
}

void
handleSignal(int sig)
{
	handleSignalAux(sig, theSigHandler);
}
void
ignoreSignal(int sig)
{
	handleSignalAux(sig, SIG_IGN);
}

} // end unnamed namespace

#endif

//////////////////////////////////////////////////////////////////////////////
extern "C" {
static void
theSigHandler(int sig, siginfo_t* info, void* context)
{
	int savedErrno = errno;
	try
	{
		Signal::SignalInformation extractedSignal;
		if( info )
		{
			Signal::extractSignalInformation( *info, extractedSignal );
		}

		switch (sig)
		{
			case SIGTERM:
			case SIGINT:
#if defined(OW_NETWARE)
			case SIGABRT:
#endif
				extractedSignal.signalAction = SHUTDOWN;
				pushSig(extractedSignal);
				break;
#ifndef OW_WIN32
			case SIGHUP:
				extractedSignal.signalAction = REINIT;
				pushSig(extractedSignal);
				break;
#endif
		}
	}
	catch (...) // can't let exceptions escape from here or we'll segfault.
	{
	}
	errno = savedErrno;

}

#ifndef WIN32

static void
fatalSigHandler(int sig, siginfo_t* info, void* context)
{
	// we can't do much of *anything* besides restart here, since whatever caused the signal has left us in an unpredictable state,
	// it's unknown what could or could not work, not to mention that there are hardly any signal safe functions we could call.
	Platform::rerunDaemon();
}

#ifdef OW_NETWARE
static void
netwareExitHandler(void*)
{
	theSigHandler(SIGTERM);
	pthread_yield();
	NonRecursiveMutexLock l(g_shutdownGuard);
	while(!g_shutDown)
	{
		g_shutdownCond.wait(l);
	}
}

static int
netwareShutDownEventHandler(void*,
	void*, void*)
{
	FromEventHandler = true;
	theSigHandler(SIGTERM);
	pthread_yield();
	NonRecursiveMutexLock l(g_shutdownGuard);
	while(!g_shutDown)
	{
		g_shutdownCond.wait(l);
	}
	return 0;
}
#endif

#endif
} // extern "C"
#ifndef WIN32

namespace
{
//////////////////////////////////////////////////////////////////////////////
void
setupSigHandler(bool dbgFlg)
{
	/* Here's a note from the glibc documentation about signal():
	 *Compatibility Note:* A problem encountered when working with the
	 `signal' function is that it has different semantics on BSD and SVID
	 systems.  The difference is that on SVID systems the signal handler is
	 deinstalled after signal delivery.  On BSD systems the handler must be
	 explicitly deinstalled.  In the GNU C Library we use the BSD version by
	 default.  To use the SVID version you can either use the function
	 `sysv_signal' (see below) or use the `_XOPEN_SOURCE' feature select
	 macro ( Feature Test Macros).  In general, use of these
	 functions should be avoided because of compatibility problems.  It is
	 better to use `sigaction' if it is available since the results are much
	 more reliable.
	 We avoid using signal and use sigaction instead.
	 */
	if (dbgFlg)
	{
		handleSignal(SIGINT);
	}
	else
	{
		ignoreSignal(SIGINT);
	}
	handleSignal(SIGTERM);
	handleSignal(SIGHUP);
//	handleSignal(SIGUSR2);

// The thread code uses SIGUSR1 to implement cooperative cancellation, since
// sending a signal can wake up a blocked system call.
//	handleSignal(SIGUSR1);

	ignoreSignal(SIGTTIN);
	ignoreSignal(SIGTTOU);
	ignoreSignal(SIGTSTP);
#ifdef SIGPOLL
	ignoreSignal(SIGPOLL);
#endif
#ifdef SIGIO
	ignoreSignal(SIGIO);
#endif
	ignoreSignal(SIGPIPE);
	// ?
#ifdef SIGIOT // NetWare doesn't have this signal
	ignoreSignal(SIGIOT);
#endif
	ignoreSignal(SIGCONT);
#ifdef SIGURG // NetWare doesn't have this signal
	ignoreSignal(SIGURG);
#endif
#ifdef SIGXCPU // NetWare doesn't have this signal
	ignoreSignal(SIGXCPU);
#endif
#ifdef SIGXFSZ // NetWare doesn't have this signal
	ignoreSignal(SIGXFSZ);
#endif
#ifdef SIGVTALRM // NetWare doesn't have this signal
	ignoreSignal(SIGVTALRM);
#endif
#ifdef SIGPROF // NetWare doesn't have this signal
	ignoreSignal(SIGPROF);
#endif
#ifdef SIGPWR // FreeBSD doesn't have SIGPWR
	ignoreSignal(SIGPWR);
#endif

	//handleSignal(SIGALRM);
	//handleSignal(SIGSTKFLT);

#ifdef OW_NETWARE
	int rv;
	if ((rv = NXVmRegisterExitHandler(netwareExitHandler, 0) != 0))
	{
		OW_THROW(DaemonException,
			Format("FAILED TO REGISTER EXIT HANDLER "
			"NXVmRegisterExitHandler returned %1", rv).c_str());
	}
	EventRTag = AllocateResourceTag(getnlmhandle(), "Server down event",
		EventSignature);
	if(!EventRTag)
	{
		OW_THROW(DaemonException, "AllocationResourceTag FAILED");
	}
	NX_WRAP_INTERFACE((void*)netwareShutDownEventHandler, 3, &WarnFuncRef);
	DownEvent = RegisterForEventNotification(EventRTag,
		EVENT_DOWN_SERVER | EVENT_CONSUMER_MT_SAFE,
		EVENT_PRIORITY_APPLICATION, (Warn_t)WarnFuncRef, (Report_t)0, 0);
	if(!DownEvent)
	{
		OW_THROW(DaemonException, "FAILED to register for shutdown event");
	}
#endif
}

} // end unnamed namespace

//////////////////////////////////////////////////////////////////////////////
void installFatalSignalHandlers()
{
	handleSignalAux(SIGABRT, fatalSigHandler);

	handleSignalAux(SIGILL, fatalSigHandler);
#ifdef SIGBUS // NetWare doesn't have this signal
	handleSignalAux(SIGBUS, fatalSigHandler);
#endif
	handleSignalAux(SIGSEGV, fatalSigHandler);
	handleSignalAux(SIGFPE, fatalSigHandler);
}

//////////////////////////////////////////////////////////////////////////////
void removeFatalSignalHandlers()
{
	handleSignalAux(SIGABRT, SIG_DFL);

	handleSignalAux(SIGILL, SIG_DFL);
#ifdef SIGBUS // NetWare doesn't have this signal
	handleSignalAux(SIGBUS, SIG_DFL);
#endif
	handleSignalAux(SIGSEGV, SIG_DFL);
	handleSignalAux(SIGFPE, SIG_DFL);
}
#else // WIN32

BOOL WINAPI CtrlHandlerRoutine(DWORD dwCtrlType)
{
	theSigHandler(SIGTERM, 0, 0);
	return TRUE;
}

void installFatalSignalHandlers()
{
	::SetConsoleCtrlHandler(CtrlHandlerRoutine, TRUE);
}

void removeFatalSignalHandlers()
{
	::SetConsoleCtrlHandler(CtrlHandlerRoutine, FALSE);
}

#endif // WIN32

//////////////////////////////////////////////////////////////////////////////
void initDaemonizePipe()
{
	daemonize_upipe = UnnamedPipe::createUnnamedPipe();
	daemonize_upipe->setTimeouts(DAEMONIZE_PIPE_TIMEOUT);
}

//////////////////////////////////////////////////////////////////////////////
void sendDaemonizeStatus(int status)
{
	if (daemonize_upipe)
	{
		daemonize_upipe->writeInt(status);
	}
}

//////////////////////////////////////////////////////////////////////////////
void initSig()
{
	plat_upipe = UnnamedPipe::createUnnamedPipe();
	plat_upipe->setBlocking(UnnamedPipe::E_NONBLOCKING);
}
//////////////////////////////////////////////////////////////////////////////
void pushSig(const Signal::SignalInformation& sig)
{
	if (plat_upipe)
	{
		Signal::flattenSignalInformation(sig, plat_upipe);
	}
	// don't throw from this function, it may cause a segfault or deadlock.
}
//////////////////////////////////////////////////////////////////////////////
int popSig(Signal::SignalInformation& sig)
{
	int tmp = -2;
	if (plat_upipe)
	{
		if( !Signal::unflattenSignalInformation(sig, plat_upipe) )
		{
			return -1;
		}
		tmp = sig.signalAction;
	}
	return tmp;
}
//////////////////////////////////////////////////////////////////////////////
void shutdownSig()
{
	plat_upipe = 0;
}

//////////////////////////////////////////////////////////////////////////////
SelectableIFCRef getSigSelectable()
{
	return plat_upipe;
}


//////////////////////////////////////////////////////////////////////////////

} // end namespace Platform
} // end namespace OW_NAMESPACE

