//---------------------------------------------------------------------
// <copyright file="_pUpdateService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pUpdateService : public ResourceProvider
{
public:
    _pUpdateService() : ResourceProvider("UpdateService")    
    {
        enum TransferProtocolType 
        {
            TransferProtocolType_CIFS,
            TransferProtocolType_FTP,
            TransferProtocolType_SFTP,
            TransferProtocolType_HTTP,
            TransferProtocolType_HTTPS,
            TransferProtocolType_NSF,
            TransferProtocolType_SCP,
            TransferProtocolType_TFTP,
            TransferProtocolType_OEM,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("FirmwareInventory",  nullptr);
        create_prop("HttpPushUri",  nullptr);
        create_prop("HttpPushUriTargets",  nullptr);
        create_prop("HttpPushUriTargetsBusy",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("SoftwareInventory",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("UpdateService.v1_2_1");
        set_desc("This is the schema definition for the Update Service. It represents the properties for the service itself and has links to collections of firmware and software inventory.");
    }

    virtual ~_pUpdateService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("SoftwareInventory");
        add_navigation_contained_props("FirmwareInventory");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#UpdateService.SimpleUpdate"
                << BSON("target" << (get_base_odata_id() + "/Actions/UpdateService.SimpleUpdate")
                << "title" << "SimpleUpdate"
                << "TransferProtocol@Redfish.AllowableValues"
                << BSON_ARRAY("CIFS"
                             << "FTP"
                             << "SFTP"
                             << "HTTP"
                             << "HTTPS"
                             << "NSF"
                             << "SCP"
                             << "TFTP"
                             << "OEM"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("FirmwareInventory", "Navigation Type.Entity", "SoftwareInventoryCollection");
        add_property_class("HttpPushUri", "Primitive Type.", "Edm.String");
        add_property_class("HttpPushUriTargets", "Collection Type.", "Edm.String");
        add_property_class("HttpPushUriTargetsBusy", "Primitive Type.", "Edm.Boolean");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("SoftwareInventory", "Navigation Type.Entity", "SoftwareInventoryCollection");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto SoftwareInventory_attr = std::make_shared<prop_attribute>();
        SoftwareInventory_attr->prop_name = "SoftwareInventory";
        SoftwareInventory_attr->read_only = true;
        add_property_attr("SoftwareInventory", SoftwareInventory_attr);

        auto FirmwareInventory_attr = std::make_shared<prop_attribute>();
        FirmwareInventory_attr->prop_name = "FirmwareInventory";
        FirmwareInventory_attr->read_only = true;
        add_property_attr("FirmwareInventory", FirmwareInventory_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto HttpPushUri_attr = std::make_shared<prop_attribute>();
        HttpPushUri_attr->prop_name = "HttpPushUri";
        HttpPushUri_attr->read_only = true;
        add_property_attr("HttpPushUri", HttpPushUri_attr);

        auto HttpPushUriTargetsBusy_attr = std::make_shared<prop_attribute>();
        HttpPushUriTargetsBusy_attr->prop_name = "HttpPushUriTargetsBusy";
        HttpPushUriTargetsBusy_attr->read_only = false;
        add_property_attr("HttpPushUriTargetsBusy", HttpPushUriTargetsBusy_attr);

        auto HttpPushUriTargets_attr = std::make_shared<prop_attribute>();
        HttpPushUriTargets_attr->prop_name = "HttpPushUriTargets";
        HttpPushUriTargets_attr->read_only = false;
        add_property_attr("HttpPushUriTargets", HttpPushUriTargets_attr);

     }

};

}}

