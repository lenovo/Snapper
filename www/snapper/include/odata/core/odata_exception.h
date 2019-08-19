//---------------------------------------------------------------------
// <copyright file="odata_exception.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/common/utility.h"
#include "odata/common/asyncrt_utils.h"
#include <stdlib.h>
#include <assert.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <dlfcn.h>

namespace odata { namespace core
{

enum odata_exception_err{
	ERROR_NOT_RELATIVE_URI = 0,
	ERROR_UNSUPPORTED_SEGMENT = 1,
	ERROR_RESOURCE_NOT_FOUND = 2,
	ERROR_UNEXPECTED_PATH_ROOT = 3,
	ERROR_UNEXPECTED_PARENTHESIS_EXPRESSION =4,
	ERROR_EMPTY_SEGMENT_IDENTIFIER = 5,
	ERROR_PARENTHESIS_MISMATCH = 6,
	ERROR_NAME_MUST_BE_PROVIDED = 7,
	ERROR_NAME_MUST_NOT_DUPLICATE = 8,
	ERROR_KEY_COUNT_MISMATCH = 9,
	ERROR_KEY_NOT_FOUND = 10,
	ERROR_CLOSE_CHAR_EXPECTED = 11,
	ERROR_NOT_OPEN_TYPE = 12,
	ERROR_NO_NAVIGATION_SOURCE =  13,
	ERROR_PARAMETER_COUNT_MISMATCH = 14 ,
	ERROR_PARAMETER_NOT_FOUND = 15,
	ERROR_BOUND_OPERATION_IMPORT_FOUND = 16,
	ERROR_UNBOUND_OPERATION_FOUND = 17,
	ERROR_BINDING_PARAMETER_NOT_FOUND = 18,
	ERROR_BINDING_TYPE_MISMATCH = 19,
	ERROR_SEGMENT_FOLLOW = 20,
	ERROR_SEGMENT_FOLLOW_NONCOMPOSABLE = 21,
	ERROR_INVALID_COUNT_QUERY = 22,
	ERROR_INVALID_CHARACTER = 23,
	ERROR_UNEXPECTED_TOKEN = 24,
	ERROR_TOKEN_KIND_EXPECTED = 25,
	ERROR_CHAR_KIND_EXPECTED = 26,
	ERROR_INVALID_VALUE = 27,
	ERROR_EMPTY_NAME_VALUE_PAIR = 28 ,
	ERROR_DUPLICATE_RANGE_VARIABLE = 29,
	ERROR_FILTER_ON_NONCOLLECTION = 30,
	ERROR_ORDERBY_ON_NONCOLLECTION = 31,
	ERROR_SELECT_OR_EXPAND_ON_NONSTRUCTURED_TYPE = 32,
	ERROR_NO_AVAILABLE_BINDING = 33,


	ERROR_UNKNOWN = 50
};

/// <summary>
/// Represents an OData exception
/// </summary>
class odata_exception : public std::exception
{
public:

    void odata_backtrace(::odata::utility::string_t error)
    {
        std::cout << std::endl;
        std::cout << "-----Exception [odata_exception]-----" << std::endl;
        std::cout << "Error: " << error << ". err# " << err_num << ". Backtrace : " << std::endl;
    
#define FR_NUM 10
        void * bt[FR_NUM];
        int entries = backtrace( (void **) &bt, FR_NUM );
        if ( entries )
        {
            char **data = backtrace_symbols( bt, entries );
            if ( data )
            {
                for (int i = 0; i < entries; i++ )
                {    
                    std::cout << "      [" << i << "] " << data[i] << std::endl;
                }
                free( data );
            }
        }

    }

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="error">A string value containing the service error.</param>
    explicit odata_exception(::odata::utility::string_t error, int err = 0) : m_error(error), err_num(err)
    {
        odata_backtrace(m_error);
    }

    /// <summary>
    /// Destructor
    /// </summary>
    ~odata_exception() _noexcept {}

    const ::odata::utility::string_t& what()
    {
        return m_error;
    }

private:
    ::odata::utility::string_t m_error;
	int err_num;
};

}}
