//---------------------------------------------------------------------
// <copyright file="_pMemoryChunks.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pMemoryChunks : public ResourceProvider
{
public:
    _pMemoryChunks() : ResourceProvider("MemoryChunks")    
    {
        enum AddressRangeType 
        {
            AddressRangeType_Volatile,
            AddressRangeType_PMEM,
            AddressRangeType_Block,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AddressRangeType",  nullptr);
        create_prop("InterleaveSets",  nullptr);
        create_prop("IsMirrorEnabled",  nullptr);
        create_prop("IsSpare",  nullptr);
        create_prop("MemoryChunkSizeMiB",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("MemoryChunks.v1_2_1");
        set_desc("This is the schema definition of a Memory Chunk and its configuration.");
    }

    virtual ~_pMemoryChunks()    
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
        add_property_class("AddressRangeType", "Enum Type.", "AddressRangeType");
        add_property_class("InterleaveSets", "Collection Type.", "InterleaveSet");
        add_property_class("IsMirrorEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("IsSpare", "Primitive Type.", "Edm.Boolean");
        add_property_class("MemoryChunkSizeMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto IsSpare_attr = std::make_shared<prop_attribute>();
        IsSpare_attr->prop_name = "IsSpare";
        IsSpare_attr->read_only = true;
        add_property_attr("IsSpare", IsSpare_attr);

        auto IsMirrorEnabled_attr = std::make_shared<prop_attribute>();
        IsMirrorEnabled_attr->prop_name = "IsMirrorEnabled";
        IsMirrorEnabled_attr->read_only = true;
        add_property_attr("IsMirrorEnabled", IsMirrorEnabled_attr);

        auto AddressRangeType_attr = std::make_shared<prop_attribute>();
        AddressRangeType_attr->prop_name = "AddressRangeType";
        AddressRangeType_attr->read_only = true;
        AddressRangeType_attr->add_enum("Volatile");
        AddressRangeType_attr->add_enum("PMEM");
        AddressRangeType_attr->add_enum("Block");
        add_property_attr("AddressRangeType", AddressRangeType_attr);

        auto MemoryChunkSizeMiB_attr = std::make_shared<prop_attribute>();
        MemoryChunkSizeMiB_attr->prop_name = "MemoryChunkSizeMiB";
        MemoryChunkSizeMiB_attr->read_only = true;
        add_property_attr("MemoryChunkSizeMiB", MemoryChunkSizeMiB_attr);

     }

};

}}

