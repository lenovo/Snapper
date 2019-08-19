//---------------------------------------------------------------------
// <copyright file="TaskCollection.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 

#include "class/_pTaskCollection.h"

namespace snapper { namespace providers 
{

class TaskCollection : public _pTaskCollection
{
public:
    TaskCollection() : _pTaskCollection()    
    {}

    virtual ~TaskCollection()    
    {}
    
    virtual int handle_get(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_post(shared_ptr<::snapper::service::request_context> request);

    virtual char *allows()
    {
        // resource allowed methods: GET HEAD POST PUT PATCH DELETE 
        static char methods[6] = {   1,   1,   1,   0,   0,   0   };
        return (char *) methods;
    }

private:
};

}}

