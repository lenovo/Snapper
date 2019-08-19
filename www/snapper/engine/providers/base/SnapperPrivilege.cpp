//---------------------------------------------------------------------
// <copyright file="_pSnapperPrivilege.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#include "class/SnapperPrivilege.h" 

#include "class/_pManagerPrivilege.h" 
#include "class/_pManagerCollectionPrivilege.h" 
#include "class/_pComputerSystemPrivilege.h" 
#include "class/_pComputerSystemCollectionPrivilege.h" 
#include "class/_pEthernetInterfacePrivilege.h" 
#include "class/_pEthernetInterfaceCollectionPrivilege.h" 
#include "class/_pManagerAccountPrivilege.h" 
#include "class/_pManagerAccountCollectionPrivilege.h" 
#include "class/_pAccountServicePrivilege.h" 
#include "class/_pChassisPrivilege.h" 
#include "class/_pChassisCollectionPrivilege.h" 
#include "class/_pLogServicePrivilege.h" 
#include "class/_pLogServiceCollectionPrivilege.h" 
#include "class/_pLogEntryPrivilege.h" 
#include "class/_pLogEntryCollectionPrivilege.h" 
#include "class/_pPowerPrivilege.h" 
#include "class/_pProcessorPrivilege.h" 
#include "class/_pProcessorCollectionPrivilege.h" 
#include "class/_pRolePrivilege.h" 
#include "class/_pRoleCollectionPrivilege.h" 
#include "class/_pSerialInterfacePrivilege.h" 
#include "class/_pSerialInterfaceCollectionPrivilege.h" 
#include "class/_pSessionServicePrivilege.h" 
#include "class/_pSessionPrivilege.h" 
#include "class/_pSessionCollectionPrivilege.h" 
#include "class/_pTaskPrivilege.h" 
#include "class/_pTaskCollectionPrivilege.h" 
#include "class/_pTaskServicePrivilege.h" 
#include "class/_pThermalPrivilege.h" 
#include "class/_pVirtualMediaPrivilege.h" 
#include "class/_pVirtualMediaCollectionPrivilege.h" 
#include "class/_pVLanNetworkInterfacePrivilege.h" 
#include "class/_pVLanNetworkInterfaceCollectionPrivilege.h" 
#include "class/_pBiosPrivilege.h" 
#include "class/_pDrivePrivilege.h" 
#include "class/_pEventServicePrivilege.h" 
#include "class/_pEventDestinationPrivilege.h" 
#include "class/_pEventDestinationCollectionPrivilege.h" 
#include "class/_pFabricPrivilege.h" 
#include "class/_pFabricCollectionPrivilege.h" 
#include "class/_pManagerNetworkProtocolPrivilege.h" 
#include "class/_pMemoryPrivilege.h" 
#include "class/_pMemoryCollectionPrivilege.h" 
#include "class/_pMemoryChunksPrivilege.h" 
#include "class/_pMemoryChunksCollectionPrivilege.h" 
#include "class/_pMemoryDomainPrivilege.h" 
#include "class/_pMemoryDomainCollectionPrivilege.h" 
#include "class/_pMemoryMetricsPrivilege.h" 
#include "class/_pPCIeDevicePrivilege.h" 
#include "class/_pPCIeFunctionPrivilege.h" 
#include "class/_pPortPrivilege.h" 
#include "class/_pPortCollectionPrivilege.h" 
#include "class/_pSecureBootPrivilege.h" 
#include "class/_pSoftwareInventoryPrivilege.h" 
#include "class/_pSoftwareInventoryCollectionPrivilege.h" 
#include "class/_pStoragePrivilege.h" 
#include "class/_pStorageCollectionPrivilege.h" 
#include "class/_pSwitchPrivilege.h" 
#include "class/_pSwitchCollectionPrivilege.h" 
#include "class/_pUpdateServicePrivilege.h" 
#include "class/_pVolumePrivilege.h" 
#include "class/_pVolumeCollectionPrivilege.h" 
#include "class/_pZonePrivilege.h" 
#include "class/_pZoneCollectionPrivilege.h" 
#include "class/_pEndpointPrivilege.h" 
#include "class/_pEndpointCollectionPrivilege.h" 
#include "class/_pJsonSchemaFilePrivilege.h" 
#include "class/_pJsonSchemaFileCollectionPrivilege.h" 
#include "class/_pMessageRegistryPrivilege.h" 
#include "class/_pMessageRegistryCollectionPrivilege.h" 
#include "class/_pMessageRegistryFilePrivilege.h" 
#include "class/_pMessageRegistryFileCollectionPrivilege.h" 
#include "class/_pPhysicalContextPrivilege.h" 
#include "class/_pRedundancyPrivilege.h" 
#include "class/_pServiceRootPrivilege.h" 
#include "class/_pSimpleStoragePrivilege.h" 
#include "class/_pSimpleStorageCollectionPrivilege.h" 
namespace snapper { namespace providers 
{

    map<string, std::shared_ptr<SnapperPrivilege>> PrivilegeObjectFactory::ObjMap;

    REGISTER_PRIVILEGE(_pManagerPrivilege);
    REGISTER_PRIVILEGE(_pManagerCollectionPrivilege);
    REGISTER_PRIVILEGE(_pComputerSystemPrivilege);
    REGISTER_PRIVILEGE(_pComputerSystemCollectionPrivilege);
    REGISTER_PRIVILEGE(_pEthernetInterfacePrivilege);
    REGISTER_PRIVILEGE(_pEthernetInterfaceCollectionPrivilege);
    REGISTER_PRIVILEGE(_pManagerAccountPrivilege);
    REGISTER_PRIVILEGE(_pManagerAccountCollectionPrivilege);
    REGISTER_PRIVILEGE(_pAccountServicePrivilege);
    REGISTER_PRIVILEGE(_pChassisPrivilege);
    REGISTER_PRIVILEGE(_pChassisCollectionPrivilege);
    REGISTER_PRIVILEGE(_pLogServicePrivilege);
    REGISTER_PRIVILEGE(_pLogServiceCollectionPrivilege);
    REGISTER_PRIVILEGE(_pLogEntryPrivilege);
    REGISTER_PRIVILEGE(_pLogEntryCollectionPrivilege);
    REGISTER_PRIVILEGE(_pPowerPrivilege);
    REGISTER_PRIVILEGE(_pProcessorPrivilege);
    REGISTER_PRIVILEGE(_pProcessorCollectionPrivilege);
    REGISTER_PRIVILEGE(_pRolePrivilege);
    REGISTER_PRIVILEGE(_pRoleCollectionPrivilege);
    REGISTER_PRIVILEGE(_pSerialInterfacePrivilege);
    REGISTER_PRIVILEGE(_pSerialInterfaceCollectionPrivilege);
    REGISTER_PRIVILEGE(_pSessionServicePrivilege);
    REGISTER_PRIVILEGE(_pSessionPrivilege);
    REGISTER_PRIVILEGE(_pSessionCollectionPrivilege);
    REGISTER_PRIVILEGE(_pTaskPrivilege);
    REGISTER_PRIVILEGE(_pTaskCollectionPrivilege);
    REGISTER_PRIVILEGE(_pTaskServicePrivilege);
    REGISTER_PRIVILEGE(_pThermalPrivilege);
    REGISTER_PRIVILEGE(_pVirtualMediaPrivilege);
    REGISTER_PRIVILEGE(_pVirtualMediaCollectionPrivilege);
    REGISTER_PRIVILEGE(_pVLanNetworkInterfacePrivilege);
    REGISTER_PRIVILEGE(_pVLanNetworkInterfaceCollectionPrivilege);
    REGISTER_PRIVILEGE(_pBiosPrivilege);
    REGISTER_PRIVILEGE(_pDrivePrivilege);
    REGISTER_PRIVILEGE(_pEventServicePrivilege);
    REGISTER_PRIVILEGE(_pEventDestinationPrivilege);
    REGISTER_PRIVILEGE(_pEventDestinationCollectionPrivilege);
    REGISTER_PRIVILEGE(_pFabricPrivilege);
    REGISTER_PRIVILEGE(_pFabricCollectionPrivilege);
    REGISTER_PRIVILEGE(_pManagerNetworkProtocolPrivilege);
    REGISTER_PRIVILEGE(_pMemoryPrivilege);
    REGISTER_PRIVILEGE(_pMemoryCollectionPrivilege);
    REGISTER_PRIVILEGE(_pMemoryChunksPrivilege);
    REGISTER_PRIVILEGE(_pMemoryChunksCollectionPrivilege);
    REGISTER_PRIVILEGE(_pMemoryDomainPrivilege);
    REGISTER_PRIVILEGE(_pMemoryDomainCollectionPrivilege);
    REGISTER_PRIVILEGE(_pMemoryMetricsPrivilege);
    REGISTER_PRIVILEGE(_pPCIeDevicePrivilege);
    REGISTER_PRIVILEGE(_pPCIeFunctionPrivilege);
    REGISTER_PRIVILEGE(_pPortPrivilege);
    REGISTER_PRIVILEGE(_pPortCollectionPrivilege);
    REGISTER_PRIVILEGE(_pSecureBootPrivilege);
    REGISTER_PRIVILEGE(_pSoftwareInventoryPrivilege);
    REGISTER_PRIVILEGE(_pSoftwareInventoryCollectionPrivilege);
    REGISTER_PRIVILEGE(_pStoragePrivilege);
    REGISTER_PRIVILEGE(_pStorageCollectionPrivilege);
    REGISTER_PRIVILEGE(_pSwitchPrivilege);
    REGISTER_PRIVILEGE(_pSwitchCollectionPrivilege);
    REGISTER_PRIVILEGE(_pUpdateServicePrivilege);
    REGISTER_PRIVILEGE(_pVolumePrivilege);
    REGISTER_PRIVILEGE(_pVolumeCollectionPrivilege);
    REGISTER_PRIVILEGE(_pZonePrivilege);
    REGISTER_PRIVILEGE(_pZoneCollectionPrivilege);
    REGISTER_PRIVILEGE(_pEndpointPrivilege);
    REGISTER_PRIVILEGE(_pEndpointCollectionPrivilege);
    REGISTER_PRIVILEGE(_pJsonSchemaFilePrivilege);
    REGISTER_PRIVILEGE(_pJsonSchemaFileCollectionPrivilege);
    REGISTER_PRIVILEGE(_pMessageRegistryPrivilege);
    REGISTER_PRIVILEGE(_pMessageRegistryCollectionPrivilege);
    REGISTER_PRIVILEGE(_pMessageRegistryFilePrivilege);
    REGISTER_PRIVILEGE(_pMessageRegistryFileCollectionPrivilege);
    REGISTER_PRIVILEGE(_pPhysicalContextPrivilege);
    REGISTER_PRIVILEGE(_pRedundancyPrivilege);
    REGISTER_PRIVILEGE(_pServiceRootPrivilege);
    REGISTER_PRIVILEGE(_pSimpleStoragePrivilege);
    REGISTER_PRIVILEGE(_pSimpleStorageCollectionPrivilege);
}}

