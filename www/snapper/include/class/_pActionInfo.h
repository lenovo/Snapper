//---------------------------------------------------------------------
// <copyright file="_pActionInfo.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pActionInfo : public ResourceProvider
{
public:
    _pActionInfo() : ResourceProvider("ActionInfo")    
    {
        enum ParameterTypes 
        {
            ParameterTypes_Boolean,
            ParameterTypes_Number,
            ParameterTypes_NumberArray,
            ParameterTypes_String,
            ParameterTypes_StringArray,
            ParameterTypes_Object,
            ParameterTypes_ObjectArray,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Parameters",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ActionInfo.v1_0_3");
        set_desc("The ActionInfo schema describes the parameters and other information necessary to perform a Redfish Action on a particular Action target. Parameter support can differ between vendors and even between instances of a resource. This data can be used to ensure Action requests from applications contain supported parameters.");
    }

    virtual ~_pActionInfo()    
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
        add_property_class("Parameters", "Collection Type.", "Parameters");
    }

    void prep_prop_attrs()
    {
     }

};

}}

