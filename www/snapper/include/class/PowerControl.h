//---------------------------------------------------------------------
// <copyright file="PowerControl.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 
#include "class/_pPowerControl.h"

namespace snapper { namespace providers 
{

class PowerControl : public _pPowerControl
{
public:
    PowerControl() : _pPowerControl()    
    {}

    virtual ~PowerControl()    
    {}

    virtual std::shared_ptr<memid_acckey_map> getlist_memid_acckey(std::string containing_path = "");     
    
    virtual int handle_get(shared_ptr<::snapper::service::request_context> request);
    
    virtual int handle_post(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_put(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_patch(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_delete(shared_ptr<::snapper::service::request_context> request);

    virtual int autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path = "", std::shared_ptr<bson::BSONObj> q_param = nullptr);

    virtual char *allows()
    {
        // resource allowed methods: GET HEAD POST PUT PATCH DELETE 
        static char methods[6] = {   1,   1,   0,   0,   1,   0   };
        return (char *) methods;
    }

private:
    void SetRelatedItems(string className);
};

}}

