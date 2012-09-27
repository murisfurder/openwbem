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

#ifndef OW_CIMEXCEPTION_HPP_INCLUDE_GUARD_
#define OW_CIMEXCEPTION_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_Exception.hpp"

namespace OW_NAMESPACE
{

class OW_COMMON_API CIMException : public Exception
{
public:
	enum ErrNoType
	{
		/** No error */
		SUCCESS = 0,
		/**
		 * A general error occured that is not covered by a more specific error
		 * code
		 */
		FAILED = 1,
		/** Access to a CIM resource was not available to the client */
		ACCESS_DENIED = 2,
		/** The target namespace does not exist */
		INVALID_NAMESPACE = 3,
		/** One or more parameter values passed to the method were invalid */
		INVALID_PARAMETER = 4,
		/** The specified Class does not exist */
		INVALID_CLASS = 5,
		/** The requested object could not be found */
		NOT_FOUND = 6,
		/** The requested operation is not supported */
		NOT_SUPPORTED = 7,
		/**
		 * Operation cannot be carried out on this class since it has subclasses
		 */
		CLASS_HAS_CHILDREN = 8,
		/**
		 * Operation cannot be carried out on this class since it has instances
		 */
		CLASS_HAS_INSTANCES = 9,
		/**
		 * Operation cannot be carried out since the specified superclass does
		 * not exist
		 */
		INVALID_SUPERCLASS = 10,
		/** Operation cannot be carried out because an object already exists */
		ALREADY_EXISTS = 11,
		/** The specified Property does not exist */
		NO_SUCH_PROPERTY = 12,
		/** The value supplied is incompatible with the type */
		TYPE_MISMATCH = 13,
		/** The query language is not recognized or supported */
		QUERY_LANGUAGE_NOT_SUPPORTED = 14,
		/** The query is not valid for the specified query language */
		INVALID_QUERY = 15,
		/** The extrinsic Method could not be executed */
		METHOD_NOT_AVAILABLE = 16,
		/** The specified extrinsic Method does not exist */
		METHOD_NOT_FOUND = 17
	};

	CIMException(const char* file, int line, ErrNoType errval,
		const char* msg=0, const Exception* otherException = 0);

	virtual ~CIMException() throw();
	void swap(CIMException& x);
	CIMException(const CIMException& x);
	CIMException& operator=(const CIMException& x);
	
	ErrNoType getErrNo() const { return ErrNoType(getErrorCode()); }
	void setErrNo(ErrNoType e) { setErrorCode(e); }
	/**
	 * A CIMException consists of a code (ErrNoType), and an optional message for further clarification.
	 * getMessage() returns the textual representation of the code (as returned by getCodeDescription) followed by
	 * the optional message in parenthesis.
	 * This function returns just the optional message, as passed to the constructor. If not available, 0 will be returned.
	 */
	const char* getDescription() const;
	virtual const char* type() const;
	virtual CIMException* clone() const throw();

	/**
	 * Get a static string description of errCode.
	 * This function is thread safe. Each description is stored in a separate buffer.
	 * Caller must not free or modify the result.
	 * If errCode is invalid a pointer to "unknown error" will be returned.
	 */
	static const char* getCodeDescription(ErrNoType errCode);

private:
	const char* m_description;
};

/**
 * Throw a CIMException with error code errval.
 * Consider providing a message and using OW_THROWCIMMSG instead of this macro.
 * @param errval One of the CIMException::ErrNoType enumerated values
 */
#define OW_THROWCIM(errval) \
	throw CIMException(__FILE__, __LINE__, (errval))
	
/**
 * Throw a CIMException with error code errval, and a subexception.
 * subex.getMessage() will be used as the message for this exception
 * @param errval One of the CIMException::ErrNoType enumerated values
 * @param subex A sub-exception. A pointer to it will be passed to the
 *   exception constructor, which should clone() it.
 */
#define OW_THROWCIM_SUBEX(errval, subex) \
	throw CIMException(__FILE__, __LINE__, (errval), (subex).getMessage(), &(subex))
	
/**
 * Throw a CIMException with error code errval and a message
 * @param errval One of the CIMException::ErrNoType enumerated values
 * @param msg A message associated with the exception
 */
#define OW_THROWCIMMSG(errval, msg) \
	throw CIMException(__FILE__, __LINE__, (errval), (msg))

/**
 * Throw a CIMException with error code errval, a message and a subexception
 * @param errval One of the CIMException::ErrNoType enumerated values
 * @param msg A message associated with the exception
 * @param subex A sub-exception. A pointer to it will be passed to the
 *   exception constructor, which should clone() it.
 */
#define OW_THROWCIMMSG_SUBEX(errval, msg, subex) \
	throw CIMException(__FILE__, __LINE__, (errval), (msg), &(subex))
	
} // end namespace OW_NAMESPACE

#endif
