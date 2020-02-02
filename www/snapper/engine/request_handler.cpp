//---------------------------------------------------------------------
// <copyright file="request_handler.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <www/engine/rf_debug.h>
#include <algorithm>
#include <regex.h>

#include "bson/bson.h"
#include "bson/util/json.h"


#include <www/engine/request_handler.h>
#include <www/engine/request_context.h>
#include <www/engine/rf_engine_error.h>
#include "class/ServiceRoot.h"
#include "odata_service_exception.h"
#include "odata/core/odata_message_writer.h"
#include "odata/core/odata_context_url_builder.h"
#include "topology.h"
#include "json_cache.h"
#include "sessions.h"
#include "rf_shm_session.h"

using namespace ::std;
using namespace ::odata::utility;
using namespace ::odata::edm;
using namespace ::odata::core;
using namespace ::snapper::providers;

namespace snapper { namespace service
{
//lock for prefetch as data prefetch and normal request handle are multiple threads, which
//share the same provider instance
static pthread_mutex_t prefetch_lock=PTHREAD_MUTEX_INITIALIZER;


    request_handler::request_handler(shared_ptr<edm_model> model): m_model(model)
    {
        m_op_create = false;
    }

    int request_handler::handle(shared_ptr<request_context> request)
    {

        pthread_mutex_lock( &prefetch_lock ); 
        std::shared_ptr<::odata::core::odata_path> opath = request->get_odata_path();
        if(opath == nullptr)
        {
            m_message.add_error_message_obj(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
            set_response(m_message.serialize_err_obj().c_str());
            set_httpstatus(::snapper::providers::HTTP_INTERNAL_SERVER_ERROR);
            pthread_mutex_unlock( &prefetch_lock );
            return RFRC_INVALID_PARAMS;
        }

        auto segments = opath->segments();
        if(segments.size() <= 0 || segments[0]->segment_type() != odata_path_segment_type::Singleton)
        {
            m_message.add_error_message_obj(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
            set_response(m_message.serialize_err_obj().c_str());
            set_httpstatus(::snapper::providers::HTTP_INTERNAL_SERVER_ERROR);
            pthread_mutex_unlock( &prefetch_lock );
            return RFRC_ODATA_SEG;
        }

        set_httpstatus(::snapper::providers::HTTP_OK); // init a http code
        int rc = RFRC_SUCCESS;
        base_priv_check = true;
        m_current_session = PROTOCOL::get_cur_session();
        m_method = request->get_method();
        m_method_str = request->get_method_str();
        switch (m_method)
        {
            case snapper::service::http_get:
            case snapper::service::http_head:
            {
                rc = handle_get(request);
                break;
            }

            case snapper::service::http_post:
            {
                rc = handle_post(request);
                break;
            }

            case snapper::service::http_patch:
            {
                rc = handle_patch(request);
                break;
            }

            case snapper::service::http_put:
            {
                rc = handle_put(request);
                break;
            }

            case snapper::service::http_delete:
            {
                rc = handle_delete(request);
                break;
            }

            default:
            {
                rc = RFRC_METHOD_NOT_ALLOWED;
                break;
            }
        }

        // if rc > 0, but the http code is 200, need forced conversion
        if(rc && (get_httpstatus() == ::snapper::providers::HTTP_OK))
        {
            set_httpstatus(rc_to_httpcode(rc));
            RF_PRINT_DBG("convert rc %d to http code %d\n", rc, rc_to_httpcode(rc));
        }
        RF_PRINT_DBG("http status code %d\n", get_httpstatus());
        pthread_mutex_unlock( &prefetch_lock );
        return rc;
    }

    // no need to do uri path, as has been treated seperately in flask
    // supports /redifsh/v1, /redfish/v1/odata here
    // handled in ServiceRoot Provider
    int request_handler::handle(const string full_uri)
    {
        pthread_mutex_lock( &prefetch_lock ); 

        ::odata::utility::uri uri(::odata::utility::uri::encode_uri(full_uri));
        
        std::shared_ptr<SnapperProvider> provider =  ProviderObjectFactory::GetObject("ServiceRoot");
        
        auto sr_provider = std::static_pointer_cast<ServiceRoot>(provider);        
        
        sr_provider->handle_get(uri.path());
        set_response(provider->serialize_objs());
        set_response_hdr(provider->serialize_resp_hdr(http_get));
        set_httpstatus(::snapper::providers::HTTP_OK);
        //RF_PRINT_DBG("%s\n", get_response().c_str());
        
        sr_provider->reset_obj();

        pthread_mutex_unlock( &prefetch_lock );

        return RFRC_SUCCESS;
    }
        

    std::shared_ptr<SnapperProvider> request_handler::ident_class(shared_ptr<request_context> request)
    {
        std::shared_ptr<SnapperProvider> provider = nullptr; 
        auto segments = request->get_odata_path()->segments();

        std::string upath = ROOT_URI;
        auto vpath = request->get_path_str();
        bool need_stepon = true; // one vpath segment may have multiple odata path segment. Systems - Singleton+Type. Systems/1 -  Type+Key
        int k=0;
        m_target_str.clear();
        for (auto iter = segments.cbegin(); iter != segments.cend(); iter++)
        {
            int next_seg_type = (int)odata_path_segment_type::None;
            if((iter+1) !=  segments.cend())
            {
                shared_ptr<odata_path_segment> nextseg = *(iter+1);
                next_seg_type = nextseg->segment_type();
            }

            if(k < vpath.size() && need_stepon)
                upath += "/" + vpath[k++];

            shared_ptr<odata_path_segment> seg = *iter;
            RF_PRINT(" upath %s - type %d\n", upath.c_str(), seg->segment_type());
            switch (seg->segment_type())
            {
                case odata_path_segment_type::Singleton:
                     need_stepon = false; // Singleton followed by Type, do not move to next vpath seg
                     break;            
         
                case odata_path_segment_type::Type: // hit type which is resource provider
                {
                    need_stepon = true;
                    if(next_seg_type == odata_path_segment_type::Key) // For collection memeber, Type followed by Key, do not move to next vpath seg
                        need_stepon = false;
                    shared_ptr<odata_type_segment> type_seg = seg->as<odata_type_segment>();
                    auto tname = type_seg->type()->get_name();

                    provider =  ProviderObjectFactory::GetObject( tname);
                    if( provider != nullptr )
                    {
                        RF_PRINT_DBG("Found Type provider : [%s], provider type: [%s]\n", provider->get_name().c_str(), provider->get_type_str()); 
                        if(m_target_str.empty())
                        {
                            m_target_str.append(tname);
                        }
                        else
                        {
                            m_target_str.append("/");
                            m_target_str.append(tname);
                        }
                    }
                    else
                    {
                        RF_PRINT_WARN("Type provider not found: %s\n", tname.c_str());
                        //return nullptr; //allow absence for now 
                    }                         
                    break;
                }
                 
                case odata_path_segment_type::Key: //hit instance of resource collection
                {
                    need_stepon = true;
                    shared_ptr<odata_key_segment> key_seg = seg->as<odata_key_segment>();
                    if(provider == nullptr)//previous type not implemented
                    {
                        string keytname;
                        auto navsrc = key_seg->navigation_source();
                        if(navsrc == nullptr)
                        {
                            auto entitytype = key_seg->target_entity_type();
                            if(entitytype != nullptr){
                                keytname = entitytype->get_name();
                                RF_PRINT_DBG("    key for entity type: %s\n", keytname.c_str());
                            }
                        }
                        else
                        {
                            keytname = navsrc->get_name();
                            RF_PRINT_DBG("    key for navigation source: %s\n", keytname.c_str());
                        }
                        RF_PRINT_WARN("resource type for the key %s  not found:  %s \n", key_seg->keys()[0].first.c_str(), keytname.c_str());
                        break;
                    }

                    //RF_PRINT_DBG(" key: %s | %s \n", key_seg->keys()[0].first.c_str(),  (key_seg->keys()[0].second->as<::odata::utility::string_t>()).c_str());
                    if(key_seg && key_seg->keys().size() > 0 && key_seg->key_at(0).second != nullptr)
                    {
                        if(!provider->validate_key(key_seg->key_at(0).second->as<::odata::utility::string_t>(), upath))
                        {
                            RF_PRINT_WARN("validation key failure: %s | %s , %s \n", key_seg->keys()[0].first.c_str(), 
                                 (key_seg->keys()[0].second->as<::odata::utility::string_t>()).c_str(), upath.c_str());

                            m_message.add_error_message_obj( 
                                ::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound() );
                            set_response(m_message.serialize_err_obj().c_str());
                            set_httpstatus(::snapper::providers::HTTP_NOT_FOUND);

                            return nullptr;
                        }

                    }
                    break;
                }
        
                 
                case odata_path_segment_type::NavigationProperty:  //hit property of resource like Power/Voltages
                {            
                    need_stepon = true;
                    auto prop_seg = seg->as<odata_navigation_property_segment>();

                    if(provider != nullptr && !provider->is_array_property(prop_seg->property()->get_name()))
                    {
                        RF_PRINT_WARN("validation nav property [%s] failure \n", prop_seg->property()->get_name().c_str());

                        m_message.add_error_message_obj( 
                            ::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound() );
                        set_response(m_message.serialize_err_obj().c_str());
                        set_httpstatus(::snapper::providers::HTTP_NOT_FOUND);

                        return nullptr;
                    }

                    std::shared_ptr<SnapperProvider> sub_provider =  ProviderObjectFactory::GetObject( prop_seg->property()->get_name());
                    if( sub_provider != nullptr )
                    {
                        RF_PRINT_DBG("Found NavigationProperty provider : [%s], provider type: [%s] \n", sub_provider->get_name().c_str(), sub_provider->get_type_str());
                        provider = sub_provider;
                    }
                    else
                    {
                        RF_PRINT_DBG("NavigationProperty provider not found: %s [%s] \n ", prop_seg->property()->get_name().c_str(), prop_seg->property()->get_property_type()->get_name().c_str());
                        //return nullptr; //allow absence for now 
                    }

                    break;
                }
                case odata_path_segment_type::StructuralProperty:
                {
                    need_stepon = true;
                    auto prop_seg = seg->as<odata_structural_property_segment>();
                    RF_PRINT_DBG( "--structprop \n");

                    if(provider != nullptr && !provider->is_array_property(prop_seg->property()->get_name())
                        && (prop_seg->property()->get_name().compare("Actions") != 0))
                    {
                        auto propname = prop_seg->property()->get_name();
                        if(propname.compare("Oem") == 0 || propname.compare("Lenovo") == 0)
                        {
                            RF_PRINT_DBG( " oem segment: %s\n", propname.c_str());
                            break;
                        }

                        RF_PRINT_WARN("validation property [%s] failure \n", prop_seg->property()->get_name().c_str());
                        m_message.add_error_message_obj( 
                            ::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound() );
                        set_response(m_message.serialize_err_obj().c_str());
                        set_httpstatus(::snapper::providers::HTTP_NOT_FOUND);

                        return nullptr;
                    }
                    //stop searching provider for structure prop which has no corresponding resource
                    break;
                }

                case odata_path_segment_type::Operation:
                {
                    need_stepon = true;
                    shared_ptr<odata_operation_segment> op_seg = seg->as<odata_operation_segment>();

                    bson::BSONObjBuilder o;
                    if(!validate_request_body(op_seg, request->get_request_body(), o))
                    { //error response and httpcode set in validate_request_body
                        RF_PRINT_WARN("operation has invalid request data\n");
                        return nullptr; 
                    }

                    if(op_seg != nullptr)
                        request->set_action(op_seg->operation()->get_name());
                    RF_PRINT_DBG( " action segment: %s\n", request->get_action().c_str());
                    break;
                }
                 
                default:
                {
                    need_stepon = true;
                    RF_PRINT_WARN( " unknown segment type: %d\n", seg->segment_type());
                    break;
                }
             }
        }

        if(provider == nullptr)
        {
            m_message.add_error_message_obj( 
                ::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound() );
            set_response(m_message.serialize_err_obj().c_str());
            set_httpstatus(::snapper::providers::HTTP_NOT_FOUND);
        }

        m_provider = provider;
        if(m_provider)            
            m_priv_provider = PrivilegeObjectFactory::GetObject(provider->get_name());
        else
            m_priv_provider = nullptr;
        return provider;
    }
    void request_handler::set_err_response_body_hdr_status(int rc, std::shared_ptr<::snapper::providers::SnapperProvider> provider, std::string method_str)
    {
        set_response(provider->serialize_error_obj());
        if(get_response().length() == 0)//if error obj not specified by provider, then map rc to error response
        {
            RF_PRINT_DBG( " provider %s doesn't provide error response for rc %d\n", provider->get_name().c_str(), rc);
            set_response(rc_to_httpresponse(rc, provider, method_str));
        }

        if(provider->get_http_code() == 0)//if http code not specified by provider, map rc to http code
        {
            RF_PRINT_DBG( " provider %s doesn't provide http code for rc %d\n", provider->get_name().c_str(), rc);
            set_httpstatus(rc_to_httpcode(rc));
        }
        else
            set_httpstatus(provider->get_http_code());    

        //TODO http header for error response
    }

    int request_handler::handle_get(shared_ptr<request_context> request)
    {
        bson::BSONObj hdrobj = ::bson::fromjson(request->get_request_headers()); 
        string etag = hdrobj.getStringField("If-None-Match");
        //try cache first
        auto cache = find_json_cache(request);
        if(cache != nullptr)
        {  
            bson::BSONObj cache_obj = ::bson::fromjson(cache->resp_body);
            string cache_etag = cache_obj.getStringField("ETag");
            
            if(!etag.empty() && !cache_etag.compare(etag))
            {
                set_httpstatus(::snapper::providers::HTTP_NOT_MODIFIED);
            }
            else
            {
                set_response(cache->resp_body);
                if(cache->status_code)
                    set_httpstatus(cache->status_code);
            }
            set_response_hdr(cache->resp_hdr);
            return RFRC_SUCCESS;
        }

        std::shared_ptr<SnapperProvider> provider = ident_class(request); 
        int rc = RFRC_SUCCESS;

        if (provider != nullptr)
        {
            // http code and error response are handled in pre_check
            rc = pre_check(request);
            if(rc)
                return rc;
            
            if((rc = provider->handle_get(request)) == RFRC_SUCCESS)
            {                
                bson::BSONObj hdrobj = ::bson::fromjson(request->get_request_headers());   
                auto body = provider->serialize_objs();
                auto hdr = provider->serialize_resp_hdr(request->get_method());
                if(!etag.empty() && !provider->get_etag().compare(etag))
                {
                    set_httpstatus(::snapper::providers::HTTP_NOT_MODIFIED);
                }
                else
                {
                    set_response(body);
                    if(provider->get_http_code())//by default 200
                        set_httpstatus(provider->get_http_code());
    
                    //save to cache as well
                    add_json_cache(request, body, hdr, get_httpstatus(), provider->get_name());
                }
                set_response_hdr(hdr);
            }
            else
                set_err_response_body_hdr_status(rc, provider, m_method_str);

            provider->reset_obj();
        }
        else
        {   //error response and http code all set in ident_class()
            RF_PRINT_WARN("ident_class found no provider \n");
            rc = RFRC_NOT_IMPLEMENTED;
        }
        
        //RF_PRINT_DBG("%s \n", get_response().c_str());
        return rc;
    }

    
    int request_handler::handle_post(shared_ptr<request_context> request)
    {
        std::shared_ptr<SnapperProvider> provider = ident_class(request); 
        int rc = RFRC_SUCCESS;

        if (provider != nullptr)
        {
            // http code and error response are handled in pre_check
            rc = pre_check(request);
            if(rc)
                return rc;
            
            if(provider->get_type() == Provider_ResourceCollection)//create request to a Resource Collection or Members property
            {
                std::string tname;
                if(provider->get_Members_class(tname)) // get class of Members and use provider of member class 
                {
                    RF_PRINT_DBG("POST get member class %s \n", tname.c_str());    
                    auto provider_create =  ProviderObjectFactory::GetObject( tname);
                    if( provider_create != nullptr )
                    {                        
                        bson::BSONObjBuilder o;
                        m_op_create = true;
                        if(!validate_create_body(tname, request->get_request_body(), o))
                        {
                            RF_PRINT_ERR("validate_create_body failed \n");
                            set_httpstatus(HTTP_BAD_REQUEST);
                            return RFRC_INVALID_PARAMS;
                        }
                        provider = provider_create;
                        request->set_op_create(true);
                    }
                }
            }

            provider->jcache_clean(request);// clean json cache
            provider->bcache_clean(request);// clean bson cache

            if((rc = provider->handle_post(request)) ==  RFRC_SUCCESS)
            {                
                set_response(provider->serialize_objs());
                set_response_hdr(provider->serialize_resp_hdr(request->get_method()));
                if(provider->get_http_code())
                    set_httpstatus(provider->get_http_code());
            }
            else
                set_err_response_body_hdr_status(rc, provider, m_method_str);

            provider->reset_obj();
        }
        else
        {   //error response and http code all set in ident_class()
            RF_PRINT_WARN("ident_class found no provider \n");
            rc = RFRC_NOT_IMPLEMENTED;
        }
    
        //RF_PRINT_DBG("%s \n", get_response().c_str());    
        return rc;      
    }

    int request_handler::handle_patch(shared_ptr<request_context> request)    
    {
        int rc = RFRC_SUCCESS;
        
        if(request->get_request_body().empty())
        {
            m_message.add_error_message_obj(BaseMessage::MMO_UnrecognizedRequestBody());
            set_response(m_message.serialize_err_obj().c_str());    
            set_httpstatus(HTTP_BAD_REQUEST);
            return RFRC_INVALID_PARAMS;
        }
        
        std::shared_ptr<SnapperProvider> provider = ident_class(request); 
        if (provider != nullptr)
        {
            // http code and error response are handled in pre_check
            rc = pre_check(request);
            if(rc)
                return rc;
                        
            RF_PRINT_DBG( " validate_request_body for entity type segment\n");
            bson::BSONObjBuilder o;
            if(!validate_request_body(provider->get_name(), request->get_request_body(), o))
            {
                RF_PRINT_WARN("invalid request data %s for %s\n", request->get_request_body().c_str(), provider->get_name().c_str());
                return RFRC_INVALID_PARAMS;
            }
            provider->jcache_clean(request);// clean json cache
            provider->bcache_clean(request);// clean bson cache

            if((rc = provider->handle_patch(request)) == RFRC_SUCCESS)
            {                
                set_response(provider->serialize_objs());
                set_response_hdr(provider->serialize_resp_hdr(request->get_method()));
                if(provider->get_http_code())
                    set_httpstatus(provider->get_http_code());
            }
            else
                set_err_response_body_hdr_status(rc, provider, m_method_str);

            provider->reset_obj();
        }
        else
        {   //error response and http code all set in ident_class()
            RF_PRINT_WARN("ident_class found no provider \n");
            rc = RFRC_NOT_IMPLEMENTED;
        }
    
        //RF_PRINT_DBG("%s \n", get_response().c_str());    
        return rc;      
    }

    int request_handler::handle_delete(shared_ptr<request_context> request)
    {
        std::shared_ptr<SnapperProvider> provider = ident_class(request); 
        int rc = RFRC_SUCCESS;

        if (provider != nullptr)
        {
            // http code and error response are handled in pre_check
            rc = pre_check(request);
            if(rc)
                return rc;
            
            provider->jcache_clean(request);// clean json cache
            provider->bcache_clean(request);// clean bson cache

            if((rc = provider->handle_delete(request)) == RFRC_SUCCESS)
            {                
                set_response(provider->serialize_objs());
                set_response_hdr(provider->serialize_resp_hdr(request->get_method()));
                if(provider->get_http_code())
                    set_httpstatus(provider->get_http_code());
            }
            else
                set_err_response_body_hdr_status(rc, provider, m_method_str);

            provider->reset_obj();
        }
        else
        {   //error response and http code all set in ident_class()
            RF_PRINT_WARN("ident_class found no provider \n");
            rc = RFRC_NOT_IMPLEMENTED;
        }
    
        //RF_PRINT_DBG("%s \n", get_response().c_str());    
        return rc;      
    }

    int request_handler::handle_put(shared_ptr<request_context> request)
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_GeneralError());
        set_response(err.serialize_err_obj().c_str());
        set_httpstatus(::snapper::providers::HTTP_METHOD_NOT_ALLOWED);
        RF_PRINT_ERR("put unsupported....\n");
        return RFRC_METHOD_NOT_ALLOWED;
    }

    
    // validate patch body including property name/value
    // only enum value is validate currently.  
    const std::unordered_map<int, vector<int>>::value_type init_primitive_type_to_bson_type[] = 
    {
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Binary, {bson::BinData}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Boolean, {bson::Bool}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Byte, {bson::NumberInt}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Duration, {bson::NumberInt}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::DateTimeOffset, {bson::Timestamp}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Double, {bson::NumberDouble}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Decimal, {bson::NumberInt}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Guid, {bson::String}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Int16, {bson::NumberInt}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Int32, {bson::NumberInt}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Int64, {bson::NumberInt, bson::NumberLong}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::SByte, {bson::NumberInt}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Single, {bson::String}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::Stream, {bson::String}),
        std::unordered_map<int, vector<int>>::value_type(edm_primitive_type_kind_t::String, {bson::String}),    
    };
    
    const static std::unordered_map<int, vector<int>> primitive_type_to_bson_type(init_primitive_type_to_bson_type, init_primitive_type_to_bson_type + 15);
    string raw_str(string raw_str)
    {
        std::size_t pos = raw_str.find(":");
        string value_str;
        if(pos != string::npos)
            value_str = raw_str.substr(pos + 2);
        else 
            value_str = raw_str;
        
        //value_str.erase(std::remove(value_str.begin(), value_str.end(), '"'), value_str.end());
        return value_str;
    }

    string get_annotation_attr_value(std::vector<edm_payload_annotation_type *> & notations, string term, string attr_name)
    {
        string desc("");
        for(int i = 0; i < notations.size() && notations[i] != nullptr; i++)
        {
            if(notations[i]->get_name().compare(term) != 0)
                continue;
            desc = notations[i]->get_attribute(attr_name);
            if(desc.length() == 0)
                continue;
    
            return desc;
        }
        return desc;
    }
    bool annotation_has_term(std::vector<edm_payload_annotation_type *> & notations, string term)
    {
        for(int i = 0; i < notations.size() && notations[i] != nullptr; i++)
        {
            if(notations[i]->get_name().compare(term) == 0)
                return true;
        }
        return false;
    }    
    
    edm_payload_annotation_type* annotation_get_term(std::vector<edm_payload_annotation_type *> & notations, string term)
    {
        for(int i = 0; i < notations.size() && notations[i] != nullptr; i++)
        {
            if(notations[i]->get_name().compare(term) == 0)
                return notations[i];
        }
        return nullptr;
    }

    bool is_read_only(std::shared_ptr<edm_property_type> property)
    {        
        if(annotation_has_term(property->get_annotation_list(), ANNOTATION_TERM_PERM) == true)
        {
            string perm = get_annotation_attr_value(property->get_annotation_list(), ANNOTATION_TERM_PERM, ANNOTATION_ATTR_ENUMMEMBER);
            return (perm.compare(ANNOTATION_ENUMMEMBER_R) == 0 ? true : false);
        }
        return false;
    }

    string get_validation_pattern(std::shared_ptr<edm_property_type> property)
    {        
        return get_annotation_attr_value(property->get_annotation_list(), ANNOTATION_TERM_PATTERN, ANNOTATION_ATTR_STRING);
    }

    string get_validation_pattern(std::shared_ptr<edm_type_def> type_def)
    {        
        return get_annotation_attr_value(type_def->get_annotation_list(), ANNOTATION_TERM_PATTERN, ANNOTATION_ATTR_STRING);
    }

  

    bool request_handler::validate_primitive_type(bson::BSONElement e, std::shared_ptr<edm_primitive_type> p_primitive_type, string prefix, string pattern)
    {
        RF_PRINT_DBG("%s: \n", __FUNCTION__);
        if(!p_primitive_type || e.eoo())
        {
            RF_PRINT_ERR("%s: p_primitive_type or bson element null....\n", __FUNCTION__);
            return false;
        }        
        
        auto iter = primitive_type_to_bson_type.find(p_primitive_type->get_primitive_kind());
        if (iter != primitive_type_to_bson_type.end())     
        {
            vector<int> type_vec = iter->second;
            vector<int>::iterator result = find(type_vec.begin(), type_vec.end(), e.type());
            if(result == type_vec.end())
            {
                string argument = prefix + "/" + e.fieldName();
                SnapperMessage err_msg(BaseMessage::MMO_PropertyValueTypeError(raw_str(e.toString()), argument));
                set_response(err_msg.serialize_err_obj().c_str());    
                stringstream ss("");
                for(int i = 0; i < type_vec.size(); i++)
                {
                    if(i)
                        ss << " or ";
                    ss << type_vec[i];
                }
                    
                RF_PRINT_ERR("%s: primitive type not match [%d, expected %s]....\n", __FUNCTION__, e.type(), 
                ss.str().c_str());
                return false;
            }
            else
            { 
                if((p_primitive_type->get_primitive_kind() == edm_primitive_type_kind_t::String) && !pattern.empty())
                {
                    regex_t      reRes; 
                    regmatch_t   subs[4];
                    int          err = 0;

                    if(!regcomp(&reRes, pattern.c_str(), REG_EXTENDED) 
                        && regexec(&reRes, e.str().c_str(), sizeof(subs)/sizeof(regmatch_t), subs, 0))
                    {
                        string argument = prefix + "/" + e.fieldName();
                        SnapperMessage err_msg(BaseMessage::MMO_PropertyValueFormatError(raw_str(e.toString()), argument));
                        set_response(err_msg.serialize_err_obj().c_str());                
                        RF_PRINT_ERR("%s: string pattern not valid [%s, %s]....\n", __FUNCTION__, pattern.c_str(), e.str().c_str());
                        return false;
                    }
                    else
                        return true;
                    
                }
                else
                    return true;
            }
        }
        else
        {
            RF_PRINT_ERR("%s: ignore....\n", __FUNCTION__);
            return true;
        }
    }

    bool request_handler::validate_enum_type(bson::BSONElement e, std::shared_ptr<edm_enum_type> p_enum_type, string prefix)
    {
        RF_PRINT_DBG("%s: \n", __FUNCTION__);
        if(!p_enum_type || e.eoo())
        {
            RF_PRINT_ERR("%s: p_enum_type or bson element null....\n", __FUNCTION__);
            return false;
        }

        string e_name = e.fieldName();
        string argument = prefix + "/" + e_name;

        if(e.type() != bson::String)
        {
            RF_PRINT_ERR("%s: patch body is not string....\n", __FUNCTION__);
            SnapperMessage err_msg(BaseMessage::MMO_PropertyValueTypeError(raw_str(e.toString()), argument));
            set_response(err_msg.serialize_err_obj().c_str());    
            return false;
        }
        
        auto p_enum_member = p_enum_type->find_enum_member(e.str());
        if(!p_enum_member)
        {
            RF_PRINT_ERR("%s: enum %s not found....\n", __FUNCTION__, e_name.c_str());
            SnapperMessage err_msg(BaseMessage::MMO_PropertyValueNotInList(raw_str(e.toString()), argument));
            set_response(err_msg.serialize_err_obj().c_str());    
            return false;
        }
        
        return true;
    }

    bool request_handler::validate_complex_type(bson::BSONElement e, std::shared_ptr<edm_complex_type> p_complex_type, string prefix)
    {
        string e_name = e.fieldName();
        string argument = prefix + "/" + e_name;

        if(e.type() != bson::Object)
        {
            RF_PRINT_ERR("%s: patch body is not object....\n", __FUNCTION__);
            SnapperMessage err_msg(BaseMessage::MMO_PropertyValueTypeError(raw_str(e.toString()), argument));
            set_response(err_msg.serialize_err_obj().c_str());                
            return false;
        }

        auto p_structure_type = std::dynamic_pointer_cast<edm_structured_type>(p_complex_type);
        if(!p_structure_type)
        {
            RF_PRINT_ERR("%s: invalid pointer cast of complex type\n",  __FUNCTION__);
            return true;
        } 
        
        bson::BSONObj o = e.Obj();
        for( bson::BSONObj::iterator it = o.begin(); it.more(); )
        {
            bson::BSONElement elem = it.next();
            if(elem.eoo() == true) 
                break;
                
            string e_prop_name = elem.fieldName();
            std::shared_ptr<edm_property_type> prop = m_model->find_complex_property(p_complex_type->get_name(), e_prop_name);
            if(prop == nullptr)
            {
                // check if "Redfish.DynamicPropertyPatterns" annotation
                auto annotations = p_complex_type->get_annotation_list();
                if(annotation_has_term(annotations, ANNOTATION_DYNAMIC_PROP_PATTERN) 
                    && validate_redfish_dynamic_property_pattern(elem, annotations))
                {
                    return true;
                }
                else
                {
                    RF_PRINT_ERR("%s: property %s not found in complex type %s....\n", 
                             __FUNCTION__, e_prop_name.c_str(), prefix.c_str());
                    argument += "/";
                    argument += e_prop_name; 
                    SnapperMessage err_msg(BaseMessage::MMO_PropertyUnknown(argument));
                    set_response(err_msg.serialize_err_obj().c_str());        
                    return false;
                }
            }
            else
            {
                if(!validate_property_type(elem, prop, argument))
                    return false;
                else
                    return true;
            }
        }
        return true;
    }

    bool request_handler::validate_collection_type(bson::BSONElement e, std::shared_ptr<edm_collection_type> p_collection_type, string prefix)
    {
        string e_name = e.fieldName();
        string argument = prefix + "/" + e_name;
        
        if(e.type() != bson::Array)
        {
            RF_PRINT_ERR("%s: patch body is not array....\n", __FUNCTION__);
            SnapperMessage err_msg(BaseMessage::MMO_PropertyValueTypeError(raw_str(e.toString()), argument));
            set_response(err_msg.serialize_err_obj().c_str());
            return false;
        }
            
        vector<BSONElement> c_elem = e.Array();
        if(!c_elem.size())
        {
            RF_PRINT_ERR("%s: input array null\n", __FUNCTION__);
            SnapperMessage err_msg(BaseMessage::MMO_PropertyValueTypeError(raw_str(e.toString()), argument));
            set_response(err_msg.serialize_err_obj().c_str());
            return false;
        }
            
        std::shared_ptr<edm_named_type> elem_type = p_collection_type->get_element_type();
        RF_PRINT_DBG("%s: Collection element type %d....\n", __FUNCTION__, elem_type->get_type_kind());            
            
        for(int i = 0; i < c_elem.size(); i++)
        {
            if(elem_type->get_type_kind() == edm_type_kind_t::Primitive)
            {
                if(!validate_primitive_type(c_elem[i], std::dynamic_pointer_cast<edm_primitive_type>(elem_type), argument))
                {                            
                   return false;
                }
            } 
            else if(elem_type->get_type_kind() == edm_type_kind_t::Enum) 
            {
                if(!validate_enum_type(c_elem[i], std::dynamic_pointer_cast<edm_enum_type>(elem_type), argument))
                {                        
                        return false;
                }              
            }
            else if(elem_type->get_type_kind() == edm_type_kind_t::Complex) 
            {
                if(!validate_complex_type(c_elem[i], std::dynamic_pointer_cast<edm_complex_type>(elem_type), argument))
                {                        
                   return false;
                }  
            }
            else if(elem_type->get_type_kind() == edm_type_kind_t::Collection) 
            {
                if(!validate_collection_type(c_elem[i], std::dynamic_pointer_cast<edm_collection_type>(elem_type), argument))
                {                        
                   return false;
                }  
            }
        }   

        return true;
    }

    bool request_handler::validate_redfish_dynamic_property_pattern(bson::BSONElement e, std::vector<edm_payload_annotation_type *> annotations)
    {
        // check if "Redfish.DynamicPropertyPatterns" annotation
        auto annotation = annotation_get_term(annotations, ANNOTATION_DYNAMIC_PROP_PATTERN);
        if(annotation)
        {
            auto collection = annotation->get_subordinate_collection();
            if(collection)
            {
                auto records = collection->get_records();
                if(records.size() == 1)
                {
                    auto record = records[0];
                    auto propvals = record->get_propvals();
                    if(propvals.size() == 2)
                    {
                        string pattern_str("");
                        string type_str("");
                        for(int i = 0; i < 2; i++)
                        {
                            auto propval = propvals[i];
                            if(propval->get_propval_name() == "Pattern")
                                pattern_str = propval->get_propval_expr();
                            if(propval->get_propval_name() == "Type")
                                type_str = propval->get_propval_expr();                            
                        }

                        regex_t      reRes; 
                        regmatch_t   subs[4];
                        int          err = 0;
                        string field_name = e.fieldName();
    
                        if(!regcomp(&reRes, pattern_str.c_str(), REG_EXTENDED) 
                            && !regexec(&reRes, field_name.c_str(), sizeof(subs)/sizeof(regmatch_t), subs, 0))
                        {
                            if(type_str == "Edm.Primitive")
                            {
                                for(auto it = primitive_type_to_bson_type.begin(); it != primitive_type_to_bson_type.end(); it++)
                                {
                                    vector<int> type_vec = it->second;
                                    vector<int>::iterator result = find(type_vec.begin(), type_vec.end(), e.type());
                                    if(result != type_vec.end())
                                        return true;                                    
                                }
                                
                            }
                            else if(type_str == "Edm.String")
                            {
                                if(e.type() == bson::String)
                                    return true;
                            }
                            else
                            {
                                //return true for now
                                return true;
                            }                            
                        }                        
                    }                            
                }
            }
        }
        return false;
    }
    
    bool request_handler::validate_property_type(bson::BSONElement e, std::shared_ptr<edm_property_type> property, string prefix)
    {
        if(!property)
            return false;
        
        int e_type = e.type();
        string prop_name = e.fieldName();
        
        if(!m_op_create && is_read_only(property))
        {
            m_message.add_extended_message_obj(BaseMessage::MMO_PropertyNotWritable(prop_name));
            return true;
        }

        auto prop_type = property->get_property_type();
        RF_PRINT_DBG("validate_property_type: prop_type %d....\n", prop_type->get_type_kind());

        if(prop_type->get_type_kind() == edm_type_kind_t::Primitive)
        {
            return validate_primitive_type(e, std::dynamic_pointer_cast<edm_primitive_type>(prop_type), prefix, get_validation_pattern(property));
        }
        if(prop_type->get_type_kind() == edm_type_kind_t::TypeDefinition)
        {
            auto type = std::dynamic_pointer_cast<edm_type_def>(prop_type);
            std::shared_ptr<edm_primitive_type> primitive_type = type->get_primitive_type();
            return validate_primitive_type(e, primitive_type, prefix, get_validation_pattern(type));
        }
        else if(prop_type->get_type_kind() == edm_type_kind_t::Enum) 
        {
            return validate_enum_type(e, std::dynamic_pointer_cast<edm_enum_type>(prop_type), prefix);            
        }
        else if(prop_type->get_type_kind() == edm_type_kind_t::Complex) 
        {
            return validate_complex_type(e, std::dynamic_pointer_cast<edm_complex_type>(prop_type), prefix);
        }
        else if(prop_type->get_type_kind() == edm_type_kind_t::Collection) 
        {
            return validate_collection_type(e, std::dynamic_pointer_cast<edm_collection_type>(prop_type), prefix);                       
        }
        else
        {
            RF_PRINT_ERR("validate_property_type: to do\n");
        }
        return true;
    }
     
    bool request_handler::validate_request_body(::std::string entity_name, ::std::string request_body, bson::BSONObjBuilder& err)
    {
        bson::BSONObj body = ::bson::fromjson(request_body);
        vector<bson::BSONElement> body_elements;
        body.elems(body_elements);
        
        for(unsigned char i = 0; i < body_elements.size(); i++)
        {
            string prop_name(body_elements[i].fieldName());
            if(!check_property_privilege(prop_name))
            {
                int rc = RFRC_INSUFFICIENT_PRIVILEGE;
                set_err_response_body_hdr_status(rc, m_provider, m_method_str); 
                RF_PRINT_ERR("privilege property override check for resource %s failed\n", m_provider->get_name().c_str());
                return false; 
            }
            
            std::shared_ptr<edm_property_type> prop = m_model->find_entity_property(entity_name, prop_name);
            if(!prop)
            {
                SnapperMessage err_msg(BaseMessage::MMO_PropertyUnknown(prop_name));
                set_response(err_msg.serialize_err_obj().c_str());
                set_httpstatus(::snapper::providers::HTTP_BAD_REQUEST);
                return false;
            }
            
            if(!validate_property_type(body_elements[i], prop, entity_name))
            {
                set_httpstatus(::snapper::providers::HTTP_BAD_REQUEST);
                return false; 
            }
        }
        return true;
    }
    
    bool request_handler::validate_request_body(std::shared_ptr<odata_operation_segment> seg, ::std::string request_body, bson::BSONObjBuilder& err)
    {
        bool ret = true;
        bson::BSONObj body = ::bson::fromjson(request_body);
        vector<bson::BSONElement> body_elements;
        body.elems(body_elements);

        //if (seg->segment_type() == odata_path_segment_type::Operation)
        { 
            //shared_ptr<odata_operation_segment> operation_seg = seg->as<odata_operation_segment>();
            auto parameters_from_model = seg->operation()->get_operation_parameters();

            // set up the map to record the params required for the action
            // the second "int" is set to 1 when this param is found in the request body
            // all the second "int" should be 1 indicating the request body is valid.
            // skip the first param. 
            map<string, int> params;
            for(unsigned char j = 1; j < parameters_from_model.size(); j++)
            {
                params.insert(make_pair(parameters_from_model[j]->get_param_name(), 0));
            }

            //setup the vector for recording all the invalid params passed in the request body
            //needed in the error response
            vector<string> request_params_not_found;            
            for(unsigned char i = 0; i < body_elements.size(); i++)
            { 
                ::std::string name(body_elements[i].fieldName());
                bool found = false;
                for(unsigned char j = 0; j < parameters_from_model.size(); j++)
                {
                    if (name.compare(parameters_from_model[j]->get_param_name()) == 0)
                    {
                        params[parameters_from_model[j]->get_param_name()] = 1;
                        found = true;
                    }
                    else
                        continue;
                }

                if (!found)
                {
                    request_params_not_found.push_back(name);
                }
            }

            // walk through map "params" to build the error response if any
            SnapperMessage err_msg(BaseMessage::MMO_GeneralError());

            if (request_params_not_found.size())
            {
                ret = false;
                for(unsigned char k = 0; k < request_params_not_found.size(); k++)
                {
                    err_msg.add_extended_message_obj( 
                        BaseMessage::MMO_ActionParameterUnknown(seg->operation()->get_name(), request_params_not_found[k]));
                }
            }

            // walk through vector "request_params_not_found" to build the error response if any
            map<string, int>::iterator it;
            for(it = params.begin();it != params.end();++it)
            {
               string name = it->first;
               int val = it->second;

               if(!val)
               {
                   ret = false;
                   err_msg.add_extended_message_obj( 
                       BaseMessage::MMO_ActionParameterMissing(seg->operation()->get_name(), 
                       name));                   
               }
            }

            if (!ret)
            {
                set_response(err_msg.serialize_err_obj().c_str());
                set_httpstatus(::snapper::providers::HTTP_BAD_REQUEST);
            }
        }        

        return ret;      
    }

    
    bool request_handler::validate_create_body(::std::string name, ::std::string request_body, bson::BSONObjBuilder& err)
    {
        bool ret = true;
        bson::BSONObj body = ::bson::fromjson(request_body);
        vector<bson::BSONElement> body_elements;
        body.elems(body_elements);

        auto props_on_create = m_model->find_entity_properties_required_on_create(name);
        map<string, bool> props_on_create_map;
        for(auto it = props_on_create.begin(); it != props_on_create.end(); it++)
        {
            props_on_create_map[*it] = false;
        }
        
        for(unsigned char i = 0; i < body_elements.size(); i++)
        {
            string prop_name(body_elements[i].fieldName());
            std::shared_ptr<edm_property_type> prop = m_model->find_entity_property(name, prop_name);
            if(!prop)
            {
                SnapperMessage err_msg(BaseMessage::MMO_PropertyUnknown(prop_name));
                set_response(err_msg.serialize_err_obj().c_str());
                set_httpstatus(::snapper::providers::HTTP_BAD_REQUEST);
                return false;
            }
            
            if(!validate_property_type(body_elements[i], prop, name))
                return false;  

            auto it = props_on_create_map.find(prop_name);
            if(it != props_on_create_map.end())
            {
                it->second = true;
            }
        }

        SnapperMessage err_msg(BaseMessage::MMO_GeneralError());
        for(auto it = props_on_create_map.begin(); it != props_on_create_map.end(); it++)
        {
            if(it->second == false)
            {
                err_msg.add_extended_message_obj(BaseMessage::MMO_PropertyMissing(it->first));
                ret = false;
            }
        }

        if(!ret)
        {
            set_response(err_msg.serialize_err_obj().c_str());
            set_httpstatus(::snapper::providers::HTTP_BAD_REQUEST);
        }
        return ret;
    }

    bool request_handler::check_url_privilege(shared_ptr<request_context> request)
    {
        // currenlty we have no restriction on GET
        if(m_method == http_get)
            return true;
            
        unsigned long priv = m_current_session.aim_privileges;
        // supervisor has no restriction
        if(priv == IMM_PRIV_SUPERVISOR)
            return true;

        // readonly can only get
        if((priv == IMM_PRIV_READ_ONLY) && (m_method != http_get))
            return false;

        // currenlty we have no restriction on GET
        //if(m_method == http_get)
            //return true;

        // if no priv provider found, let it pass, but report warning.
        if(m_priv_provider == nullptr)
        {
            RF_PRINT_WARN("privilege for resource %s not found, let pass\n", m_provider->get_name().c_str());
            return true;
        }
        RF_PRINT_WARN("privilege for resource %s found\n", m_provider->get_name().c_str());

        // if url override found and validated, return success immediately
        if(m_priv_provider->has_url_override()) 
        {
            string url_in = request->get_raw_path();
            int rc = m_priv_provider->check_url_priv(url_in, m_method, priv);
            if(rc == SnapperPrivilege::override_fail)
            {
                RF_PRINT_ERR("privilege url override check for resource %s failed\n", m_provider->get_name().c_str());
                return false;
            }
            else if(rc == SnapperPrivilege::override_ok)
            {
                RF_PRINT_ERR("privilege url override check for resource %s passed\n", m_provider->get_name().c_str());
                return true;
            }
        }

        // if subordinate override found and validated, return success immediately
        if(m_priv_provider->has_subordinate_override())
        {
            std::cout << "m_target_str:" << m_target_str << std::endl;
            int rc = m_priv_provider->check_subordinate_priv(m_target_str, m_method, priv);
            if(rc == SnapperPrivilege::override_fail)
            {
                RF_PRINT_ERR("privilege subordinate override check for resource %s failed\n", m_provider->get_name().c_str());
                return false;
            }
            else if(rc == SnapperPrivilege::override_ok)
            {
                RF_PRINT_ERR("privilege subordinate override check for resource %s passed\n", m_provider->get_name().c_str());
                return true;
            }
        }                

        // if basic check not pass, and no override found, return failure immediately
        // otherwise check for property override later
        base_priv_check = m_priv_provider->check_base_priv(m_method, priv);
        if(!base_priv_check && !m_priv_provider->has_override())
        {
            RF_PRINT_ERR("privilege base check failed and privilege override for resource %s not found, privilege check failed\n", m_provider->get_name().c_str());
            return false;
        }

        return true;
    }

    bool request_handler::check_property_privilege(std::string prop_name)
    {
        int rc = RFRC_INSUFFICIENT_PRIVILEGE;
        unsigned long priv = m_current_session.aim_privileges;

        // supervisor has no restriction
        if(priv == IMM_PRIV_SUPERVISOR)
            return true;
        
        if(m_priv_provider == nullptr)
            return true;
        
        int ret = m_priv_provider->check_property_priv(prop_name, m_method, priv);
        if(ret == SnapperPrivilege::override_ok)
        {
            return true;
        }
        else if(ret == SnapperPrivilege::override_fail)
        {
            RF_PRINT_ERR("privilege property override check for resource %s failed\n", m_provider->get_name().c_str());
            return false; 
        }
        else // not found
        {
            if(base_priv_check)
            {
                return true;
            }
            else
            {
                RF_PRINT_ERR("privilege basic check for resource %s failed\n", m_provider->get_name().c_str());
                return false;
            }
        }
    }

    // check method allowance and privilege
    int request_handler::pre_check(shared_ptr<request_context> request)
    {
        int rc = RFRC_SUCCESS;
        if(!m_provider->check_allow(m_method))
        {
            rc = RFRC_METHOD_NOT_ALLOWED;
            set_err_response_body_hdr_status(rc, m_provider, m_method_str); 
            return rc;
        }
        
        if(!check_url_privilege(request))
        {
            rc = RFRC_INSUFFICIENT_PRIVILEGE;
            set_err_response_body_hdr_status(rc, m_provider, m_method_str);  
            return rc;
        }

        return rc;
    }

    int request_handler::rc_to_httpcode(int rc)
    {
        switch(rc)
        {
            case RFRC_FAILURE:
            case RFRC_INTERNAL_ERR:
            case RFRC_EXCEPTION:
                return ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR; break;

            case RFRC_INVALID_PARAMS:
            case RFRC_OUT_OF_RANGE:
                return ::snapper::providers::HTTP_BAD_REQUEST; break;                

            case RFRC_DATA_NOT_FOUND:
                return ::snapper::providers::HTTP_NOT_FOUND; break;
                
            case RFRC_METHOD_NOT_ALLOWED: 
                return ::snapper::providers::HTTP_METHOD_NOT_ALLOWED; break;

            case RFRC_NOT_IMPLEMENTED:
                return ::snapper::providers::HTTP_NOT_IMPLEMENTED; break;

            case RFRC_INSUFFICIENT_PRIVILEGE:
                return ::snapper::providers::HTTP_FORBIDDEN; break;

            case RFRC_AUTH_FAILED:
                return ::snapper::providers::HTTP_UNAUTH; break;

            default:
                return ::snapper::providers::HTTP_INTERNAL_SERVER_ERROR; break;
        }        
    }

    ::std::string request_handler::rc_to_httpresponse(int rc, std::shared_ptr<::snapper::providers::SnapperProvider> provider, std::string method_str)
    {
        switch(rc)
        {
            case RFRC_FAILURE:
            case RFRC_INTERNAL_ERR:
            case RFRC_EXCEPTION:
            {
                ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_GeneralError());
                return err.serialize_err_obj();                
            }

            case RFRC_INVALID_PARAMS:
            case RFRC_OUT_OF_RANGE:
            {
                ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_BadRequest() );
                return err.serialize_err_obj();
            }

            case RFRC_DATA_NOT_FOUND:
            {
                ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound() );
                return err.serialize_err_obj();
            }
                
            case RFRC_METHOD_NOT_ALLOWED: 
            {
                ::snapper::providers::SnapperMessage err(StandardErrorMessage::MMO_MethodNotAllowed( provider->get_name(), method_str) );
                return err.serialize_err_obj();
            }

            case RFRC_INSUFFICIENT_PRIVILEGE:
            {
                ::snapper::providers::SnapperMessage err(BaseMessage::MMO_InsufficientPrivilege());
                return err.serialize_err_obj();
            }

            case RFRC_NOT_IMPLEMENTED:
            {
                ::snapper::providers::SnapperMessage err(StandardErrorMessage::MMO_NotImplementedHttpMethod());
                return err.serialize_err_obj();
            }

            case RFRC_AUTH_FAILED:
            {
                ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_Unauthorized());
                return err.serialize_err_obj();                
            }

            default:
            {
                ::snapper::providers::SnapperMessage err(::snapper::providers::BaseMessage::MMO_GeneralError());
                return err.serialize_err_obj();                
            }
        }  
        
        return "";
    }

}}
