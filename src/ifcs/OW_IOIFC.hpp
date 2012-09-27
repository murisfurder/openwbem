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
 * @author Jon Carey
 * @author Dan Nuffer
 */

#ifndef OW_IOIFC_HPP_INCLUDE_GUARD_
#define OW_IOIFC_HPP_INCLUDE_GUARD_
#include "OW_config.h"

namespace OW_NAMESPACE
{

class OW_COMMON_API IOIFC
{
public:
	virtual ~IOIFC();
	/**
	 * Read a specified number of bytes from the device that is exposing
	 * the IOIFC interface.
	 *
	 * @param dataIn A pointer to a location in memory to put the bytes
	 * 	that have been read. 
	 * @param dataInLen The number of bytes being requested from the
	 * 	device. 
	 * @param errorAsException If true and an error occurs durring the read
	 * 	operation, then throw an exception.
	 * @exception An exception will be thrown upon an error condition if
	 * 	errorAsException is true.
	 * @return The number of bytes actually read from the device, or -1 on
	 * 	error. 
	 */
	virtual int read(void* dataIn, int dataInLen,
			bool errorAsException=false) = 0;
			
	/**
	 * Write a specified number of bytes to the device that is exposing the
	 * IOIFC interface.
	 *
	 * @param dataOut A pointer to a location in memory that contains the
	 * 	bytes that will be written to the device.
	 * @param dataOutLen The length of the data pointed to by the dataOut
	 * 	param.
	 * @param errorAsException If true and an error occurs durring the
	 * 	write operation, then throw an exception.
	 * @exception An exception will be thrown upon an error condition if
	 * 	errorAsException is true.	 
	 * @return The number of bytes actually written to the device. or -1 on
	 * 	error
	 */
	virtual int write(const void* dataOut, int dataOutLen,
			bool errorAsException=false) = 0;
};

} // end namespace OW_NAMESPACE

#endif
