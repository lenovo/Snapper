//---------------------------------------------------------------------
// <copyright file="SnapperSchema.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 
#include "SnapperType.h"

namespace snapper { namespace providers 
{

class SnapperSchema
{
    string m_response;
    string m_header;
    int http_status_code;
    bson::BSONObjBuilder hdr_obj;
    
public:
    
    SnapperSchema(string file_name); 

    virtual ~SnapperSchema()    
    {}    

    string get_response();  
    string get_response_hdr(); // header
    int get_httpstatus();

};

}}

