#ifndef __RFMON_CLT_H__
#define __RFMON_CLT_H__

#include <www/engine/cache_common.h>

#ifdef __cplusplus
extern "C" {
#endif


enum mon_event_id
{
    MON_EVT_TIMER         = 0x100,
    MON_EVT_QUERY_UPDATE  = 0x101,
    MON_EVT_NEW_TASK      = 0x102,
    MON_EVT_LIST_TASKS    = 0x103,
    MON_EVT_GET_TASK      = 0x104,
    MON_EVT_REMOVE_TASK   = 0x105,
    MON_EVT_SET_TASK_PROG = 0x106,
    MON_EVT_SET_TASK_OEM  = 0x107,
    MON_EVT_INFORM_UPDATE = 0x108,
};

enum rf_task_state
{
    TASK_NEW         = 0x1,
    TASK_STARTING,
    TASK_RUNNING,
    TASK_SUSPENDED,
    TASK_INTERRUPTED,
    TASK_PENDING,
    TASK_STOPPING,
    TASK_COMPLETED,
    TASK_KILLED,
    TASK_EXCEPTION,
    TASK_SERVICE,
};

enum rf_task_ec
{
    TASK_EC_OK                     = 0x0,
    TASK_EC_INVALID_PARAMS         = 0x1,
    TASK_EC_FAILED,
    TASK_EC_NO_RESOURCE,
    TASK_EC_TIMEOUT,
    TASK_EC_CANCEL,
    TASK_EC_PARTIAL_FAILED,
    TASK_EC_DOWNLOAD_FAILED,
    TASK_EC_FLASH_FAILED,
    TASK_EC_MOUNT_FAILED,
    TASK_EC_NOT_SUPPORTED,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// following structure reuse mon_packet.data[MON_MAX_PAYLOAD]
// MON_MAX_PAYLOAD 1024 maximum payload


/*****************************************
event data to set progress and error code of task - 
MON_EVT_SET_TASK_PROG (task process <----> monitor)
******************************************/
typedef struct _task_progress_set
{
    unsigned int progress; //req
    int ec; //req
    int tid; //resp, task id returned for the client process
}task_progress_set;


/*****************************************
event data to set oem data of task - 
MON_EVT_SET_TASK_OEM (task process <----> monitor)
******************************************/
#define T_OEM_LEN    128
typedef struct _task_oemdata_set
{
    int  oemtype; // req: 0-no oem, 1-ffdc
    char oemdata[T_OEM_LEN]; //req
}task_oemdata_set;

//---------------------------------------------------------------------


/*****************************************
event data for query of resource data change - 
MON_EVT_QUERY_UPDATE (snapper engine <----> monitor)
******************************************/
// request data: none
// response data:
typedef struct _updated_resource_data
{
    unsigned int    lastquery; //resp, time of last query from woker
    unsigned char   types_map[MAX_REFRESH_BYTES];//resp

}updated_resource_data;

/*****************************************
event data for informing change of  - 
MON_EVT_INFORM_UPDATE (any <----> monitor)
******************************************/
// request data: none
// response data:
typedef struct _req_refresh_data
{
    unsigned int    length; //req, number of refresh type
    unsigned char   types[MAX_REFRESH_BITS];//req, array of refresh_data_type
}req_refresh_data;

/*****************************************
event data for event to launch new task - 
MON_EVT_NEW_TASK (snapper engine <----> monitor)
******************************************/
#define T_CMD_LEN    64
#define T_CMD_PARAM  256
#define T_TASK_NAME  32
#define T_TASK_OWNER 64
typedef struct _new_task
{
    char cmdpath[T_CMD_LEN]; //req
    char params[T_CMD_PARAM]; //req
    char tname[T_TASK_NAME]; //req
    char owner[T_TASK_OWNER]; //req
    int  tid; //resp
}new_task;


/*****************************************
event data for retrieving task id list - 
MON_EVT_LIST_TASKS (snapper engine <----> monitor)
******************************************/
#define RF_MAX_TASKS    0x100
typedef struct _task_list
{
    unsigned char count; //resp
    unsigned char tid[RF_MAX_TASKS]; //resp
}task_list;


/*****************************************
event data for retrieving task info by tid - 
MON_EVT_GET_TASK (snapper engine <----> monitor)

event data for removing task by tid - 
MON_EVT_REMOVE_TASK (snapper engine <----> monitor)
******************************************/
#define T_TIME_LEN   32
#define OEMTYPE_FFDC     1
#define OEMTYPE_UPDATE   2

typedef struct _task_info
{
    int tid; //req
    int pid; //resp
    char cmdpath[T_CMD_LEN]; //resp
    char params[T_CMD_PARAM]; //resp
    char tname[T_TASK_NAME]; //resp
    char owner[T_TASK_OWNER]; //resp
    int state; //resp
    int ec; //resp
    char starttime[T_TIME_LEN]; //resp
    char endtime[T_TIME_LEN]; //resp
    int  oemtype; // resp: 0-no oem, 1-ffdc. 
    char oemdata[T_OEM_LEN]; //resp: each task utility could define their own private oem data structure
    int progress; //resp
}task_info;


/////////////////////////////////////////////////////////////////////////////////////////////////////

int rfmon_wr_msg(unsigned int event, unsigned char *data, unsigned int len, unsigned char *outdata);
int rfmon_launch_task(char *cmdpath, char *params, char *name, int *tid, char *owner);
int rfmon_list_tasks(unsigned char *outdata);
int rfmon_get_taskinfo(int tid, unsigned char *outdata);
int rfmon_remove_task(int tid, unsigned char *outdata);
int rfmon_set_task_progress(int progress, int ec, unsigned char *outdata);
int rfmon_set_task_oemdata(int type, unsigned char *indata);
int rfmon_inform_refresh(int len, unsigned char *indata);

#ifdef __cplusplus
};
#endif


#endif
