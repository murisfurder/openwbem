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

#ifndef OW_POLLEDPROVIDERIFC_HPP_
#define OW_POLLEDPROVIDERIFC_HPP_
#include "OW_config.h"
#include "OW_ProviderBaseIFC.hpp"
#include "OW_ProviderFwd.hpp"
#include "OW_CommonFwd.hpp"
#include "OW_IfcsFwd.hpp"
#include "OW_WBEMFlags.hpp"

namespace OW_NAMESPACE
{

class OW_PROVIDER_API PolledProviderIFC : public ProviderBaseIFC
{
public:
	virtual ~PolledProviderIFC();
	/**
	 * Called by the CIMOM to give this PolledProviderIFC to
	 * opportunity to export indications if needed.
	 * @param ch	A CIMOM handle the provider can use to export
	 *					indications if needed.
	 * @return How many seconds before the next call to the poll method. If this
	 * method returns -1 then the last polling interval will be used. If it
	 * returns 0 then the poll method will never be called again.
	 */
	virtual Int32 poll(const ProviderEnvironmentIFCRef& env) = 0;
	/**
	 * @return The amount of seconds before the first call to the poll method.
	 * If this method returns zero, then the poll method is never called.
	 */
	virtual Int32 getInitialPollingInterval(const ProviderEnvironmentIFCRef& env) = 0;
	/**
	 * This function will be called if the polled provider is running and a
	 * thread cancellation has been requested.
	 */
	virtual void doCooperativeCancel() = 0;
	virtual void doDefinitiveCancel() = 0;
};

typedef IntrusiveReference<PolledProviderIFC> PolledProviderIFCRef;
typedef Array<PolledProviderIFCRef>  PolledProviderIFCRefArray;

} // end namespace OW_NAMESPACE

#endif
