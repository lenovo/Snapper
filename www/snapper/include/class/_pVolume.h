//---------------------------------------------------------------------
// <copyright file="_pVolume.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pVolume : public ResourceProvider
{
public:
    _pVolume() : ResourceProvider("Volume")    
    {
        enum InitializeType 
        {
            InitializeType_Fast,
            InitializeType_Slow,
        };

        enum EncryptionTypes 
        {
            EncryptionTypes_NativeDriveEncryption,
            EncryptionTypes_ControllerAssisted,
            EncryptionTypes_SoftwareAssisted,
        };

        enum VolumeType 
        {
            VolumeType_RawDevice,
            VolumeType_NonRedundant,
            VolumeType_Mirrored,
            VolumeType_StripedWithParity,
            VolumeType_SpannedMirrors,
            VolumeType_SpannedStripesWithParity,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("BlockSizeBytes",  nullptr);
        create_prop("CapacityBytes",  nullptr);
        create_prop("Encrypted",  nullptr);
        create_prop("EncryptionTypes",  nullptr);
        create_prop("Identifiers",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Operations",  nullptr);
        create_prop("OptimumIOSizeBytes",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("VolumeType",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Volume.v1_0_3");
        set_desc("Volume contains properties used to describe a volume, virtual disk, LUN, or other logical storage entity for any system.");
    }

    virtual ~_pVolume()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Drives"] = nullptr;
        m_Links_prop_objs["Drives@odata.count"] = nullptr;
        m_Links_prop_objs["Drives@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Drives");
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Volume.CheckConsistency"
                << BSON("target" << (get_base_odata_id() + "/Actions/Volume.CheckConsistency")
                << "title" << "CheckConsistency")
                << "#Volume.Initialize"
                << BSON("target" << (get_base_odata_id() + "/Actions/Volume.Initialize")
                << "title" << "Initialize"
                << "InitializeType@Redfish.AllowableValues"
                << BSON_ARRAY("Fast"
                             << "Slow"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("BlockSizeBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("CapacityBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("Encrypted", "Primitive Type.", "Edm.Boolean");
        add_property_class("EncryptionTypes", "Collection Type.", "EncryptionTypes");
        add_property_class("Identifiers", "Collection Type.", "Identifier");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Operations", "Collection Type.", "Operations");
        add_property_class("OptimumIOSizeBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("VolumeType", "Enum Type.", "VolumeType");
    }

    void prep_prop_attrs()
    {
        auto CapacityBytes_attr = std::make_shared<prop_attribute>();
        CapacityBytes_attr->prop_name = "CapacityBytes";
        CapacityBytes_attr->read_only = true;
        add_property_attr("CapacityBytes", CapacityBytes_attr);

        auto VolumeType_attr = std::make_shared<prop_attribute>();
        VolumeType_attr->prop_name = "VolumeType";
        VolumeType_attr->read_only = true;
        VolumeType_attr->add_enum("RawDevice");
        VolumeType_attr->add_enum("NonRedundant");
        VolumeType_attr->add_enum("Mirrored");
        VolumeType_attr->add_enum("StripedWithParity");
        VolumeType_attr->add_enum("SpannedMirrors");
        VolumeType_attr->add_enum("SpannedStripesWithParity");
        add_property_attr("VolumeType", VolumeType_attr);

        auto Encrypted_attr = std::make_shared<prop_attribute>();
        Encrypted_attr->prop_name = "Encrypted";
        Encrypted_attr->read_only = false;
        add_property_attr("Encrypted", Encrypted_attr);

        auto BlockSizeBytes_attr = std::make_shared<prop_attribute>();
        BlockSizeBytes_attr->prop_name = "BlockSizeBytes";
        BlockSizeBytes_attr->read_only = true;
        add_property_attr("BlockSizeBytes", BlockSizeBytes_attr);

        auto EncryptionTypes_attr = std::make_shared<prop_attribute>();
        EncryptionTypes_attr->prop_name = "EncryptionTypes";
        EncryptionTypes_attr->read_only = false;
        EncryptionTypes_attr->add_enum("NativeDriveEncryption");
        EncryptionTypes_attr->add_enum("ControllerAssisted");
        EncryptionTypes_attr->add_enum("SoftwareAssisted");
        add_property_attr("EncryptionTypes", EncryptionTypes_attr);

        auto OptimumIOSizeBytes_attr = std::make_shared<prop_attribute>();
        OptimumIOSizeBytes_attr->prop_name = "OptimumIOSizeBytes";
        OptimumIOSizeBytes_attr->read_only = true;
        add_property_attr("OptimumIOSizeBytes", OptimumIOSizeBytes_attr);

     }

};

}}

