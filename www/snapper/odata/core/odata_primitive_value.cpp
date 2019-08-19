﻿//---------------------------------------------------------------------
// <copyright file="odata_primitive_value.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#include "odata/core/odata_core.h"
#include "odata/edm/edm_model_utility.h"

using namespace ::odata::utility;
using namespace ::odata::edm;

namespace odata { namespace core
{

void odata_primitive_value::_try_get(std::vector<unsigned char>& value) const
{
	std::vector<unsigned char> temp(::odata::utility::conversions::from_base64(to_string()));
    value.swap(temp);
}

void odata_primitive_value::_try_get(unsigned char& value) const
{
	const auto& propValue = to_string();

	int16_t v;
    utility::bind(propValue, v);
	value = (unsigned char)v;
}

void odata_primitive_value::_try_get(char& value) const
{
	const auto& propValue = to_string();

	int32_t v;
    utility::bind(propValue, v);
	value = (char)v;
}

void odata_primitive_value::_try_get(bool& value) const
{
    const auto& propValue = to_string();
    if (propValue == U("false") || propValue == U("0")) value = false;
    else value = true;
}

void odata_primitive_value::_try_get(::odata::utility::datetime& value) const
{
    value = ::odata::utility::datetime::from_string(to_string(), ::odata::utility::datetime::ISO_8601);
}

void odata_primitive_value::_try_get(::odata::utility::seconds& value) const
{
    value = ::odata::utility::timespan::xml_duration_to_seconds(to_string());
}

void odata_primitive_value::_try_get(double& value) const
{
    const auto& propValue = to_string();
    utility::bind(propValue, value);
}

void odata_primitive_value::_try_get(float& value) const
{
    const auto& propValue = to_string();
    utility::bind(propValue, value);
}

void odata_primitive_value::_try_get(int16_t& value) const
{
    const auto& propValue = to_string();
    utility::bind(propValue, value);
}

void odata_primitive_value::_try_get(int32_t& value) const
{
    const auto& propValue = to_string();
    utility::bind(propValue, value);
}

void odata_primitive_value::_try_get(int64_t& value) const
{
    const auto& propValue = to_string();
    utility::bind(propValue, value);
}

void odata_primitive_value::_try_get(uint64_t& value) const
{
    const auto& propValue = to_string();
    utility::bind(propValue, value);
}

void odata_primitive_value::_try_get(::odata::utility::string_t& value) const
{
    value = to_string();
}

}}