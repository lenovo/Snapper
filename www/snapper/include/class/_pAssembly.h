//---------------------------------------------------------------------
// <copyright file="_pAssembly.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pAssembly : public ResourceProvider
{
public:
    _pAssembly() : ResourceProvider("Assembly")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assemblies",  nullptr);
        create_prop("Assemblies@odata.count",  nullptr);
        create_prop("Assemblies@odata.navigationLink",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Assembly.v1_1_0");
        set_desc("This is the schema definition for the Assembly properties.");
    }

    virtual ~_pAssembly()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Assemblies");
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
        add_property_class("Assemblies", "Navigation Type.Collection", "AssemblyData");
    }

    void prep_prop_attrs()
    {
        auto Assemblies_attr = std::make_shared<prop_attribute>();
        Assemblies_attr->prop_name = "Assemblies";
        Assemblies_attr->read_only = false;
        add_property_attr("Assemblies", Assemblies_attr);

     }

};

}}

