//---------------------------------------------------------------------
// <copyright file="NetworkInterfaceCollection.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 

#include "class/_pNetworkInterfaceCollection.h"

namespace snapper { namespace providers 
{

class NetworkInterfaceCollection : public _pNetworkInterfaceCollection
{
public:
    NetworkInterfaceCollection() : _pNetworkInterfaceCollection()    
    {}

    virtual ~NetworkInterfaceCollection()    
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

