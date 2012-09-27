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


#include "TestSuite.hpp"
#include "TestCaller.hpp"
#include "OW_ThreadBarrierTestCases.hpp"
#include "OW_ThreadBarrier.hpp"
#include "OW_Thread.hpp"

using namespace OpenWBEM;

void OW_ThreadBarrierTestCases::setUp()
{
}

void OW_ThreadBarrierTestCases::tearDown()
{
}

namespace {

class testThread : public Thread
{
public:
	testThread(const ThreadBarrier& b, bool& f)
		: Thread()
		, barrier(b)
		, flag(f)
	{
	}

	virtual Int32 run()
	{
		barrier.wait();
		flag = true;
		barrier.wait();
		return 0;
	}

private:
	ThreadBarrier barrier;
	bool& flag;
};


} // end anonymous namespace

void OW_ThreadBarrierTestCases::testBarrier()
{
	ThreadBarrier barrier(2);
	bool flag = false;
	testThread anotherThread(barrier, flag);
	anotherThread.start();
	unitAssert(flag == false);
	ThreadImpl::yield(); // give the other thread a chance to run
	unitAssert(flag == false);

	barrier.wait();
	// now the other thread should be setting the flag
	barrier.wait();
	// now we can check the value again
	unitAssert(flag == true);

	anotherThread.join();
}

Test* OW_ThreadBarrierTestCases::suite()
{
	TestSuite *testSuite = new TestSuite ("OW_ThreadBarrier");

	ADD_TEST_TO_SUITE(OW_ThreadBarrierTestCases, testBarrier);

	return testSuite;
}

