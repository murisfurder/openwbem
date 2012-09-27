/*******************************************************************************
* Copyright (C) 2003-2004 Vintela, Inc. All rights reserved.
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
 * @author Jon Carey
 * @author Dan Nuffer
 */

#include "OW_config.h"
#include "OW_StringStream.hpp"

namespace OW_NAMESPACE
{

///////////////////////////////////////////////////////////////////////////////
OStringStreamBuf::OStringStreamBuf(size_t size)
	: BaseStreamBuffer(size, "out"), m_buf(size)
{
}
///////////////////////////////////////////////////////////////////////////////
OStringStreamBuf::~OStringStreamBuf()
{
}
///////////////////////////////////////////////////////////////////////////////
String OStringStreamBuf::toString() const
{
	return m_buf.toString();
}
///////////////////////////////////////////////////////////////////////////////
String OStringStreamBuf::releaseString()
{
	return m_buf.releaseString();
}
///////////////////////////////////////////////////////////////////////////////
size_t OStringStreamBuf::length() const
{
	return m_buf.length();
}
///////////////////////////////////////////////////////////////////////////////
const char* OStringStreamBuf::c_str() const
{
	return m_buf.c_str();
}
///////////////////////////////////////////////////////////////////////////////
void OStringStreamBuf::reset()
{
	m_buf.reset();
}
///////////////////////////////////////////////////////////////////////////////
int OStringStreamBuf::buffer_to_device(const char *c, int n)
{
	m_buf.append(c, n);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
OStringStreamBase::OStringStreamBase(size_t sz)
	: m_buf(sz)
{
}
///////////////////////////////////////////////////////////////////////////////
OStringStream::OStringStream(size_t size)
	: OStringStreamBase(size)
	, std::basic_ostream<char, std::char_traits<char> >(&m_buf)
{
}
///////////////////////////////////////////////////////////////////////////////
OStringStream::~OStringStream()
{
}
///////////////////////////////////////////////////////////////////////////////
OStringStream::OStringStream(const OStringStream& ostr)
#if !defined(__GNUC__) || __GNUC__ > 2
	: std::basic_ios<char>()
#else
	: std::ios() // gcc 2.95.x broken library.
#endif
	, OStringStreamBase(ostr.length())
	, std::basic_ostream<char, std::char_traits<char> >(&m_buf)
{
	*this << ostr.toString();
}
///////////////////////////////////////////////////////////////////////////////
OStringStream& OStringStream::operator=(const OStringStream& ostr)
{
	if ( &ostr != this )
	{
		this->reset();
		*this << ostr.toString();
	}
	return *this;
}


///////////////////////////////////////////////////////////////////////////////
String OStringStream::toString() const
{
	m_buf.sync();
	return m_buf.toString();
}
///////////////////////////////////////////////////////////////////////////////
String OStringStream::releaseString()
{
	m_buf.sync();
	return m_buf.releaseString();
}
///////////////////////////////////////////////////////////////////////////////
size_t OStringStream::length() const
{
	m_buf.sync();
	return m_buf.length();
}
///////////////////////////////////////////////////////////////////////////////
const char* OStringStream::c_str() const
{
	m_buf.sync();
	return m_buf.c_str();
}
///////////////////////////////////////////////////////////////////////////////
void OStringStream::reset()
{
	m_buf.reset();
}

} // end namespace OW_NAMESPACE

