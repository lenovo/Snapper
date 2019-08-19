//---------------------------------------------------------------------
// <copyright file="SnapperSchema.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <sstream>
#include <iostream>

#include "class/SnapperSchema.h"
#include "class/BaseMessage.h"
#include "class/StandardErrorMessage.h"
#include "class/AuditEventMessage.h"
#include "class/SnapperMessage.h"
#include "class/SnapperProvider.h"
#include <www/engine/rf_debug.h>


namespace snapper { namespace providers 
{
#ifndef __SIM_X86__
const string JSON_DIR = "/var/www/snapper/schema_json/";    
const string XML_DIR = "/var/www/snapper/schema_xml/";
#else
const string JSON_DIR = "../schema_json/";    
const string XML_DIR = "../schema_xml/";
#endif

SnapperSchema::SnapperSchema(string file_name) 
{
    string _file_name;
    if(file_name.compare("$metadata") == 0)
        _file_name = "metadata.xml";
    else
        _file_name = file_name;

    RF_PRINT_DBG("SnapperSchema: %s \n", _file_name.c_str());
    
    std::size_t found = _file_name.find_last_of(".");
    string fileExt = _file_name.substr(found + 1);

    if(fileExt.compare("xml") && fileExt.compare("json"))
    {
        ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
        m_response = err.serialize_err_obj();
        http_status_code = 404;
    }
    else
    { 
        string base_dir;
        if(fileExt.compare("xml") == 0)
            base_dir = XML_DIR;
        else if(fileExt.compare("json") == 0)
            base_dir = JSON_DIR;
           
        ifstream schemafile(base_dir + _file_name, ios::binary);
        if(schemafile.is_open())
        {            
            stringstream buffer;
            buffer << schemafile.rdbuf();
            m_response = buffer.str();
            if(fileExt.compare("xml") == 0)
            {
                hdr_obj.append("Content-Type", "application/xml;charset=UTF-8"); 
            }
            else if(fileExt.compare("json") == 0)
            {
                hdr_obj.append("Content-Type", "application/json;charset=UTF-8");                
            }
            
            stringstream ss;
            ss << "W/\"" << hex << HASH_STRING(m_response.c_str()) << "\"";
            hdr_obj.append("ETag", ss.str().c_str());
            hdr_obj.append("Allow", "GET");
            http_status_code = 200;
        }
        else
        {            
            ::snapper::providers::SnapperMessage err(::snapper::providers::StandardErrorMessage::MMO_RequestUriNotFound());
            m_response = err.serialize_err_obj();            
            http_status_code = 404;
        }
    
    }
        
    
}

string SnapperSchema::get_response()  // schema content
{
    return m_response;
}

string SnapperSchema::get_response_hdr() // header
{
    return hdr_obj.obj().jsonString();
}

int SnapperSchema::get_httpstatus()
{
    return http_status_code;
}
}}

