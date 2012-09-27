/*******************************************************************************
* Copyright (C) 2001-3 Vintela, Inc. All rights reserved.
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




/* autoconf set variables here */

@TOP@

/* The system has OpenSSL headers and libs */
#undef HAVE_OPENSSL

/* The system doesn't have OpenSSL */
#undef NO_SSL

/* Dirs from configure */
#undef DEFAULT_SYSCONF_DIR
#undef DEFAULT_STATE_DIR
#undef DEFAULT_LIB_DIR
#undef DEFAULT_LIBEXEC_DIR
#undef PIDFILE_DIR

/* Either "" or the argument to --with-package-prefix */
#undef PACKAGE_PREFIX

/* Defined if --enable-stack-trace was passed to configure */
#undef ENABLE_STACK_TRACE_ON_EXCEPTIONS

/* Defined if --enable-debug was passed to configure */
#undef DEBUG

/* Defined if --enable-profile was passed to configure */
#undef PROFILE

/* Defined if we are building gnu pthreads version */
#undef USE_PTHREAD

/* Defined if we want to use custom "new" operator to debug memory leaks */
#undef DEBUG_MEMORY

/* Define if we want to print "Entering"/"Leaving" <functionName> */
#undef PRINT_FUNC_DEBUG

/* Define if we want to check for NULL references and throw an exception */
#undef CHECK_NULL_REFERENCES

/* Define if we want to check for valid array indexing and throw an exception */
#undef CHECK_ARRAY_INDEXING

/* Define if we want to build the perlIFC */
#undef PERLIFC

/* Define which one is the current platform */
#undef GNU_LINUX
#undef OPENUNIX
#undef SOLARIS
#undef OPENSERVER
#undef DARWIN
#undef HPUX
#undef FREEBSD


#undef u_int8_t
#undef u_int16_t
#undef u_int32_t
#undef HAVE_SOCKLEN_T

#undef HAVE_PTHREAD_MUTEXATTR_SETTYPE
#undef HAVE_PTHREAD_SPIN_LOCK
#undef HAVE_PTHREAD_BARRIER
#undef HAVE_PAM

/* Define if system has dlfcn.h */
#undef USE_DL
/* Define if system has shl_*() <dl.h> */
#undef USE_SHL
/* Define if a system has dyld.h (Mac OS X) */
#undef USE_DYLD

#undef DISABLE_DIGEST
#undef DISABLE_ASSOCIATION_TRAVERSAL
#undef DISABLE_QUALIFIER_DECLARATION
#undef DISABLE_SCHEMA_MANIPULATION
#undef DISABLE_INSTANCE_MANIPULATION
#undef DISABLE_PROPERTY_OPERATIONS
#undef DISABLE_NAMESPACE_MANIPULATION

/* Define to enable workarounds so we can work with valgrind */
#undef VALGRIND_SUPPORT

/* Define to enable workarounds for non-thread safe exception handling support */
#undef NON_THREAD_SAFE_EXCEPTION_HANDLING

@BOTTOM@

/* end of autoconf set vars */

/**
 * The OW_DEPRECATED macro can be used to trigger compile-time warnings
 * with gcc >= 3.2 when deprecated functions are used.
 *
 * For non-inline functions, the macro is used at the very end of the
 * function declaration, right before the semicolon, unless it's pure
 * virtual:
 *
 * int deprecatedFunc() const OW_DEPRECATED;
 * virtual int deprecatedPureVirtualFunc() const OW_DEPRECATED = 0;
 *
 * Functions which are implemented inline are handled differently:
 * the OW_DEPRECATED macro is used at the front, right before the return
 * type, but after "static" or "virtual":
 *
 * OW_DEPRECATED void deprecatedFuncA() { .. }
 * virtual OW_DEPRECATED int deprecatedFuncB() { .. }
 * static OW_DEPRECATED bool deprecatedFuncC() { .. }
 *
 * You can also mark whole structs or classes as deprecated, by inserting the
 * OW_DEPRECATED macro after the struct/class keyword, but before the
 * name of the struct/class:
 *
 * class OW_DEPRECATED DeprecatedClass { };
 * struct OW_DEPRECATED DeprecatedStruct { };
 * 
 * However, deprecating a struct/class doesn't create a warning for gcc 
 * versions <= 3.3 (haven't tried 3.4 yet).  If you want to deprecate a class,
 * also deprecate all member functions as well (which will cause warnings).
 *
 */
#if __GNUC__ - 0 > 3 || (__GNUC__ - 0 == 3 && __GNUC_MINOR__ - 0 >= 2)
#define DEPRECATED __attribute__ ((deprecated))
#else
#define DEPRECATED
#endif



#ifdef OW_WIN32
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#else
#define EXPORT
#define IMPORT
#endif

#ifdef OW_COMMON_BUILD
#define COMMON_API OW_EXPORT
#else
#define COMMON_API OW_IMPORT
#endif

#ifdef OW_XML_BUILD
#define XML_API OW_EXPORT
#else
#define XML_API OW_IMPORT
#endif

#ifdef OW_MOF_BUILD
#define MOF_API OW_EXPORT
#else
#define MOF_API OW_IMPORT
#endif

#ifdef OW_HTTP_BUILD
#define HTTP_API OW_EXPORT
#else
#define HTTP_API OW_IMPORT
#endif

#ifdef OW_HTTPSVC_BUILD
#define HTTPSVC_API OW_EXPORT
#else
#define HTTPSVC_API OW_IMPORT
#endif

#ifdef OW_LISTENER_BUILD
#define LISTENER_API OW_EXPORT
#else
#define LISTENER_API OW_IMPORT
#endif


#ifdef OW_CLIENT_BUILD
#define CLIENT_API OW_EXPORT
#else
#define CLIENT_API OW_IMPORT
#endif

#ifdef OW_DB_BUILD
#define DB_API OW_EXPORT
#else
#define DB_API OW_IMPORT
#endif

#ifdef OW_REPHDB_BUILD
#define HDB_API OW_EXPORT
#else
#define HDB_API OW_IMPORT
#endif

#ifdef OW_WQL_BUILD
#define WQL_API OW_EXPORT
#else
#define WQL_API OW_IMPORT
#endif

#ifdef OW_WQLCOMMON_BUILD
#define WQLCOMMON_API OW_EXPORT
#else
#define WQLCOMMON_API OW_IMPORT
#endif

#ifdef OW_PROVIDER_BUILD
#define PROVIDER_API OW_EXPORT
#else
#define PROVIDER_API OW_IMPORT
#endif

#ifdef OW_CPPPROVIFC_BUILD
#define CPPPROVIFC_API OW_EXPORT
#else
#define CPPPROVIFC_API OW_IMPORT
#endif

#ifdef OW_CIMOMSERVER_BUILD
#define CIMOMSERVER_API OW_EXPORT
#else
#define CIMOMSERVER_API OW_IMPORT
#endif

#ifdef OW_CIMOMCOMMON_BUILD
#define CIMOMCOMMON_API OW_EXPORT
#else
#define CIMOMCOMMON_API OW_IMPORT
#endif

#ifdef OW_INDICATIONSERVER_BUILD
#define INDICATIONSERVER_API OW_EXPORT
#else
#define INDICATIONSERVER_API OW_IMPORT
#endif

#ifdef OW_INDICATIONREPLAYER_BUILD
#define INDICATIONREPLAYER_API OW_EXPORT
#else
#define INDICATIONREPLAYER_API OW_IMPORT
#endif

#ifdef OW_PROVIDERAGENT_BUILD
#define PROVIDERAGENT_API OW_EXPORT
#else
#define PROVIDERAGENT_API OW_IMPORT
#endif

#ifdef OW_OWBI1PROVIFC_BUILD
#define OWBI1PROVIFC_API OW_EXPORT
#else
#define OWBI1PROVIFC_API OW_IMPORT
#endif

#ifdef OW_WIN32
#define EXPORT_TEMPLATE(API, TMPL, X) template class API TMPL< X >
#else
#define EXPORT_TEMPLATE(API, TMPL, X)
#endif

/* C++ specific stuff here */
#ifdef __cplusplus

/* Need this first macro because ## doesn't expand vars, and we need an intermediate step */
#define NAMESPACE_CAT(ow, ver) ow ## ver
#define NAMESPACE_AUX(ver) OW_NAMESPACE_CAT(OpenWBEM, ver)
#define NAMESPACE OW_NAMESPACE_AUX(OW_OPENWBEM_LIBRARY_VERSION)

/* This is so this particular code is only active in OW_config.h, not OWBI1_config.h */
#ifdef OW_NAMESPACE
/* need this to set up an alias. */
namespace OW_NAMESPACE
{
}

namespace OpenWBEM = OW_NAMESPACE;
#endif

#ifdef OW_DEBUG_MEMORY
#include "OW_MemTracer.hpp"
#endif



#endif /* #ifdef __cplusplus */

