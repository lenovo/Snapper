﻿//---------------------------------------------------------------------
// <copyright file="odata_json_operation_payload_parameter_writer.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/common/json.h"
#include "odata/common/utility.h"
#include "odata/core/odata_core.h"
#include "odata/edm/odata_edm.h"

namespace odata { namespace core
{

class odata_json_operation_payload_parameter_writer
{
public:
	odata_json_operation_payload_parameter_writer(std::shared_ptr<::odata::edm::edm_model> model) : m_model(model)
	{
	}

	ODATACPP_API ::odata::utility::json::value serialize(std::vector<std::shared_ptr<odata_parameter>> parameters);

private:
	void handle_serialize_odata_parameter(::odata::utility::stringstream_t& ss, const std::shared_ptr<::odata::core::odata_parameter>& parameter, ::odata::utility::char_t mark, ::odata::utility::char_t separator);
	void handle_serialize_odata_value(::odata::utility::stringstream_t& ss, const std::shared_ptr<::odata::edm::edm_named_type>& property_type, const std::shared_ptr<odata_value>& property_value);
	void handle_serialize_primitive_value(::odata::utility::stringstream_t& ss, const std::shared_ptr<::odata::edm::edm_primitive_type>& p_primitive_type, const std::shared_ptr<odata_primitive_value>& p_value);
	void handle_serialize_enum_value(::odata::utility::stringstream_t& ss, const std::shared_ptr<odata_enum_value>& p_value);
	void handle_serialize_collection_value(::odata::utility::stringstream_t& ss, const std::shared_ptr<odata_collection_value>& p_value);
	void handle_serialize_odata_properties(::odata::utility::stringstream_t& ss, const odata_property_map& properties);
	bool is_type_serializable(const std::shared_ptr<::odata::edm::edm_named_type>& property_type);
	
	std::shared_ptr<::odata::edm::edm_model> m_model;
};

}}