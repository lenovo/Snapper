//---------------------------------------------------------------------
// <copyright file="_pVirtualMedia.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pVirtualMedia : public ResourceProvider
{
public:
    _pVirtualMedia() : ResourceProvider("VirtualMedia")    
    {
        enum ConnectedVia 
        {
            ConnectedVia_NotConnected,
            ConnectedVia_URI,
            ConnectedVia_Applet,
            ConnectedVia_Oem,
        };

        enum MediaType 
        {
            MediaType_CD,
            MediaType_Floppy,
            MediaType_USBStick,
            MediaType_DVD,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ConnectedVia",  nullptr);
        create_prop("Image",  nullptr);
        create_prop("ImageName",  nullptr);
        create_prop("Inserted",  nullptr);
        create_prop("MediaTypes",  nullptr);
        create_prop("WriteProtected",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("VirtualMedia.v1_2_0");
        set_desc("The VirtualMedia schema contains properties related to monitoring and control of an instance of virtual media such as a remote CD, DVD, or USB device. Virtual media functionality is provided by a Manager for a system or device.");
    }

    virtual ~_pVirtualMedia()    
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
                "#VirtualMedia.EjectMedia"
                << BSON("target" << (get_base_odata_id() + "/Actions/VirtualMedia.EjectMedia")
                << "title" << "EjectMedia")
                << "#VirtualMedia.InsertMedia"
                << BSON("target" << (get_base_odata_id() + "/Actions/VirtualMedia.InsertMedia")
                << "title" << "InsertMedia")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("ConnectedVia", "Enum Type.", "ConnectedVia");
        add_property_class("Image", "Primitive Type.", "Edm.String");
        add_property_class("ImageName", "Primitive Type.", "Edm.String");
        add_property_class("Inserted", "Primitive Type.", "Edm.Boolean");
        add_property_class("MediaTypes", "Collection Type.", "MediaType");
        add_property_class("WriteProtected", "Primitive Type.", "Edm.Boolean");
    }

    void prep_prop_attrs()
    {
        auto WriteProtected_attr = std::make_shared<prop_attribute>();
        WriteProtected_attr->prop_name = "WriteProtected";
        WriteProtected_attr->read_only = false;
        add_property_attr("WriteProtected", WriteProtected_attr);

        auto Inserted_attr = std::make_shared<prop_attribute>();
        Inserted_attr->prop_name = "Inserted";
        Inserted_attr->read_only = false;
        add_property_attr("Inserted", Inserted_attr);

        auto ConnectedVia_attr = std::make_shared<prop_attribute>();
        ConnectedVia_attr->prop_name = "ConnectedVia";
        ConnectedVia_attr->read_only = true;
        ConnectedVia_attr->add_enum("NotConnected");
        ConnectedVia_attr->add_enum("URI");
        ConnectedVia_attr->add_enum("Applet");
        ConnectedVia_attr->add_enum("Oem");
        add_property_attr("ConnectedVia", ConnectedVia_attr);

        auto MediaTypes_attr = std::make_shared<prop_attribute>();
        MediaTypes_attr->prop_name = "MediaTypes";
        MediaTypes_attr->read_only = true;
        MediaTypes_attr->add_enum("CD");
        MediaTypes_attr->add_enum("Floppy");
        MediaTypes_attr->add_enum("USBStick");
        MediaTypes_attr->add_enum("DVD");
        add_property_attr("MediaTypes", MediaTypes_attr);

        auto Image_attr = std::make_shared<prop_attribute>();
        Image_attr->prop_name = "Image";
        Image_attr->read_only = false;
        add_property_attr("Image", Image_attr);

        auto ImageName_attr = std::make_shared<prop_attribute>();
        ImageName_attr->prop_name = "ImageName";
        ImageName_attr->read_only = true;
        add_property_attr("ImageName", ImageName_attr);

     }

};

}}

