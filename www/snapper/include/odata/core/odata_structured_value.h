﻿//---------------------------------------------------------------------
// <copyright file="odata_structured_value.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/edm/odata_edm.h"
#include "odata/core/odata_value.h"
#include "odata/core/odata_primitive_value.h"

namespace odata { namespace core
{
class odata_collection_value;
class odata_entity_value;
class odata_complex_value;
class odata_enum_value;

class odata_structured_value : public odata_value
{
public:
	odata_structured_value(std::shared_ptr<::odata::edm::edm_named_type>type) : odata_value(type)
	{
	}

	odata_structured_value(std::shared_ptr<::odata::edm::edm_named_type>type, odata_property_map properties) 
		: m_properties(std::move(properties)), odata_value(type)
	{
		
	}

	virtual ~odata_structured_value(){}

    /// <summary>Returns a const reference to the property map.</summary>
    const odata_property_map& properties() const { return m_properties; }

	void set_properties(odata_property_map map)
	{
		m_properties = std::move(map);
	}

    /// <summary>Tells whether the structured object has a property of a given name.</summary>
    /// <param name="property_name">The name of the property</param>
    bool has_property(const ::odata::utility::string_t& property_name) const
    {
        std::shared_ptr<odata_value> details;
        return m_properties.try_get(property_name, details);
    }

    /// <summary>Tells whether the structured object has a property of a given name.</summary>
    /// <param name="property_name">The name of the property</param>
	bool has_property(const ::odata::utility::string_t& property_name, std::shared_ptr<::odata::edm::edm_named_type>& type) const
    {
        std::shared_ptr<odata_value> details;
        bool result = m_properties.try_get(property_name, details);
        if ( result )
        {
            type = details->get_value_type();
        }
        return result;
    }

	bool get_property_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_value>& property_value)
	{
		return m_properties.try_get(property_name, property_value);
	}

    template<typename T>
    bool try_get(const ::odata::utility::string_t& property_name, T& value) const
    {
        return m_properties.try_get(property_name, value);
    }

	void set_value(const ::odata::utility::string_t& property_name, float float_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::SINGLE(), ::odata::utility::print_float(float_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, unsigned char ubyte_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::BYTE(), ::odata::utility::conversions::print_string(ubyte_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, char byte_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::BYTE(), ::odata::utility::conversions::print_string(byte_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, int32_t int32_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::INT32(), ::odata::utility::conversions::print_string(int32_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, const std::vector<unsigned char>& binary_data)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::BINARY(), ::odata::utility::conversions::to_base64(binary_data));
	}

	void set_value(const ::odata::utility::string_t& property_name, bool boolean_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::BOOLEAN(), ::odata::utility::conversions::print_string(boolean_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, ::odata::utility::datetime datetime_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::DATETIMEOFFSET(), datetime_value.to_string(::odata::utility::datetime::date_format::ISO_8601));
	}

	void set_value(const ::odata::utility::string_t& property_name, ::odata::utility::seconds duration_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::DURATION(), ::odata::utility::timespan::seconds_to_xml_duration(duration_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, double double_precision_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::DOUBLE(), ::odata::utility::print_double(double_precision_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, int64_t int64_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::INT64(), ::odata::utility::conversions::print_string(int64_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, uint64_t u_int64_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::INT64(), ::odata::utility::conversions::print_string(u_int64_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, int16_t int16_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::INT16(), ::odata::utility::conversions::print_string(int16_value));
	}

	void set_value(const ::odata::utility::string_t& property_name, const ::odata::utility::char_t* string_value)
	{
		m_properties[property_name] = std::make_shared<odata_primitive_value>(::odata::edm::edm_primitive_type::STRING(), string_value);
	}

	void set_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_value> property_value)
	{
		m_properties[property_name] = property_value;
	}

	ODATACPP_API void set_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_primitive_value> property_value);

	ODATACPP_API void set_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_complex_value> property_value);

	ODATACPP_API void set_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_entity_value> property_value);

	ODATACPP_API void set_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_enum_value> property_value);

	ODATACPP_API void set_value(const ::odata::utility::string_t& property_name, std::shared_ptr<odata_collection_value> property_value);

	ODATACPP_API void set_value(const ::odata::utility::string_t& property_name, const ::odata::utility::string_t& string_value);

    /// <summary>
    /// Removes a property from the structured object if it is present.
    /// </summary>
    /// <param name="string_value">A string representing the property value.</param>
    odata_structured_value& remove(const ::odata::utility::string_t& property_name)
    {
        m_properties.erase(property_name);
        return *this;
    }

protected:
	odata_property_map             m_properties;
};

}}