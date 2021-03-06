/*******************************************************************************
* Copyright (C) 2004 Vintela, Inc. All rights reserved.
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

#include "OW_config.h"
#include "OW_COWIntrusiveReference.hpp"
#ifdef OW_CHECK_NULL_REFERENCES
#include "OW_Exception.hpp"
#include "OW_ExceptionIds.hpp"
#endif
#ifdef OW_DEBUG
#include <cstdlib> // for abort
#endif

namespace OW_NAMESPACE
{

#ifdef OW_CHECK_NULL_REFERENCES

OW_DECLARE_EXCEPTION(NULLCOWIntrusiveReference);
OW_DEFINE_EXCEPTION_WITH_ID(NULLCOWIntrusiveReference);

namespace COWIntrusiveReferenceHelpers
{

// these are not part of COWIntrusiveReference to try and avoid template bloat.
void throwNULLException()
{
#ifdef OW_DEBUG
	abort(); // segfault so we can get a core
#endif
	OW_THROW(NULLCOWIntrusiveReferenceException, "NULL COWReference dereferenced");
}

}
#endif


} // end namespace OW_NAMESPACE



