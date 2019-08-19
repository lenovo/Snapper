//---------------------------------------------------------------------
// <copyright file="Manager.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 
#include "class/_pManager.h"

namespace snapper { namespace providers 
{

class Manager : public _pManager
{
public:
    Manager() : _pManager()    
    {
	}

    virtual ~Manager()    
    {}
    
    virtual std::shared_ptr<memid_acckey_map> getlist_memid_acckey(std::string containing_path = ""); 
    
    virtual int handle_get(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_post(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_put(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_patch(shared_ptr<::snapper::service::request_context> request);

    virtual int handle_delete(shared_ptr<::snapper::service::request_context> request);

    virtual void set_actions_obj()
    {
        //override default Actions
        create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
            "#Manager.ForceFailover"
            << BSON("target" << (get_base_odata_id() + "/Actions/Manager.ForceFailover")
            << "title" << "ForceFailover")
            << "#Manager.Reset"
            << BSON("target" << (get_base_odata_id() + "/Actions/Manager.Reset")
            << "title" << "Reset"
            << "ResetType@Redfish.AllowableValues"
            << BSON_ARRAY("GracefulRestart"))
            )
            )) );
    }

    virtual char *allows()
    {
        // resource allowed methods: GET HEAD POST PUT PATCH DELETE 
        static char methods[6] = {   1,   1,   0,   0,  1 ,   0   };
        return (char *) methods;
    }

private:
    int navigation_property_query(shared_ptr<::snapper::service::request_context> request);

};

}}

