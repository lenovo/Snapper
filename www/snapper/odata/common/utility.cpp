﻿//---------------------------------------------------------------------
// <copyright file="utility.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#include "odata/common/utility.h"

namespace odata { namespace utility
{

string_t strip_string(const string_t& escaped)
{
    string_t::size_type first = 0;
    string_t::size_type size = escaped.size();

	if (escaped.empty())
	{
		return escaped;
	}

    if (escaped[0] == U('"'))
	{
        first += 1;
	}

    if (escaped[size - 1] == U('"'))
	{
        size -= 1;
	}

    return escaped.substr(first, size - first);
}

void split_string(string_t& source, const string_t& delim, std::list<string_t>& ret)
{
	ret.clear();

	if (delim.empty() || source.empty())
	{
		ret.push_back(source);
		return ;
	}

	size_t last = 0;
	size_t index = source.find(delim, last);

    while (index!=std::string::npos)
    {
		ret.push_back(source.substr(last, index - last));
		last = index + delim.size();
		index = source.find(delim, last);
	}

    if(index - last > 0)
	{
		ret.push_back(source.substr(last, index - last));
	}
}

bool is_relative_path(const string_t& _root_url, const string_t& _path)
{
	if (_root_url.empty() || _path.empty())
	{
		return false;
	}

	string_t root_url = _root_url;
	string_t path = _path;

	if (root_url.length() > path.length())
	{
		return true;
	}

	std::transform(root_url.begin(), root_url.end(), root_url.begin(), ::tolower);
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);

	return path.find(root_url) != 0;
}

string_t print_double(const double& db, int precision)
{
    ostringstream_t oss;
	oss << std::setiosflags(std::ios::fixed) << std::setiosflags(std::ios::right) << std::setprecision(precision)  << db;
    if (oss.bad())
	{
        throw std::bad_cast();
	}

	string_t output = oss.str();
	int dot = (int)output.find(U('.'));
	if (dot > 0)
	{
		int i;
		for (i = (int)output.length() - 1; i > dot; i--)
		{
			if (output[i] != U('0'))
			{
				break;
			}
		}

		if (i == dot)
		{
			i++;
		}

		output = output.substr(0, i + 1);
	}

    return output;
}

string_t print_float(const float& db, int precision)
{
    ostringstream_t oss;
	oss << std::setiosflags(std::ios::fixed) << std::setiosflags(std::ios::right) << std::setprecision(precision)  << db;
    if (oss.bad())
	{
        throw std::bad_cast();
	}

	string_t output = oss.str();
	int dot = (int)output.find(U('.'));
	if (dot > 0)
	{
		int i;
		for (i = (int)output.length() - 1; i > dot; i--)
		{
			if (output[i] != U('0'))
			{
				break;
			}
		}

		if (i == dot)
		{
			i++;
		}

		output = output.substr(0, i + 1);
	}

    return output;
}

bool is_digit(char_t c)
{
#ifdef _UTF16_STRINGS
	return iswdigit(c) != 0;
#else
	return isdigit(c) != 0;
#endif
}

bool is_hex_digit(char_t c)
{
#ifdef _UTF16_STRINGS
	return iswxdigit(c) != 0;
#else
	return isxdigit(c) != 0;
#endif
}

bool is_letter(char_t c)
{
#ifdef _UTF16_STRINGS
	return iswalpha(c) != 0;
#else
	return isalpha(c) != 0;
#endif
}

bool is_letter_or_digit(char_t c)
{
	return is_letter(c) || is_digit(c);
}

}}