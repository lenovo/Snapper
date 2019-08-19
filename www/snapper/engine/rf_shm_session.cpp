/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/
#include "rf_shm_session.h"
#include "rf_debug.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <security/pam_appl.h>
#include <sys/sysinfo.h>

#ifdef __cplusplus
extern "C" {
#endif


const char *lockfile = "/tmp/.rfsess-shm.lock";
void   *mem_start=NULL;
int    shm_id = -1;

int *g_modified = NULL;

/*----------------------------------------------------------*/
void sendLogoutEvent(unsigned int eventID, char *usr, char *ip, int ishttps)
{
/*
remove
*/
}


/*----------------------------------------------------------*/
int acquire_lock(int *lockfd)
{
    struct flock fd_flock;
    int fd = -1;

    if((fd = open (lockfile, O_RDWR | O_CREAT, S_IRUSR| S_IWUSR)) < 0)
        return -1;

    fd_flock.l_type = F_WRLCK;
    fd_flock.l_whence = SEEK_SET;
    fd_flock.l_start = 0;
    fd_flock.l_len = 0;
    fd_flock.l_pid = getpid();
    if(fcntl(fd, F_SETLKW,  &fd_flock) < 0) // wait on lock
    {
        close(fd);
        return -1;
    }
    *lockfd = fd;
    return 0;
}
int release_lock(int lockfd)
{
    struct flock fd_flock;

	fd_flock.l_type = F_UNLCK;
	fd_flock.l_whence = SEEK_SET;
	fd_flock.l_start = 0;
	fd_flock.l_len = 0;
   if (fcntl(lockfd, F_SETLKW,  &fd_flock) < 0)
   {
        close(lockfd);
        return -1;
   }
   close(lockfd);
   return 0;
}

int open_session_data()
{
    key_t  key = 0x72665F73;
    size_t memsize=MAX_USR_SESSIONS*sizeof(rf_usr_session) + 64;

    if((shm_id = shmget(key, memsize, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        if(errno == EEXIST)// already initiated
        {
            if((shm_id = shmget(key, memsize, 0666 )) < 0)
                return -1;
            if((mem_start = shmat(shm_id,NULL,0)) == (void *) -1)
                return -1;
        }
        else
            return -1;
    }
    else
    {
        if((mem_start = shmat(shm_id,NULL,0)) == (void *) -1)
            return -1;
        memset(mem_start, 0, memsize);
    }
    g_modified = (int *)((long)mem_start + MAX_USR_SESSIONS*sizeof(rf_usr_session));
    return 0;
}

int add_session_entry(rf_usr_session *sess)
{
    int lock, i, pos, dup, ret = -1;
    rf_usr_session *sessions;
    
    if(acquire_lock(&lock) < 0)
        return -1;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {   // initiate session data
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return -1;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    pos = -1;
    dup = 0;
    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        rf_usr_session *p = &(sessions[MAX_USR_SESSIONS-1-i]);
        if(p->valid && strcmp(p->rf_sessid, sess->rf_sessid) == 0)
            dup = 1;
        if(p->valid == 0)
            pos = MAX_USR_SESSIONS-1-i;
    }
    if(dup == 0 && pos >= 0)
    {
        struct sysinfo s_info;
        ret = pos;
        memcpy(&(sessions[pos]), sess, sizeof(rf_usr_session));
        if(g_modified)
            *g_modified |= 1;
    }

    release_lock(lock);
    return ret;
}

int search_session_entry(char *rf_sessid, rf_usr_session *sess)
{
    int lock, i, rc = 0;
    rf_usr_session *sessions;

    if(!sess || !rf_sessid || acquire_lock(&lock) < 0)
        return -1;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return -1;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid && strcmp(sessions[i].rf_sessid, rf_sessid) == 0)
        {
            memcpy(sess, &(sessions[i]), sizeof(rf_usr_session));
            break;
        }
    }
    if(i==MAX_USR_SESSIONS)
        rc = -1;

    release_lock(lock);
    return rc;
}

int search_session_slot(unsigned int slot, rf_usr_session *sess)
{
    int lock, i, rc = 0;
    rf_usr_session *sessions;

    if(!sess || slot >= MAX_USR_SESSIONS || acquire_lock(&lock) < 0)
        return -1;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return -1;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    if(sessions[slot].valid == 0)
        rc = -1;
    else
        memcpy(sess, &(sessions[slot]), sizeof(rf_usr_session));

    release_lock(lock);
    return rc;
}


int update_session_entry(rf_usr_session *sess)
{
    int lock, i;
    rf_usr_session *sessions;
    
    if(acquire_lock(&lock) < 0)
        return -1;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return -1;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid && sessions[i].logoff ==0 && strcmp(sessions[i].rf_sessid, sess->rf_sessid) == 0)
        {   //currently only expires changes.....
            struct sysinfo s_info;
            sessions[i].expires = sess->expires;
            break;
        }
    }

    release_lock(lock);
    if(i == MAX_USR_SESSIONS)
        return -1;
    return 0;
}

void scan_session_expires()
{
    int lock, i, err;
    rf_usr_session *sessions;
    //time_t t;
    struct sysinfo s_info;

    if(acquire_lock(&lock) < 0)
        return;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    err = sysinfo(&s_info);
    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        pam_handle_t* pamHandle;
        int ret = PAM_SUCCESS, pid = getpid();
        //if(sessions[i].valid)
        //    RF_PRINT("pid %d(%d) [%d, %d]", i, sessions[i].pid, (unsigned int)sessions[i].expires, s_info.uptime);

        //timestamp expires, only close pam handle in the same process of gunicorn worker
        if(sessions[i].valid && ((err == 0) && (((unsigned int)sessions[i].expires) < s_info.uptime)))
        {
            RF_PRINT("*** pid %d scaning - close expired '%s' session (%s) of pam %d/%d [%d, %d] ***", sessions[i].pid, sessions[i].usrname, sessions[i].rf_sessid, 
                      sessions[i].pamhandle, sessions[i].aimsession, (unsigned int)sessions[i].expires, (int)s_info.uptime);
            if(pid == sessions[i].pid)
            {
                int aimsession = sessions[i].aimsession;
                pamHandle = (pam_handle_t*)(sessions[i].pamhandle);
                if( pamHandle != NULL )
                {
                    if(SESSIONLESS_ID != aimsession && (ret = pam_close_session( pamHandle, 0 )) != PAM_SUCCESS)
                        RF_PRINT("failed to close session of pam %d", sessions[i].pamhandle);
                    if(pam_end( pamHandle, ret) != PAM_SUCCESS)
	                    RF_PRINT("failed to endpam %d", sessions[i].pamhandle);
                }
                RF_PRINT("pam close session");
            }
            else
            {
/*
remove
*/
            }

            // cancel web update
            if(sessions[i].flag & FLAG_UPDATE)
            {
                RF_PRINT("%s webcancel in expire scan", sessions[i].usrname);
            }

            memset(&(sessions[i]), 0, sizeof(rf_usr_session));
            if(g_modified)
                *g_modified |= 2;
        }
    }

    release_lock(lock);
}


void scan_session_logoff()
{
    int lock, i, err;
    rf_usr_session *sessions;
    struct sysinfo s_info;

    err = sysinfo(&s_info);    
    if(err)
        RF_PRINT("failed to get uptime");
    if(acquire_lock(&lock) < 0)
        return ;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return ;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        pam_handle_t* pamHandle;
        int ret = PAM_SUCCESS, pid = getpid();


        //only close pam handle in the same process of gunicorn worker
        if(sessions[i].valid && sessions[i].logoff == 1)
        {
            RF_PRINT("pid %d logoff '%s' session (%s) of pam %d/%d", sessions[i].pid, sessions[i].usrname, sessions[i].rf_sessid, sessions[i].pamhandle, sessions[i].aimsession);
            if(pid == sessions[i].pid)
            {
                int aimsession = sessions[i].aimsession;
                pamHandle = (pam_handle_t*)(sessions[i].pamhandle);
                if( pamHandle != NULL )
                {
                    if(SESSIONLESS_ID != aimsession && (ret = pam_close_session( pamHandle, 0 )) != PAM_SUCCESS)
                        RF_PRINT("failed to close session of pam %d", sessions[i].pamhandle);
                    if(pam_end( pamHandle, ret) != PAM_SUCCESS)
	                    RF_PRINT("failed to endpam %d", sessions[i].pamhandle);
                }
                RF_PRINT("pam close session");
            }
            else
            {
/*
remove
*/
            }

            // cancel web update
            if(sessions[i].flag & FLAG_UPDATE)
            {
                RF_PRINT("%s webcancel in logoff scan", sessions[i].usrname);
            }

            memset(&(sessions[i]), 0, sizeof(rf_usr_session));
            if(g_modified)
                *g_modified |= 2;
        }
    }

    release_lock(lock);
}


int is_session_entry_expired(char *rf_sessid)
{
    int lock, i, err, rc = 0;
    rf_usr_session *sessions;
    //time_t t;
    struct sysinfo s_info;
    
    if(acquire_lock(&lock) < 0)
        return 0;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return 0;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    //t = time(NULL);
    err = sysinfo(&s_info);
    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid && 
            strcmp(sessions[i].rf_sessid, rf_sessid) == 0 &&
            ((err == 0) && (((unsigned int)sessions[i].expires) < s_info.uptime)))
        {
            rc = 1;
            RF_PRINT("*** session expired(%d) %d, %d", i, (unsigned int)sessions[i].expires, (int)s_info.uptime);
        }
    }

    release_lock(lock);
    return rc;
}

int is_session_entry_logoff(char *rf_sessid)
{
    int lock, i, rc = 0;
    rf_usr_session *sessions;

    if(acquire_lock(&lock) < 0)
        return 0;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return 0;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid && strcmp(sessions[i].rf_sessid, rf_sessid) == 0)
        {
            if(sessions[i].logoff != 0)
                rc = 1;
            break;
        }
    }
    if(i==MAX_USR_SESSIONS) // not found as logout
        rc = 1;

    release_lock(lock);
    return rc;
}

void set_session_logoff(char *rf_sessid)
{
    int lock, i;
    rf_usr_session *sessions;

    if(acquire_lock(&lock) < 0)
        return ;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return ;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid && strcmp(sessions[i].rf_sessid, rf_sessid) == 0 )
            sessions[i].logoff = 1;
    }

    release_lock(lock);
}



void clean_session_all()
{
    int lock, i, flag = 0;
    rf_usr_session *sessions;
    
    if(acquire_lock(&lock) < 0)
        return ;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return ;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    //'clean all' normall used when app exit which already release resource. 
    //so do not need to close pam handle 
    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid)
        {
/*
remove
*/
        }

        // cancel web update
        if(sessions[i].valid && (sessions[i].flag & FLAG_UPDATE))
        {
            //RF_PRINT( "%s[%d] webcancel in cleanall", sessions[i].usrname, sessions[i].aimsession);
            flag = 1;
        }
        memset(&(sessions[i]), 0, sizeof(rf_usr_session));
    }

    if(flag)
        ;//webcancel();

    release_lock(lock);
}
void print_sessions()
{
    int lock, i;
    rf_usr_session *sessions;

    if(acquire_lock(&lock) < 0)
    {
        printf("lock failure\n");
        return;
    }
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            printf("read shm failure\n");
            release_lock(lock);
            return;
        }
    }

    sessions = (rf_usr_session *)mem_start;
    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid)
        {
            printf("[%d] %s/%d:(0x%x/0x%x) privilege=0x%x, expires=%u(%u), sess=%s pid=%d flag=%d logoff=%d pamreason=%d loginname=%s ip=%s\n", 
                  i, sessions[i].usrname, sessions[i].usrid, sessions[i].pamhandle, sessions[i].aimsession,
                  sessions[i].privilege, sessions[i].expires, sessions[i].lifetime, sessions[i].rf_sessid, sessions[i].pid, sessions[i].flag, sessions[i].logoff,
                  sessions[i].pamreason, sessions[i].loginname, sessions[i].remoteip);
        }            
    }

    release_lock(lock);
}

/*----------------------------------------------------------*/

void set_session_fwupdate(char *rf_sessid, char reserve)
{
    int lock, i;
    rf_usr_session *sessions;

    if(acquire_lock(&lock) < 0)
        return ;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return ;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid && strcmp(sessions[i].rf_sessid, rf_sessid) == 0 ){
            if(reserve)
                sessions[i].flag |= FLAG_UPDATE;
            else
                sessions[i].flag &= ~FLAG_UPDATE;
        	//RF_PRINT( "set fw flag %s, %s, %d %d", sessions[i].rf_sessid, rf_sessid, reserve, sessions[i].flag);
        }
    }

    release_lock(lock);
}


int get_session_slots()
{
    int lock, i, slots = 0;
    rf_usr_session *sessions;

    if(acquire_lock(&lock) < 0)
        return slots;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return slots;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid == 0 )
            slots++;
    }

    release_lock(lock);
    return slots;
}

int get_session_instances(unsigned char *arr)
{
    int lock, i, inst = 0;
    rf_usr_session *sessions;

    if(!arr || acquire_lock(&lock) < 0)
        return inst;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return inst;
        }
    }
    sessions = (rf_usr_session *)mem_start;

    for(i=0;i<MAX_USR_SESSIONS;i++)
    {
        if(sessions[i].valid != 0 )
            arr[inst++] = (unsigned char)i;
    }

    release_lock(lock);
    return inst;
}

int sessions_modified()
{
    int lock, update;
    if(acquire_lock(&lock) < 0)
        return 0;
    if(shm_id < 0 || !mem_start || (mem_start == (void *) -1))
    {
        if(open_session_data() < 0)
        {
            release_lock(lock);
            return 0;
        }
    }

    update = *g_modified;
    *g_modified = 0;
    release_lock(lock);

    return update;
}

#ifdef __cplusplus
}
#endif

