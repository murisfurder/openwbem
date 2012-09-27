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
#include "OW_File.hpp"

#ifdef OW_WIN32
	#include <io.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <memory.h>
#else
	#include <fcntl.h>
	#ifdef OW_HAVE_UNISTD_H
		#include <unistd.h>
	#endif
#endif


namespace OW_NAMESPACE
{
#ifdef OW_WIN32
namespace
{
/////////////////////////////////////////////////////////////////////////////
// implementation of lock functions
int
doLock(HANDLE hFile, bool doWait)
{
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	DWORD flags = LOCKFILE_EXCLUSIVE_LOCK;
	if (!doWait)
	{
		flags |= LOCKFILE_FAIL_IMMEDIATELY;
	}

	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));
	if (!LockFileEx(hFile, flags, 0, 0xffffffff,
		0xffffffff, &ov))
	{
		return -1;
	}

	return 0;
}

} // end unnamed namespace

/////////////////////////////////////////////////////////////////////////////
File::File(const File& x) : m_hdl(OW_INVALID_FILEHANDLE)
{
	if( x.m_hdl != OW_INVALID_FILEHANDLE )
	{
		DuplicateHandle(GetCurrentProcess(), x.m_hdl, GetCurrentProcess(),
			&m_hdl , 0, FALSE, DUPLICATE_SAME_ACCESS);
	}
}
/////////////////////////////////////////////////////////////////////////////
int 
File::getLock()
{
	return doLock(m_hdl, true);
}
/////////////////////////////////////////////////////////////////////////////
int
File::tryLock()
{
	return doLock(m_hdl, false);
}
/////////////////////////////////////////////////////////////////////////////
int
File::unlock()
{
	if (m_hdl == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));
	if (!UnlockFileEx(m_hdl, 0, 0xffffffff, 0xffffffff, &ov))
	{
		return -1;
	}

	return 0;
}

#else	// NOT WIN32

/////////////////////////////////////////////////////////////////////////////
File::File(const File& x) : m_hdl(dup(x.m_hdl))
{
}

namespace {
/////////////////////////////////////////////////////////////////////////////
// implementation of lock functions
int
doLock(int hdl, int cmd, short int type)
{
	struct flock lck;
	::memset (&lck, '\0', sizeof (lck));
	lck.l_type = type;          // type of lock
	lck.l_whence = 0;           // 0 offset for l_start
	lck.l_start = 0L;           // lock starts at BOF
	lck.l_len = 0L;             // extent is entire file
	return ::fcntl(hdl, cmd, &lck);
}
} // end unnamed namespace
/////////////////////////////////////////////////////////////////////////////
int 
File::getLock()
{
	return doLock(m_hdl, F_SETLKW, F_WRLCK);
}
/////////////////////////////////////////////////////////////////////////////
int
File::tryLock()
{
	return doLock(m_hdl, F_SETLK, F_WRLCK);
}
/////////////////////////////////////////////////////////////////////////////
int
File::unlock()
{
	return doLock(m_hdl, F_SETLK, F_UNLCK);
}
#endif

} // end namespace OW_NAMESPACE

