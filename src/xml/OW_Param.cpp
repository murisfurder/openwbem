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

//
// OW_Param.cpp
//
#include	<OW_config.h>
#include	"OW_Param.hpp"

namespace OW_NAMESPACE
{

Param::Param(const String& argname, Param::ParamValues mode, const String& value) : m_argName(argname), m_argValue(value), m_argMode(mode)
{
}
Param::Param(const String& argname, const String& value) : m_argName(argname), m_argValue(value), m_argMode(VALUENOTSET)
{
}
Param::Param(const String& argname, bool value) : m_argName(argname), m_argValue(), m_argMode(VALUENOTSET)
{
	if (value)
	{
		m_argValue = "TRUE";
	}
	else		    
	{
		m_argValue = "FALSE";
	}
}
	
String
Param::getArgName() const 
{
	return m_argName;
}
String
Param::getArgValue() const 
{
	if (!m_argValue.empty())
	{
		if (m_argMode==VALUENOTSET)
		{
			return(String("<VALUE>"+m_argValue+"</VALUE>"));
		}
		else
		{
			return(m_argValue);
		}
	}
	return String();
}

} // end namespace OW_NAMESPACE

