//---------------------------------------------------------------------
// <copyright file="NetworkAdapter.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 
#include "class/_pNetworkAdapter.h"

namespace snapper { namespace providers 
{

class NetworkAdapter : public _pNetworkAdapter
{
public:
    NetworkAdapter() : _pNetworkAdapter()    
    {}

    virtual ~NetworkAdapter()    
    {}
    
    virtual std::shared_ptr<memid_acckey_map> getlist_memid_acckey(std::string containing_path = ""); 
    
    virtual int handle_get(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_post(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_put(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_patch(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_delete(shared_ptr<::snapper::service::request_context> request);

    virtual char *allows()
    {
        // resource allowed methods: GET HEAD POST PUT PATCH DELETE 
        static char methods[6] = {   1,   1,   0,   0,   0,   0   };
        return (char *) methods;
    }

private:
    int navigation_property_query(shared_ptr<::snapper::service::request_context> request);

};

}}

