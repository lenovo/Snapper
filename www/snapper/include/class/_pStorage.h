//---------------------------------------------------------------------
// <copyright file="_pStorage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pStorage : public ResourceProvider
{
public:
    _pStorage() : ResourceProvider("Storage")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Drives",  nullptr);
        create_prop("Drives@odata.count",  nullptr);
        create_prop("Drives@odata.navigationLink",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("StorageControllers",  nullptr);
        create_prop("StorageControllers@odata.count",  nullptr);
        create_prop("StorageControllers@odata.navigationLink",  nullptr);
        create_prop("Volumes",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Storage.v1_4_0");
        set_desc("This schema defines a storage subsystem and its respective properties.  A storage subsystem represents a set of storage controllers (physical or virtual) and the resources such as volumes that can be accessed from that subsystem.");
    }

    virtual ~_pStorage()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
        add_navigation_arr_props("Drives");
        add_navigation_arr_props("StorageControllers");
        add_navigation_contained_props("Volumes");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Enclosures"] = nullptr;
        m_Links_prop_objs["Enclosures@odata.count"] = nullptr;
        m_Links_prop_objs["Enclosures@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Enclosures");
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Storage.SetEncryptionKey"
                << BSON("target" << (get_base_odata_id() + "/Actions/Storage.SetEncryptionKey")
                << "title" << "SetEncryptionKey")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Drives", "Navigation Type.Collection", "Drive");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("StorageControllers", "Navigation Type.Collection", "StorageController");
        add_property_class("Volumes", "Navigation Type.Entity", "VolumeCollection");
    }

    void prep_prop_attrs()
    {
        auto Volumes_attr = std::make_shared<prop_attribute>();
        Volumes_attr->prop_name = "Volumes";
        Volumes_attr->read_only = true;
        add_property_attr("Volumes", Volumes_attr);

        auto Drives_attr = std::make_shared<prop_attribute>();
        Drives_attr->prop_name = "Drives";
        Drives_attr->read_only = true;
        add_property_attr("Drives", Drives_attr);

        auto StorageControllers_attr = std::make_shared<prop_attribute>();
        StorageControllers_attr->prop_name = "StorageControllers";
        StorageControllers_attr->read_only = true;
        add_property_attr("StorageControllers", StorageControllers_attr);

     }

};

}}

