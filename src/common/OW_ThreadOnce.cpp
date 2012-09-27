/*******************************************************************************
* Copyright (C) 2005 Vintela, Inc. All rights reserved.
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
#include "OW_ThreadOnce.hpp"
#include "OW_Assertion.hpp"

#if defined(OW_WIN32)

#include <stdio.h>

namespace OW_NAMESPACE
{

void callOnce(OnceFlag& flag, void (*func)())
{
	// this is the double-checked locking pattern, but with a bit more strength than normally implemented :-)
    if (InterlockedCompareExchange(&flag, 1, 1) == 0)
    {
		wchar_t mutexName[MAX_PATH];
		_snwprintf(mutexName, MAX_PATH, L"%X-%p-587ccea9-c95a-4e81-ac51-ab0ddc6cef63", GetCurrentProcessId(), &flag);
		mutexName[MAX_PATH - 1] = 0;

        HANDLE mutex = CreateMutexW(NULL, FALSE, mutexName);
        OW_ASSERT(mutex != NULL);

        int res = 0;
        res = WaitForSingleObject(mutex, INFINITE);
        OW_ASSERT(res == WAIT_OBJECT_0);

        if (InterlockedCompareExchange(&flag, 1, 1) == 0)
        {
            try
            {
                func();
            }
            catch (...)
            {
                res = ReleaseMutex(mutex);
                OW_ASSERT(res);
                res = CloseHandle(mutex);
                OW_ASSERT(res);
                throw;
            }
            InterlockedExchange(&flag, 1);
        }

        res = ReleaseMutex(mutex);
        OW_ASSERT(res);
        res = CloseHandle(mutex);
        OW_ASSERT(res);
    }
}


} // end namespace OW_NAMESPACE

#endif


