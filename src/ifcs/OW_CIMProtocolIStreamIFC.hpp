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

#ifndef OW_CIMPROTOCOLISTREAMIFC_HPP_INCLUDE_GUARD_
#define OW_CIMPROTOCOLISTREAMIFC_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_String.hpp"
#include "OW_IntrusiveReference.hpp"
#include "OW_IntrusiveCountableBase.hpp"

#if defined(OW_HAVE_ISTREAM)
#include <istream>
#elif defined(OW_HAVE_ISTREAM_H)
#include <istream.h>
#else
#include <iostream>
#endif

// The classes and functions defined in this file are not meant for general
// use, they are internal implementation details.  They may change at any time.

namespace OW_NAMESPACE
{

class OW_COMMON_API CIMProtocolIStreamIFC : public IntrusiveCountableBase, public std::istream
{
public:
	CIMProtocolIStreamIFC(std::streambuf* strbuf);
	// TODO: Move all this knowledge about CIM and specific trailers into HTTPClient
	/**
	 * This function should be called after the end of the stream has
	 * been reached.  It will check the trailers for an error, and throw
	 * an appropriate CIMException (constructed from the info from the
	 * trailers).
	 */
	virtual void checkForError() const;
	virtual ~CIMProtocolIStreamIFC();
};

} // end namespace OW_NAMESPACE

#endif
