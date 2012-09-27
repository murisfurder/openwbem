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

#ifndef OW_CPPINDICATIONEXPORTXMLHTTPPROVIDER_HPP_INCLUDE_GUARD_
#define OW_CPPINDICATIONEXPORTXMLHTTPPROVIDER_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_CppIndicationExportProviderIFC.hpp"
#include "OW_HTTPClient.hpp"
#include "OW_Mutex.hpp"
#include <list>

namespace OW_NAMESPACE
{

class CppIndicationExportXMLHTTPProvider : public CppIndicationExportProviderIFC
{
public:
	CppIndicationExportXMLHTTPProvider();
	~CppIndicationExportXMLHTTPProvider();
	/**
	 * Export the given indication
	 */
	virtual void exportIndication(const ProviderEnvironmentIFCRef& env,
		const String& ns,
		const CIMInstance &indHandlerInst, const CIMInstance &indicationInst);
	/**
	 * @return The class names of all the CIM_CppIndicationHandler sub-classes
	 * this IndicationExportProvider handles.
	 */
	virtual StringArray getHandlerClassNames();
	/**
	 * Called by the CIMOM when the provider is initialized
	 *
	 * @param hdl The handle to the cimom
	 *
	 * @throws CIMException
	 */
	virtual void initialize(const ProviderEnvironmentIFCRef&) {}

	virtual void doCooperativeCancel();
private:
	// We store these (vs. keeping it on the stack) so that when a cancellation request is made
	// close() can be called which will stop the exporting thread(s).
	std::list<HTTPClientRef> m_httpClients;
	Mutex m_guard;
	bool m_cancelled;
};

} // end namespace OW_NAMESPACE

#endif
