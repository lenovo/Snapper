/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include "bson/bson.h"
#include "bson/util/json.h"

#include "odata/edm/edm_model_reader.h"
#include "odata/core/odata_service_document.h"
#include "odata_service_exception.h"

#include <www/engine/request_handler.h>
#include <www/engine/request_context.h>
#include <www/engine/BSONCache.h>
#include "topology.h"
#include "rf_shm_session.h"
#include "json_cache.h"

#include "datainf/DataInterfaceConfigMgr.h"
#include "datainf/DataInterfaceMgr.h"
#include "class/SnapperProvider.h"
#include "class/SnapperSchema.h"
#include "class/ClassCommon.h"

#include <www/engine/rf_jwt.h>
#include <www/engine/rfmon_clt.h>

#include <time.h>
#include <sys/sysinfo.h>
#include <sys/types.h>


using namespace ::std;
using namespace ::snapper::service;
using namespace ::snapper::datamgr;

#ifdef __cplusplus
extern  "C" {
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include "engine_api.h"
#include "engine_cache.h"
#include "protocol.h"
#include "rf_debug.h"
#include "rf_engine_error.h"

#define LOGIN_PATH  "/redfish/v1/SessionService/Sessions"

static int snapper_initialized = 0;
static pthread_mutex_t init_mutex=PTHREAD_MUTEX_INITIALIZER;

std::shared_ptr <::odata::edm::edm_model_reader> snapper_model_reader = nullptr;
std::shared_ptr <::odata::edm::edm_model> snapper_model = nullptr;

int g_engine_loglvl = RF_LOGLVL_INFO;
/************************************************************
 * load schema for engine
 * 
 ***********************************************************/
int snapper_init_engine(char *dir)
{
    ::odata::utility::string_t metadata_dir(dir);
    DIR *dp;
    struct dirent *dirp;
    
    //get xml file list
    if (!dir || (dp  = opendir(metadata_dir.c_str())) == NULL) 
    {
        RF_PRINT("metadata opendir error %s\n", metadata_dir.c_str());
        return -1;
    }
    vector<::odata::utility::string_t> fileNameList;
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        std::size_t found = filename.find_first_of(".");
        if (found != std::string::npos)
        {
            ::odata::utility::string_t fileBase = filename.substr(0,found);
            ::odata::utility::string_t fileExt  = filename.substr(found);


            if ((fileExt.compare(".xml") == 0) && (fileBase.compare("metadata")))
            {                
                ::odata::utility::string_t absFilename = metadata_dir + "/" + filename;
                fileNameList.push_back(absFilename);
            }
        }
    }
    closedir(dp);

    //get OemShim xml file list for oem schema
    std::string oemshim_dir = metadata_dir;
    if (strncmp((const char*)&oemshim_dir.back(), "/", 1) != 0)
        oemshim_dir += "/";
    oemshim_dir += "OemShim/";
    if ((dp  = opendir(oemshim_dir.c_str())) == NULL) 
    {
        RF_PRINT_ERR("OemShim opendir error %s", oemshim_dir.c_str());
        return -1;
    }
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        std::size_t found = filename.find_first_of(".");
        if (found != std::string::npos)
        {
            ::odata::utility::string_t fileBase = filename.substr(0,found);
            ::odata::utility::string_t fileExt  = filename.substr(found);
 
            if (fileExt.compare(".xml") == 0)
            {
                ::odata::utility::string_t absFilename = oemshim_dir + "/" + filename;
                fileNameList.push_back(absFilename);
                //std::cout << "Shim folder" << absFilename << std::endl;
            }
        }
    }
    closedir(dp);


    // build model from schema
    if(!snapper_initialized)
    {
        pthread_mutex_lock( &init_mutex );
        if(!snapper_initialized)
        {
            time_t t1, t2;
            //loading schema
            ::odata::utility::string_t fileName = fileNameList[0];
            std::ifstream ifs(fileName);        
            t1 = time(NULL);
            snapper_model_reader = std::make_shared<::odata::edm::edm_model_reader>(ifs);
            snapper_model_reader->parse_edm();
            snapper_model = snapper_model_reader->get_model();
            
            for (unsigned int i = 1; i < fileNameList.size(); i++)
            {
                ::odata::utility::string_t fileName = fileNameList[i];
                std::ifstream ifs(fileName);        
                snapper_model_reader = std::make_shared<::odata::edm::edm_model_reader>(ifs, snapper_model);
                snapper_model_reader->parse_edm();
            }
            snapper_model_reader->resolve_edm();
            //snapper_model_reader->dump_model();
            t2 = time(NULL);
            RF_PRINT_DBG("==== edm parsing cost %d secs ===\n", (int)(t2-t1));

            //loading datainterface mgr
            DataInterfaceConfigMgr* pDICfgMgr = DataInterfaceConfigMgr::get();
            t1 = time(NULL);
            pDICfgMgr->initialize();
            DataInterfaceMgr::initialize();
            t2 = time(NULL);
            RF_PRINT_DBG("==== datainterface profile parsing cost %d secs ===\n", (int)(t2-t1));

            snapper_initialized = 1;
        }
        pthread_mutex_unlock( &init_mutex );
    }

    return 0;
}
/************************************************************
 * add event destination when sse connection coming
 ***********************************************************/
int sse_add_destination(unsigned int types, char *desturl, char *ctx, char *prot, char *subtype, char *hdrs, char *msgids, char *res)
{
    static int insertId=0;
/*
remove
*/
    return (int)insertId++;
}

/************************************************************
 * drop event destination when sse connection coming
 ***********************************************************/
int sse_del_destination(int id)
{
/*
remove
*/
    return RFRC_SUCCESS;
}


/************************************************************
 * query event destination
 ***********************************************************/
int sse_query_destination(int destid)
{
/*
remove
*/
    return RFRC_SUCCESS;
}

/************************************************************
 * common function for login
 ***********************************************************/
int authen_handle(int method, int *authtype, const char *uri_path, const char *auth, const char * session_token, const char * ip)
{
    string uri_s(uri_path);
    string remoteip(ip);

    *authtype = 0;
    if (auth && strstr(auth, "Basic ") != NULL) // field name case-insensitive, field value case sensitive
        *authtype = PROTOCOL::AUTH_BASIC;
    else if(uri_s.find(LOGIN_PATH) != string::npos && 
            uri_s.substr(uri_s.find(LOGIN_PATH)).compare(LOGIN_PATH) == 0 && method == snapper::service::http_post)
        *authtype = PROTOCOL::AUTH_SESSION;
    else if (session_token && strlen(session_token) > 0)
        *authtype = PROTOCOL::IDENT_SESSION;

    if(remoteip.length() == 0)
        remoteip = "unknown";

    // do authorization
    if(*authtype == PROTOCOL::AUTH_BASIC)
    {
        string usr,pwd,family("unknown");
        int login_rc;
        char *p_family;
        string cred(strchr(auth,' '));

        cred.erase(0,cred.find_first_not_of(" "));//trim space
        cred.erase(cred.find_last_not_of(" ") + 1); 
        cred = ::PROTOCOL::base64_decode(cred);
        usr = cred.substr(0, cred.find(":"));
        pwd = cred.substr(cred.find(":")+1);
        if((p_family = getenv( "IMM_FAMILY" )) != 0 )   
            family.assign(p_family);

        RF_PRINT_DBG("%s - basic credential [%s] %s %s from %s %s\n", __FUNCTION__, cred.c_str(), usr.c_str(), pwd.c_str(), family.c_str(), remoteip.c_str());
#ifndef __SIM_X86__
        login_rc = ::PROTOCOL::do_login("webguis", (char *)usr.c_str(), (char *)pwd.c_str(), (char *)family.c_str(), (char *)remoteip.c_str(), true);
#else
        login_rc = ::PROTOCOL::do_login_x86("webguis", (char *)usr.c_str(), (char *)pwd.c_str(), (char *)family.c_str(), (char *)remoteip.c_str(), true);
#endif
        if(login_rc == RFRC_SUCCESS)
        {
            if(::PROTOCOL::get_cur_session().reason_chgpwd) //handle change pwd rc R_CHGPWD_EXPIRED, R_CHGPWD_FORCE for specific url
                RF_PRINT_DBG("%s - need to handle request of changing pwd reason=%d\n", __FUNCTION__, ::PROTOCOL::get_cur_session().reason_chgpwd);
        }

        return login_rc;
    }
    else if(*authtype == PROTOCOL::IDENT_SESSION)
    {
        int ident_rc = ::PROTOCOL::open_session((char *)session_token);
        return ident_rc;
    }

    return RFRC_SUCCESS;
}
/************************************************************
 * snapper engine handle of Redfish request
 * uri - resource uri
 * headers - request headers in json str
 * body - request body in json str
 * method - http_method: 0-get,1-head,2-post,3-put,4-patch,5-delete
 * httpcode - http status code to return
 * rc   - internal error code to return
 * return - json string
 * NOTE: returned pointer to new string needs free by invoker!
 ***********************************************************/
char * snapper_request_handle(char *uri, int method, char *headers, char *body, int *httpcode, int *rc, char *resp_headers)
{
    ::PROTOCOL::clear_cur_session();

    resp_headers[0] = 0;
    if(snapper_model == nullptr || uri == NULL || body == NULL)
    {
        RF_PRINT("no redfish model to use !! \n");
        ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_InternalError());
        *rc = RFRC_INVALID_PARAMS;
        *httpcode = ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR;
        return strdup(err.serialize_err_obj().c_str());
    }
    RF_PRINT_DBG("%s - uri: %s\n header: %s\nbody: %s\n", __FUNCTION__, uri, headers, body);

    string uri_s(uri);    
    if (strncmp((const char*)&uri_s.back(), "/", 1) == 0)
    {
        RF_PRINT_DBG("remove last / \n");
        uri_s.erase(uri_s.size() - 1);
    }

    // get authentication field from http header. to support basic and token
    bson::BSONObj hdr = ::bson::fromjson(headers);
    string odataver = hdr.getStringField("OData-Version");
    const char *ip = hdr.getStringField("X-Real-IP");
    const char *auth = hdr.getStringField("Authorization");
    const char *session_token = hdr.getStringField("X-Auth-Token");

    if(odataver.length() && odataver.compare("4.0") != 0)
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_OdataVerHeaderNotSatisfied());
        *rc = RFRC_INVALID_HEADER;
        *httpcode = ::snapper::providers::HTTP_PRECONDITION_FAILED;
        return strdup(err.serialize_err_obj().c_str());
    }

    // handle basic or session token authentication
    int authtype = 0;
    int authrc = authen_handle(method, &authtype, uri_s.c_str(), auth, session_token, ip);
    if(authtype == 0)
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_ResourceAtUriUnauthorized(uri, "No Credential"));
        *rc = RFRC_AUTH_FAILED;
        *httpcode = ::snapper::providers::HTTP_UNAUTH;
        return strdup(err.serialize_err_obj().c_str());
    }
    if(authrc != RFRC_SUCCESS)
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_ResourceAtUriUnauthorized(uri, to_string(authrc)));
        err.add_extended_message_obj(::snapper::providers::StandardErrorMessage::MMO_InvalidCredentials());
        *rc = authrc;
        *httpcode = ::snapper::providers::HTTP_UNAUTH;
        return strdup(err.serialize_err_obj().c_str());
    }

    //handle request
    DataInterfaceMgr::DataMgrClientInfo(::PROTOCOL::get_cur_session().aim_privileges, ::PROTOCOL::get_cur_session().display_name, ::PROTOCOL::get_cur_session().remoteip);
    try
    {
        auto reqctx = std::make_shared<::snapper::service::request_context>(uri_s, method, snapper_model, headers, body);
        auto handler = std::make_shared<::snapper::service::request_handler>(snapper_model);

        *rc = handler->handle(reqctx);
        *httpcode = handler->get_httpstatus();
        if(authtype == ::PROTOCOL::AUTH_BASIC && ::PROTOCOL::get_cur_session().pam_handle)
#ifndef __SIM_X86__
            ::PROTOCOL::do_logout(true);
#else
            ::PROTOCOL::do_logout_x86(true);
#endif

        strncpy(resp_headers, handler->get_response_hdr().c_str(), RESP_HEADERS_LEN-1);
        return strdup(handler->get_response().c_str());
    }
    catch (::odata::core::odata_exception &e)
    {
        RF_PRINT_ERR("OData Exception: %s \n", e.what().c_str());
    }
    catch (::odata::service::odata_service_exception &e)
    {
        RF_PRINT_ERR("OData Service Exception: %s \n", e.what().c_str());
    }
    catch (::bson::assertion &e)
    {
        RF_PRINT_ERR("BSON Exception: %s \n", e.what());
    }

    // exception occurred during the URI parse, return "RequestUriNotFound" error message simply for now
    ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
    
    *rc = RFRC_EXCEPTION;
    *httpcode = ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR;
    if(authtype == ::PROTOCOL::AUTH_BASIC && ::PROTOCOL::get_cur_session().pam_handle)
#ifndef __SIM_X86__
        ::PROTOCOL::do_logout(true);
#else
        ::PROTOCOL::do_logout_x86(true);
#endif
    return strdup(err.serialize_err_obj().c_str());
}

/************************************************************
 * snapper engine handle of Redfish request schema
 * uri - resource uri
 * headers - request headers in json str
 * body - request body in json str
 * httpcode - http status code to return
 * rc   - internal error code to return
 * return - json string
 * NOTE: returned pointer to new string needs free by invoker!
 ***********************************************************/
char * snapper_request_schema_handle(char *uri, int method, char *headers, char *body, int *httpcode, int *rc, char *resp_headers)
{
    resp_headers[0] = 0;
    if(snapper_model == nullptr || uri == NULL || body == NULL)
    {
        RF_PRINT("no redfish model to use !! \n");
        ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_InternalError());
        *rc = RFRC_INVALID_PARAMS;
        *httpcode = ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR;
        return strdup(err.serialize_err_obj().c_str());
    }
    RF_PRINT_DBG("%s - header: %s\nbody: %s\n", __FUNCTION__, headers, body);

    string uri_s(uri);    
    if (strncmp((const char*)&uri_s.back(), "/", 1) == 0)
    {
        RF_PRINT_DBG("remove last / \n");
        uri_s.erase(uri_s.size() - 1);
    }

    // get authentication field from http header. to support basic and token
    bson::BSONObj hdr = ::bson::fromjson(headers);
    string odataver = hdr.getStringField("OData-Version");
    const char *ip = hdr.getStringField("X-Real-IP");
    const char *auth = hdr.getStringField("Authorization");
    const char *session_token = hdr.getStringField("X-Auth-Token");

    if(odataver.length() && odataver.compare("4.0") != 0)
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_OdataVerHeaderNotSatisfied());
        *rc = RFRC_INVALID_HEADER;
        *httpcode = ::snapper::providers::HTTP_PRECONDITION_FAILED;
        return strdup(err.serialize_err_obj().c_str());
    }

    // no auth needed for /redfish/v1/$metadata
    bool do_auth = true;
    if (uri_s.find("/redfish/v1/$metadata") != string::npos)
        do_auth = false;

    int authtype = 0;
    if(do_auth)
    {
        // handle basic or session token authentication
        int authrc = authen_handle(method, &authtype, uri_s.c_str(), auth, session_token, ip);
        if(authtype == 0)
        {
            ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_ResourceAtUriUnauthorized(uri, "No Credential"));
            *rc = RFRC_AUTH_FAILED;
            *httpcode = ::snapper::providers::HTTP_UNAUTH;
            return strdup(err.serialize_err_obj().c_str());
        }
        if(authrc != RFRC_SUCCESS)
        {
            ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_ResourceAtUriUnauthorized(uri, to_string(authrc)));
            err.add_extended_message_obj(::snapper::providers::StandardErrorMessage::MMO_InvalidCredentials());
            *rc = authrc;
            *httpcode = ::snapper::providers::HTTP_UNAUTH;
            return strdup(err.serialize_err_obj().c_str());
        }    
    }

    //handle request
    try
    {
        string base_str("/redfish/v1/schemas/"); 
        std::size_t pos = uri_s.find(base_str); 
        string file_name;
        if(pos != string::npos)
            file_name = uri_s.substr(pos + base_str.length());
        else
            file_name = uri_s.substr(uri_s.find_last_of("/") + 1);
        ::snapper::providers::SnapperSchema s_schema(file_name);
        
        *rc = 0;
        *httpcode = s_schema.get_httpstatus();
        if(do_auth)
        {
            if(authtype == ::PROTOCOL::AUTH_BASIC && ::PROTOCOL::get_cur_session().pam_handle)
#ifndef __SIM_X86__
                ::PROTOCOL::do_logout(true);
#else
                ::PROTOCOL::do_logout_x86(true);
#endif
        }

        strncpy(resp_headers, s_schema.get_response_hdr().c_str(), RESP_HEADERS_LEN-1);
        return strdup(s_schema.get_response().c_str());
    }
    catch (::odata::core::odata_exception &e)
    {
        RF_PRINT_ERR("OData Exception: %s \n", e.what().c_str());
    }
    catch (::odata::service::odata_service_exception &e)
    {
        RF_PRINT_ERR("OData Service Exception: %s \n", e.what().c_str());
    }
    catch (::bson::assertion &e)
    {
        RF_PRINT_ERR("BSON Exception: %s \n", e.what());
    }

    // exception occurred during the URI parse, return "RequestUriNotFound" error message simply for now
    ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
    
    *rc = RFRC_EXCEPTION;
    *httpcode = ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR;
    if(do_auth)
    {
        if(authtype == ::PROTOCOL::AUTH_BASIC && ::PROTOCOL::get_cur_session().pam_handle)
#ifndef __SIM_X86__
            ::PROTOCOL::do_logout(true);
#else
            ::PROTOCOL::do_logout_x86(true);
#endif
    }
    return strdup(err.serialize_err_obj().c_str());
}



/************************************************************
 * snapper engine handle of Redfish request
 * NOTE: non auth request
 * NOTE: returned pointer to new string needs free by invoker!
 ***********************************************************/
char * snapper_request_handle_non_auth(char *uri, int method, char *headers, char *body, int *httpcode, int *rc, char *resp_headers)
{
    resp_headers[0] = 0;
    if(snapper_model == nullptr || uri == NULL || body == NULL)
    {
        RF_PRINT("no redfish model to use !! \n");
        ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_InternalError());
        *rc = RFRC_INVALID_PARAMS;
        *httpcode = ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR;
        return strdup(err.serialize_err_obj().c_str());
    }
    RF_PRINT_DBG("%s - header: %s\nbody: %s\n", __FUNCTION__, headers, body);

    bson::BSONObj hdr = ::bson::fromjson(headers);
    string odataver = hdr.getStringField("OData-Version");
    if(odataver.length() && odataver.compare("4.0") != 0)
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_OdataVerHeaderNotSatisfied());
        *rc = RFRC_INVALID_HEADER;
        *httpcode = ::snapper::providers::HTTP_PRECONDITION_FAILED;
        return strdup(err.serialize_err_obj().c_str());
    }

    string uri_s(uri);    
    if (strncmp((const char*)&uri_s.back(), "/", 1) == 0)
    {
        RF_PRINT_DBG("remove last / \n");
        uri_s.erase(uri_s.size() - 1);
    }

    try
    {
        auto handler = std::make_shared<::snapper::service::request_handler>(snapper_model);
        // do not need to parse URI again as has been done in flask
        *rc = handler->handle(uri_s);
        *httpcode = handler->get_httpstatus();
        strncpy(resp_headers, handler->get_response_hdr().c_str(), RESP_HEADERS_LEN-1);
        return strdup(handler->get_response().c_str());
    }
    catch (::odata::core::odata_exception &e)
    {
        RF_PRINT("Exception: %s \n", e.what().c_str());
    }


    ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
    *rc = RFRC_EXCEPTION;
    *httpcode = ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR;
    return strdup(err.serialize_err_obj().c_str());
}

/*
run in thread SessionTimerThread() launched by gunicorn 
with timer 3 seconds
1. firstly scan resource data change for caching discard 
2. then scan topology change of resource tree
3. finally prefetch new data
*/
void snapper_refresh_topology()
{
    //check debug log level
    struct stat logflag;
    if (stat("/tmp/SLOG_T",&logflag) == 0) 
        g_engine_loglvl = RF_LOGLVL_TRACE;
    else if (stat("/tmp/SLOG_I",&logflag) == 0) 
        g_engine_loglvl = RF_LOGLVL_INFO;
    else if (stat("/tmp/SLOG_W",&logflag) == 0) 
        g_engine_loglvl = RF_LOGLVL_WARN;
    else if (stat("/tmp/SLOG_E",&logflag) == 0)
        g_engine_loglvl = RF_LOGLVL_ERROR;

#ifdef __SIM_X86__
    if(is_ready() == false)
        return;

    if(ResourceTopology::topology_created == false)
    {
        RF_PRINT_DBG("[cache] ---------- ready to build topology ------------ \n");
        clear_bson_cache();
        ResourceTopology::build_topology();
        ResourceTopology::topology_created = true;        
    }
#endif


#ifndef __SIM_X86__
    refresh_engine_data();
    prefetch_engine_data(snapper_model);
#endif

}

#ifdef __cplusplus
}
#endif

