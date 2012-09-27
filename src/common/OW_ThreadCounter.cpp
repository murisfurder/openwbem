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
#include "OW_ThreadCounter.hpp"
#include "OW_NonRecursiveMutexLock.hpp"
#include "OW_Assertion.hpp"
#include "OW_TimeoutException.hpp"

namespace OW_NAMESPACE
{

ThreadCounter::ThreadCounter(Int32 maxThreads)
	: m_maxThreads(maxThreads)
	, m_runCount(0)
{}
ThreadCounter::~ThreadCounter()
{}
void
ThreadCounter::incThreadCount(UInt32 sTimeout, UInt32 usTimeout)
{
	NonRecursiveMutexLock l(m_runCountGuard);
	while (m_runCount >= m_maxThreads)
	{
		if (!m_runCountCondition.timedWait(l, sTimeout, usTimeout))
		{
			OW_THROW(TimeoutException, "ThreadCounter::incThreadCount timedout");
		}
	}
	++m_runCount;
}
void
ThreadCounter::decThreadCount()
{
	NonRecursiveMutexLock l(m_runCountGuard);
	OW_ASSERT(m_runCount > 0);
	--m_runCount;
	m_runCountCondition.notifyAll();
}
Int32
ThreadCounter::getThreadCount()
{
	NonRecursiveMutexLock l(m_runCountGuard);
	return m_runCount;
}
void
ThreadCounter::waitForAll(UInt32 sTimeout, UInt32 usTimeout)
{
	NonRecursiveMutexLock runCountLock(m_runCountGuard);
	while (m_runCount > 0)
	{
		if (!m_runCountCondition.timedWait(runCountLock, sTimeout, usTimeout))
		{
			OW_THROW(TimeoutException, "ThreadCounter::waitForAll timedout");
		}
	}
}
void
ThreadCounter::setMax(Int32 maxThreads)
{
	NonRecursiveMutexLock runCountLock(m_runCountGuard);
	m_maxThreads = maxThreads;
	m_runCountCondition.notifyAll();
}
ThreadCountDecrementer::ThreadCountDecrementer(ThreadCounterRef const& x)
	: m_counter(x)
{}
ThreadCountDecrementer::~ThreadCountDecrementer()
{}
void
ThreadCountDecrementer::doNotifyThreadDone(Thread *)
{
	m_counter->decThreadCount();
}

} // end namespace OW_NAMESPACE

