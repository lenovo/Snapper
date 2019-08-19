/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include "bson/bson.h"
#include "bson/util/json.h"

#include "odata/edm/edm_model_reader.h"
#include "odata_service_exception.h"

#include <www/engine/request_handler.h>
#include <www/engine/request_context.h>
#include <www/engine/BSONCache.h>
#include "topology.h"
#include "json_cache.h"

#include "datainf/DataInterfaceMgr.h"
#include "class/SnapperProvider.h"
#include "class/SnapperSchema.h"
#include "class/ClassCommon.h"

#include <www/engine/rf_jwt.h>
#include <www/engine/rfmon_clt.h>

#include <time.h>
#include <sys/sysinfo.h>
#include <sys/types.h>

using namespace ::std;
using namespace ::snapper::service;
using namespace ::snapper::datamgr;

struct bson_fetch_rec
{
    bson_fetch_rec(unsigned int c, string key, bson::BSONObj obj): counter(c), keyname(key), args(obj)
    {}
    unsigned int counter;
    string keyname;
    bson::BSONObj args;
};

struct json_urifetch_rec
{
    json_urifetch_rec(unsigned int c, string uri): counter(c), target(uri)
    {}
    unsigned int counter;
    string target;
};

struct topo_node_refresh_rec
{
    topo_node_refresh_rec(unsigned int t, string n): datatype(t), classname(n)
    {}
    unsigned int datatype;
    string classname;
};

struct jcache_refresh_rec
{
    jcache_refresh_rec(unsigned int t, string n): datatype(t), classname(n)
    {}
    unsigned int datatype;
    string classname;
};


static void TOPOLOGY_REFRESH_CONFIG(std::vector<topo_node_refresh_rec> & NODES)
{
#define TOPOLOGY_TYPE_RESOURCE_MAP(type,resource)   NODES.push_back(topo_node_refresh_rec(type,resource))
    if(NODES.size() != 0)
        return;

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_RESC_SESSION, "SessionCollection"); // session refresh


    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_RESC_TASK, "TaskCollection"); // task refresh
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_TBL_EVENTDEST, "EventDestinationCollection"); // event refresh

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_RESC_VMDISK, "VirtualMediaCollection"); // vm/rdoc refresh

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_AIM_VPDFRU, "ComputerSystem"); // vpdd refresh or readiness
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_AIM_VPDFRU, "Chassis");
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_AIM_VPDFRU, "Manager");

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_AIM_VPDCOMP, "ComputerSystem"); // vpdd refresh or readiness
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_AIM_VPDCOMP, "Chassis");
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_AIM_VPDCOMP, "Manager");

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_TBL_VPDFRU, "ComputerSystem"); // vpdd refresh or readiness
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_TBL_VPDFRU, "Chassis");
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_TBL_VPDFRU, "Manager");

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_PROCSYNC_VPDD, "ComputerSystem"); // vpdd refresh or readiness
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_PROCSYNC_VPDD, "Chassis");
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_PROCSYNC_VPDD, "Manager");

    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_INOTIFY_FOD, "LenovoFoDService"); // fod refresh
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_INOTIFY_FOD, "LenovoFoDKey");
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_TBL_ROLE, "RoleCollection");
    TOPOLOGY_TYPE_RESOURCE_MAP(REFRESH_TBL_USER_ROLE_MAP, "ManagerAccountCollection");


}

static void JCACHE_REFRESH_CONFIG(std::vector<jcache_refresh_rec> & RECORDS)
{
#define JCACHE_TYPE_RESOURCE_MAP(type,resource)   RECORDS.push_back(jcache_refresh_rec(type,resource))
    if(RECORDS.size() != 0)
        return;

    JCACHE_TYPE_RESOURCE_MAP(REFRESH_AIM_EVENTLOG, "LogEntryCollection");

    JCACHE_TYPE_RESOURCE_MAP(REFRESH_RESC_SESSION, "SessionCollection");
    JCACHE_TYPE_RESOURCE_MAP(REFRESH_RESC_SESSION, "Session");

    JCACHE_TYPE_RESOURCE_MAP(REFRESH_RESC_TASK, "TaskCollection");
    JCACHE_TYPE_RESOURCE_MAP(REFRESH_RESC_TASK, "Task");
};

static void URL_FETCH_CONFIG(std::vector<json_urifetch_rec> & RECORDS)
{
#define JSON_URI_FETCH(interval,url)  RECORDS.push_back(json_urifetch_rec(interval,url))
    if(RECORDS.size() != 0)
        return;

    // log use json cache so URI prefetch is better
    JSON_URI_FETCH(40, "http://localhost/redfish/v1/Systems/1/LogServices/" STD_LOG "/Entries");
    JSON_URI_FETCH(41, "http://localhost/redfish/v1/Systems/1/LogServices/" EVENT_LOG "/Entries");
    JSON_URI_FETCH(42, "http://localhost/redfish/v1/Systems/1/LogServices/" AUDIT_LOG "/Entries");
    JSON_URI_FETCH(43, "http://localhost/redfish/v1/Systems/1/LogServices/" ACTIVE_LOG "/Entries");

    //use BSON prefetch: JSON_URI_FETCH(51, "http://localhost/redfish/v1/Systems/1");
    //use BSON prefetch: JSON_URI_FETCH(52, "http://localhost/redfish/v1/Chassis/1");
    //use BSON prefetch: JSON_URI_FETCH(53, "http://localhost/redfish/v1/Managers/1");
    //use BSON prefetch: JSON_URI_FETCH(54, "http://localhost/redfish/v1/Systems/1/Storage");
    //use BSON prefetch: JSON_URI_FETCH(55, "http://localhost/redfish/v1/Managers/1/VirtualMedia");
    //use BSON prefetch: JSON_URI_FETCH(56, "http://localhost/redfish/v1/Managers/1/NetworkProtocol");
    //use BSON prefetch: JSON_URI_FETCH(57, "http://localhost/redfish/v1/AccountService");
    //use BSON prefetch: JSON_URI_FETCH(58, "http://localhost/redfish/v1/Managers/1/Oem/Lenovo/FoD");
}

/*
  recommend to use BSON prefetch to reduce URI prefetch, cause URI prefetch will also pend
  Redfish requests which increases the response time
*/
static void BSON_FETCH_CONFIG(std::vector<bson_fetch_rec> & RECORDS)
{
#define BSON_FETCH(interval,keyname,args)  RECORDS.push_back(bson_fetch_rec(interval,keyname,args))
    if(RECORDS.size() != 0)
        return;

    bson::BSONObj emptyobj;
    BSON_FETCH(60, "ComputerSystem_NV", emptyobj);

    bson::BSONObj ipmidata_pn = BSON("IPMI_raw_command" << BSON_ARRAY(0x3A << 0x0B << 0x3C << 0x0 << 0x10 << 12));
    BSON_FETCH(61, "ComputerSystem_NV", ipmidata_pn);

    bson::BSONObj ipmidata_asset = BSON("IPMI_raw_command" << BSON_ARRAY(0x3A << 0x0B << 0x1C << 0x0 << 0x10 << 32));
    BSON_FETCH(62, "ComputerSystem_NV", ipmidata_asset);

    BSON_FETCH(64, "Chassis_NV", emptyobj);
    BSON_FETCH(65, "Chassis_NV", ipmidata_pn);
    BSON_FETCH(66, "Chassis_NV", ipmidata_asset);

    BSON_FETCH(67, "Manager_NV", emptyobj);

    BSON_FETCH(68, "VirtualMedia", emptyobj);

    bson::BSONObj a1 = BSON("storage_GetAllDevices" << BSON_ARRAY("storage_GetAllDevices"));
    bson::BSONObj a2 = BSON("storage_GetAIMDisks" << BSON_ARRAY("storage_GetAIMDisks"));
    bson::BSONObj a3 = BSON("storage_GetAllDisks" << BSON_ARRAY("storage_GetAllDisks"));
    bson::BSONObj a4 = BSON("storage_GetAllVolumes" << BSON_ARRAY("storage_GetAllVolumes"));
    BSON_FETCH(72, "Storage", a1);
    BSON_FETCH(73, "Storage", a2);
    BSON_FETCH(74, "Storage", a3);
    BSON_FETCH(75, "Storage", a4);

    BSON_FETCH(80, "ManagerNetworkProtocol_osinet", emptyobj);
    BSON_FETCH(81, "ManagerNetworkProtocol", emptyobj);
    BSON_FETCH(82, "ManagerNetworkProtocol_tm", emptyobj);

    BSON_FETCH(83, "AccountService_seccfg", emptyobj);
    BSON_FETCH(84, "AccountService_timeout", emptyobj);

    BSON_FETCH(85, "LenovoFoD", emptyobj);
}

#ifdef __cplusplus
extern  "C" {
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include "engine_api.h"
#include "protocol.h"
#include "rf_debug.h"
#include "rf_engine_error.h"

#define  READY_TIME  200
bool is_ready()
{
    static bool allready = false;
#ifdef __SIM_X86__
    allready = true;
#endif
    if(allready == true)
        return allready;

    //TODO define ready timing
    struct sysinfo s_info;
    long uptime = time(NULL);
    if(sysinfo(&s_info) == 0)
        uptime = s_info.uptime;

    if(uptime < READY_TIME)
        return false;

    //check readiness of vpd
    //to be added

    //check readiness of database or other data providers
    //to be added

    allready = true;
    return true;
}

bool is_cmr_ready()
{
    if(access("/tmp/DS/config", F_OK) == 0)
        return true;
    else
        return false;
}

int CHK_REFRESH_BIT(unsigned char *map, unsigned int type)
{
    if(type < 0 || type >= REFRESH_MAX)
    {
        RF_PRINT_ERR("[cache] received invalid refresh type %d\n", type);
        return 0;
    }
    unsigned int bytes = (type/8);
    unsigned int bits = (type%8);
    if(map[bytes] & (1 << bits))  
        return 1;
    else
        return 0;
}

void refresh_engine_data()
{
    //support multiple workers and keep data consistent in workers
    unsigned char buf[128];
    int rc;
    memset(buf, 0, sizeof(buf));
    rc = rfmon_wr_msg(MON_EVT_QUERY_UPDATE, NULL, 0, buf); 
    if(rc <= 0)
    {
        RF_PRINT_DBG("[cache] failed to query refresh\n");
        return;
    }
    updated_resource_data *p = (updated_resource_data *) buf;

    /////////////////////////////////////////////////////////////
    //////////////////// refresh bson cache  ////////////////////
    // db table/adam/resource change -> worker update flags (in monitor) -> data type of bson cache
    std::vector<unsigned int> bsontypes; //refresh_data_type
    std::stringstream ss;
    for(int m = 0; m < MAX_REFRESH_BYTES; m++)
    {
        for(int n = 0; n < 8; n++)
        {
            if((p->types_map[m] & (1 << n)))
            {
                unsigned int t = m*8 + n;
                bsontypes.push_back(t);
                ss << " " << t;
            }
        }
    }
    if(ss.str().length())
        RF_PRINT_DBG("[cache] ==> found refresh types : %s\n", ss.str().c_str());

    refresh_bson_cache(bsontypes);

    /////////////////////////////////////////////////////////////
    ////////////////// refresh json cache ///////////////////////
    static std::vector<jcache_refresh_rec> jcachelist;
    JCACHE_REFRESH_CONFIG(jcachelist);

    std::vector<std::string> json_resources; // resource name
    for(int i = 0; i < jcachelist.size(); i++)
    {
        if(CHK_REFRESH_BIT(p->types_map, jcachelist[i].datatype))
        {
            RF_PRINT_DBG("[cache] ==> %s json cache need updates\n", jcachelist[i].classname.c_str());
            json_resources.push_back(jcachelist[i].classname);
        }
    }
    refresh_json_cache(json_resources);

    /////////////////////////////////////////////////////////////
    //////////////////// refresh topology  //////////////////////
    // session, task, event, bios, vm refresh
    static std::vector<topo_node_refresh_rec> nodelist;
    TOPOLOGY_REFRESH_CONFIG(nodelist);

    if(is_ready())
    {
        for(int i = 0; i < nodelist.size(); i++)
        {
            if(CHK_REFRESH_BIT(p->types_map, nodelist[i].datatype))
            {
                RF_PRINT_DBG("[cache] ==> %s nodes need updates\n", nodelist[i].classname.c_str());
                ResourceTopology::update_topology(nodelist[i].classname);
            }
        }
        //TODO more topology refresh. e.g. the whole topology
    }
}

void prefetch_engine_data(std::shared_ptr <::odata::edm::edm_model> model)
{
    static std::vector<bson_fetch_rec> fetchlist;
    static std::vector<json_urifetch_rec> tgtlist;
    static unsigned int counter = 0;

    if(model == nullptr)
        return;

    int rc;

    //////////////////////////////////////////////////////////////////////////
    ////////////////    fetch data for BSON cache by list    //////////////////
    BSON_FETCH_CONFIG(fetchlist);

    if(is_ready() == true)
    {
        for(int i = 0; i < fetchlist.size(); i++)
        {
            if((counter % fetchlist[i].counter) == 0)
            {
                bson::BSONObjBuilder rslt;
                DataInterfaceMgr::getData(fetchlist[i].keyname, fetchlist[i].args, rslt);
                //RF_PRINT_DBG("[cache] ------- prefetch BSON %s | %s \n", fetchlist[i].keyname.c_str(), fetchlist[i].args.jsonString().c_str());
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////
    ////////////////    fetch data for json cache by URI    //////////////////
    URL_FETCH_CONFIG(tgtlist);

    DataInterfaceMgr::DataMgrClientInfo(IMM_PRIV_SUPERVISOR, "root", "127.0.0.1");
    try
    {
      if(is_ready() == true)
      {
          for(int i = 0; i < tgtlist.size(); i++)
          {
              if((counter % tgtlist[i].counter) == 0)
              {
                  auto reqctx = std::make_shared<::snapper::service::request_context>(tgtlist[i].target, ::snapper::service::http_get, model);
                  auto handler = std::make_shared<::snapper::service::request_handler>(model);
                  rc = handler->handle(reqctx);
                  if(rc != RFRC_SUCCESS)
                      RF_PRINT_WARN("[cache] ------ failed to prefetch uri %s rc=%d \n", tgtlist[i].target.c_str(), rc);
              }
          }
      }

    }
    catch (::odata::core::odata_exception &e)
    {
        RF_PRINT_ERR("OData Exception: %s \n", e.what().c_str());
    }
    catch (::odata::service::odata_service_exception &e)
    {
        RF_PRINT_ERR("OData Service Exception: %s \n", e.what().c_str());
    }
    catch (::bson::assertion &e)
    {
        RF_PRINT_ERR("BSON Exception: %s \n", e.what());
    }

    counter++;
}


#ifdef __cplusplus
}
#endif

