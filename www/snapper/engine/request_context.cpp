//---------------------------------------------------------------------
// <copyright file="request_context.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <www/engine/rf_debug.h>

#include <www/engine/request_context.h>

using namespace ::std;
using namespace ::odata::edm;
using namespace ::odata::core;

namespace snapper { namespace service
{
    request_context::request_context(std::string full_uri, int method, ::std::shared_ptr<::odata::edm::edm_model> model, ::std::string request_headers, ::std::string request_body) : m_full_uri(full_uri), 
    m_method(method), m_op_creat(false), m_request_headers(request_headers), m_request_body(request_body)
    {
        m_uri_parser = make_shared<::odata::core::odata_uri_parser>(model);
        m_odata_uri = m_uri_parser->parse_uri(::odata::utility::uri::encode_uri(full_uri));

        ::odata::utility::uri uri(::odata::utility::uri::encode_uri(full_uri)); //full_uri -  http://localhost/redfish/v1/Systems/1/
        m_raw_path = ::odata::utility::uri::decode(uri.path());  //raw path - /redfish/v1/Systems/1/
        m_uripath_str = ::odata::utility::uri::split_path( m_raw_path ); //uripath_str -  <"Systems", "1">  without service root
        m_fragment = ::odata::utility::uri::encode_uri(uri.fragment()); // /Voltages/0  from /redfish/v1/Chassis/1/Power/?$top=3#/Voltages/0

		//debug log: segment name
		auto path = m_odata_uri->path();
		if(path != nullptr)
		{
			auto visitor = std::make_shared<::snapper::service::print_visitor>();
			auto result = path->visit_with(std::static_pointer_cast<::odata::core::odata_path_segment_visitor<::odata::utility::string_t>>(visitor));
			for (auto it = result.begin(); it != result.end(); ++it)
			{
				RF_PRINT_DBG("==> segment name: %s \n", (*it).c_str());
			}
		}
    }

}}
