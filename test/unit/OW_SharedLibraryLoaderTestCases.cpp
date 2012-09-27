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
#include "OW_SharedLibraryLoaderTestCases.hpp"
#include "OW_SharedLibraryLoader.hpp"
#include "OW_SharedLibrary.hpp"
#include "testSharedLibraryLoader.hpp"

using namespace OpenWBEM;

namespace
{
	const String COMPONENT_NAME("ow.test");
}

void OW_SharedLibraryLoaderTestCases::setUp()
{
}

void OW_SharedLibraryLoaderTestCases::tearDown()
{
}

	
void OW_SharedLibraryLoaderTestCases::testLoadSharedLibrary()
{
	testSharedLibraryLoader sll;
	SharedLibraryRef slp = sll.loadSharedLibrary( "testlib", g_testEnvironment->getLogger(COMPONENT_NAME) );
	unitAssert( slp );
}

Test* OW_SharedLibraryLoaderTestCases::suite()
{
	TestSuite *testSuite = new TestSuite ("OW_SharedLibraryLoader");

	testSuite->addTest (new TestCaller <OW_SharedLibraryLoaderTestCases>
			("testLoadSharedLibrary",
			&OW_SharedLibraryLoaderTestCases::testLoadSharedLibrary));

	return testSuite;
}

