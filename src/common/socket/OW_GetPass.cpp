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

#include "OW_config.h"
#include "OW_GetPass.hpp"
#include <cstring>
extern "C"
{
#ifdef OW_HAVE_UNISTD_H
#include <unistd.h>
#endif

#if defined(OW_WIN32)
#include <conio.h>
#include <stdio.h>
#endif
}

#ifdef OW_NETWARE
#include <screen.h>
#endif

namespace OW_NAMESPACE
{

#if defined(OW_WIN32)
#define MAXPASSWORD 128
String
GetPass::getPass(const String& prompt)
{
	int ch, len = 0;
	char bfr[MAXPASSWORD+1];

	bfr[0] = 0;
	_cputs(prompt.c_str());

	do
	{
		ch = _getch();
		if (ch != '\r' && len < MAXPASSWORD)
		{
			bfr[len++] = ch;
			bfr[len] = 0;
			_putch('*');
		}
	} while (ch != '\r');
	printf("\n");
	return String(bfr);
}
#else
String
GetPass::getPass(const String& prompt)
{
#ifdef OW_NETWARE
        char pw[128];
	char* ptr = ::getpassword(prompt.c_str(), pw, 128);
#else
	char* ptr = ::getpass(prompt.c_str());
#endif
	String retStr = ptr;
	memset(ptr, 0x00, strlen(ptr) * sizeof(char));
	return retStr;
}
#endif

} // end namespace OW_NAMESPACE

