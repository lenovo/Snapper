/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <dirent.h>

#include "bson/bson.h"
#include "bson/util/json.h"

#include "odata/edm/edm_model_reader.h"
#include "odata/core/odata_service_document.h"

#include "odata/core/odata_path_segment_visitor.h"
#include "odata/core/odata_query_node_visitor.h"
#include <www/engine/request_handler.h>
#include <www/engine/request_context.h>
#include "privilege_registeries_autogen.h"

#include <boost/noncopyable.hpp>

using namespace std;
using namespace ::odata::core;
using namespace ::odata::edm;
using namespace ::odata::utility;
using namespace ::bson;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "invalide parameters:  snapper_autogen_privreg srcdir destdir" << std::endl;
        return false;
    }

    gen_privilege_registry(argv[2], argv[1]);

    return 0;

}

