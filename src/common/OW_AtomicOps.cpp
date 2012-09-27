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
 ******************************************************************************/

/**
 * @author Dan Nuffer
 */

#include "OW_config.h"
#include "OW_AtomicOps.hpp"

#if defined(OW_USE_PTHREAD_SPIN_LOCK_ATOMIC_OPS)

namespace OW_NAMESPACE
{

Atomic_t::Atomic_t()
	: val(0)
{
	pthread_spin_init(&spinlock, 0);
}
Atomic_t::Atomic_t(int i)
	: val(i)
{
	pthread_spin_init(&spinlock, 0);
}
void AtomicInc(Atomic_t &v)
{
	pthread_spin_lock(&v.spinlock);
	++v.val;
	pthread_spin_unlock(&v.spinlock);
}
bool AtomicDecAndTest(Atomic_t &v)
{
	pthread_spin_lock(&v.spinlock);
	--v.val;
	bool b = ((v.val == 0) ? true : false) ;
	pthread_spin_unlock(&v.spinlock);
	return b;
}
int AtomicGet(Atomic_t const &v)
{
	return v.val;
}
void AtomicDec(Atomic_t &v)
{
	pthread_spin_lock(&v.spinlock);
	--v.val;
	pthread_spin_unlock(&v.spinlock);
}

} // end namespace OW_NAMESPACE

#elif defined(OW_USE_OW_DEFAULT_ATOMIC_OPS)
#include "OW_Mutex.hpp"
#include "OW_MutexLock.hpp"
#include "OW_ThreadOnce.hpp"

namespace OW_NAMESPACE
{

// this needs to be a pointer because of static initialization order conflicts.  
// It shouldn't ever be deleted b/c it may be referenced by a destructor of a 
// static variable that is being deleted.
static Mutex* guard = 0;
static OnceFlag g_once = OW_ONCE_INIT;
static void initGuard()
{
	guard = new Mutex();
}
void AtomicInc(Atomic_t &v)
{
	callOnce(g_once, initGuard);
	MutexLock lock(*guard);
	++v.val;
}
bool AtomicDecAndTest(Atomic_t &v)
{
	callOnce(g_once, initGuard);
	MutexLock lock(*guard);
	return --v.val == 0;
}
int AtomicGet(Atomic_t const &v)
{
	callOnce(g_once, initGuard);
	MutexLock lock(*guard);
	return v.val;
}
void AtomicDec(Atomic_t &v)
{
	callOnce(g_once, initGuard);
	MutexLock lock(*guard);
	--v.val;
}

} // end namespace OW_NAMESPACE

#endif


