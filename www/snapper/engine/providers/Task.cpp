//---------------------------------------------------------------------
// <copyright file="Task.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Task.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>
#include "protocol.h"
#include <www/engine/rfmon_clt.h>
#include <www/engine/helpercmn.h>

extern "C" {

}
#include "class/ClassCommon.h"

string task_ec_to_str(unsigned int ec)
{
    if(ec == TASK_EC_INVALID_PARAMS)
        return "Invalid parameters.";
    else if(ec == TASK_EC_FAILED)
        return "Task failed.";
    else if(ec == TASK_EC_NO_RESOURCE)
        return "System busy. Failed to execute the task.";
    else if(ec == TASK_EC_TIMEOUT)
        return "Task timeout.";
    else if(ec == TASK_EC_CANCEL)
        return "Task cancelled.";
    else if(ec == TASK_EC_PARTIAL_FAILED)
        return "Task partially failed.";
    else if(ec == TASK_EC_DOWNLOAD_FAILED)
        return "Task failed to download file.";
    else if(ec == TASK_EC_FLASH_FAILED)
        return "Task failed to download file.";
    else if(ec == TASK_EC_NOT_SUPPORTED)
        return "Task failed to download file.";
    return "";
}

using namespace snapper::service;

namespace snapper { namespace providers 
{



std::shared_ptr<memid_acckey_map> Task::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    unsigned char outdata[1024];
    memset(outdata, 0, sizeof(outdata));
    task_list *tp = (task_list *)outdata; 

    rfmon_list_tasks(outdata);
    for(int i=0;i<tp->count && i < RF_MAX_TASKS;i++)
    {
        stringstream ss;
        ss << (unsigned int)(tp->tid[i]);
        (*list)[ss.str()] = ss.str() + "@Task";
        //std::cout << "task id " << ss.str() << ":"<< tp->tid[i] << std::endl;
    }

    return list;
}

string Task::state_conv(int state)
{
    if(state == TASK_NEW)
        return MAKE_ENUM_STRING(TaskState_New);
    else if(state == TASK_STARTING)
        return MAKE_ENUM_STRING(TaskState_Starting);
    else if(state == TASK_RUNNING)
        return MAKE_ENUM_STRING(TaskState_Running);
    else if(state == TASK_SUSPENDED)
        return MAKE_ENUM_STRING(TaskState_Suspended);
    else if(state == TASK_INTERRUPTED)
        return MAKE_ENUM_STRING(TaskState_Interrupted);
    else if(state == TASK_PENDING)
        return MAKE_ENUM_STRING(TaskState_Pending);
    else if(state == TASK_STOPPING)
        return MAKE_ENUM_STRING(TaskState_Stopping);
    else if(state == TASK_COMPLETED)
        return MAKE_ENUM_STRING(TaskState_Completed);
    else if(state == TASK_KILLED)
        return MAKE_ENUM_STRING(TaskState_Killed);
    else if(state == TASK_SERVICE)
        return MAKE_ENUM_STRING(TaskState_Service);
    else
        return MAKE_ENUM_STRING(TaskState_Exception);

}


void Task:: build_messages(task_info *tp, bson::BSONArrayBuilder* TaskMsgArr)
{
    RF_PRINT_DBG("----------task ec %d\n", tp->ec);
    int err_code = 0;
    stringstream Errorstr;
    char au8Buffer[128] = {0};
    bson::BSONElement pldm_Err;
    bson::BSONObj TaskMsg;

    if(tp->state == TASK_RUNNING )
    {
        fw_update_oem *p = (fw_update_oem *)tp->oemdata;
        Errorstr.str("");

        if(strstr((char *)p->target, BACKUP_BANK))
            Errorstr<<FW_TYPE_BMC_B<<":";
        else if(strstr((char *)p->target, PRIMARY_BANK))
            Errorstr<<FW_TYPE_BMC_P<<":";

        Errorstr<<tp->progress;
        TaskMsgArr->append(::snapper::providers::StandardErrorMessage::MMO_FirmwareUpdating(Errorstr.str())->copy()); // create a message with progress code
    }
    else if(tp->state == TASK_EXCEPTION )
    {
        fw_update_oem *p = (fw_update_oem *)tp->oemdata;
        string target = string(p->target);
        // TODO convert fwtype + target to target string
        if(p->fmerr)
        {
            //TODO convert fm error to human readable string. 
            //no necessary to get specific pldm error from database. just use transaction::map_error_detail to 
            //map fmerr to common error string
            RF_PRINT_DBG("fm error:  %d\n", p->fmerr);
            TaskMsgArr->append(::snapper::providers::StandardErrorMessage::MMO_FirmwareUpdateError(target,string(au8Buffer))->copy());
        }
        else
        {
            TaskMsgArr->append(::snapper::providers::StandardErrorMessage::MMO_FirmwareUpdateError(target, task_ec_to_str(tp->ec))->copy());
        }
    }

}

int Task::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);

    // reuse Task resource to handle Task Monitor URL
    string oid_in = request->get_raw_path();
    bool monitor = false;
    
                    
    string k = get_id_key();
    if(k.find(TASK_MONITOR_ID_PRE) != string::npos)
    {
        set_id_key(k.substr(k.find(TASK_MONITOR_ID_PRE)+4));
        monitor = true;
        RF_PRINT_DBG("id key for monitor %s, new key %s\n", k.c_str(), get_id_key().c_str());
    }
    RF_PRINT_DBG("is monitor url %d\n", monitor);

    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)
        return RFRC_DATA_NOT_FOUND;


    //////////////////////////////////////////////////////
    // GET resource query

    int tid = atoi(get_id_key().c_str());
    unsigned char outdata[1024];
    task_info *tp = (task_info *)outdata; 
    int ret = rfmon_get_taskinfo(tid, outdata);
    if(ret)
        return RFRC_DATA_NOT_FOUND;
    RF_PRINT_DBG("----------task owner %s, oemtype: %d,  oemdata %s\n", tp->owner,tp->oemtype, tp->oemdata);
    std::string name = get_name() + " " + get_id_key();
    if(strlen(tp->tname))
        name += " (" + std::string(tp->tname) + ")";
    setobj( RESOURCE_NAME,       MAKE_BSON_OBJ(RESOURCE_NAME, name) );
    setobj( "TaskState",         MAKE_BSON_OBJ("TaskState", state_conv(tp->state)) );

    setobj( "StartTime",         MAKE_BSON_OBJ("StartTime", tp->starttime) );
    setobj( "EndTime",           MAKE_BSON_OBJ("EndTime",   tp->endtime) );
    
    if(tp->oemtype == OEMTYPE_FFDC)
    {
        std::string fileuri((char *)tp->oemdata);
        setOemLenovoobj( "FFDCForDownloading",         MAKE_BSON_OBJ("FFDCForDownloading", BSON("Path" << fileuri)) );
    }

    if(tp->state == TASK_EXCEPTION)
        setobj( "TaskStatus",           MAKE_BSON_OBJ("TaskStatus",   MAKE_ENUM_STRING(Health_Warning)) );
    else
        setobj( "TaskStatus",           MAKE_BSON_OBJ("TaskStatus",   MAKE_ENUM_STRING(Health_OK)) );

    //use the tp->ec to fill the task message
    bson::BSONArrayBuilder TaskMsgArr;

    if(tp->oemtype == OEMTYPE_UPDATE)
       build_messages(tp, &TaskMsgArr);
    setobj( "Messages",  MAKE_BSON_OBJ("Messages", TaskMsgArr.arr()));


    if(monitor == true)
    {
        if(tp->state == TASK_RUNNING)
            override_http_code(HTTP_ACCEPTED);
    }
    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);

    return RFRC_SUCCESS;
}

int Task::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Task::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int Task::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Task::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(Task);
}}

