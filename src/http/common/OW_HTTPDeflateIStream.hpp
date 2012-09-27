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

#ifndef OW_HTTPDEFLATEISTREAM_HPP_INCLUDE_GUARD_
#define OW_HTTPDEFLATEISTREAM_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#ifdef OW_HAVE_ZLIB_H
#include "OW_CIMProtocolIStreamIFC.hpp"
#include "OW_BaseStreamBuffer.hpp"
#include "OW_AutoPtr.hpp"
#include "OW_IfcsFwd.hpp"
#include <zlib.h>

namespace OW_NAMESPACE
{

class OW_HTTP_API HTTPDeflateIStreamBuffer : public BaseStreamBuffer
{
public:
	HTTPDeflateIStreamBuffer(std::istream& istr);
	~HTTPDeflateIStreamBuffer();
protected:
	virtual int buffer_from_device(char *, int);
private:
	std::istream& m_istr;
	z_stream m_zstr;
	enum { m_inBufSize = HTTP_BUF_SIZE };

	Bytef m_inBuf[m_inBufSize];
	// don't allow copying and assigning
	HTTPDeflateIStreamBuffer(const HTTPDeflateIStreamBuffer&);
	HTTPDeflateIStreamBuffer& operator=(HTTPDeflateIStreamBuffer&);
};
//////////////////////////////////////////////////////////////////////////////
class OW_HTTP_API HTTPDeflateIStreamBase
{
public:
	HTTPDeflateIStreamBase(std::istream& istr)
		: m_strbuf(istr) {}
	HTTPDeflateIStreamBuffer m_strbuf;
};
//////////////////////////////////////////////////////////////////////////////
class OW_HTTP_API HTTPDeflateIStream : private HTTPDeflateIStreamBase,
	public CIMProtocolIStreamIFC
{
public:
	/**
	 * Convert an istream to a HTTPDeflateIStream.  This wraps the
	 * istream.  Anything read from the new istream, is first read from
	 * the original istream, and then inflated.
	 * @param istr the original istream to wrap.
	 */
	HTTPDeflateIStream(const CIMProtocolIStreamIFCRef& istr);
	/**
	 * Get the original istream
	 * @return the original istream.
	 */
	CIMProtocolIStreamIFCRef getInputStreamOrig();
	// TODO: Move all this knowledge about CIM and specific trailers into HTTPClient
	virtual void checkForError() const;
private:

#ifdef OW_WIN32
#pragma warning (push)
#pragma warning (disable: 4251)
#endif

	CIMProtocolIStreamIFCRef m_istr;

#ifdef OW_WIN32
#pragma warning (pop)
#endif

	// don't allow copying and assigning
	HTTPDeflateIStream(const HTTPDeflateIStream&);
	HTTPDeflateIStream& operator=(HTTPDeflateIStream&);
};

} // end namespace OW_NAMESPACE

#endif
#endif // #ifdef OW_HAVE_ZLIB_H
