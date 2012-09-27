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
#include "OW_SocketUtilsTestCases.hpp"
#include "OW_SocketUtils.hpp"
#include "OW_SocketException.hpp"
#include "OW_String.hpp"

using namespace OpenWBEM;

void OW_SocketUtilsTestCases::setUp()
{
}

void OW_SocketUtilsTestCases::tearDown()
{
}

void OW_SocketUtilsTestCases::testGetFullyQualifiedHostName()
{
	// If this doesn't throw, then make sure it worked.
	try
	{
		String hn = SocketUtils::getFullyQualifiedHostName();
		unitAssert(!hn.empty());
		unitAssert(hn.indexOf('.') != String::npos);
	}
	catch (const SocketException& e)
	{
	}
}

Test* OW_SocketUtilsTestCases::suite()
{
	TestSuite *testSuite = new TestSuite ("OW_SocketUtils");

	ADD_TEST_TO_SUITE(OW_SocketUtilsTestCases, testGetFullyQualifiedHostName);

	return testSuite;
}

