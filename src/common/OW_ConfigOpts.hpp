/*******************************************************************************
* Copyright (C) 2004 Vintela, Inc. All rights reserved.
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

#ifndef OW_CONFIGOPTS_HPP_INCLUDE_GUARD_
#define OW_CONFIGOPTS_HPP_INCLUDE_GUARD_
#include "OW_config.h"
#include "OW_Types.hpp" // for OW_SHAREDLIB_EXTENSION

#ifndef OW_DEFAULT_DEBUGFLAG
#define OW_DEFAULT_DEBUGFLAG "false"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_HTTP_PORT
#define OW_DEFAULT_HTTP_SERVER_HTTP_PORT "5988"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_HTTPS_PORT
#define OW_DEFAULT_HTTP_SERVER_HTTPS_PORT "5989"
#endif
#ifndef OW_DEFAULT_LOG_LOCATION
#define OW_DEFAULT_LOG_LOCATION "syslog"
#endif
#ifndef OW_DEFAULT_LOG_LEVEL
#define OW_DEFAULT_LOG_LEVEL "error"
#endif
// deprecated - use OW_DEFAULT_OWLIBDIR instead
#ifndef OW_DEFAULT_OWLIB_DIR
#define OW_DEFAULT_OWLIB_DIR OW_DEFAULT_LIB_DIR"/openwbem"
#endif
#ifndef OW_DEFAULT_OWLIBDIR
#define OW_DEFAULT_OWLIBDIR OW_DEFAULT_LIB_DIR"/openwbem"
#endif
#ifndef OW_DEFAULT_PROVIDER_IFC_LIBS
#define OW_DEFAULT_PROVIDER_IFC_LIBS OW_DEFAULT_OWLIBDIR"/provifcs"
#endif
#ifndef OW_DEFAULT_SERVICES_PATH
#define OW_DEFAULT_SERVICES_PATH OW_DEFAULT_OWLIBDIR"/services"
#endif
#ifndef OW_DEFAULT_REQUEST_HANDLER_PATH
#define OW_DEFAULT_REQUEST_HANDLER_PATH OW_DEFAULT_OWLIBDIR"/requesthandlers"
#endif
#ifndef OW_DEFAULT_CPPPROVIFC_PROV_LOCATION
#define OW_DEFAULT_CPPPROVIFC_PROV_LOCATION OW_DEFAULT_OWLIBDIR"/c++providers"
#endif
#ifndef OW_DEFAULT_NPIPROVIFC_PROV_LOCATION
#define OW_DEFAULT_NPIPROVIFC_PROV_LOCATION OW_DEFAULT_OWLIBDIR"/npiproviders"
#endif
#ifndef OW_DEFAULT_CMPIPROVIFC_PROV_LOCATION
#define OW_DEFAULT_CMPIPROVIFC_PROV_LOCATION OW_DEFAULT_OWLIBDIR"/cmpiproviders"
#endif
#ifndef OW_DEFAULT_PERLPROVIFC_PROV_LOCATION
#define OW_DEFAULT_PERLPROVIFC_PROV_LOCATION OW_DEFAULT_OWLIBDIR"/perlproviders"
#endif
#ifndef OW_DEFAULT_AUTHENTICATION_MODULE
#define OW_DEFAULT_AUTHENTICATION_MODULE OW_DEFAULT_OWLIBDIR"/authentication/libpamauthentication"OW_SHAREDLIB_EXTENSION
#endif
#ifndef OW_DEFAULT_CONFIG_FILE
#define OW_DEFAULT_CONFIG_FILE OW_DEFAULT_SYSCONF_DIR"/openwbem/openwbem.conf"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_DIGEST_PASSWORD_FILE
#define OW_DEFAULT_HTTP_SERVER_DIGEST_PASSWORD_FILE OW_DEFAULT_SYSCONF_DIR"/openwbem/digest_auth.passwd"
#endif
#ifndef OW_DEFAULT_SIMPLE_AUTH_PASSWORD_FILE
#define OW_DEFAULT_SIMPLE_AUTH_PASSWORD_FILE OW_DEFAULT_SYSCONF_DIR"/openwbem/simple_auth.passwd"
#endif
// deprecated - use OW_DEFAULT_DATADIR instead
#ifndef OW_DEFAULT_DATA_DIR
#define OW_DEFAULT_DATA_DIR OW_DEFAULT_STATE_DIR"/lib/openwbem"
#endif
#ifndef OW_DEFAULT_DATADIR
#define OW_DEFAULT_DATADIR OW_DEFAULT_STATE_DIR"/lib/openwbem"
#endif
#ifndef OW_DEFAULT_OWLIBEXECDIR
#define OW_DEFAULT_OWLIBEXECDIR OW_DEFAULT_LIBEXEC_DIR"/openwbem"
#endif
#ifndef OW_DEFAULT_ALLOW_ANONYMOUS
#define OW_DEFAULT_ALLOW_ANONYMOUS "false"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_MAX_CONNECTIONS
#define OW_DEFAULT_HTTP_SERVER_MAX_CONNECTIONS "30"
#endif
#ifndef OW_DEFAULT_DISABLE_INDICATIONS
#define OW_DEFAULT_DISABLE_INDICATIONS "false"
#endif
#ifndef OW_DEFAULT_WQL_LIB
#define OW_DEFAULT_WQL_LIB OW_DEFAULT_LIB_DIR"/libowwql"OW_SHAREDLIB_EXTENSION
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_ENABLE_DEFLATE
#define OW_DEFAULT_HTTP_SERVER_ENABLE_DEFLATE "true"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_USE_UDS
#define OW_DEFAULT_HTTP_SERVER_USE_UDS "true"
#endif
#ifndef OW_DEFAULT_CPPPROVIFC_PROV_TTL
#define OW_DEFAULT_CPPPROVIFC_PROV_TTL "5"
#endif
#ifndef OW_DEFAULT_CMPIPROVIFC_PROV_TTL
#define OW_DEFAULT_CMPIPROVIFC_PROV_TTL "-1"
#endif
#ifndef OW_DEFAULT_REQUEST_HANDLER_TTL
#define OW_DEFAULT_REQUEST_HANDLER_TTL "5"
#endif
#ifndef OW_DEFAULT_MAX_CLASS_CACHE_SIZE_I
#define OW_DEFAULT_MAX_CLASS_CACHE_SIZE_I 128
#endif
#ifndef OW_DEFAULT_MAX_CLASS_CACHE_SIZE
#define OW_DEFAULT_MAX_CLASS_CACHE_SIZE "128"
#endif
#ifndef OW_DEFAULT_CHECK_REFERENTIAL_INTEGRITY
#define OW_DEFAULT_CHECK_REFERENTIAL_INTEGRITY "false"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_SINGLE_THREAD
#define OW_DEFAULT_HTTP_SERVER_SINGLE_THREAD "false"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_USE_DIGEST
#define OW_DEFAULT_HTTP_SERVER_USE_DIGEST "true"
#endif
#ifndef OW_DEFAULT_POLLING_MANAGER_MAX_THREADS
#define OW_DEFAULT_POLLING_MANAGER_MAX_THREADS "256"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_TIMEOUT
#define OW_DEFAULT_HTTP_SERVER_TIMEOUT "300"
#endif
#ifndef OW_DEFAULT_MAX_INDICATION_EXPORT_THREADS
#define OW_DEFAULT_MAX_INDICATION_EXPORT_THREADS "30"
#endif
#ifndef OW_DEFAULT_RESTART_ON_ERROR
#define OW_DEFAULT_RESTART_ON_ERROR "true"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_LISTEN_ADDRESSES
#define OW_DEFAULT_HTTP_SERVER_LISTEN_ADDRESSES "0.0.0.0"
#endif
#ifndef OW_DEFAULT_SLP_ENABLE_ADVERTISEMENT
#define OW_DEFAULT_SLP_ENABLE_ADVERTISEMENT "true"
#endif
#ifndef OW_DEFAULT_INTEROP_SCHEMA_NAMESPACE
#define OW_DEFAULT_INTEROP_SCHEMA_NAMESPACE "root"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_UDS_FILENAME
#define OW_DEFAULT_HTTP_SERVER_UDS_FILENAME "/tmp/OW@LCL@APIIPC_72859_Xq47Bf_P9r761-5_J-7_Q"OW_PACKAGE_PREFIX
#endif
#ifndef OW_DEFAULT_ALLOW_LOCAL_AUTHENTICATION
#define OW_DEFAULT_ALLOW_LOCAL_AUTHENTICATION "false"
#endif
#ifndef OW_DEFAULT_REMOTEPROVIFC_MAX_CONNECTIONS_PER_URL
#define OW_DEFAULT_REMOTEPROVIFC_MAX_CONNECTIONS_PER_URL "5"
#endif
#ifndef OW_DEFAULT_ALLOWED_USERS
#define OW_DEFAULT_ALLOWED_USERS "*"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_DEFAULT_CONTENT_LANGUAGE
#define OW_DEFAULT_HTTP_SERVER_DEFAULT_CONTENT_LANGUAGE "en"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_SSL_CLIENT_VERIFICATION
#define OW_DEFAULT_HTTP_SERVER_SSL_CLIENT_VERIFICATION "disabled"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_SSL_TRUST_STORE
#define OW_DEFAULT_HTTP_SERVER_SSL_TRUST_STORE OW_DEFAULT_SYSCONF_DIR"/openwbem/truststore"
#endif
#ifndef OW_DEFAULT_LOG_1_TYPE
#define OW_DEFAULT_LOG_1_TYPE "syslog"
#endif
#ifndef OW_DEFAULT_LOG_1_COMPONENTS
#define OW_DEFAULT_LOG_1_COMPONENTS "*"
#endif
#ifndef OW_DEFAULT_LOG_1_LEVEL
#define OW_DEFAULT_LOG_1_LEVEL "error"
#endif
#ifndef OW_DEFAULT_LOG_1_FORMAT
#define OW_DEFAULT_LOG_1_FORMAT "[%t]%m"
#endif
#ifndef OW_DEFAULT_LOG_1_MAX_FILE_SIZE
#define OW_DEFAULT_LOG_1_MAX_FILE_SIZE "0"
#endif
#ifndef OW_DEFAULT_LOG_1_MAX_BACKUP_INDEX
#define OW_DEFAULT_LOG_1_MAX_BACKUP_INDEX "1"
#endif
#ifndef OW_DEFAULT_LOG_1_FLUSH
#define OW_DEFAULT_LOG_1_FLUSH "true"
#endif
#ifndef OW_DEFAULT_DISABLE_CPP_PROVIDER_INTERFACE
#define OW_DEFAULT_DISABLE_CPP_PROVIDER_INTERFACE "false"
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_ALLOW_LOCAL_AUTHENTICATION
#define OW_DEFAULT_HTTP_SERVER_ALLOW_LOCAL_AUTHENTICATION "false" 
#endif
#ifndef OW_DEFAULT_HTTP_SERVER_REUSE_ADDR
#define OW_DEFAULT_HTTP_SERVER_REUSE_ADDR "true" 
#endif
#ifndef OW_DEFAULT_OWBI1IFC_PROV_LOCATION
#define OW_DEFAULT_OWBI1IFC_PROV_LOCATION OW_DEFAULT_OWLIBDIR"/owbi1providers"
#endif
#ifndef OW_DEFAULT_OWBI1IFC_PROV_TTL
#define OW_DEFAULT_OWBI1IFC_PROV_TTL "5"
#endif
#ifndef OW_DEFAULT_PIDFILE
#define OW_DEFAULT_PIDFILE OW_PIDFILE_DIR "/" OW_PACKAGE_PREFIX "owcimomd.pid"
#endif
#ifndef OW_DEFAULT_DROP_ROOT_PRIVILEGES
#define OW_DEFAULT_DROP_ROOT_PRIVILEGES "false"
#endif
#ifndef OW_DEFAULT_ADDITIONAL_CONFIG_FILES_DIRS
#define OW_DEFAULT_ADDITIONAL_CONFIG_FILES_DIRS OW_DEFAULT_SYSCONF_DIR"/openwbem/openwbem.conf.d"
#endif


namespace OW_NAMESPACE
{
namespace ConfigOpts
{
	// Naming rule: if the option begins with owcimomd, name is the same text all caps w/out owcimomd and _opt.
	// If the options begins with something else, the prefix must be part of the all caps name.
	// If the option has a default, the default macro is named OW_DEFAULT_<all caps name>
	static const char* const DEBUGFLAG_opt = "owcimomd.debugflag";
	static const char* const CONFIG_FILE_opt = "owcimomd.config_file";
	static const char* const LOG_LOCATION_opt = "owcimomd.log_location";
	static const char* const LOG_LEVEL_opt = "owcimomd.log_level";
	static const char* const PROVIDER_IFC_LIBS_opt = "owcimomd.provider_ifc_libs";
	static const char* const ONLYHELP_opt = "owcimomd.onlyhelp";
	static const char* const LIBEXECDIR_opt = "owcimomd.libexecdir";
	static const char* const OWLIBDIR_opt = "owcimomd.owlibdir";
	static const char* const DATADIR_opt = "owcimomd.datadir";
	static const char* const ALLOW_ANONYMOUS_opt = "owcimomd.allow_anonymous";
	static const char* const PAM_ALLOWED_USERS_opt = "pam.allowed_users";
	static const char* const SIMPLE_AUTH_PASSWORD_FILE_opt = "simple_auth.password_file";
	static const char* const AUTHENTICATION_MODULE_opt = "owcimomd.authentication_module";
	static const char* const DUMP_SOCKET_IO_opt = "owcimomd.dump_socket_io";
	static const char* const CPPPROVIFC_PROV_LOCATION_opt = "cppprovifc.prov_location";
	static const char* const DISABLE_INDICATIONS_opt = "owcimomd.disable_indications";
	static const char* const WQL_LIB_opt = "owcimomd.wql_lib";
	static const char* const ACL_SUPERUSER_opt = "owcimomd.ACL_superuser";
	// 2.0 additions
	static const char* const SERVICES_PATH_opt = "owcimomd.services_path";
	static const char* const REQUEST_HANDLER_PATH_opt = "owcimomd.request_handler_path";
	static const char* const SLP_ENABLE_ADVERTISEMENT_opt = "slp.enable_advertisement";
	static const char* const HTTP_SERVER_USE_UDS_opt = "http_server.use_UDS";
	static const char* const NPIPROVIFC_PROV_LOCATION_opt = "npiprovifc.prov_location";
	static const char* const HTTP_SERVER_SINGLE_THREAD_opt = "http_server.single_thread";
	static const char* const HTTP_SERVER_HTTP_PORT_opt = "http_server.http_port";
	static const char* const HTTP_SERVER_HTTPS_PORT_opt = "http_server.https_port";
	static const char* const HTTP_SERVER_ENABLE_DEFLATE_opt = "http_server.enable_deflate";
	static const char* const HTTP_SERVER_USE_DIGEST_opt = "http_server.use_digest";
#ifndef OW_DISABLE_DIGEST
	static const char* const HTTP_SERVER_DIGEST_PASSWORD_FILE_opt = "http_server.digest_password_file";
#endif
	static const char* const HTTP_SERVER_MAX_CONNECTIONS_opt = "http_server.max_connections";
	static const char* const HTTP_SERVER_SSL_CERT_opt = "http_server.SSL_cert";
	static const char* const HTTP_SERVER_SSL_KEY_opt = "http_server.SSL_key";
	static const char* const CPPPROVIFC_PROV_TTL_opt = "cppprovifc.prov_TTL";
	static const char* const REQUEST_HANDLER_TTL_opt = "owcimomd.request_handler_TTL";
	static const char* const MAX_CLASS_CACHE_SIZE_opt = "owcimomd.max_class_cache_size";
	// 3.0 additions
	static const char* const HTTP_SERVER_REUSE_ADDR_opt = "http_server.reuse_addr";
	static const char* const CMPIPROVIFC_PROV_LOCATION_opt = "cmpiprovifc.prov_location";
	static const char* const CMPIPROVIFC_PROV_TTL_opt = "cmpiprovifc.prov_TTL";
	static const char* const PERLPROVIFC_PROV_LOCATION_opt = "perlprovifc.prov_location";
	static const char* const CHECK_REFERENTIAL_INTEGRITY_opt = "owcimomd.check_referential_integrity";
	static const char* const POLLING_MANAGER_MAX_THREADS_opt = "owcimomd.polling_manager_max_threads";
	static const char* const HTTP_SERVER_TIMEOUT_opt = "http_server.timeout";
	static const char* const MAX_INDICATION_EXPORT_THREADS_opt = "owcimomd.max_indication_export_threads";
	static const char* const RESTART_ON_ERROR_opt = "owcimomd.restart_on_error";
	static const char* const AUTHORIZATION_LIB_opt = "owcimomd.authorization_lib";
	static const char* const AUTHORIZATION2_LIB_opt = "owcimomd.authorization2_lib";
	static const char* const HTTP_SERVER_LISTEN_ADDRESSES_opt = "http_server.listen_addresses";
	static const char* const INTEROP_SCHEMA_NAMESPACE_opt = "owcimomd.interop_schema_namespace";
	static const char* const HTTP_SERVER_UDS_FILENAME_opt = "http_server.uds_filename";
	static const char* const HTTP_SERVER_ALLOW_LOCAL_AUTHENTICATION_opt = "http_server.allow_local_authentication";
	static const char* const REMOTEPROVIFC_MAX_CONNECTIONS_PER_URL_opt = "remoteprovifc.max_connections_per_url";
	static const char* const ALLOWED_USERS_opt = "owcimomd.allowed_users";
	static const char* const HTTP_SERVER_DEFAULT_CONTENT_LANGUAGE_opt = "http_server.default_content_language";
	// 3.1 additions.
	static const char* const HTTP_SERVER_SSL_CLIENT_VERIFICATION_opt = "http_server.ssl_client_verification";
	static const char* const HTTP_SERVER_SSL_TRUST_STORE = "http_server.ssl_trust_store";
	static const char* const ADDITIONAL_LOGS_opt = "owcimomd.additional_logs";
	static const char* const DISABLE_CPP_PROVIDER_INTERFACE_opt = "owcimomd.disable_cpp_provider_interface";
	// These aren't a whole config option, but log names, which are substituted as part of the log options
	static const char* const LOG_DEBUG_LOG_NAME = "debug";
	static const char* const LOG_MAIN_LOG_NAME = "main";
	// These log options aren't usable as is, the log name has to be substituted in using Format()
	static const char* const LOG_1_TYPE_opt = "log.%1.type";
	static const char* const LOG_1_COMPONENTS_opt = "log.%1.components";
	static const char* const LOG_1_CATEGORIES_opt = "log.%1.categories";
	static const char* const LOG_1_LEVEL_opt = "log.%1.level";
	static const char* const LOG_1_FORMAT_opt = "log.%1.format";
	static const char* const LOG_1_LOCATION_opt = "log.%1.location";
	static const char* const LOG_1_MAX_FILE_SIZE_opt = "log.%1.max_file_size";
	static const char* const LOG_1_MAX_BACKUP_INDEX_opt = "log.%1.max_backup_index";
	// 3.2 additions.
	static const char* const OWBI1IFC_PROV_LOCATION_opt = "owbi1provifc.prov_location";
	static const char* const OWBI1IFC_PROV_TTL_opt = "owbi1provifc.prov_ttl";
	static const char* const LOG_1_FLUSH_opt = "log.%1.flush";

	static const char* const PIDFILE_opt = "owcimomd.pidfile";
	static const char* const DROP_ROOT_PRIVILEGES_opt = "owcimomd.drop_root_privileges";
	static const char* const ADDITIONAL_CONFIG_FILES_DIRS_opt = "owcimomd.additional_config_files_dirs";

	static const char* const EXPLICIT_REGISTRATION_NAMESPACES_opt = "owcimomd.explicit_registration_namespaces";

	// Naming rule: if the option begins with owcimomd, name is the same text all caps w/out owcimomd and _opt.
	// If the options begins with something else, the prefix must be part of the all caps name.
	// If the option has a default, the default macro is named OW_DEFAULT_<all caps name>


	struct NameAndDefault {
		const char* name; 
		const char* defaultValue; 
	}; 
	extern const NameAndDefault g_defaults[];
	extern const NameAndDefault* const g_defaultsEnd;

} // end namespace ConfigOpts
} // end namespace OW_NAMESPACE

#endif
