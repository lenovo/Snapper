//---------------------------------------------------------------------
// <copyright file="BSONCache_Config.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <www/engine/rf_debug.h>
#include <www/engine/request_context.h>
#include <www/engine/BSONCache.h>
#include <www/engine/cache_common.h>

#include <time.h>
#include <map>
#include <vector>
#include <pthread.h>


using namespace bson;
namespace snapper { namespace datamgr
{

void bson_cache_config(std::map<const std::string, std::shared_ptr<BCache_Config>> & config)
{
    ///////////////////////////////////////////////////////////////////////
    //registry key name in datamgr xml(di_metadata/) for caching. 
    // check_dbchanges()/check_adamchanges() - refresh_data_type,
    //            ==> refresh_resource_data() - updated_resource_data flag, 
    //                     ==> snapper_refresh_topology - refresh_data_type
    //example with 300s timeout even without data change:
    //config["LogEntry"] = std::make_shared<BCache_Config>(300); 
    ///////////////////////////////////////////////////////////////////////

    //register cache for key "ComputerSystem_NV" and refresh type
    config["ComputerSystem_NV"] = std::make_shared<BCache_Config>(600);
    config["ComputerSystem_NV"]->addtype(REFRESH_AIM_VPDFRU);
    config["ComputerSystem_NV"]->addtype(REFRESH_AIM_VPDCOMP);
    config["ComputerSystem_NV"]->addtype(REFRESH_TBL_VPDFRU);
    config["ComputerSystem_NV"]->addtype(REFRESH_AIM_OSINET);
    config["ComputerSystem_NV"]->addtype(REFRESH_INOTIFY_NETWORK);
    config["ComputerSystem_NV"]->addtype(REFRESH_PROCSYNC_VPDD);

    //register cache for key "Chassis_NV" and refresh type
    config["Chassis_NV"] = std::make_shared<BCache_Config>(600);
    config["Chassis_NV"]->addtype(REFRESH_AIM_VPDFRU);
    config["Chassis_NV"]->addtype(REFRESH_AIM_VPDCOMP);
    config["Chassis_NV"]->addtype(REFRESH_TBL_VPDFRU);
    config["Chassis_NV"]->addtype(REFRESH_ADAM_SERVERPROP);
    config["Chassis_NV"]->addtype(REFRESH_PROCSYNC_VPDD);

    //register cache for key "Processor" and refresh type
    config["Processor"] = std::make_shared<BCache_Config>(600);
    config["Processor"]->addtype(REFRESH_TBL_CPU);
    config["Processor"]->addtype(REFRESH_AIM_VPDFRU);
    config["Processor"]->addtype(REFRESH_AIM_VPDCOMP);
    config["Processor"]->addtype(REFRESH_PROCSYNC_VPDD);

    //register cache for key "Memory" and refresh type
    config["Memory"] = std::make_shared<BCache_Config>(600);
    config["Memory"]->addtype(REFRESH_TBL_MEM);
    config["Memory"]->addtype(REFRESH_AIM_VPDFRU);
    config["Memory"]->addtype(REFRESH_AIM_VPDCOMP);
    config["Memory"]->addtype(REFRESH_PROCSYNC_VPDD);

    //register cache for key "Manager_NV" and refresh type
    config["Manager_NV"] = std::make_shared<BCache_Config>(600);
    config["Manager_NV"]->addtype(REFRESH_ADAM_CLOCK);
    config["Manager_NV"]->addtype(REFRESH_TBL_IPMIPROP_V2_FWTBL);
    config["Manager_NV"]->addtype(REFRESH_TBL_VPDFRU);
    config["Manager_NV"]->addtype(REFRESH_PROCSYNC_VPDD);

    //register cache for key "Storage" and refresh type
    config["Storage"] = std::make_shared<BCache_Config>(600);
    config["Storage"]->addtype(REFRESH_TBL_STORAGE);
    config["Storage"]->addtype(REFRESH_TBL_NVME);

    //register cache for "BiosAttributes" and refresh type
    config["BiosAttributes"] = std::make_shared<BCache_Config>(600);
    config["BiosAttributes"]->addtype(REFRESH_INOTIFY_BIOS);
    
    config["BiosAttributes_Pending"] = std::make_shared<BCache_Config>(600);
    config["BiosAttributes_Pending"]->addtype(REFRESH_INOTIFY_BIOS_PENDING);
    
    config["BiosAttributes_Changed"] = std::make_shared<BCache_Config>(600);
    config["BiosAttributes_Changed"]->addtype(REFRESH_INOTIFY_BIOS);
    config["BiosAttributes_Changed"]->addtype(REFRESH_INOTIFY_BIOS_PENDING);

    //register cache for key "VirtualMedia" and refresh type
    config["VirtualMedia"] = std::make_shared<BCache_Config>(600);
    config["VirtualMedia"]->addtype(REFRESH_RESC_VMDISK);

    //register cache for key "ManagerNetworkProtocol_osinet" and refresh type
    config["ManagerNetworkProtocol_osinet"] = std::make_shared<BCache_Config>(600);
    config["ManagerNetworkProtocol_osinet"]->addtype(REFRESH_ADAM_NETPROTO);

    //register cache for key "ManagerNetworkProtocol_tm" and refresh type
    config["ManagerNetworkProtocol_tm"] = std::make_shared<BCache_Config>(600);
    config["ManagerNetworkProtocol_tm"]->addtype(REFRESH_ADAM_CLOCK);

    //register cache for key "ManagerNetworkProtocol_tm" and refresh type
    config["AccountService_seccfg"] = std::make_shared<BCache_Config>(600);
    config["AccountService_seccfg"]->addtype(REFRESH_ADAM_SECURITY_CFG);
    
    //register cache for key "AccountService_timeout" and refresh type
    config["AccountService_timeout"] = std::make_shared<BCache_Config>(600);
    config["AccountService_timeout"]->addtype(REFRESH_ADAM_WEBGUI_CFG);

    //register cache for key Role and refresh type
    config["Role"] = std::make_shared<BCache_Config>(1200);
    config["Role"]->addtype(REFRESH_TBL_ROLE);

    //register cache for key ManagerAccount and refresh type
    config["ManagerAccount"] = std::make_shared<BCache_Config>(1200);
    config["ManagerAccount"]->addtype(REFRESH_TBL_USER_ROLE_MAP);

    //register cache for key LenovoFoD and refresh type
    config["LenovoFoD"] = std::make_shared<BCache_Config>(1200);
    config["LenovoFoD"]->addtype(REFRESH_INOTIFY_FOD);

}

}}
