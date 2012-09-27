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
#include "OW_CppMethodProviderIFC.hpp"
#include "OW_Assertion.hpp"
#include "OW_Format.hpp"
#include "OW_CIMValue.hpp"
#include "OW_CIMException.hpp"
#include "OW_CIMObjectPath.hpp"
#include "OW_CIMParamValue.hpp"
#include "OW_CIMInstance.hpp"
#include "OW_Logger.hpp"
#include "OW_Thread.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;
using namespace OpenWBEM;

namespace
{

const String COMPONENT_NAME("ow.test.MethodProviderTest");

class MethodProviderTest: public CppMethodProviderIFC
{
public:
	/**
	 * The CIMOM calls this method when the method specified in the parameters
	 * is to be invoked.
	 *
	 * @param cop Contains the path to the instance whose method must be
	 * 	invoked.
	 * @param methodName The name of the method.
	 * @param inParams An array of CIMValues which are the input parameters
	 * 	for this method.
	 * @param outParams An array of CIMValues which are the output
	 * 	parameters for this method.
	 *
	 * @returns CIMValue - The return value of the method.  If the method
	 * 	has no return value, it must return a default CIMValue().
	 *
	 * @throws CIMException
	 */
	void initialize(const ProviderEnvironmentIFCRef& env);
	virtual ~MethodProviderTest()
	{
	}
	virtual CIMValue invokeMethod(
			const ProviderEnvironmentIFCRef& env,
			const String& ns,
			const CIMObjectPath& path,
			const String &methodName,
			const CIMParamValueArray &in,
			CIMParamValueArray &out);
private:
};
//////////////////////////////////////////////////////////////////////////////
void
MethodProviderTest::initialize(const ProviderEnvironmentIFCRef& env)
{
	OW_LOG_DEBUG(env->getLogger(COMPONENT_NAME), "MethodProviderTest initialize called");
}


String getFileName()
{
    const char* fNameEnv = getenv("OW_METHOD_PROVIDER_TEST_FILENAME");
	if (fNameEnv)
	{
		return fNameEnv;
	}
	return "ow_methodProviderTestFile.txt";
}

String getState()
{
	ifstream ifstr(getFileName().c_str(), std::ios::in);
	if (!ifstr)
	{
		return String("off");
	}
	char buf[80];
	ifstr >> buf;
	String val(buf, strlen(buf));
	if (val.equalsIgnoreCase("on"))
	{
		return String("on");
	}
	else
	{
		return String("off");
	}
	return String();
}

void setState(const String& newState)
{
	ofstream ofstr(getFileName().c_str(), std::ios::out | std::ios::trunc);
	ofstr << newState << endl;
}

void toggleState()
{
	if (getState().equals("off"))
	{
		setState(String("on"));
	}
	else
	{
		setState(String("off"));
	}
}


CIMValue
MethodProviderTest::invokeMethod(
		const ProviderEnvironmentIFCRef&,
		const String& ns,
		const CIMObjectPath& path,
		const String &methodName,
		const CIMParamValueArray &in,
		CIMParamValueArray &out)
{
	if (methodName.equalsIgnoreCase("getstate"))
	{
		// MOF of this method:
		//    string GetState(
		//		[in] string s,
		//		[in] uint8 uint8array[],
		//		[out] boolean b,
		//		[out] real64 r64,
		//		[in, out] sint16 io16,
		//		[out] string msg,
		//		[in, out] CIM_System REF paths[],
		//		[in, out] datetime nullParam);
    		//		[in, out,
                //        EmbeddedInstance("CIM_ResourceAllocationSettingData")]
                //        string embedded_insts[]);

		OW_ASSERT(in.size() == 7);
		OW_ASSERT(out.size() == 8);
		OW_ASSERT(in[0].getName() == "s");
		OW_ASSERT(in[1].getName() == "uint8array");
		OW_ASSERT(in[2].getName() == "io16");
		OW_ASSERT(in[3].getName() == "paths");
		OW_ASSERT(in[4].getName() == "nullParam");
		OW_ASSERT(in[5].getName() == "embedded_insts");
		OW_ASSERT(in[6].getName() == "embedded_inst");
		OW_ASSERT(out[0].getName() == "b");
		OW_ASSERT(out[1].getName() == "r64");
		OW_ASSERT(out[2].getName() == "io16");
		OW_ASSERT(out[2].getValue() == in[2].getValue());
		OW_ASSERT(out[3].getName() == "msg");
		OW_ASSERT(out[4].getName() == "paths");
		OW_ASSERT(out[4].getValue() == in[3].getValue());
		OW_ASSERT(out[5].getName() == "nullParam");
		OW_ASSERT(out[5].getValue() == in[4].getValue());
		OW_ASSERT(out[6].getName() == "embedded_insts");
		OW_ASSERT(out[6].getValue() == in[5].getValue());
		OW_ASSERT(out[7].getName() == "embedded_inst");
		OW_ASSERT(out[7].getValue() == in[6].getValue());
		CIMValue cv = in[5].getValue(); 
		if (cv)
		{
		    CIMInstanceArray insta; 
		    cv.get(insta); 
		    OW_ASSERT(insta.size() == 1); 
		    CIMInstance inst = insta[0]; 
		    OW_ASSERT(inst.getClassName().equalsIgnoreCase(path.getClassName())); 
		    inst.updatePropertyValue("Description", CIMValue(String("another system")));
		    insta.push_back(inst); 
		    out[6].setValue(CIMValue(insta)); 
		    out[7].setValue(CIMValue(inst)); 
		    cv = in[6].getValue(); 
		    cv.get(inst); 
		}
		out[0].setValue(CIMValue(true));
		out[1].setValue(CIMValue(Real64(9.87654321098765e32l)));
		out[2].setValue(CIMValue(Int16(555)));
		out[3].setValue(CIMValue(String(
			Format("MethodProviderTest::invokeMethod.  in[0] = %1, "
				"in[1] = %2, in[2] = %3, in[3] = %4, in[4] = %5, "
			        "in[5] = %6, out[0] = %7, out[1] = %8, %9",
				in[0].toString(), in[1].toString(), in[2].toString(), 
			        in[3].toString(), in[4].toString(), in[5].toString(),
				out[0].toString(), out[1].toString(), 
			       String(Format( "out[2] = %1, out[4] = %2, out[6] = %3",
			       out[2].toString(), out[4].toString(), out[6].toString()))))));

		return CIMValue(getState());
	}
	else if (methodName.equalsIgnoreCase("setstate"))
	{
		OW_ASSERT(in.size() == 1);
		String newState;
		in[0].getValue().get(newState);
		setState(newState);
		return CIMValue(getState());
	}
	else if (methodName.equalsIgnoreCase("togglestate"))
	{
		toggleState();
		return CIMValue(getState());
	}
	else if (methodName.equalsIgnoreCase("Sleep"))
	{
		UInt32 duration = in[0].getValue().toUInt32();
		Thread::sleep(duration * 1000);
		return CIMValue(duration);
	}
	else
	{
		OW_THROWCIMMSG(CIMException::METHOD_NOT_FOUND, Format("Cannot find "
			"method: %1", methodName).c_str());
	}
}

} // end anonymous namespace

OW_PROVIDERFACTORY(MethodProviderTest, methodtest)
