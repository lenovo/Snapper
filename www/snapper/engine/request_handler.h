//---------------------------------------------------------------------
// <copyright file="request_handler.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/edm/edm_model.h"
#include "odata/edm/edm_type.h"
#include "class/SnapperProvider.h"
#include "odata/edm/odata_edm.h"
#include <algorithm>
#include "protocol.h"
#include "class/SnapperProvider.h"
#include "class/SnapperPrivilege.h"
using namespace ::odata::edm;
using namespace ::snapper::providers;
using namespace ::bson;

namespace snapper { namespace service
{

class request_handler
{
public:
    request_handler(::std::shared_ptr<::odata::edm::edm_model> model);
    ~request_handler() {};

    int handle(::std::shared_ptr<request_context> request);
    int handle(const string full_uri);

    std::shared_ptr<snapper::providers::SnapperProvider> ident_class(::std::shared_ptr<request_context> request);
    int handle_get(::std::shared_ptr<request_context> request);
    int handle_get(const string full_uri);
    int handle_post(::std::shared_ptr<request_context> request);
    int handle_patch(::std::shared_ptr<request_context> request);
    int handle_put(::std::shared_ptr<request_context> request);
    int handle_delete(::std::shared_ptr<request_context> request);
    bool validate_redfish_dynamic_property_pattern(bson::BSONElement e, std::vector<edm_payload_annotation_type *> annotations);
    bool validate_primitive_type(bson::BSONElement e, std::shared_ptr<edm_primitive_type> p_primitive_type, 
                                       string prefix = "", string pattern = "");
    bool validate_enum_type(bson::BSONElement e, std::shared_ptr<edm_enum_type> p_enum_type, string prefix = "");
    bool validate_complex_type(bson::BSONElement e, std::shared_ptr<edm_complex_type> p_complex_type, string prefix = "");
    bool validate_collection_type(bson::BSONElement e, std::shared_ptr<edm_collection_type> p_collection_type, string prefix = "");
    bool validate_property_type(bson::BSONElement e, std::shared_ptr<edm_property_type> p_type, string prefix);
    bool validate_request_body(::std::string entity_name, ::std::string request_body, bson::BSONObjBuilder& err);
    bool validate_request_body(std::shared_ptr<odata_operation_segment> seg, ::std::string request_body, bson::BSONObjBuilder& err);
    bool validate_create_body(::std::string name, ::std::string request_body, bson::BSONObjBuilder& err);
    bool check_url_privilege(shared_ptr<request_context> request);
    bool check_property_privilege(std::string prop_name);
    int pre_check(shared_ptr<request_context> request);

    const ::std::string& get_response() const { return m_response; }
    void set_response(const ::std::string& resp)
    {
        auto extended_obj = m_message.get_extended_info_obj();
        if(extended_obj == nullptr)
        {
            m_response = resp;
        }
        else
        {
            bson::BSONObjBuilder o;
            o.appendElementsUnique(*extended_obj);
            bson::BSONObj obj = bson::fromjson(resp);
            for( BSONObj::iterator i = obj.begin(); i.more(); ) 
            {
                BSONElement e = i.next();
                o.append(e);
            }
            m_response = o.obj().jsonString();
        }
    }

    const ::std::string& get_response_hdr() const { return m_response_hdr; }
    void set_response_hdr(const ::std::string& resphdr)
    {
		m_response_hdr = resphdr;
    }

    unsigned int get_httpstatus(){ return m_httpstatus;}
    void set_httpstatus(unsigned int status){ m_httpstatus = status;}

    void set_err_response_body_hdr_status(int rc, std::shared_ptr<::snapper::providers::SnapperProvider> provider, std::string method_str);

private:

    ::std::shared_ptr<::odata::edm::edm_model> m_model;
    ::std::string m_response;
    ::std::string m_response_hdr;
    unsigned int m_httpstatus; 
    bool m_op_create;
    SnapperMessage m_message;
    CURRENT_SESSION m_current_session;
    ::std::string m_target_str;
    bool base_priv_check;
    std::shared_ptr<SnapperProvider> m_provider;
    std::shared_ptr<SnapperPrivilege> m_priv_provider;
    int m_method;
    std::string m_method_str;

    int rc_to_httpcode(int rc);
    ::std::string rc_to_httpresponse(int rc);
    ::std::string rc_to_httpresponse(int rc, std::shared_ptr<::snapper::providers::SnapperProvider> provider, std::string method_str);
};

}}
