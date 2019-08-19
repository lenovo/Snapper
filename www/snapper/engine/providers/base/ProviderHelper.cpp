//---------------------------------------------------------------------
// <copyright file="ProviderHelper.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <time.h>
#include <www/engine/request_context.h>
#include <www/engine/rf_debug.h>
#include <www/engine/rfmon_clt.h>

#include "class/ClassNames.h"
#include "class/Task.h"
#include "class/ProviderHelper.h"
#include "rf_engine_error.h"
#include "datainf/DataInterfaceMgr.h"

using namespace snapper::service;
using namespace std;
using namespace ::bson;
	
namespace snapper { namespace providers 
{

typedef struct _tzformat_map{
    char *rf_tz;
    char *aim_tz;
}tz_string;
static tz_string tz_list[] = {
 {"+00:00", "GMT+0"},
 {"+01:00", "GMT+1"},
 {"+02:00", "GMT+2"}, 
 {"+03:00", "GMT+3"}, 
 {"+03:30", "GMT+3:30"}, 
 {"+04:00", "GMT+4"}, 
 {"+04:30", "GMT+4:30"}, 
 {"+05:00", "GMT+5"}, 
 {"+05:30", "GMT+5:30"}, 
 {"+05:45", "GMT+5:45"}, 
 {"+06:00", "GMT+6"}, 
 {"+06:30", "GMT+6:30"}, 
 {"+07:00", "GMT+7"}, 
 {"+08:00", "GMT+8"}, 
 {"+09:00", "GMT+9"}, 
 {"+09:30", "GMT+9:30"}, 
 {"+10:00", "GMT+10"}, 
 {"+11:00", "GMT+11"}, 
 {"+12:00", "GMT+12"}, 
 {"+13:00", "GMT+13"},
 {"-12:00", "GMT-12"}, 
 {"-11:00", "GMT-11"}, 
 {"-10:00", "GMT-10"}, 
 {"-09:00", "GMT-9"}, 
 {"-08:00", "GMT-8"}, 
 {"-07:00", "GMT-7"}, 
 {"-06:00", "GMT-6"}, 
 {"-05:00", "GMT-5"}, 
 {"-04:30", "GMT-4:30"}, 
 {"-04:00", "GMT-4"}, 
 {"-03:30", "GMT-3:30"},
 {"-03:00", "GMT-3"},
 {"-02:00", "GMT-2"},
 {"-01:00", "GMT-1"},

 {NULL, NULL}
};

std::string tz_rf2aim(std::string rf_tz)
{
    std::map<std::string, std::string> tz;
    for(int i = 0; i < sizeof(tz_list)/ sizeof(tz_string) && tz_list[i].rf_tz && tz_list[i].aim_tz; i++)
        tz[tz_list[i].rf_tz] = tz_list[i].aim_tz;

    if(tz.find(rf_tz) != tz.end())
        return tz[rf_tz];
    return "";
}

std::string tz_aim2rf(std::string aim_tz)
{
    std::map<std::string, std::string> tz;
    for(int i = 0; i < sizeof(tz_list)/ sizeof(tz_string) && tz_list[i].rf_tz && tz_list[i].aim_tz; i++)
        tz[tz_list[i].aim_tz] = tz_list[i].rf_tz;

    if(tz.find(aim_tz) != tz.end())
        return tz[aim_tz];
    return "";
}



std::string serialize_Task_objs(unsigned int taskid, shared_ptr<::snapper::service::request_context> request)
{
    string output;
    string path = request->get_raw_path();
	auto task = std::make_shared<Task>();

    stringstream newpath;
    newpath << "/redfish/v1/Tasks/Tasks/" << taskid;

    request->set_raw_path(newpath.str());
    task->handle_get(request);
    output = task->serialize_objs();
    request->set_raw_path(path);

    RF_PRINT_DBG("task information: %s\n", output.c_str());
	return output;
}

int GetHostPowerState(unsigned int *powerstate)
{
    bson::BSONObj ipmidata = BSON("IPMI_raw_command" << BSON_ARRAY(0 << 1));
    bson::BSONObjBuilder ipmi_builder;
    int ipmirc = RFRC_FAILURE;
    *powerstate = -1;
    ipmirc = DataInterfaceMgr::getData("ipmi_cmd", ipmidata, ipmi_builder);
    if(ipmirc != RFRC_SUCCESS)
        RF_PRINT_ERR("Get power state failed, the return code: %d\n", ipmirc);
    else
    {
        bson::BSONObj ipmiobj = ipmi_builder.obj();
        bson::BSONElement elem = ipmiobj.getField("ipmi_resp");
        if(elem.eoo() || elem.type() != bson::Array)
        {
            RF_PRINT_ERR("IPMI response data is not expected\n");
            ipmirc = RFRC_FAILURE;
        }
        else
        {
            std::vector<bson::BSONElement> data = elem.Array();
            if(data[0].Int()==0)
            {
                *powerstate = data[1].Int()&1; // '1': power on
                ipmirc = RFRC_SUCCESS;
            }
            else 
                ipmirc = data[0].Int();

        }
    }
    RF_PRINT_ERR("IPMI response: rc=%d, powerstate=%d\n",ipmirc,  *powerstate);
    return ipmirc;
}






}}

