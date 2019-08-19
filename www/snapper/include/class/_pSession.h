//---------------------------------------------------------------------
// <copyright file="_pSession.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSession : public ResourceProvider
{
public:
    _pSession() : ResourceProvider("Session")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Password",  nullptr);
        create_prop("UserName",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Session.v1_1_0");
        set_desc("The Session resource describes a single connection (session) between a client and a Redfish service instance.");
    }

    virtual ~_pSession()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Password", "Primitive Type.", "Edm.String");
        add_property_class("UserName", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto Password_attr = std::make_shared<prop_attribute>();
        Password_attr->prop_name = "Password";
        Password_attr->read_only = true;
        Password_attr->required_on_create = true;
        add_property_attr("Password", Password_attr);

        auto UserName_attr = std::make_shared<prop_attribute>();
        UserName_attr->prop_name = "UserName";
        UserName_attr->read_only = true;
        UserName_attr->required_on_create = true;
        add_property_attr("UserName", UserName_attr);

     }

};

}}

