/*******************************************************************************
* Copyright (C) 2001 Vintela, Inc. All rights reserved.
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

#include "OW_config.h"
#include "TestSuite.hpp"
#include "TestCaller.hpp"
#include "CryptographicRandomNumberTestCases.hpp"
#include "OW_CryptographicRandomNumber.hpp"

using namespace OpenWBEM;

void CryptographicRandomNumberTestCases::setUp()
{
	CryptographicRandomNumber::initRandomness();
}

void CryptographicRandomNumberTestCases::tearDown()
{
	CryptographicRandomNumber::saveRandomState();
}

// Need a fairly high test count to get a good test of randomness.
// But don't make it too high, or else the unit tests will be too slow.
const int MIN_TEST_COUNT = 1000;
const int LONG_TEST_COUNT = 100000;
const long long MAX_TEST_COUNT = 10000000;

void CryptographicRandomNumberTestCases::doTestRange(int low, int high)
{
	CryptographicRandomNumber gen(low, high);
	bool saw_low = false;
	bool saw_high = false;
	long long i = 0;
	while ((i < MIN_TEST_COUNT) || ((i < MAX_TEST_COUNT) && (!saw_low || !saw_high)))
	{
		Int32 rn = gen.getNextNumber();
		unitAssert(rn >= low && rn <= high);
		if (rn == low)
		{
			saw_low = true;
		}
		if (rn == high)
		{
			saw_high = true;
		}
		++i;
	}
	unitAssert(saw_low);
	unitAssert(saw_high);
}

void CryptographicRandomNumberTestCases::testRandomNumbers()
{
	// test default.  range: 0-RAND_MAX
	CryptographicRandomNumber g1;
	int count = MIN_TEST_COUNT;
	if (getenv("OWLONGTEST"))
	{
		count = LONG_TEST_COUNT;
	}
	bool hitNonZero = false; 
	for (int i = 0; i < count; ++i)
	{
		Int32 rn = g1.getNextNumber();
		if (rn != 0)
		{
		    hitNonZero = true; 
		}
		unitAssert(rn >= 0 && rn <= RAND_MAX);
	}
	unitAssert(hitNonZero); 

	doTestRange(0, 1);
	doTestRange(0, 2);
	doTestRange(0, 4);
	doTestRange(0, 10);
	doTestRange(0, 15);
	doTestRange(0, 16);
	doTestRange(0, 17);
	doTestRange(1, 16);
	doTestRange(1, 17);
	doTestRange(1, 18);
	doTestRange(0, 1024);
	doTestRange(1000001, 1000010);

}

Test* CryptographicRandomNumberTestCases::suite()
{
	TestSuite *testSuite = new TestSuite ("CryptographicRandomNumber");

	ADD_TEST_TO_SUITE(CryptographicRandomNumberTestCases, testRandomNumbers);

	return testSuite;
}

