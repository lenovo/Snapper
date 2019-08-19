//---------------------------------------------------------------------
// <copyright file="Task.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 
#include "class/_pTask.h"
#include <www/engine/rfmon_clt.h>


namespace snapper { namespace providers 
{

class Task : public _pTask
{
public:
    Task() : _pTask()    
    {}

    virtual ~Task()    
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
        static char methods[6] = {   1,   1,   0,   0,   0,   1   };
        return (char *) methods;
    }
private:

    string state_conv(int state);
    void build_messages(task_info *tp, bson::BSONArrayBuilder* TaskMsgArr);

};

}}

