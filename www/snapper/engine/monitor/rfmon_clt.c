
#include "rfmon_clt.h"
#include "common.h"

#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

static char initialized = 0;
static pthread_mutex_t init_mutex=PTHREAD_MUTEX_INITIALIZER;
static int sock_fd = -1;
static struct sockaddr_un local_addr={0,{0}};
static struct sockaddr_un rfmon_addr={0,{0}};
#ifdef __cplusplus
extern "C" {
#endif

#define CLIENT_SOCK             "/tmp/rfmon_clt"

static __attribute__((destructor)) void rfmon_clt_fini()
{
    if(strlen(local_addr.sun_path))
        unlink(local_addr.sun_path);
}

int rfmon_clt_init()
{
    int buff_size = 1024*10;
    struct timeval timeout = {3,0};
    pthread_mutex_lock( &init_mutex ); 
    if (initialized && sock_fd > 0)
    {        
        pthread_mutex_unlock( &init_mutex );
        return 1;
    }

    sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sock_fd == -1)
    {
        pthread_mutex_unlock( &init_mutex ); 
        return 0;
    }
    bzero((char *)&local_addr, sizeof(struct sockaddr_un));
    local_addr.sun_family = AF_UNIX;
    snprintf(local_addr.sun_path, sizeof(local_addr.sun_path)-1, "%s_%d.sock", CLIENT_SOCK, getpid());
    unlink(local_addr.sun_path);
    if(bind(sock_fd, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0)
    {
        close(sock_fd);
        pthread_mutex_unlock( &init_mutex ); 
        return 0;
    }
    if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &buff_size, sizeof(buff_size)) < 0)
    {
        close(sock_fd);
        pthread_mutex_unlock( &init_mutex ); 
        return 0;
    }
    if(setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval)) < 0)
    {
        close(sock_fd);
        pthread_mutex_unlock( &init_mutex ); 
        return 0;
    }

    bzero((char *)&rfmon_addr,sizeof(struct sockaddr_un));
    rfmon_addr.sun_family = AF_UNIX;
    strncpy(rfmon_addr.sun_path, MON_SOCK, sizeof(rfmon_addr.sun_path) - 1);

    initialized = 1;
    pthread_mutex_unlock( &init_mutex ); 
    return 1;
}
/*
  indata - payload
  len - payload length
  outdata - payload of response
  return length of response payload

  if param outdata is null, only send data and return sent bytes
  if param outdata is not null, send data and read response and return received bytes
*/
int rfmon_wr_msg(unsigned int event, unsigned char *indata, unsigned int len, unsigned char *outdata)
{
    mon_packet packet; 
    int bytes;
    socklen_t addrlen;
    struct sockaddr_un from_addr;
    if(rfmon_clt_init() == 0)
        return -1;

    memset(&packet, 0, sizeof(mon_packet)); 
    if(len > MON_MAX_PAYLOAD)
        len = MON_MAX_PAYLOAD;

    packet.event = event; 
    packet.timestamp = time(NULL); 
    packet.sender_pid = getpid(); 
    packet.op = 0; 
    packet.needack = (outdata==NULL?0:1); 
    if(indata)
    {
        packet.data_len = len;
        memcpy(packet.data, indata, len);
    }

    bytes = sendto(sock_fd, (unsigned char *)&packet, sizeof(packet), 0, (struct sockaddr*)&rfmon_addr, sizeof(rfmon_addr));
    if(bytes < 0)
        return -1;

    if(!outdata)
        return bytes;

    memset(&packet, 0, sizeof(mon_packet)); 
    addrlen = sizeof(struct sockaddr_un);
    bytes = recvfrom(sock_fd, (unsigned char *)&packet, sizeof(packet), 0, (struct sockaddr*)&from_addr, &addrlen);
    if(bytes < 0)
        return -1;
    if(packet.event != event || packet.op != 1)//response should match request
        return -1;
    if(packet.cc)
        return -1*packet.cc;


    len = (packet.data_len > MON_MAX_PAYLOAD ? MON_MAX_PAYLOAD : packet.data_len);
    memcpy(outdata, packet.data, len);
    return len;
}

/*
  cmdpath - file path
  params - parameter string, separated by space
  name - task name
  tid = returned task id
*/
int rfmon_launch_task(char *cmdpath, char *params, char *name, int *tid, char *owner)
{
    int rc;
    new_task task = {{0}, {0}, {0}, {0}, 0};
    if(!cmdpath || !tid)
        return -1;

    strncpy(task.cmdpath, cmdpath, sizeof(task.cmdpath)-1);
    if(params)
        strncpy(task.params, params, sizeof(task.params)-1);
    if(name)
        strncpy(task.tname, name, sizeof(task.tname)-1);
    if(owner)
        strncpy(task.owner, owner, sizeof(task.owner)-1);

    rc = rfmon_wr_msg(MON_EVT_NEW_TASK, (unsigned char *)&task, sizeof(task), (unsigned char *)&task); 
    if(rc == 0)
        return -1;
    if(rc < 0)
        return rc;

    *tid = task.tid;
    return 0;
}


/*
  outdata - returned task_list

*/
int rfmon_list_tasks(unsigned char *outdata)
{
    int rc;
    if(!outdata)
        return -1;

    rc = rfmon_wr_msg(MON_EVT_LIST_TASKS, NULL, 0, outdata); 
    if(rc <= 0)
        return -1;

    return 0;
}

/*
  tid -  requested task id
  outdata - returned task_info
*/
int rfmon_get_taskinfo(int tid, unsigned char *outdata)
{
    int rc;
    task_info taskinfo;
    if(!outdata)
        return -1;

    taskinfo.tid = tid;
    rc = rfmon_wr_msg(MON_EVT_GET_TASK, (unsigned char *)&taskinfo, sizeof(taskinfo), outdata);
    if(rc == 0)
        return -1;
    if(rc < 0)
        return rc;

    return 0;
}

/*
  tid -  requested task id
  outdata - returned task_info
*/
int rfmon_remove_task(int tid, unsigned char *outdata)
{
    int rc;
    task_info taskinfo;
    if(!outdata)
        return -1;

    taskinfo.tid = tid;
    rc = rfmon_wr_msg(MON_EVT_REMOVE_TASK, (unsigned char *)&taskinfo, sizeof(taskinfo), outdata);
    if(rc == 0)
        return -1;
    if(rc < 0)
        return rc;

    return 0;
}

/*
  progress - task progress to set
  ec - task error to set. rf_task_ec
  outdata - returned task_info
*/
int rfmon_set_task_progress(int progress, int ec, unsigned char *outdata)
{
    int rc;
    task_progress_set tp;
    if(!outdata)
        return -1;

    tp.progress = progress;
    tp.ec = ec;
    rc = rfmon_wr_msg(MON_EVT_SET_TASK_PROG, (unsigned char *)&tp, sizeof(tp), outdata);
    if(rc == 0)
        return -1;
    if(rc < 0)
        return rc;

    return 0;
}

/*
  type - oem data type to set
  indata - binary oem data to set
*/
int rfmon_set_task_oemdata(int type, unsigned char *indata)
{
    int rc;
    task_oemdata_set tp;
    if(!indata)
        return -1;

    tp.oemtype = type;
    memcpy(tp.oemdata, indata, T_OEM_LEN);
    rc = rfmon_wr_msg(MON_EVT_SET_TASK_OEM, (unsigned char *)&tp, sizeof(tp), NULL);
    if(rc == 0)
        return -1;
    if(rc < 0)
        return rc;

    return 0;
}

/*
  len - number of resource data type to refresh
  indata - array of refresh_data_type
*/
int rfmon_inform_refresh(int len, unsigned char *indata)
{
    int rc;
    req_refresh_data req;
    if(!indata)
        return -1;
    if(len > sizeof(req.types))
        len = sizeof(req.types);

    req.length = len;
    memcpy(req.types, indata, len);
    rc = rfmon_wr_msg(MON_EVT_INFORM_UPDATE, (unsigned char *)&req, sizeof(req), NULL);
    if(rc == 0)
        return -1;
    if(rc < 0)
        return rc;

    return 0;
}


#ifdef __cplusplus
}
#endif

