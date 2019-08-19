//---------------------------------------------------------------------
// <copyright file="_pManagerAccount.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pManagerAccount : public ResourceProvider
{
public:
    _pManagerAccount() : ResourceProvider("ManagerAccount")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Enabled",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Locked",  nullptr);
        create_prop("Password",  nullptr);
        create_prop("RoleId",  nullptr);
        create_prop("UserName",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ManagerAccount.v1_1_2");
        set_desc("The user accounts, owned by a Manager, are defined in this resource.  Changes to a Manager Account may affect the current Redfish service connection if this manager is responsible for the Redfish service.");
    }

    virtual ~_pManagerAccount()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Role"] = nullptr;
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Enabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Locked", "Primitive Type.", "Edm.Boolean");
        add_property_class("Password", "Primitive Type.", "Edm.String");
        add_property_class("RoleId", "Primitive Type.", "Edm.String");
        add_property_class("UserName", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto Enabled_attr = std::make_shared<prop_attribute>();
        Enabled_attr->prop_name = "Enabled";
        Enabled_attr->read_only = false;
        add_property_attr("Enabled", Enabled_attr);

        auto Locked_attr = std::make_shared<prop_attribute>();
        Locked_attr->prop_name = "Locked";
        Locked_attr->read_only = false;
        add_property_attr("Locked", Locked_attr);

        auto RoleId_attr = std::make_shared<prop_attribute>();
        RoleId_attr->prop_name = "RoleId";
        RoleId_attr->read_only = false;
        RoleId_attr->required_on_create = true;
        add_property_attr("RoleId", RoleId_attr);

        auto UserName_attr = std::make_shared<prop_attribute>();
        UserName_attr->prop_name = "UserName";
        UserName_attr->read_only = false;
        UserName_attr->required_on_create = true;
        add_property_attr("UserName", UserName_attr);

        auto Password_attr = std::make_shared<prop_attribute>();
        Password_attr->prop_name = "Password";
        Password_attr->read_only = false;
        Password_attr->required_on_create = true;
        add_property_attr("Password", Password_attr);

     }

};

}}

