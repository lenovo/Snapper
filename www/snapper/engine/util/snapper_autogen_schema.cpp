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

#include <boost/noncopyable.hpp>

using namespace std;
using namespace ::odata::core;
using namespace ::odata::edm;
using namespace ::odata::utility;
using namespace ::bson;

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cout << "invalide parameters:  snapper_autogen_schema srcXMLdir srcJSONdir destdir" << std::endl;
        return false;
    }

    ::odata::utility::string_t metadata_dir(argv[1]);
    DIR *dp;
    struct dirent *dirp;
    if ((dp  = opendir(metadata_dir.c_str())) == NULL) 
    {
        std::cout << "opendir error" << std::endl;
        return false;
    }

    vector<::odata::utility::string_t> fileNameList;
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        std::size_t found = filename.find_first_of(".");
        if (found != std::string::npos)
        {
            ::odata::utility::string_t fileBase = filename.substr(1,(found-1));
            ::odata::utility::string_t fileExt  = filename.substr(found);

            if (fileExt.compare(".xml") == 0)
            {
                ::odata::utility::string_t absFilename = metadata_dir + "/" + filename;
                fileNameList.push_back(absFilename);
                //std::ifstream ifs(absFilename);
                //rf_metadata << ifs.rdbuf();
            }
        }
    }
    closedir(dp);

    std::string oemshim_dir = metadata_dir;
    if (strncmp((const char*)&oemshim_dir.back(), "/", 1) != 0)
        oemshim_dir += "/";
    oemshim_dir += "OemShim/";
    if ((dp  = opendir(oemshim_dir.c_str())) == NULL) 
    {
        std::cout << "OemShim opendir error" << std::endl;
        return false;
    }
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        std::size_t found = filename.find_first_of(".");
        if (found != std::string::npos)
        {
            ::odata::utility::string_t fileBase = filename.substr(0,found);
            ::odata::utility::string_t fileExt  = filename.substr(found);
 
            if (fileExt.compare(".xml") == 0)
            {
                ::odata::utility::string_t absFilename = oemshim_dir + "/" + filename;
                fileNameList.push_back(absFilename);
                //std::cout << "Shim folder" << absFilename << std::endl;
            }
        }
    }
    closedir(dp);

    ::odata::utility::string_t fileName = fileNameList[0];
    std::ifstream ifs(fileName);        
    auto model_reader = std::make_shared<::odata::edm::edm_model_reader>(ifs);
    model_reader->parse_edm();
    auto model = model_reader->get_model();

    for (unsigned int i = 1; i < fileNameList.size(); i++)
    {
        ::odata::utility::string_t fileName = fileNameList[i];
        std::ifstream ifs(fileName);        
        model_reader = std::make_shared<::odata::edm::edm_model_reader>(ifs, model);
        model_reader->parse_edm();
    }
    model_reader->resolve_edm();
//    model_reader->dump_model();


    DIR *tgtdp;
    if ((tgtdp  = opendir(argv[2])) == NULL) 
    {
        std::cout << "opendir error :" << argv[2] << std::endl;
        return false;
    }
    closedir(tgtdp);
    if ((tgtdp  = opendir(argv[3])) == NULL) 
    {
        std::cout << "opendir error :" << argv[3] << std::endl;
        return false;
    }
    closedir(tgtdp);


    model_reader->gen_resource_provider(argv[3], argv[1], argv[2]);

    return 0;

}

