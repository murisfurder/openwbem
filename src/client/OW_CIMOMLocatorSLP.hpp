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

#ifndef OW_CIMOMLOCATORSLP_HPP_INCLUDE_GUARD_
#define OW_CIMOMLOCATORSLP_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_CIMOMLocator.hpp"

#ifdef OW_HAVE_SLP_H
#include <slp.h>

// The classes and functions defined in this file are not meant for general
// use, they are internal implementation details.  They may change at any time.

#define OW_CIMOM_SLP_SERVICE_TYPE "wbem"
#define OW_CIMOM_SLP_URL_PREFIX "service:"OW_CIMOM_SLP_SERVICE_TYPE":"

namespace OW_NAMESPACE
{

class OW_CLIENT_API CIMOMLocatorSLP : public CIMOMLocator
{
public:
	CIMOMLocatorSLP(); 
	CIMOMInfoArray findCIMOMs();
	virtual ~CIMOMLocatorSLP();
private:
#ifdef OW_HAVE_SLP_H
	SLPHandle m_hslp; 
#endif // OW_HAVE_SLP_H
	static void processAttributes(const String& attrs, CIMOMInfo& info);
};

} // end namespace OW_NAMESPACE

#endif // OW_HAVE_SLP_H

#endif
