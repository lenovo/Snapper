/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#ifndef _RF_SESS_H
#define _RF_SESS_H

#ifdef __cplusplus
extern "C" {
#endif

#define SESSIONLESS_ID    0x6379772E

#define MAX_USR_SESSIONS   20

#define FLAG_UPDATE 0x1

typedef struct _rf_usr_session{
    char valid;
    char logoff;
    char flag;
    int pamhandle;
    int aimsession;
    int privilege;
    int usrid;
    int expires; // next uptime to session expire
    int lifetime; // lifetime in seconds. 
    int pid;
    int pamreason; // pam reason: passwd expire, force change etc
    char loginname[64];
    char usrname[64];
    char rf_sessid[64];
    char remoteip[64];

    char hdr_orig[64];
}rf_usr_session;


void set_session_fwupdate(char *rf_sessid, char reserve);
int get_session_slots();
int get_session_instances(unsigned char *arr);
int search_session_entry(char *rf_sessid, rf_usr_session *sess);
int search_session_slot(unsigned int slot, rf_usr_session *sess);

int add_session_entry(rf_usr_session *sess);
int update_session_entry(rf_usr_session *sess);
void scan_session_expires();
void scan_session_logoff();
void set_session_logoff(char *rf_sessid);
int is_session_entry_expired(char *rf_sessid);
int is_session_entry_logoff(char *rf_sessid);
int sessions_modified();

void clean_session_all();
void print_sessions();


#ifdef __cplusplus
};
#endif

#endif // _RF_SESS_H


