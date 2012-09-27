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
 * @author Bart Whiteley
 * @author Dan Nuffer
 */

#include "OW_config.h"
#include "OW_RandomNumber.hpp"
#include "OW_Assertion.hpp"
#include "OW_ThreadOnce.hpp"
#include "OW_Mutex.hpp"
#include "OW_MutexLock.hpp"
#include <fstream>
#include <sys/types.h>

#ifdef OW_HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef OW_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#include <stdlib.h>
#include <time.h>

namespace OW_NAMESPACE
{

/////////////////////////////////////////////////////////////////////////////
namespace
{
OnceFlag guard;
unsigned int seed = 0;
}

/////////////////////////////////////////////////////////////////////////////
RandomNumber::RandomNumber(Int32 lowVal, Int32 highVal)
: m_lowVal(lowVal), m_highVal(highVal)
{
	if (lowVal > highVal)
	{
		m_lowVal = highVal;
		m_highVal = lowVal;
	}
	callOnce(guard, &initRandomness);
}
	
/////////////////////////////////////////////////////////////////////////////
void
RandomNumber::initRandomness()
{
#ifdef OW_WIN32
	time_t timeval = ::time(NULL);
	seed = timeval;
#else
	// use the time as part of the seed
	struct timeval tv;
	gettimeofday(&tv, 0);
	// try to get something from the kernel
	std::ifstream infile("/dev/urandom", std::ios::in);
	if (!infile)
	{
		infile.open("/dev/random", std::ios::in);
	}
	// don't initialize this, we may get random stack
	// junk in case infile isn't usable.
	unsigned int dev_rand_input;
	if (infile)
	{
		infile.read(reinterpret_cast<char*>(&dev_rand_input), sizeof(dev_rand_input));
		infile.close();
	}
	// Build the seed. Take into account our pid and uid.
	seed = dev_rand_input ^ (getpid() << 16) ^ getuid() ^ tv.tv_sec ^ tv.tv_usec;
#endif
#ifdef OW_HAVE_SRANDOM
	srandom(seed);
#else
	srand(seed);
#endif
}

/////////////////////////////////////////////////////////////////////////////
void
RandomNumber::saveRandomState()
{
	// Do nothing. This function is so that RandomNumber has the same interface as CryptographicRandomNumber
}

namespace
{
Mutex g_guard;
}
/////////////////////////////////////////////////////////////////////////////
Int32
RandomNumber::getNextNumber()
{
	MutexLock lock(g_guard);
#ifdef OW_HAVE_RANDOM
	return m_lowVal + (random() % (m_highVal - m_lowVal + 1));
#else
	return m_lowVal + (rand() % (m_highVal - m_lowVal + 1));
#endif
}

} // end namespace OW_NAMESPACE

