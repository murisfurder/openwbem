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

#ifndef OW_MOF_COMPILER_HPP_INCLUDE_GUARD_
#define OW_MOF_COMPILER_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_CIMOMHandleIFC.hpp"
#include "OW_String.hpp"
#include "OW_MOFParserErrorHandlerIFC.hpp"
#include "OW_Exception.hpp"
#include "OW_Array.hpp"
#include "OW_MOFLineInfo.hpp"
#include "OW_MOFGrammar.hpp"
#include "OW_CIMFwd.hpp"
#include "OW_Logger.hpp"

#ifdef OW_WIN32
#pragma warning (push)
#pragma warning (disable: 4251)
#endif

// these 2 need to be at global scope because flex also declares them.
struct owmof_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;

namespace OW_NAMESPACE
{

OW_DECLARE_APIEXCEPTION(MOFCompiler, OW_MOF_API);

namespace MOF
{

class OW_MOF_API Compiler
{
public:
	struct Options
	{
		Options()
			: m_createNamespaces(false)
			, m_checkSyntaxOnly(false)
			, m_remove(false)
			, m_preserve(false)
			, m_upgrade(true)
			, m_ignoreDoubleIncludes(false)
			, m_removeDescriptions(false)
			, m_removeObjects(false)
		{}
		Options(const String& namespace_,
			bool createNamespaces, bool checkSyntaxOnly, const String& dumpXmlFile,
			bool remove, bool preserve, bool upgrade, const StringArray& includeDirs,
			bool ignoreDoubleIncludes, bool removeDescriptions, bool removeObjects, 
			const String& depSearchDir = "")
			: m_namespace(namespace_)
			, m_createNamespaces(createNamespaces)
			, m_checkSyntaxOnly(checkSyntaxOnly)
			, m_dumpXmlFile(dumpXmlFile)
			, m_remove(remove)
			, m_preserve(preserve)
			, m_upgrade(upgrade)
			, m_includeDirs(includeDirs)
			, m_ignoreDoubleIncludes(ignoreDoubleIncludes)
			, m_removeDescriptions(removeDescriptions)
			, m_removeObjects(removeObjects)
			, m_depSearchDir(depSearchDir)
		{
		}

		String m_namespace;
		bool m_createNamespaces;
		bool m_checkSyntaxOnly;
		String m_dumpXmlFile;
		bool m_remove;
		bool m_preserve;
		bool m_upgrade;
		StringArray m_includeDirs;
		bool m_ignoreDoubleIncludes;
		bool m_removeDescriptions;
		bool m_removeObjects;
		String m_depSearchDir; 
	};

	Compiler( const CIMOMHandleIFCRef& ch, const Options& opts, const ParserErrorHandlerIFCRef& mpeh );
	~Compiler();
	long compile( const String& filename );
	long compileString( const String& mof );
	static String fixParsedString(const String& s);

	ParserErrorHandlerIFCRef theErrorHandler;
	AutoPtr<MOFSpecification> mofSpecification;
	String basepath;

	// This variable is only for convenience for the lexer and parser.
	// After parsing is complete, it should not be used.  The filename and
	// line numbers are stored in the AST.
	LineInfo theLineInfo;

	// Needed by the code to implement includes
	enum
	{
		E_MAX_INCLUDE_DEPTH = 100
	};

	struct include_t
	{
		YY_BUFFER_STATE owmofBufferState;
		LineInfo theLineInfo;
	};

	include_t include_stack[E_MAX_INCLUDE_DEPTH];
	int include_stack_ptr;

private:
	CIMOMHandleIFCRef m_ch;
	Options m_opts;
	// unimplemented
	Compiler(const Compiler& x);
	Compiler& operator=(const Compiler& x);

};


OW_MOF_API CIMInstance compileInstanceFromMOF(const String& instMOF, const LoggerRef& logger = LoggerRef()) OW_DEPRECATED; // in 3.2.0
OW_MOF_API CIMInstanceArray compileInstancesFromMOF(const String& instMOF, const LoggerRef& logger = LoggerRef()) OW_DEPRECATED; // in 3.2.0
OW_MOF_API CIMInstanceArray compileInstancesFromMOF(const String& instMOF, const CIMOMHandleIFCRef& realhdl, const String& ns, const LoggerRef& logger = LoggerRef()) OW_DEPRECATED; // in 3.2.0

/**
 * @param realhdl If null, a dummy handle will be used which will supply "fake" CIMClasses and CIMQualifierTypes to the mof compiler
 */
OW_MOF_API void compileMOF(const String& mof, const CIMOMHandleIFCRef& realhdl, const String& ns,
	CIMInstanceArray& instances, CIMClassArray& classes, CIMQualifierTypeArray& qualifierTypes, const LoggerRef& logger = LoggerRef());



} // end namespace MOF
} // end namespace OW_NAMESPACE

#ifdef OW_WIN32
#pragma warning (pop)
#endif

#endif // MOF_COMPILER_HPP_
