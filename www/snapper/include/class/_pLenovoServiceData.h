//---------------------------------------------------------------------
// <copyright file="_pLenovoServiceData.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pLenovoServiceData : public ResourceProvider
{
public:
    _pLenovoServiceData() : ResourceProvider("LenovoServiceData")    
    {
        enum SchemesType 
        {
            SchemesType_TFTP,
            SchemesType_SFTP,
        };

        enum CollectionType 
        {
            CollectionType_ProcessorDump,
            CollectionType_ServiceDataFile,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("CaptureTimeout",  nullptr);
        create_prop("DataCollectionType",  nullptr);
        create_prop("ExportProgress",  nullptr);
        create_prop("FFDCs",  nullptr);
        create_prop("FileTransferTimeout",  nullptr);
        create_prop("IsScreenAvailable",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("LenovoServiceData.v1_0_0");
        set_desc("This schema defines a resource for user to collect service Data.");
    }

    virtual ~_pLenovoServiceData()    
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

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#LenovoServiceData.ExportHealthReport"
                << BSON("target" << (get_base_odata_id() + "/Actions/LenovoServiceData.ExportHealthReport")
                << "title" << "ExportHealthReport")
                << "#LenovoServiceData.ExportLatestOSFailureScreen"
                << BSON("target" << (get_base_odata_id() + "/Actions/LenovoServiceData.ExportLatestOSFailureScreen")
                << "title" << "ExportLatestOSFailureScreen")
                << "#LenovoServiceData.PushFFDCData"
                << BSON("target" << (get_base_odata_id() + "/Actions/LenovoServiceData.PushFFDCData")
                << "title" << "PushFFDCData"
                << "DataCollectionType@Redfish.AllowableValues"
                << BSON_ARRAY("ProcessorDump"
                             << "ServiceDataFile")
                << "ExportingScheme@Redfish.AllowableValues"
                << BSON_ARRAY("TFTP"
                             << "SFTP"))
                << "#LenovoServiceData.GenerateFFDCData"
                << BSON("target" << (get_base_odata_id() + "/Actions/LenovoServiceData.GenerateFFDCData")
                << "title" << "GenerateFFDCData"
                << "DataCollectionType@Redfish.AllowableValues"
                << BSON_ARRAY("ProcessorDump"
                             << "ServiceDataFile"))
                << "#LenovoServiceData.ExportFFDCData"
                << BSON("target" << (get_base_odata_id() + "/Actions/LenovoServiceData.ExportFFDCData")
                << "title" << "ExportFFDCData"
                << "DataCollectionType@Redfish.AllowableValues"
                << BSON_ARRAY("ProcessorDump"
                             << "ServiceDataFile"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("CaptureTimeout", "Primitive Type.", "Edm.Decimal");
        add_property_class("DataCollectionType", "Collection Type.", "CollectionType");
        add_property_class("ExportProgress", "Primitive Type.", "Edm.String");
        add_property_class("FFDCs", "Collection Type.", "FFDCDump");
        add_property_class("FileTransferTimeout", "Primitive Type.", "Edm.Decimal");
        add_property_class("IsScreenAvailable", "Primitive Type.", "Edm.Boolean");
    }

    void prep_prop_attrs()
    {
        auto DataCollectionType_attr = std::make_shared<prop_attribute>();
        DataCollectionType_attr->prop_name = "DataCollectionType";
        DataCollectionType_attr->read_only = true;
        DataCollectionType_attr->add_enum("ProcessorDump");
        DataCollectionType_attr->add_enum("ServiceDataFile");
        add_property_attr("DataCollectionType", DataCollectionType_attr);

        auto FFDCs_attr = std::make_shared<prop_attribute>();
        FFDCs_attr->prop_name = "FFDCs";
        FFDCs_attr->read_only = true;
        add_property_attr("FFDCs", FFDCs_attr);

     }

};

}}

