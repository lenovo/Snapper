//---------------------------------------------------------------------
// <copyright file="_pExternalAccountProviderCollection.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pExternalAccountProviderCollection : public ResourceCollectionProvider
{
public:
    _pExternalAccountProviderCollection() : ResourceCollectionProvider("ExternalAccountProviderCollection")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Members",  nullptr);
        create_prop("Members@odata.count",  nullptr);
        create_prop("Members@odata.navigationLink",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ExternalAccountProviderCollection");
        set_desc("A Collection of ExternalAccountProvider resource instances.");
    }

    virtual ~_pExternalAccountProviderCollection()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Members");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Members", "Navigation Type.Collection", "ExternalAccountProvider");
    }

    void prep_prop_attrs()
    {
        auto Members_attr = std::make_shared<prop_attribute>();
        Members_attr->prop_name = "Members";
        Members_attr->read_only = true;
        add_property_attr("Members", Members_attr);

     }

};

}}

