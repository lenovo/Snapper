//---------------------------------------------------------------------
// <copyright file="ResourceProvider.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details. 
// </copyright>
//---------------------------------------------------------------------
#pragma once
#include <string>
#include "odata/common/basic_types.h"

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <dirent.h>

#include "bson/bson.h"
//#include "odata/edm/edm_model_reader.h"
#include "odata/core/odata_service_document.h"
#include "odata/core/odata_path_segment.h"

using namespace std;
using namespace ::odata::core;
//using namespace ::odata::edm;
//using namespace ::odata::utility;

namespace snapper { namespace providers
{
#define ROOT_URI           "/redfish/v1"
#define ROOT_METADATA      "$metadata#"
#define ODATA_ID           "@odata.id"
#define ODATA_TYPE         "@odata.type"
#define ODATA_CONTEXT      "@odata.context"
#define ODATA_ETAG         "@odata.etag"
#define ODATA_NEXT_LINK    "@odata.nextLink"
#define ODATA_COUNT        "@odata.count"
#define ODATA_NAVLINK      "@odata.navigationLink"   
#define MESSAGE_EXTENDED   "@Message.ExtendedInfo"
#define REDFISH_SETTINGS   "@Redfish.Settings"
#define SCHEMA_URI         "/schemas"

// common resource properties
#define RESOURCE_NAME      "Name"
#define RESOURCE_DESC      "Description"
#define RESOURCE_ID        "Id"
#define RESOURCE_HEALTH    "Status"
#define RESOURCE_LINKS     "Links"
#define RESOURCE_MEMBERS   "Members"
#define RESOURCE_RELATED_ITEM  "RelatedItem"
#define RESOURCE_ACTIONS   "Actions"
#define RESOURCE_OEM       "Oem"
    
#define MEMBERS_COUNT      "Members@odata.count"
#define MEMBERS_NEXT_LINK  "Members@odata.nextLink"
#define MEMBERS_NAV_LINK   "Members@odata.navigationLink"

const string root_uri(ROOT_URI);
const string schema_uri = root_uri + SCHEMA_URI; 
    
#define MAKE_BSON_OBJ(x, y)  std::make_shared<bson::BSONObj>(BSON(x << y))

#define MAKE_ERROR(httpcode, mmo, ...)         \
do{                                                \
    m_message.add_error_message_obj(mmo(__VA_ARGS__)); \
    override_http_code(httpcode);  \
} while(0)

typedef enum
{
    // 200: The request was successfully completed and includes a representation in its body.
    HTTP_OK                     = 200,

    // 201: A request that created a new resource completed successfully. The Location
    //        header shall be set to the canonical URI for the newly created resource. A
    //        representation of the newly created resource may be included in the response body.
    HTTP_CREATED                = 201,

    // 202: The request has been accepted for processing, but the processing has not been
    //       completed. The Location header shall be set to the URI of a Task resource that
    //       can later be queried to determine the status of the operation. A 
    //       representation of the Task resource may be included in the response body.
    HTTP_ACCEPTED               = 202,

    // 204: The request succeeded, but no content is being returned in the body of the response.
    HTTP_NO_CONTENT             = 204,

    // 301: The requested resource resides under a different URI
    HTTP_MOVED_PERMANENT        = 301,

    // 302: The requested resource resides temporarily under a different URI.
    HTTP_FOUND                  = 302,

    // 304: The service has performed a conditional GET request where access is allowed,
    //        but the resource content has not changed. Conditional requests are initiated 
    //        using the headers If-Modified-Since and/or If-None-Match (see HTTP 1.1, sections 14.25
    //        and 14.26) to save network bandwidth if there is no change.
    HTTP_NOT_MODIFIED           = 304,

    // 400: The request could not be processed because it contains missing or invalid
    //        information (such as validation error on an input field, a missing required value,
    //        and so on). An extended error shall be returned in the response body, as 
    //        defined in clause Error Responses.
    HTTP_BAD_REQUEST            = 400,

    // 401: The authentication credentials included with this request are missing or invalid.
    HTTP_UNAUTH                 = 401,

    // 403: The server recognized the credentials in the request, but those credentials do not
    //        possess authorization to perform this request.
    HTTP_FORBIDDEN              = 403,

    // 404: The request specified a URI of a resource that does not exist.
    HTTP_NOT_FOUND              = 404,
    
    // 405: The HTTP verb specified in the request (e.g., DELETE, GET, HEAD, POST, PUT, PATCH) is not supported for this request URI. 
    //        The response shall include an Allow header which provides a list of methods that are supported by the resource
    //        identified by the Request-URI. The response shall include an Allow
    //        header which provides a list of methods that are supported by the resource
    //        identified by the Request-URI.
    HTTP_METHOD_NOT_ALLOWED     = 405, 

    // 406: The Accept header was specified in the request and the resource identified by this
    //        request is not capable of generating a representation corresponding to one of 
    //        the media types in the Accept header.
    HTTP_NOT_ACCEPTABLE         = 406,  

    // 409: A creation or update request could not be completed, because it would cause a
    //       conflict in the current state of the resources supported by the platform (for
    //       example, an attempt to set multiple attributes that work in a linked manner 
    //       using incompatible values).
    HTTP_CONFLICT               = 409, 

    // 410: The requested resource is no longer available at the server and no forwarding
    //       address is known. This condition is expected to be considered permanent. Clients
    //       with link editing capabilities SHOULD delete references to the Request-URI after
    //       user approval. If the server does not know, or has no facility to determine, whether
    //       or not the condition is permanent, the status code 404 (Not Found) SHOULD be
    //       used instead. This response is cacheable unless indicated otherwise.
    HTTP_GONE                   = 410,  

    // 411: The request did not specify the length of its content using the Content-Length
    //       header (perhaps Transfer-Encoding: chunked was used instead). The addressed
    //       resource requires the Content-Length header.
    HTTP_LEN_REQUEIRED          = 411,  

    // 412: Precondition (such as OData-Version, If Match or If Not Modified headers) check failed.
    HTTP_PRECONDITION_FAILED    = 412, 

    // 415: The request specifies a Content-Type for the body that is not supported.
    HTTP_UNSUPPORTED_MEDIA_TYPE = 415,  

    // 500: The server encountered an unexpected condition that prevented it from fulfilling
    //      the request. An extended error shall be returned in the response body, as 
    //      defined in clause Error Responses.
    HTTP_INTERNAL_SERVER_ERROR  = 500, 

    // 501: The server does not (currently) support the functionality required to fulfill the
    //      request. This is the appropriate response when the server does not recognize 
    //      the request method and is not capable of supporting the method for any resource.
    HTTP_NOT_IMPLEMENTED        = 501,

    // 503: The server is currently unable to handle the request due to temporary overloading
    //         or maintenance of the server.
    HTTP_SERVICE_UNAVAILABLE    = 503,
    

    // 507: The server is unable to build the response for the client due to the size of the
    //      response.
    HTTP_INSUFFICIENT_STORAGE   = 507

} SNAPPER_HTTP_CODE;


    
}}
