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

#ifndef OW_THREAD_TYPES_HPP_
#define OW_THREAD_TYPES_HPP_
#include "OW_config.h"

// The classes and functions defined in this file are not meant for general
// use, they are internal implementation details.  They may change at any time.

#if defined(OW_USE_PTHREAD)

	#include <pthread.h>

	namespace OW_NAMESPACE
	{

		// Platform specific thread type
		typedef pthread_t			Thread_t;
		typedef pthread_mutex_t NativeMutex_t;
		struct NonRecursiveMutex_t
		{
			pthread_mutex_t mutex;
		};

		#if defined(OW_HAVE_PTHREAD_MUTEXATTR_SETTYPE)
		// Platform specific mutex type
		// we have native recursive mutexes.
		struct Mutex_t
		{
			pthread_mutex_t mutex;
		};

		#else

		// we have to emulate recursive mutexes.
		struct Mutex_t
		{
			pthread_mutex_t mutex;
			pthread_cond_t unlocked;
			bool valid_id;
			unsigned count;
			pthread_t thread_id;
		};
		#endif

		// Platform specific conditional variable type
		typedef pthread_cond_t 			ConditionVar_t;
		struct NonRecursiveMutexLockState
		{
			pthread_t thread_id;
			NativeMutex_t* pmutex;
		};

	} // end namespace OW_NAMESPACE

#elif defined(OW_WIN32)

	namespace OW_NAMESPACE
	{
		// Platform specific thread type
		typedef DWORD Thread_t;
		typedef HANDLE NativeMutex_t;
		typedef HANDLE NonRecursiveMutex_t;
		typedef LPCRITICAL_SECTION Mutex_t;

		// Platform specific conditional variable type
		typedef struct
		{
			// Number of waiting threads
			int waitersCount;
			// Serialize access to waitersCount
			CRITICAL_SECTION waitersCountLock;
			// Semaphore used to queue up threads waiting for the condition to
			// become signaled
            HANDLE queue;
			// An auto-reset event used during broadcasting to wait for all the 
			// threads to wake up and be released from the queue
			HANDLE waitersDone;
			// Keeps track of whether we are broadcasting or signaling. This allows
			// for optimization if just signaling.
			bool wasBroadcast;
		} ConditionInfo_t;

		typedef ConditionInfo_t* ConditionVar_t;
		//typedef void* 			ConditionVar_t;
		struct NonRecursiveMutexLockState
		{
			DWORD thread_id;
			NativeMutex_t* pmutex;
		};

	} // end namespace OW_NAMESPACE

#endif

#endif	// #ifndef OW_THREAD_TYPES_HPP_
				
