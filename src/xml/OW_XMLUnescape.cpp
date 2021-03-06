/* Generated by re2c 0.10.6 on Tue Oct 17 12:05:36 2006 */
#line 1 "OW_XMLUnescape.re"
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

/* a simple lexical scanner to escape xml */
#include "OW_config.h"
#include "OW_XMLUnescape.hpp"
#include "OW_StringBuffer.hpp"
#include "OW_XMLParseException.hpp"
#include "OW_Format.hpp"
#include <limits.h> // for CHAR_MAX
#include <stdlib.h> // for strtol

namespace OW_NAMESPACE
{

String XMLUnescape(const char* escapedText, unsigned len)
{
	StringBuffer rval(len);
	const char* begin = escapedText;
	const char* q;
	const char* thisTokStart = escapedText;
	#define YYCTYPE char
	#define YYCURSOR        begin
	#define YYLIMIT         begin
	#define YYMARKER        q
	#define YYFILL(n)
start:
	
#line 63 "OW_XMLUnescape.cpp"
{
	YYCTYPE yych;

	if((YYLIMIT - YYCURSOR) < 6) { YYFILL(6); }
	yych = *YYCURSOR;
	switch(yych) {
	case 0x00:	goto yy5;
	case '&':	goto yy2;
	default:	goto yy4;
	}
yy2:
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych) {
	case '#':	goto yy7;
	case 'a':	goto yy9;
	case 'g':	goto yy12;
	case 'l':	goto yy11;
	case 'q':	goto yy10;
	default:	goto yy3;
	}
yy3:
#line 92 "OW_XMLUnescape.re"
	{ rval += *(YYCURSOR-1); thisTokStart = YYCURSOR; goto start; }
#line 87 "OW_XMLUnescape.cpp"
yy4:
	yych = *++YYCURSOR;
	goto yy3;
yy5:
	++YYCURSOR;
#line 93 "OW_XMLUnescape.re"
	{ return rval.releaseString(); }
#line 95 "OW_XMLUnescape.cpp"
yy7:
	yych = *++YYCURSOR;
	switch(yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy34;
	case 'x':	goto yy33;
	default:	goto yy8;
	}
yy8:
	YYCURSOR = YYMARKER;
	goto yy3;
yy9:
	yych = *++YYCURSOR;
	switch(yych) {
	case 'm':	goto yy24;
	case 'p':	goto yy25;
	default:	goto yy8;
	}
yy10:
	yych = *++YYCURSOR;
	switch(yych) {
	case 'u':	goto yy19;
	default:	goto yy8;
	}
yy11:
	yych = *++YYCURSOR;
	switch(yych) {
	case 't':	goto yy16;
	default:	goto yy8;
	}
yy12:
	yych = *++YYCURSOR;
	switch(yych) {
	case 't':	goto yy13;
	default:	goto yy8;
	}
yy13:
	yych = *++YYCURSOR;
	switch(yych) {
	case ';':	goto yy14;
	default:	goto yy8;
	}
yy14:
	++YYCURSOR;
#line 65 "OW_XMLUnescape.re"
	{ rval += '>'; thisTokStart = YYCURSOR; goto start; }
#line 150 "OW_XMLUnescape.cpp"
yy16:
	yych = *++YYCURSOR;
	switch(yych) {
	case ';':	goto yy17;
	default:	goto yy8;
	}
yy17:
	++YYCURSOR;
#line 66 "OW_XMLUnescape.re"
	{ rval += '<'; thisTokStart = YYCURSOR; goto start; }
#line 161 "OW_XMLUnescape.cpp"
yy19:
	yych = *++YYCURSOR;
	switch(yych) {
	case 'o':	goto yy20;
	default:	goto yy8;
	}
yy20:
	yych = *++YYCURSOR;
	switch(yych) {
	case 't':	goto yy21;
	default:	goto yy8;
	}
yy21:
	yych = *++YYCURSOR;
	switch(yych) {
	case ';':	goto yy22;
	default:	goto yy8;
	}
yy22:
	++YYCURSOR;
#line 68 "OW_XMLUnescape.re"
	{ rval += '\"'; thisTokStart = YYCURSOR; goto start; }
#line 184 "OW_XMLUnescape.cpp"
yy24:
	yych = *++YYCURSOR;
	switch(yych) {
	case 'p':	goto yy30;
	default:	goto yy8;
	}
yy25:
	yych = *++YYCURSOR;
	switch(yych) {
	case 'o':	goto yy26;
	default:	goto yy8;
	}
yy26:
	yych = *++YYCURSOR;
	switch(yych) {
	case 's':	goto yy27;
	default:	goto yy8;
	}
yy27:
	yych = *++YYCURSOR;
	switch(yych) {
	case ';':	goto yy28;
	default:	goto yy8;
	}
yy28:
	++YYCURSOR;
#line 69 "OW_XMLUnescape.re"
	{ rval += '\''; thisTokStart = YYCURSOR; goto start; }
#line 213 "OW_XMLUnescape.cpp"
yy30:
	yych = *++YYCURSOR;
	switch(yych) {
	case ';':	goto yy31;
	default:	goto yy8;
	}
yy31:
	++YYCURSOR;
#line 67 "OW_XMLUnescape.re"
	{ rval += '&'; thisTokStart = YYCURSOR; goto start; }
#line 224 "OW_XMLUnescape.cpp"
yy33:
	yych = *++YYCURSOR;
	switch(yych) {
	case ';':	goto yy8;
	default:	goto yy39;
	}
yy34:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) { YYFILL(1); }
	yych = *YYCURSOR;
	switch(yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy34;
	case ';':	goto yy36;
	default:	goto yy8;
	}
yy36:
	++YYCURSOR;
#line 82 "OW_XMLUnescape.re"
	{
		unsigned long lval = strtoul( thisTokStart + 2, NULL, 10 );
		if (lval > CHAR_MAX)
		{
			OW_THROWXML(XMLParseException::MALFORMED_REFERENCE, Format("XML escape code in unsupported range: %1", YYCURSOR - 1).c_str());
		}
		char val = lval;
		rval += val;
		thisTokStart = YYCURSOR; goto start;
	}
#line 262 "OW_XMLUnescape.cpp"
yy38:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) { YYFILL(1); }
	yych = *YYCURSOR;
yy39:
	switch(yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy38;
	case ';':	goto yy40;
	default:	goto yy8;
	}
yy40:
	++YYCURSOR;
#line 71 "OW_XMLUnescape.re"
	{
		unsigned long lval = strtoul( thisTokStart + 3, NULL, 16 );
		if (lval > CHAR_MAX)
		{
			OW_THROWXML(XMLParseException::MALFORMED_REFERENCE, Format("XML escape code in unsupported range: %1", YYCURSOR - 1).c_str());
		}
		char val = lval;
		rval += val;
		thisTokStart = YYCURSOR; goto start;
	}
#line 307 "OW_XMLUnescape.cpp"
}
#line 94 "OW_XMLUnescape.re"


	return rval.releaseString();
}

} // end namespace OpenWBEM
