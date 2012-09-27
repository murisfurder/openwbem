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

#ifndef OW_SHAREDLIBRARY_HPP_
#define OW_SHAREDLIBRARY_HPP_
#include "OW_config.h"
#include "OW_String.hpp"
#include "OW_IntrusiveReference.hpp"
#include "OW_IntrusiveCountableBase.hpp"

namespace OW_NAMESPACE
{

/**
 * SharedLibrary is a base class for platform classes that implement the
 * functionality of loading and querying shared libraries.
 */
class OW_COMMON_API SharedLibrary : public IntrusiveCountableBase
{
public:
	virtual ~SharedLibrary();
	/**
	 * given a symbol name, getFunctionPointer will store a pointer to the
	 * function in retval.  If the symbol is found the function returns
	 * true, otherwise false.
	 * This function should be called like this:
	 * typedef ReturnType (*func_t)(param_t p1, ...);
	 * func_t theFunction;
	 * sharedLibrary->getFunctionPointer(sharedLibrary, "FunctionName", theFunction);
	 *
	 * @param functionName	The name of the function to resolve.
	 * @param retval			Will be set to the function pointer.
	 * @return true if function succeeded, false otherwise.
	 */
	template< class fptype >
	bool getFunctionPointer(const String& functionName, fptype& retval )
	{
		return this->doGetFunctionPointer( functionName, reinterpret_cast<void**>(&retval));
	}

protected:
	/**
	 * Derived classes have to override this function to implement
	 * the symbol loading.  The symbol to be looked up is contained in
	 * functionName, and the pointer to the function should be written
	 * into *fp.  Return true if the function succeeded, false otherwise.
	 * @param functionName	The name of the function to resolve.
	 * @param fp				Where to store the function pointer.
	 * @return true if function succeeded, false otherwise.
	 */
	virtual bool doGetFunctionPointer( const String& functionName,
			void** fp ) const = 0;
};
typedef IntrusiveReference<SharedLibrary> SharedLibraryRef;

} // end namespace OW_NAMESPACE

#endif
