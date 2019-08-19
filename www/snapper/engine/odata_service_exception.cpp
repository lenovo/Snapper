//---------------------------------------------------------------------
// <copyright file="odata_service_exception.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------
#include <www/engine/rf_debug.h>
#include "odata/edm/edm_model.h"
#include "odata/core/odata_uri_parser.h"
#include "odata_service_exception.h"
#include <stdlib.h>
#include <assert.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <dlfcn.h>


using namespace ::std;
using namespace ::odata::edm;
using namespace ::odata::core;

namespace odata { namespace service
{


void odata_service_exception::odata_backtrace(::odata::utility::string_t error)
{
	RF_PRINT_ERR("\n-----Exception [odata_service_exception]-----\n");
	RF_PRINT_ERR("Error: %s. Backtrace : \n", error.c_str());

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
                RF_PRINT_ERR( "    [%d] %s\n", i, data[i]);
            }
            free( data );
		}
	}
	
}


}}
