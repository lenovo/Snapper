//---------------------------------------------------------------------
// <copyright file="request_context.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/edm/edm_model.h"
#include "odata/core/odata_uri_parser.h"
#include "odata/core/odata_path_segment_visitor.h"

using namespace ::odata::utility;
using namespace ::odata::core;

namespace snapper { namespace service
{

enum http_method
{
    http_get = 0,
    http_head,
    http_post,
    http_put,
    http_patch,
    http_delete,
};
//will be used to index allows(). pls don't change the order of method

class request_context
{
public:
    request_context(::std::string full_uri, int method, ::std::shared_ptr<::odata::edm::edm_model> model, 
                       ::std::string request_headers = "",  ::std::string request_body = "" );
    ~request_context() {};


    ::std::shared_ptr<::odata::core::odata_path> get_odata_path()
    {
        if(m_odata_uri != nullptr)
            return m_odata_uri->path();
        return nullptr;
    }

    ::std::string &get_uri()
    {
        return m_full_uri;
    }

    ::std::string &get_raw_path()
    {
        return m_raw_path;
    }

    void set_raw_path(::std::string p)
    {
        m_raw_path = p;
    }

    ::std::string &get_fragment()
    {
        return m_fragment;
    }

    ::std::string &get_request_headers()
    {
        return m_request_headers;
    }

    ::std::string &get_request_body()
    {
        return m_request_body;
    }

    int get_method()
    {
        return m_method;
    }

    ::std::string get_method_str()
    {
        switch (m_method)
        {
            case http_get:  return "GET"; break;
            case http_post: return "POST"; break;
            case http_put:  return "PUT"; break;
            case http_patch: return "PATCH"; break;
            case http_delete: return "DELETE"; break;
            case http_head: return "HEAD"; break;
            default: return ""; break;
        }
        return "";
    }


    std::vector<std::string> &get_path_str()
    {
        return m_uripath_str;
    }

    // 0 - no top parameter, others - top number
    int top()
    {
        return (m_odata_uri->top().has_value() ? m_odata_uri->top().value(): 0);
    }

    // 0 - no skip parameter, others - skip number
    int skip()
    {
        return (m_odata_uri->skip().has_value() ? m_odata_uri->skip().value(): 0);
    }

    void set_op_create(bool f)
    {
        m_op_creat = f;
    }
    bool is_op_create()
    {
        return m_op_creat;
    }

    const ::std::string& get_action() const { return m_action; }
    void set_action(const ::std::string& action)
    {
		m_action = action;
    }

private:
    //m_full_uri: string includes scheme, host, userinfo, path, query and fragment
    //m_odata_uri: odata_uri includes odata path and odata query
    //m_raw_path: string path of url
    //m_uripath_str: vector of segment string in uri path
    //m_fragment: url part after #

    ::std::string m_full_uri;
    ::std::string m_raw_path;
    ::std::string m_fragment;
    ::std::string m_request_headers;
    ::std::string m_request_body;
    std::vector<std::string> m_uripath_str;
    int m_method;
    bool m_op_creat;
    ::std::string m_action;

    ::std::shared_ptr<::odata::core::odata_uri_parser> m_uri_parser;
    ::std::shared_ptr<::odata::core::odata_uri> m_odata_uri; // uri string converted to odata uri segments


};


class print_visitor : public odata_path_segment_visitor<::odata::utility::string_t>
{
public:
	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_metadata_segment> segment)
	{
        std::stringstream name("");
        name << "Metadata (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_batch_segment> segment)
	{
        std::stringstream name("");
        name << "Batch (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_entity_set_segment> segment)
	{
        std::stringstream name("");
        name << "EntitySet (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_singleton_segment> segment)
	{
        std::stringstream name("");
        name << "Singleton (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_key_segment> segment)
	{
        std::stringstream name("");
        name << "Key (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_structural_property_segment> segment)
	{
        std::stringstream name("");
        name << "StructuralProperty (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_navigation_property_segment> segment)
	{
        std::stringstream name("");
        name << "NavigationProperty (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_dynamic_property_segment> segment)
	{
        std::stringstream name("");
        name << "DynamicProperty (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_value_segment> segment)
	{
        std::stringstream name("");
        name << "Value (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_count_segment> segment)
	{
        std::stringstream name("");
        name << "Count (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_ref_segment> segment)
	{
        std::stringstream name("");
        name << "Ref (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_type_segment> segment)
	{
        std::stringstream name("");
        name << "Type (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_operation_segment> segment)
	{
        std::stringstream name("");
        name << "Operation (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit(std::shared_ptr<::odata::core::odata_operation_import_segment> segment)
	{
        std::stringstream name("");
        name << "OperationImport (" << segment->segment_type() << ")";
		return name.str();
	}

	::odata::utility::string_t visit_any(std::shared_ptr<::odata::core::odata_path_segment> segment)
	{
        std::stringstream name("");
        name << "Any (" << segment->segment_type() << ")";
		return name.str();
	}
};



}}

