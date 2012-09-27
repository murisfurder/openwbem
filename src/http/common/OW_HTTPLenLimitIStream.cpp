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
#include "OW_HTTPLenLimitIStream.hpp"

namespace OW_NAMESPACE
{

using std::istream;
HTTPLengthLimitStreamBuffer::HTTPLengthLimitStreamBuffer(
		istream& istr, UInt64 length)
	: BaseStreamBuffer(2048, "in"), m_istr(istr),
	  m_length(length), m_pos(0), m_isEnd(false)
// 2048 is a nice power of 2 that should be more than enough to hold most
// packets, since ethernet MTU is 1500
{
}
//////////////////////////////////////////////////////////////////////////////
HTTPLengthLimitStreamBuffer::~HTTPLengthLimitStreamBuffer()
{
}
//////////////////////////////////////////////////////////////////////////////
int
HTTPLengthLimitStreamBuffer::buffer_from_device(char* c, int n)
{
	if (m_isEnd || n < 0)
	{
		return -1;
	}
	unsigned int un = n; 
	// min of n and (length - pos)
	int tmpInLen = (un < (m_length - m_pos)) ? un : (m_length - m_pos);
	m_istr.read(c, tmpInLen);
	int lastRead = m_istr.gcount();
	m_pos += lastRead;
	if (m_pos == m_length)
	{
		m_isEnd = true;
	}
	return lastRead;
}
//////////////////////////////////////////////////////////////////////////////
void
HTTPLengthLimitStreamBuffer::resetLen(UInt64 len)
{
	initGetBuffer();
	m_length = len;
	m_pos = 0;
	m_isEnd = false;
}
//////////////////////////////////////////////////////////////////////////////
void
HTTPLenLimitIStream::resetLen(UInt64 len)
{
	clear();
	m_strbuf.resetLen(len);
}
//////////////////////////////////////////////////////////////////////////////
HTTPLenLimitIStream::HTTPLenLimitIStream(istream& istr, UInt64 len)
	: HTTPLenLimitIStreamBase(istr, len)
	, CIMProtocolIStreamIFC(&m_strbuf)
	, m_istr(istr)
{
}
//////////////////////////////////////////////////////////////////////////////

} // end namespace OW_NAMESPACE

