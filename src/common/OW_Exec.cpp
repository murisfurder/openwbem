/*******************************************************************************
* Copyright (C) 2004 Vintela, Inc. All rights reserved.
* Copyright (C) 2005 Novell, Inc. All rights reserved.
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
*  - Neither the name of Vintela, Inc., Novell, Inc., nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL Vintela, Inc., Novell, Inc., OR THE 
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/**
 * @author Dan Nuffer
 */

#include "OW_config.h"
#include "OW_Array.hpp"
#include "OW_Exec.hpp"
#include "OW_Format.hpp"
#include "OW_Assertion.hpp"
#include "OW_PosixUnnamedPipe.hpp"
#include "OW_IOException.hpp"
#include "OW_Thread.hpp"
#include "OW_Select.hpp"
#include "OW_ExceptionIds.hpp"
#include "OW_IntrusiveCountableBase.hpp"
#include "OW_DateTime.hpp"
#include "OW_AutoPtr.hpp"

#include <map>

extern "C"
{
#ifdef OW_HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif
#ifndef OW_WIN32
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#endif
#include <errno.h>
#include <stdio.h> // for perror
#include <signal.h>
}

#include <cerrno>
#include <iostream>	// for cerr

// NSIG may be defined by signal.h, otherwise 64 should be plenty.
#ifndef NSIG
#define NSIG 64
#endif

namespace OW_NAMESPACE
{

using std::cerr;
using std::endl;
OW_DEFINE_EXCEPTION_WITH_ID(ExecTimeout);
OW_DEFINE_EXCEPTION_WITH_ID(ExecBufferFull);
OW_DEFINE_EXCEPTION_WITH_ID(ExecError);

#ifndef OW_WIN32
class PopenStreamsImpl : public IntrusiveCountableBase
{
public:
	PopenStreamsImpl();
	~PopenStreamsImpl();
	UnnamedPipeRef in() const;
	void in(const UnnamedPipeRef& pipe);
	UnnamedPipeRef out() const;
	void out(const UnnamedPipeRef& pipe);
	UnnamedPipeRef err() const;
	void err(const UnnamedPipeRef& pipe);
	Array<UnnamedPipeRef> extraPipes() const;
	void setExtraPipes(const Array<UnnamedPipeRef>& pipes);

	pid_t pid();
	void pid(pid_t newPid);
	int getExitStatus();
	int getExitStatus(UInt32 wait_initial, UInt32 wait_close, UInt32 wait_term);
	void setProcessStatus(int ps)
	{
		m_processstatus = ps;
	}
private:
	UnnamedPipeRef m_in;
	UnnamedPipeRef m_out;
	UnnamedPipeRef m_err;
	Array<UnnamedPipeRef> m_extraPipes;
	pid_t m_pid;
	int m_processstatus;
};
//////////////////////////////////////////////////////////////////////////////
PopenStreamsImpl::PopenStreamsImpl()
	: m_pid(-1)
	, m_processstatus(-1)
{
}
//////////////////////////////////////////////////////////////////////////////
UnnamedPipeRef PopenStreamsImpl::in() const
{
	return m_in;
}
//////////////////////////////////////////////////////////////////////////////
void PopenStreamsImpl::in(const UnnamedPipeRef& pipe)
{
	m_in = pipe;
}
//////////////////////////////////////////////////////////////////////////////
UnnamedPipeRef PopenStreamsImpl::out() const
{
	return m_out;
}
//////////////////////////////////////////////////////////////////////////////
void PopenStreamsImpl::out(const UnnamedPipeRef& pipe)
{
	m_out = pipe;
}
//////////////////////////////////////////////////////////////////////////////
UnnamedPipeRef PopenStreamsImpl::err() const
{
	return m_err;
}
//////////////////////////////////////////////////////////////////////////////
void PopenStreamsImpl::err(const UnnamedPipeRef& pipe)
{
	m_err = pipe;
}
//////////////////////////////////////////////////////////////////////////////
Array<UnnamedPipeRef> PopenStreamsImpl::extraPipes() const
{
	return m_extraPipes;
}
//////////////////////////////////////////////////////////////////////////////
void PopenStreamsImpl::setExtraPipes(const Array<UnnamedPipeRef>& pipes)
{
	m_extraPipes = pipes;
}
//////////////////////////////////////////////////////////////////////////////
pid_t PopenStreamsImpl::pid()
{
	return m_pid;
}
//////////////////////////////////////////////////////////////////////////////
void PopenStreamsImpl::pid(pid_t newPid)
{
	m_pid = newPid;
}
//////////////////////////////////////////////////////////////////////
static inline ProcId safeWaitPid(ProcId pid, int* status, int options)
{
	// The status is not passed directly to waitpid because some implementations
	// store a value there even when the function returns <= 0.
	int localReturnValue = -1;
	pid_t returnedPID = ::waitpid(pid, &localReturnValue, options);
	if( returnedPID > 0 )
	{
		*status = localReturnValue;
	}	
	return returnedPID;
}

//////////////////////////////////////////////////////////////////////
static ProcId noIntrWaitPid(ProcId pid, int* status, int options)
{
	pid_t waitpidrv;
	do
	{
		Thread::testCancel();
		waitpidrv = safeWaitPid(pid, status, options);
	} while (waitpidrv == -1 && errno == EINTR);
	return waitpidrv;
}

//////////////////////////////////////////////////////////////////////////////
static inline void
milliSleep(UInt32 milliSeconds)
{
	Thread::sleep(milliSeconds);
}
//////////////////////////////////////////////////////////////////////////////
static inline void
secSleep(UInt32 seconds)
{
	Thread::sleep(seconds * 1000);
}
//////////////////////////////////////////////////////////////////////////////
static bool
timedWaitPid(ProcId pid, int * pstatus, UInt32 wait_time)
{
	UInt32 const N = 154;
	UInt32 const M = 128;  // N/M is about 1.20
	UInt32 const MAXPERIOD = 5000;
	UInt32 period = 100;
	UInt32 t = 0;
	ProcId waitpidrv = noIntrWaitPid(pid, pstatus, WNOHANG);
	while (t < wait_time && waitpidrv == 0) {
		milliSleep(period);
		t += period;
		period *= N;
		period /= M; 
		if (period > MAXPERIOD)
		{
			period = MAXPERIOD;
		}
		waitpidrv = noIntrWaitPid(pid, pstatus, WNOHANG);
	}
	if (waitpidrv < 0) {
		OW_THROW_ERRNO_MSG(ExecErrorException, "waitpid() failed.");
	}
	return waitpidrv != 0;
}

//////////////////////////////////////////////////////////////////////////////
// Send signal sig to the process, then wait at most wait_time milliseconds.
// for the process to terminate.  Return true if termination detected.
//
static bool killWait(
	ProcId pid, int * pstatus, UInt32 wait_time, int sig, char const * signame
)
{
	if (::kill(pid, sig) == -1) {
		// don't trust waitpid, Format ctor, etc. to leave errno alone
		int errnum = errno;
		// maybe kill() failed because child terminated first
		if (noIntrWaitPid(pid, pstatus, WNOHANG) > 0) {
			return true;
		}
		else {
			Format fmt("Failed sending %1 to process %2.", signame, pid);
			char const * msg = fmt.c_str();
			errno = errnum;
			OW_THROW_ERRNO_MSG(ExecErrorException, msg);
		}
	}
	return timedWaitPid(pid, pstatus, wait_time);
}

//////////////////////////////////////////////////////////////////////////////
int PopenStreamsImpl::getExitStatus()
{
	return this->getExitStatus(0, 10 *1000, 10 * 1000);
}

//////////////////////////////////////////////////////////////////////////////
int PopenStreamsImpl::getExitStatus(
	UInt32 wait_initial, UInt32 wait_close, UInt32 wait_term)
{
	if (m_pid < 0)
	{
		return m_processstatus;
	}
	if (m_pid == ::getpid())
	{
		OW_THROW(ExecErrorException, "PopenStreamsImpl::getExitStatus: m_pid == getpid()");
	}

	ProcId pid = m_pid;
	m_pid = -1;
	int * pstatus = &m_processstatus;

	// Convert times to milliseconds
	wait_initial *= 1000;
	wait_close *= 1000;
	wait_term *= 1000;

	if (wait_initial > 0 &&	timedWaitPid(pid, pstatus, wait_initial))
	{
		return m_processstatus;
	}

	if (wait_close > 0)
	{
		// Close the streams. If the child process is blocked waiting to output,
		// then this will cause it to get a SIGPIPE, and it may be able to clean
		// up after itself.  Likewise, if the child process is blocked waiting
		// for input, it will now detect EOF.
		UnnamedPipeRef upr;
		if (upr = in())
		{
			upr->close();
		}
		if (upr = out())
		{
			upr->close();
		}
		if (upr = err())
		{
			upr->close();
		}
		if (timedWaitPid(pid, pstatus, wait_close))
		{
			return m_processstatus;
		}
	}

	if (wait_term > 0 && killWait(pid, pstatus, wait_term, SIGTERM, "SIGTERM"))
	{
		return m_processstatus;
	}
	if (!killWait(pid, pstatus, 5000, SIGKILL, "SIGKILL")) {
		OW_THROW(
			ExecErrorException, "PopenStreamsImpl::getExitStatus: Child process has not exited after sending it a SIGKILL."
		);
	}
	return m_processstatus;
}
//////////////////////////////////////////////////////////////////////////////
PopenStreamsImpl::~PopenStreamsImpl()
{
	try // can't let exceptions past.
	{
		// This will terminate the process.
		getExitStatus();
	}
	catch (...)
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
PopenStreams::PopenStreams()
	: m_impl(new PopenStreamsImpl)
{
}
/////////////////////////////////////////////////////////////////////////////
PopenStreams::~PopenStreams()
{
}
/////////////////////////////////////////////////////////////////////////////
UnnamedPipeRef PopenStreams::in() const
{
	return m_impl->in();
}
/////////////////////////////////////////////////////////////////////////////
void PopenStreams::in(const UnnamedPipeRef& pipe)
{
	m_impl->in(pipe);
}
/////////////////////////////////////////////////////////////////////////////
UnnamedPipeRef PopenStreams::out() const
{
	return m_impl->out();
}
/////////////////////////////////////////////////////////////////////////////
void PopenStreams::out(const UnnamedPipeRef& pipe)
{
	m_impl->out(pipe);
}
/////////////////////////////////////////////////////////////////////////////
UnnamedPipeRef PopenStreams::err() const
{
	return m_impl->err();
}
/////////////////////////////////////////////////////////////////////////////
void PopenStreams::err(const UnnamedPipeRef& pipe)
{
	m_impl->err(pipe);
}
/////////////////////////////////////////////////////////////////////////////
Array<UnnamedPipeRef> PopenStreams::extraPipes() const
{
	return m_impl->extraPipes();
}
/////////////////////////////////////////////////////////////////////////////
void PopenStreams::setExtraPipes(const Array<UnnamedPipeRef>& pipes)
{
	m_impl->setExtraPipes(pipes);
}
/////////////////////////////////////////////////////////////////////////////
pid_t PopenStreams::pid() const
{
	return m_impl->pid();
}
/////////////////////////////////////////////////////////////////////////////
void PopenStreams::pid(pid_t newPid)
{
	m_impl->pid(newPid);
}
/////////////////////////////////////////////////////////////////////////////
int PopenStreams::getExitStatus()
{
	return m_impl->getExitStatus();
}
/////////////////////////////////////////////////////////////////////////////
int PopenStreams::getExitStatus(UInt32 wait0, UInt32 wait1, UInt32 wait2)
{
	return m_impl->getExitStatus(wait0, wait1, wait2);
}
/////////////////////////////////////////////////////////////////////////////
void PopenStreams::setProcessStatus(int ps)
{
	m_impl->setProcessStatus(ps);
}
/////////////////////////////////////////////////////////////////////////////
PopenStreams::PopenStreams(const PopenStreams& src)
	: m_impl(src.m_impl)
{
}
/////////////////////////////////////////////////////////////////////////////
PopenStreams& PopenStreams::operator=(const PopenStreams& src)
{
	m_impl = src.m_impl;
	return *this;
}

//////////////////////////////////////////////////////////////////////////////
bool operator==(const PopenStreams& x, const PopenStreams& y)
{
	return x.m_impl == y.m_impl;
}

//////////////////////////////////////////////////////////////////////////////
namespace Exec
{

//////////////////////////////////////////////////////////////////////////////
int 
safeSystem(const Array<String>& command, const EnvVars& envVars)
{
	const char* const* envp = (envVars.size() > 0) ? envVars.getenvp() : 0;
	return safeSystem(command, envp);
}

//////////////////////////////////////////////////////////////////////////////
int
safeSystem(const Array<String>& command, const char* const envp[])
{
	int status;
	pid_t pid;
	if (command.size() == 0)
	{
		return 1;
	}

	// This has to be done before fork().  In a multi-threaded app, calling new after fork() can cause a deadlock.
	AutoPtrVec<const char*> argv(new const char*[command.size() + 1]);
	for (size_t i = 0; i < command.size(); i++)
	{
		argv[i] = command[i].c_str();
	}
	argv[command.size()] = 0;

	pid = ::fork();
	if (pid == -1)
	{
		return -1;
	}
	if (pid == 0)
	{
		try
		{

			// according to susv3:
			//        This  volume  of  IEEE Std 1003.1-2001  specifies  that  signals set to
			//        SIG_IGN remain set to SIG_IGN, and that  the  process  signal  mask  be
			//        unchanged  across an exec. This is consistent with historical implemen-
			//        tations, and it permits some useful functionality, such  as  the  nohup
			//        command.  However,  it  should be noted that many existing applications
			//        wrongly assume that they start with certain signals set to the  default
			//        action  and/or  unblocked.  In  particular, applications written with a
			//        simpler signal model that does not include blocking of signals, such as
			//        the  one in the ISO C standard, may not behave properly if invoked with
			//        some signals blocked. Therefore, it is best not to block or ignore sig-
			//        nals  across execs without explicit reason to do so, and especially not
			//        to block signals across execs of arbitrary (not  closely  co-operating)
			//        programs.

			// so we'll reset the signal mask and all signal handlers to SIG_DFL. We set them all
			// just in case the current handlers may misbehave now that we've fork()ed.
			sigset_t emptymask;
			sigemptyset(&emptymask);
			::sigprocmask(SIG_SETMASK, &emptymask, 0);

			for (size_t sig = 1; sig <= NSIG; ++sig)
			{
				struct sigaction temp;
				sigaction(sig, 0, &temp);
				temp.sa_handler = SIG_DFL;
				sigaction(sig, &temp, NULL);
			}

			// Close all file handle from parent process
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
			while (i > 2)
			{
				// set it for close on exec
				::fcntl(i, F_SETFD, FD_CLOEXEC);
				i--;
			}

			int rval; 
			if (envp)
			{
				rval = execve(argv[0], const_cast<char* const*>(argv.get()), const_cast<char* const*>(envp));
			}
			else
			{
				rval = execv(argv[0], const_cast<char* const*>(argv.get()));
			}
			cerr << Format( "Exec::safeSystem: execv failed for program "
					"%1, rval is %2", argv[0], rval);
		}
		catch (...)
		{
			cerr << "something threw an exception after fork()!";
		}
		_exit(127);
	}
	do
	{
		Thread::testCancel();
		if (waitpid(pid, &status, 0) == -1)
		{
			if (errno != EINTR)
			{
				return -1;
			}
		}
		else
		{
			return WEXITSTATUS(status);
		}
	} while (1);
}

//////////////////////////////////////////////////////////////////////////////
PopenStreams
safePopen(const Array<String>& command,
		const String& initialInput)
{
	PopenStreams retval = safePopen(command);

	if (initialInput != "")
	{
		if (retval.in()->write(initialInput.c_str(), initialInput.length()) == -1)
		{
			OW_THROW_ERRNO_MSG(IOException, "Exec::safePopen: Failed writing input to process");
		}
	}

	return retval;
}

//////////////////////////////////////////////////////////////////////////////
PopenStreams 
safePopen(const Array<String>& command, const EnvVars& envVars)
{
	const char* const* envp = (envVars.size() > 0) ? envVars.getenvp() : 0;
	return safePopen(command, envp);
}

//////////////////////////////////////////////////////////////////////////////
PopenStreams
safePopen(const Array<String>& command, const char* const envp[])
{
	// sent over the execErrorPipe if an exception is caught after fork()ing.
	// Negative because errno values are positive. Maybe this is a bad assumption? 
	// The worst that could happen is reporting an unknown exception instead of the real errno value.
	const int UNKNOWN_EXCEPTION = -2000; 

	if (command.size() == 0)
	{
		OW_THROW(ExecErrorException, "Exec::safePopen: command is empty");
	}
	
	PopenStreams retval;
	retval.in( UnnamedPipe::createUnnamedPipe() );
	UnnamedPipeRef upipeOut = UnnamedPipe::createUnnamedPipe();
	retval.out( upipeOut );
	UnnamedPipeRef upipeErr = UnnamedPipe::createUnnamedPipe();
	retval.err( upipeErr );

	UnnamedPipeRef execErrorPipe = UnnamedPipe::createUnnamedPipe();

	// This has to be done before fork().  In a multi-threaded app, calling new after fork() can cause a deadlock.
	AutoPtrVec<const char*> argv(new const char*[command.size() + 1]);
	for (size_t i = 0; i < command.size(); i++)
	{
		argv[i] = command[i].c_str();
	}
	argv[command.size()] = 0;

	pid_t forkrv = ::fork();
	if (forkrv == -1)
	{
		OW_THROW_ERRNO_MSG(ExecErrorException, "Exec::safePopen: fork() failed");
	}
	if (forkrv == 0)
	{
		int execErrorFd = -1;
		try
		{

			// child process
			// according to susv3:
			//        This  volume  of  IEEE Std 1003.1-2001  specifies  that  signals set to
			//        SIG_IGN remain set to SIG_IGN, and that  the  process  signal  mask  be
			//        unchanged  across an exec. This is consistent with historical implemen-
			//        tations, and it permits some useful functionality, such  as  the  nohup
			//        command.  However,  it  should be noted that many existing applications
			//        wrongly assume that they start with certain signals set to the  default
			//        action  and/or  unblocked.  In  particular, applications written with a
			//        simpler signal model that does not include blocking of signals, such as
			//        the  one in the ISO C standard, may not behave properly if invoked with
			//        some signals blocked. Therefore, it is best not to block or ignore sig-
			//        nals  across execs without explicit reason to do so, and especially not
			//        to block signals across execs of arbitrary (not  closely  co-operating)
			//        programs.
	
			// so we'll reset the signal mask and all signal handlers to SIG_DFL. We set them all
			// just in case the current handlers may misbehave now that we've fork()ed.
			sigset_t emptymask;
			sigemptyset(&emptymask);
			::sigprocmask(SIG_SETMASK, &emptymask, 0);
	
			for (size_t sig = 1; sig <= NSIG; ++sig)
			{
				struct sigaction temp;
				sigaction(sig, 0, &temp);
				temp.sa_handler = SIG_DFL;
				sigaction(sig, &temp, NULL);
			}
	
			// Close stdin, stdout, and stderr.
			close(0);
			close(1);
			close(2);

			// this should only fail because of programmer error.
			UnnamedPipeRef foo1 = retval.in();
			PosixUnnamedPipeRef in = foo1.cast_to<PosixUnnamedPipe>();
	
			UnnamedPipeRef foo2 = retval.out();
			PosixUnnamedPipeRef out = foo2.cast_to<PosixUnnamedPipe>();
	
			UnnamedPipeRef foo3 = retval.err();
			PosixUnnamedPipeRef err = foo3.cast_to<PosixUnnamedPipe>();

			
			OW_ASSERT(in);
			OW_ASSERT(out);
			OW_ASSERT(err);
			// connect stdin, stdout, and stderr to the return pipes.
			int rv = dup2(in->getInputHandle(), 0);
			OW_ASSERT(rv != -1);
			rv = dup2(out->getOutputHandle(), 1);
			OW_ASSERT(rv != -1);
			rv = dup2(err->getOutputHandle(), 2);
			OW_ASSERT(rv != -1);

			// set up the execError fd
			PosixUnnamedPipeRef execError = execErrorPipe.cast_to<PosixUnnamedPipe>();
			OW_ASSERT(execError);
			execErrorFd = execError->getOutputHandle();


			// Close all other file handle from parent process
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
			while (i > 2)
			{
				// set it for close on exec
				::fcntl(i, F_SETFD, FD_CLOEXEC);
				i--;
			}
	
			int rval = 0;
			if (envp)
			{
				rval = execve(argv[0], const_cast<char* const*>(argv.get()), const_cast<char* const*>(envp));
			}
			else
			{
				rval = execv(argv[0], const_cast<char* const*>(argv.get()));
			}
			// send errno over the pipe
			int lerrno = errno;
			write(execErrorFd, &lerrno, sizeof(lerrno));
		}
		catch (...)
		{
			int errorVal = UNKNOWN_EXCEPTION;
			write(execErrorFd, &errorVal, sizeof(errorVal));
		}
		_exit(127);
	}

	// parent process
	retval.pid (forkrv);

	// this should only fail because of programmer error.
	UnnamedPipeRef foo1 = retval.in();
	PosixUnnamedPipeRef in = foo1.cast_to<PosixUnnamedPipe>();
	UnnamedPipeRef foo2 = retval.out();	
	PosixUnnamedPipeRef out = foo2.cast_to<PosixUnnamedPipe>();
	UnnamedPipeRef foo3 = retval.err();	
	PosixUnnamedPipeRef err = foo3.cast_to<PosixUnnamedPipe>();
	OW_ASSERT(in);
	OW_ASSERT(out);
	OW_ASSERT(err);
	// prevent the parent from using the child's end of the pipes.
	in->closeInputHandle();
	out->closeOutputHandle();
	err->closeOutputHandle();
	
	PosixUnnamedPipeRef execErrorPosixPipe = execErrorPipe.cast_to<PosixUnnamedPipe>();
	OW_ASSERT(execErrorPosixPipe);
	// we need to close the parent's output side so that when the child's output side is closed, it can be detected.
	execErrorPosixPipe->closeOutputHandle();

	const int SECONDS_TO_WAIT_FOR_CHILD_TO_EXEC = 10; // 10 seconds should be plenty for the child to go from fork() to execv()
	execErrorPipe->setReadTimeout(SECONDS_TO_WAIT_FOR_CHILD_TO_EXEC);

	int childErrorCode = 0;
	int bytesRead = execErrorPipe->read(&childErrorCode, sizeof(childErrorCode));
	// 0 bytes means execv() happened successfully.
	if (bytesRead == ETIMEDOUT) // broken interface... grumble, grumble...
	{
		// for some reason the child never ran exec(). Must've deadlocked or the system is *really* loaded down.
		// Kill it forcefully.
		kill(forkrv, SIGKILL);
		OW_THROW(ExecErrorException, "Exec::safePopen: timed out waiting for child process to exec()");
	}
	if (bytesRead > 0)
	{
		// exec failed
		if (childErrorCode == UNKNOWN_EXCEPTION)
		{
			OW_THROW(ExecErrorException, "Exec::safePopen: child process caught an exception before reaching exec()");
		}
		else
		{
			errno = childErrorCode;
			OW_THROW_ERRNO_MSG(ExecErrorException, Format("Exec::safePopen: child process failed running exec() process = %1", command[0]));
		}
	}

	return retval;
}

namespace
{

#ifndef OW_MIN
#define OW_MIN(x, y) (x) < (y) ? (x) : (y)
#endif

/////////////////////////////////////////////////////////////////////////////
class StringOutputGatherer : public OutputCallback
{
public:
	StringOutputGatherer(String& output, int outputLimit)
		: m_output(output)
		, m_outputLimit(outputLimit)
	{
	}
private:
	virtual void doHandleData(const char* data, size_t dataLen, EOutputSource outputSource, PopenStreams& theStream, size_t streamIndex, Array<char>& inputBuffer)
	{
		if (m_outputLimit >= 0 && m_output.length() + dataLen > static_cast<size_t>(m_outputLimit))
		{
			// the process output too much, so just copy what we can and return error
			int lentocopy = OW_MIN(m_outputLimit - m_output.length(), dataLen);
			if (lentocopy >= 0)
			{
				m_output += String(data, lentocopy);
			}
			OW_THROW(ExecBufferFullException, "Exec::StringOutputGatherer::doHandleData(): buffer full");
		}

		m_output += data;
	}
	String& m_output;
	int m_outputLimit;
};

/////////////////////////////////////////////////////////////////////////////
class SingleStringInputCallback : public InputCallback
{
public:
	SingleStringInputCallback(const String& s)
		: m_s(s)
	{
	}
private:
	virtual void doGetData(Array<char>& inputBuffer, PopenStreams& theStream, size_t streamIndex)
	{
		if (m_s.length() > 0)
		{
			inputBuffer.insert(inputBuffer.end(), m_s.c_str(), m_s.c_str() + m_s.length());
			m_s.erase();
		}
		else if (theStream.in()->isOpen())
		{
			theStream.in()->close();
		}
	}
	String m_s;
};

}// end anonymous namespace

/////////////////////////////////////////////////////////////////////////////
void
executeProcessAndGatherOutput(const Array<String>& command,
	String& output, int& processStatus,
	int timeoutSecs, int outputLimit, const String& input)
{
	executeProcessAndGatherOutput(command, output, processStatus, EnvVars(),
		timeoutSecs, outputLimit, input);
}

/////////////////////////////////////////////////////////////////////////////
void executeProcessAndGatherOutput(
	const Array<String>& command,
	String& output, 
	int& processStatus, 
	const EnvVars& envVars,
	int timeoutSecs, 
	int outputLimit, 
	const String& input)
{
	processStatus = -1;
	Array<PopenStreams> streams;
	streams.push_back(safePopen(command, envVars));
	Array<ProcessStatus> processStatuses(1);
	SingleStringInputCallback singleStringInputCallback(input);

	StringOutputGatherer gatherer(output, outputLimit);
	processInputOutput(gatherer, streams, processStatuses, 
		singleStringInputCallback, timeoutSecs);

	if (processStatuses[0].hasExited())
	{
		processStatus = processStatuses[0].getStatus();
	}
	else
	{
		processStatus = streams[0].getExitStatus();
	}
}

/////////////////////////////////////////////////////////////////////////////
void
gatherOutput(String& output, PopenStreams& stream, int& processStatus, int timeoutSecs, int outputLimit)
{
	Array<PopenStreams> streams;
	streams.push_back(stream);
	Array<ProcessStatus> processStatuses(1);

	StringOutputGatherer gatherer(output, outputLimit);
	SingleStringInputCallback singleStringInputCallback = SingleStringInputCallback(String());
	processInputOutput(gatherer, streams, processStatuses, singleStringInputCallback, timeoutSecs);
	if (processStatuses[0].hasExited())
	{
		processStatus = processStatuses[0].getStatus();
	}
}

/////////////////////////////////////////////////////////////////////////////
OutputCallback::~OutputCallback()
{

}

/////////////////////////////////////////////////////////////////////////////
void
OutputCallback::handleData(const char* data, size_t dataLen, EOutputSource outputSource, PopenStreams& theStream, size_t streamIndex, Array<char>& inputBuffer)
{
	doHandleData(data, dataLen, outputSource, theStream, streamIndex, inputBuffer);
}

/////////////////////////////////////////////////////////////////////////////
InputCallback::~InputCallback()
{
}

/////////////////////////////////////////////////////////////////////////////
void
InputCallback::getData(Array<char>& inputBuffer, PopenStreams& theStream, size_t streamIndex)
{
	doGetData(inputBuffer, theStream, streamIndex);
}

namespace
{
	struct ProcessOutputState
	{
		bool inIsOpen;
		bool outIsOpen;
		bool errIsOpen;
		size_t availableDataLen;

		ProcessOutputState()
			: inIsOpen(true)
			, outIsOpen(true)
			, errIsOpen(true)
			, availableDataLen(0)
		{
		}
	};

}
/////////////////////////////////////////////////////////////////////////////
void
processInputOutput(OutputCallback& output, Array<PopenStreams>& streams, Array<ProcessStatus>& processStatuses, InputCallback& input, int timeoutsecs)
{
	processStatuses.clear();
	processStatuses.resize(streams.size());

	Array<ProcessOutputState> processStates(streams.size());
	int numOpenPipes(streams.size() * 2); // count of stdout & stderr. Ignore stdin for purposes of algorithm termination.

	DateTime curTime;
	curTime.setToCurrent();
	DateTime timeoutEnd(curTime);
	timeoutEnd += timeoutsecs;

	Array<Array<char> > inputs(processStates.size());
	for (size_t i = 0; i < processStates.size(); ++i)
	{
		input.getData(inputs[i], streams[i], i);
		processStates[i].availableDataLen = inputs[i].size();
		if (!streams[i].out()->isOpen())
		{
			processStates[i].outIsOpen = false;
		}
		if (!streams[i].err()->isOpen())
		{
			processStates[i].errIsOpen = false;
		}
		if (!streams[i].in()->isOpen())
		{
			processStates[i].inIsOpen = false;
		}

	}

	while (numOpenPipes > 0)
	{
		Select::SelectObjectArray selObjs; 
		std::map<int, int> inputIndexProcessIndex;
		std::map<int, int> outputIndexProcessIndex;
		for (size_t i = 0; i < streams.size(); ++i)
		{
			if (processStates[i].outIsOpen)
			{
				Select::SelectObject selObj(streams[i].out()->getSelectObj()); 
				selObj.waitForRead = true; 
				selObjs.push_back(selObj); 
				inputIndexProcessIndex[selObjs.size() - 1] = i;
			}
			if (processStates[i].errIsOpen)
			{
				Select::SelectObject selObj(streams[i].err()->getSelectObj()); 
				selObj.waitForRead = true; 
				selObjs.push_back(selObj); 
				inputIndexProcessIndex[selObjs.size() - 1] = i;
			}
			if (processStates[i].inIsOpen && processStates[i].availableDataLen > 0)
			{
				Select::SelectObject selObj(streams[i].in()->getWriteSelectObj()); 
				selObj.waitForWrite = true; 
				selObjs.push_back(selObj); 
				outputIndexProcessIndex[selObjs.size() - 1] = i;
			}

			// check if the child has exited - the pid gets set to -1 once it's exited.
			if (streams[i].pid() != -1)
			{
				pid_t waitpidrv;
				int processStatus(-1);
				waitpidrv = noIntrWaitPid(streams[i].pid(), &processStatus, WNOHANG);
				if (waitpidrv == -1)
				{
					streams[i].pid(-1);
					OW_THROW_ERRNO_MSG(ExecErrorException, "Exec::gatherOutput: waitpid() failed");
				}
				else if (waitpidrv != 0)
				{
					streams[i].pid(-1);
					streams[i].setProcessStatus(processStatus);
					processStatuses[i] = ProcessStatus(processStatus);
				}
			}
		}

		const int mstimeout = 100; // use 1/10 of a second
		int selectrval = Select::selectRW(selObjs, mstimeout);
		switch (selectrval)
		{
			case Select::SELECT_INTERRUPTED:
				// if we got interrupted, just try again
				break;
			case Select::SELECT_ERROR:
			{
				OW_THROW_ERRNO_MSG(ExecErrorException, "Exec::gatherOutput: error selecting on stdout and stderr");
			}
			break;
			case Select::SELECT_TIMEOUT:
			{
				// Check all processes and see if they've exited but the pipes are still open. If so, close the pipes,
				// since there's nothing to read from them.
				for (size_t i = 0; i < streams.size(); ++i)
				{
					if (streams[i].pid() == -1)
					{
						if (processStates[i].inIsOpen)
						{
							processStates[i].inIsOpen = false;
							streams[i].in()->close();
						}
						if (processStates[i].outIsOpen)
						{
							processStates[i].outIsOpen = false;
							streams[i].out()->close();
							--numOpenPipes;
						}
						if (processStates[i].errIsOpen)
						{
							processStates[i].errIsOpen = false;
							streams[i].err()->close();
							--numOpenPipes;
						}
					}
				}

				curTime.setToCurrent();
				if (timeoutsecs >= 0 && curTime > timeoutEnd)
				{
					OW_THROW(ExecTimeoutException, "Exec::gatherOutput: timedout");
				}
			}
			break;
			default:
			{
				int availableToFind = selectrval;
				// reset the timeout counter
				curTime.setToCurrent();
				timeoutEnd = curTime;
				timeoutEnd += timeoutsecs;

				for (size_t i = 0; i < selObjs.size() && availableToFind > 0; ++i)
				{
					if (!selObjs[i].readAvailable)
					{
						continue;
					}
					else
					{
						--availableToFind;
					}
					int streamIndex = inputIndexProcessIndex[i];
					UnnamedPipeRef readstream;
					if (processStates[streamIndex].outIsOpen)
					{
						if (streams[streamIndex].out()->getSelectObj() == selObjs[i].s)
						{
							readstream = streams[streamIndex].out();
						}
					}

					if (!readstream && processStates[streamIndex].errIsOpen)
					{
						if (streams[streamIndex].err()->getSelectObj() == selObjs[i].s)
						{
							readstream = streams[streamIndex].err();
						}
					}

					if (!readstream)
					{
						continue; // for loop
					}

					char buff[1024];
					int readrc = readstream->read(buff, sizeof(buff) - 1);
					if (readrc == 0)
					{
						if (readstream == streams[streamIndex].out())
						{
							processStates[streamIndex].outIsOpen = false;
							streams[streamIndex].out()->close();
						}
						else
						{
							processStates[streamIndex].errIsOpen = false;
							streams[streamIndex].err()->close();
						}
						--numOpenPipes;
					}
					else if (readrc == -1)
					{
						OW_THROW_ERRNO_MSG(ExecErrorException, "Exec::gatherOutput: read error");
					}
					else
					{
						buff[readrc] = '\0';
						output.handleData(buff, readrc, readstream == streams[streamIndex].out() ? E_STDOUT : E_STDERR, streams[streamIndex],
							streamIndex, inputs[streamIndex]);
					}
				}

				// handle stdin for all processes which have data to send to them.
				for (size_t i = 0; i < selObjs.size() && availableToFind > 0; ++i)
				{
					if (!selObjs[i].writeAvailable)
					{
						continue;
					}
					else
					{
						--availableToFind;
					}
					int streamIndex = outputIndexProcessIndex[i];
					UnnamedPipeRef writestream;
					if (processStates[streamIndex].inIsOpen)
					{
						writestream = streams[streamIndex].in();
					}

					if (!writestream)
					{
						continue; // for loop
					}

					size_t offset = inputs[streamIndex].size() - processStates[streamIndex].availableDataLen;
					int writerc = writestream->write(&inputs[streamIndex][offset], processStates[streamIndex].availableDataLen);
					if (writerc == 0)
					{
						processStates[streamIndex].inIsOpen = false;
						streams[streamIndex].in()->close();
					}
					else if (writerc == -1)
					{
						OW_THROW_ERRNO_MSG(ExecErrorException, "Exec::gatherOutput: write error");
					}
					else
					{
						inputs[streamIndex].erase(inputs[streamIndex].begin(), inputs[streamIndex].begin() + writerc);
						input.getData(inputs[streamIndex], streams[streamIndex], streamIndex);
						processStates[streamIndex].availableDataLen = inputs[streamIndex].size();
					}
				}
			}
			break;
		}
	}
}

} // end namespace Exec
#endif
} // end namespace OW_NAMESPACE

