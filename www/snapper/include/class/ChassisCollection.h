//---------------------------------------------------------------------
// <copyright file="ChassisCollection.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 

#include "class/_pChassisCollection.h"

namespace snapper { namespace providers 
{

class ChassisCollection : public _pChassisCollection
{
public:
    ChassisCollection() : _pChassisCollection()    
    {}

    virtual ~ChassisCollection()    
    {}
    
    virtual int handle_get(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_post(shared_ptr<::snapper::service::request_context> request);

    virtual char *allows()
    {
        // resource allowed methods: GET HEAD POST PUT PATCH DELETE 
        static char methods[6] = {   1,   1,   0,   0,   0,   0   };
        return (char *) methods;
    }
private:
};

}}

