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
 */

#include "OW_config.h"
#include "OW_NonRecursiveMutexImpl.hpp"
#include <cerrno>
#include <cassert>

namespace OW_NAMESPACE
{

namespace NonRecursiveMutexImpl
{

/**
 * Create a platform specific mutext handle.
 * @param handle	The mutex handle that should be initialized by this method
 * @return 0 on success. Otherwise -1.
 */
int
createMutex(NonRecursiveMutex_t& handle)
{
#if defined(OW_USE_PTHREAD)
	pthread_mutexattr_t attr;
	int res = pthread_mutexattr_init(&attr);
	assert(res == 0);
	if (res != 0)
	{
		return -1;
	}
 
	res = pthread_mutex_init(&handle.mutex, &attr);
	pthread_mutexattr_destroy(&attr);
	if (res != 0)
	{
		return -1;
	}
 
	return 0;
#elif defined(OW_WIN32)
	int cc = -1;
	if ((handle = CreateMutex(NULL, FALSE, NULL)))
	{
		cc = 0;
	}
	return cc;
#else
#error "port me!"
#endif
}
/**
 * Destroy a mutex previously created with createMutex.
 * @param handle The handle to the mutex that will be destroyed.
 * @return The following error codes:
 *		 0:	success
 *		-1:	Could not be acquired for destruction because it is currently
 *				locked.
 *		-2:	All other error conditions
 */
int
destroyMutex(NonRecursiveMutex_t& handle)
{
#if defined(OW_USE_PTHREAD)
	switch (pthread_mutex_destroy(&handle.mutex))
	{
		case 0:
			break;
		case EBUSY:
			return -1;
			break;
		default:
			return -2;
	}
	return 0;
#elif defined (OW_WIN32)
	ReleaseMutex(handle);
	return (CloseHandle(handle) == 0) ? -2 : 0;
#else
#error "port me!"
#endif
}
/**
 * Acquire the mutex specified by a given mutex handle. This method should
 * block until the desired mutex can be acquired. The error return value is
 * used to indicate critical errors.
 *
 * @param handle The mutex to acquire.
 * @return 0 on success. -1 indicates a critical error.
 */
int
acquireMutex(NonRecursiveMutex_t& handle)
{
#if defined (OW_USE_PTHREAD)
	int res = pthread_mutex_lock(&handle.mutex);
	assert(res == 0);
	return res;
#elif defined (OW_WIN32)
	int cc = -1;
	if (WaitForSingleObject(handle, INFINITE) != WAIT_FAILED)
	{
		cc = 0;
	}
	return cc;
#else
#error "port me!"
#endif
}
/**
 * Release a mutex that was previously acquired with the acquireMutex
 * method.
 * @param handle The handle to the mutex that is being released.
 * @return 0 on success. -1 indicates a critical error.
 */
int
releaseMutex(NonRecursiveMutex_t& handle)
{
#if defined (OW_USE_PTHREAD)
	int res = pthread_mutex_unlock(&handle.mutex);
	assert(res == 0);
	return res;
 
#elif defined (OW_WIN32)
	return (ReleaseMutex(handle)) ? 0 : -1;
#else
#error "port me!"
#endif
}

int
conditionPreWait(NonRecursiveMutex_t& handle, NonRecursiveMutexLockState& state)
{
#if defined (OW_WIN32)
	state.pmutex = &handle;
#else
	state.pmutex = &handle.mutex;
#endif
	return 0;
}
int
conditionPostWait(NonRecursiveMutex_t& handle, NonRecursiveMutexLockState& state)
{
	return 0;
}

} // end namespace NonRecursiveMutexImpl
} // end namespace OW_NAMESPACE

