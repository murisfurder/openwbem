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
#include "OW_Param.hpp"
#include "OW_XMLOperationGeneric.hpp"
#include "OW_Assertion.hpp"
#include "OW_CIMErrorException.hpp"
#include "OW_CIMXMLParser.hpp"

namespace OW_NAMESPACE
{

using std::istream;
using std::ostream;
void
XMLOperationGeneric::XMLGetCIMElement(CIMXMLParser& parser)
{
	if (!parser.tokenIsId(CIMXMLParser::E_CIM))
	{
		OW_THROW(CIMErrorException, CIMErrorException::request_not_loosely_valid);
	}
	String str = parser.mustGetAttribute(CIMXMLParser::A_CIMVERSION);
	if (!str.equals(CIMXMLParser::AV_CIMVERSION20_VALUE) &&
		!str.equals(CIMXMLParser::AV_CIMVERSION21_VALUE) &&
	!str.equals(CIMXMLParser::AV_CIMVERSION22_VALUE))
	{
		OW_THROW(CIMErrorException,
			CIMErrorException::unsupported_cim_version);
	}
	str = parser.mustGetAttribute(CIMXMLParser::A_DTDVERSION);
	if (!str.equals(CIMXMLParser::AV_DTDVERSION20_VALUE) &&
		!str.equals(CIMXMLParser::AV_DTDVERSION21_VALUE))
	{
		OW_THROW(CIMErrorException,
			CIMErrorException::unsupported_dtd_version);
	}
	parser.getChild();
	if (!parser)
	{
		OW_THROW(CIMErrorException, CIMErrorException::request_not_loosely_valid);
	}
	return;
}

} // end namespace OW_NAMESPACE

