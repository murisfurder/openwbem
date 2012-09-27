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

#include "OW_CIMErrorException.hpp"

namespace OW_NAMESPACE
{

CIMErrorException::CIMErrorException(const char* file, int line, const char* msg)
	: Exception(file, line, msg, Exception::UNKNOWN_ERROR_CODE, 0, ExceptionIds::CIMErrorExceptionId)
{
}

CIMErrorException::~CIMErrorException()	throw()
{
}

const char*
CIMErrorException::type() const
{
	return "CIMErrorException";
}


const char* const CIMErrorException::unsupported_protocol_version =
	"unsupported-protocol-version";
const char* const CIMErrorException::multiple_requests_unsupported =
	"multiple-requests-unsupported";
const char* const CIMErrorException::unsupported_cim_version =
	"unsupported-cim-version";
const char* const CIMErrorException::unsupported_dtd_version =
	"unsupported-dtd-version";
const char* const CIMErrorException::request_not_valid =
	"request-not-valid";
const char* const CIMErrorException::request_not_well_formed =
	"request-not-well-formed";
const char* const CIMErrorException::request_not_loosely_valid =
	"request-not-loosely-valid";
const char* const CIMErrorException::header_mismatch =
	"header-mismatch";
const char* const CIMErrorException::unsupported_operation =
	"unsupported-operation";

} // end namespace OW_NAMESPACE

