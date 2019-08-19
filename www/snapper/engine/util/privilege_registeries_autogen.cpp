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
#include <regex.h>

#include "bson/bson.h"
#include "bson/util/json.h"
#include "odata/core/odata_core.h"


#include "privilege_registeries_autogen.h"


#include <boost/noncopyable.hpp>

using namespace std;
using namespace ::odata::core;
using namespace ::odata::edm;
using namespace ::odata::utility;
using namespace ::bson;

    /////////////////////////////////////////////
// define static text of header code
/////////////////////////////////////////////
    const char *sHdr = 
"//---------------------------------------------------------------------\n"
"// <copyright file=\"_p%sPrivilege.h\" company=\"Lenovo\">\n"
"//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.\n"
"// </copyright>\n"
"//---------------------------------------------------------------------\n\n"
"#pragma once \n\n"
"#include \"SnapperPrivilege.h\" \n\n";

    const char *sNS_Class_Hdr = 
"namespace snapper { namespace providers \n"
"{\n\n"
"class _p%sPrivilege: public SnapperPrivilege\n"
"{\n"
"public:\n";
    
     const char *sNS_Class_Tail =    
"};\n\n"
"}}\n\n"; 

     const char *sNS_Class_Func = 
"    _p%sPrivilege(): SnapperPrivilege(\"%s\")\n"
"    {\n";

     const char *sNS_Class_Func_end = 
"    }\n\n"
"    virtual ~_p%sPrivilege() \n"
"    {}\n\n";
     
         
     const char *sNS_Class_Func_add_base_priv = 
"        add_base_priv(\"%s\", \"%s\");\n";
     const char *sNS_Class_Func_add_prop_priv = 
"        add_prop_priv(\"%s\", \"%s\", \"%s\");\n";
     const char *sNS_Class_Func_add_subordinate_priv = 
"        add_subordinate_priv(\"%s\", \"%s\", \"%s\");\n";
     const char *sNS_Class_Func_add_url_priv = 
"        add_url_priv(\"%s\", \"%s\", \"%s\");\n";


     // for cpp file
     const char *sHdr_cpp = 
     "//---------------------------------------------------------------------\n"
     "// <copyright file=\"_pSnapperPrivilege.cpp\" company=\"Lenovo\">\n"
     "//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.\n"
     "// </copyright>\n"
     "//---------------------------------------------------------------------\n\n"
     "#include \"class/SnapperPrivilege.h\" \n\n";

     const char *sInclude = 
     "#include \"class/_p%sPrivilege.h\" \n";

     const char *sNS_start = 
     "namespace snapper { namespace providers \n"
     "{\n\n"
     "    map<string, std::shared_ptr<SnapperPrivilege>> PrivilegeObjectFactory::ObjMap;\n\n";

     const char *sRegister_cpp = 
     "    REGISTER_PRIVILEGE(_p%sPrivilege);\n";

     const char *sNS_end = 
     "}}\n\n";

enum func_type
{
    BASE_PRIV,
    PROP_OVERRIDE,
    SUBORDINATE_OVERRIDE,
    URL_OVERRIDE
};

void _gen_add_priv_func(FILE *fp, vector<bson::BSONElement>& elements, func_type type, string target_name)
{
    for(unsigned char i = 0; i < elements.size(); i++)
    {
        bson::BSONElement elem = elements[i];
        string method = elem.fieldName();
        vector<bson::BSONElement> method_elems = elem.Array();
        for(unsigned char j = 0; j < method_elems.size(); j++)
        {             
            bson::BSONObj priv_obj = method_elems[j].Obj();  
            bson::BSONElement priv_elem = priv_obj["Privilege"];
            vector<bson::BSONElement> priv_elems = priv_elem.Array();
            for(unsigned char k = 0; k < priv_elems.size(); k++)
            {
                string priv_str = priv_elems[k].String();
                switch (type)
                {
                    case BASE_PRIV:
                        fprintf(fp, sNS_Class_Func_add_base_priv, method.c_str(), priv_str.c_str()); break;
                    case PROP_OVERRIDE:
                        fprintf(fp, sNS_Class_Func_add_prop_priv, target_name.c_str(), method.c_str(), priv_str.c_str()); break;
                    case SUBORDINATE_OVERRIDE:
                        fprintf(fp, sNS_Class_Func_add_subordinate_priv, target_name.c_str(), method.c_str(), priv_str.c_str()); break;
                    case URL_OVERRIDE:
                        fprintf(fp, sNS_Class_Func_add_url_priv, target_name.c_str(), method.c_str(), priv_str.c_str()); break;
                }
            }                
        }
    }
}

void _gen_privilege_registry_cpp_file(string dest_dir, vector<string> & resource)
{
#pragma GCC diagnostic ignored "-Wformat-security"		
    stringstream register_file_name;
    FILE *fp_reg = NULL;
            
    register_file_name.str("");
    register_file_name << dest_dir << "/_pSnapperPrivilege.cpp"; //for privilege register
            
    fp_reg = fopen(register_file_name.str().c_str(), "w+");
    if(fp_reg == NULL)
    {
       cout << "failed to generate privilege registery file " << register_file_name.str().c_str() << endl;
       return;
    }

    fprintf(fp_reg, sHdr_cpp);  
    for(unsigned int i = 0; i < resource.size(); i++)
    {
        fprintf(fp_reg, sInclude, resource[i].c_str());  
    }

    fprintf(fp_reg, sNS_start); 

    for(unsigned int i = 0; i < resource.size(); i++)
    {
        fprintf(fp_reg, sRegister_cpp, resource[i].c_str());  
    }
    fprintf(fp_reg, sNS_end);    
#pragma GCC diagnostic warning "-Wformat-security"
}

void _gen_privilege_header_file(string file_name, string dest_dir)
{
#pragma GCC diagnostic ignored "-Wformat-security"		
    
    ifstream ifs(file_name);
    stringstream buffer;
    buffer << ifs.rdbuf();  
    string contents(buffer.str());

    string str = contents.substr(0, contents.find_last_of("}")+1);
    bson::BSONObj o = bson::fromjson(str);    
    bson::BSONElement mappings_ele = o["Mappings"];
    vector<bson::BSONElement> elements = mappings_ele.Array();        
    
    vector<string> resource_vec;    
    for(unsigned char i = 0; i < elements.size(); i++)
    {
        bson::BSONObj mapping_elem_obj = elements[i].Obj();    
        string resource_name = mapping_elem_obj.getStringField("Entity");
        
        stringstream fname;
        FILE *fp = NULL;
        
        fname.str("");
        fname << dest_dir << "/_p" << resource_name << "Privilege.h"; // auto gen file _pXXXPrivilege.h
        
        fp = fopen(fname.str().c_str(), "w+");
        if(fp == NULL)
        {
            cout << "failed to generate privilege registery " << fname.str().c_str() << endl;
            continue;
        }

        resource_vec.push_back(resource_name);
        //std::cout << "filename " << fname.str() << std::endl;

        //file header
        fprintf(fp, sHdr, resource_name.c_str());
        
        //class header
        fprintf(fp, sNS_Class_Hdr, resource_name.c_str());
        
        //func start
        fprintf(fp, sNS_Class_Func, resource_name.c_str(), resource_name.c_str());  

        //constructor
        bson::BSONObj OperationMap = mapping_elem_obj.getObjectField("OperationMap"); 
        vector<bson::BSONElement> OperationMap_elements;
        OperationMap.elems(OperationMap_elements);
        _gen_add_priv_func(fp, OperationMap_elements, BASE_PRIV, "");        
        fprintf(fp, "\n");
        
        if(mapping_elem_obj.hasElement("PropertyOverrides"))
        {
            bson::BSONElement PropertyOverrides_elem = mapping_elem_obj["PropertyOverrides"];
            vector<bson::BSONElement> PropertyOverrides_elems = PropertyOverrides_elem.Array();
            for(unsigned char k = 0; k < PropertyOverrides_elems.size(); k++)
            {
                bson::BSONObj PropertyOverrides_map_obj = PropertyOverrides_elems[k].Obj();
                bson::BSONElement target_elem = PropertyOverrides_map_obj["Targets"];                
                vector<bson::BSONElement> elem = target_elem.Array();
                string prop_name = elem[0].String();
                bson::BSONObj prop_OperationMap = PropertyOverrides_map_obj.getObjectField("OperationMap");
                vector<bson::BSONElement> OperationMap_elements;
                prop_OperationMap.elems(OperationMap_elements);
                _gen_add_priv_func(fp, OperationMap_elements, PROP_OVERRIDE, prop_name);
                fprintf(fp, "\n");                
            } 
        }

        if(mapping_elem_obj.hasElement("SubordinateOverrides"))
        {
            bson::BSONElement SubordinateOverrides_elem = mapping_elem_obj["SubordinateOverrides"];
            vector<bson::BSONElement> SubordinateOverrides_elems = SubordinateOverrides_elem.Array();
            for(unsigned char k = 0; k < SubordinateOverrides_elems.size(); k++)
            {
                bson::BSONObj SubordinateOverrides_map_obj = SubordinateOverrides_elems[k].Obj();
                bson::BSONElement target_elem = SubordinateOverrides_map_obj["Targets"];                
                vector<bson::BSONElement> elem = target_elem.Array();
                string target_str;
                for(unsigned char m = 0; m < elem.size(); m++)
                {
                    if(m == 0)
                    {
                        target_str = elem[m].String();
                    }
                    else
                    {
                        target_str += "/";
                        target_str += elem[m].String();
                    }                        
                }
                bson::BSONObj suboridnate_OperationMap = SubordinateOverrides_map_obj.getObjectField("OperationMap");
                vector<bson::BSONElement> OperationMap_elements;
                suboridnate_OperationMap.elems(OperationMap_elements);
                _gen_add_priv_func(fp, OperationMap_elements, SUBORDINATE_OVERRIDE, target_str);
                fprintf(fp, "\n");                
            } 
        }

        if(mapping_elem_obj.hasElement("ResourceURIOverrides"))
        {
            bson::BSONElement ResourceURIOverrides_elem = mapping_elem_obj["ResourceURIOverrides"];
            vector<bson::BSONElement> ResourceURIOverrides_elems = ResourceURIOverrides_elem.Array();
            for(unsigned char k = 0; k < ResourceURIOverrides_elems.size(); k++)
            {
                bson::BSONObj ResourceURIOverrides_map_obj = ResourceURIOverrides_elems[k].Obj();
                bson::BSONElement target_elem = ResourceURIOverrides_map_obj["Targets"];                
                vector<bson::BSONElement> elem = target_elem.Array();
                string target_str;
                for(unsigned char m = 0; m < elem.size(); m++)
                {
                    target_str = elem[m].String();
                    bson::BSONObj suboridnate_OperationMap = ResourceURIOverrides_map_obj.getObjectField("OperationMap");
                    vector<bson::BSONElement> OperationMap_elements;
                    suboridnate_OperationMap.elems(OperationMap_elements);
                    _gen_add_priv_func(fp, OperationMap_elements, URL_OVERRIDE, target_str);
                    fprintf(fp, "\n");                                          
                }                             
            } 
        }

        //func end
        fprintf(fp, sNS_Class_Func_end, resource_name.c_str());        

        // class end
        fprintf(fp, sNS_Class_Tail);
        fclose(fp);
    }

    _gen_privilege_registry_cpp_file(dest_dir, resource_vec);

#pragma GCC diagnostic warning "-Wformat-security"
   
}

void gen_privilege_registry(string dest_dir, string src_dir)
{
     regex_t      reRes1, reRes2, reRes3;
     regmatch_t   subs[4];
     string regexRes1 = "(Redfish_)([0-9]{1,2}\\.[0-9]{1,2}\\.[0-9]{1,2})(_PrivilegeRegistry)\\.(json)";

     if(regcomp(&reRes1, regexRes1.c_str(), REG_EXTENDED))
     {
        std::cout << "regex compile error: " << std::endl;
        return ;
     }
    
    ::odata::utility::string_t reg_dir(src_dir);
    DIR *dp;
    struct dirent *dirp;
    if ((dp  = opendir(reg_dir.c_str())) == NULL) 
    {
        std::cout << "opendir " << src_dir  <<" error" << std::endl;
        return;
    }

    vector<::odata::utility::string_t> fileNameList;
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        size_t found = filename.find_last_of(".");
        if (found != string::npos)
        {
            //std::cout << "file " << filename << std::endl;
                
            if (!regexec(&reRes1, filename.c_str(), sizeof(subs)/sizeof(regmatch_t), subs, 0))                
            {
                ::odata::utility::string_t absFilename = src_dir + "/" + filename;
                //std::cout << "file " << absFilename << std::endl;
                _gen_privilege_header_file(absFilename, dest_dir);
            }
        }
    }
    std::cout << "privilege files generated" << std::endl;
    closedir(dp);
}


