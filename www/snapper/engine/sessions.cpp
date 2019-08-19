//---------------------------------------------------------------------
// <copyright file="sessions.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#include <www/engine/rf_jwt.h>
#include <www/engine/rf_debug.h>

#include "bson/bson.h"
#include "bson/util/json.h"

#include "protocol.h"
#include "rf_engine_error.h"
#include "sessions.h"
#include "rf_shm_session.h"
#include "datainf/DataInterfaceMgr.h"

#include <string.h>
#include <uuid/uuid.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <unistd.h>

using namespace ::std;
using namespace ::snapper::datamgr;

namespace snapper { namespace service
{

CURRENT_SESSION PROTOCOL::cur_session;

void PROTOCOL::set_cur_session(int handle, int aimid, char *loginname, char *displayname, char *remoteip, int privil, int uid, int pwdreason, char *orig)
{
    cur_session.pam_handle = handle;
    cur_session.aim_sessionid = aimid;
    if(loginname)
        strncpy(cur_session.login_name, loginname, sizeof(cur_session.login_name)-1);
    if(displayname)
        strncpy(cur_session.display_name, displayname, sizeof(cur_session.display_name)-1);
    cur_session.aim_privileges = privil;
    cur_session.local_userid = uid;
    if(remoteip)
        strncpy(cur_session.remoteip, remoteip, sizeof(cur_session.remoteip)-1);
    if(orig && strlen(orig))
        strncpy(cur_session.hdr_orig, orig, sizeof(cur_session.hdr_orig)-1);
    cur_session.reason_chgpwd = pwdreason;
}

CURRENT_SESSION & PROTOCOL::get_cur_session()
{
    return cur_session;
}

void PROTOCOL::clear_cur_session()
{
    cur_session.clear();
}

/************************************************************
 * sharemem sessions management
 * 
 ***********************************************************/


int PROTOCOL::avail_sessions_num()
{
    return get_session_slots();
}

std::vector<unsigned int> PROTOCOL::session_instances()
{
    std::vector<unsigned int> l;
    unsigned char arr[MAX_USR_SESSIONS+2];
    int num, i;

    num = get_session_instances(arr);
    for(i=0;i<num;i++)
        l.push_back(arr[i]);

    return l;
}


int PROTOCOL::add_new_session(CURRENT_SESSION &sess_in, string &token_out)
{
    uuid_t uuid;
    char uuid_str[64];
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);

    char *token = rf_auth_token_enc(uuid_str);
    if(!token)
        return -1;
    token_out = string(token);
    free(token);

    rf_usr_session new_sess;
    struct sysinfo s_info;
    long uptime = time(NULL);
    if(sysinfo(&s_info) == 0)
        uptime = s_info.uptime;

    string keyname = "SessionService";    
    bson::BSONObjBuilder arguments;
    bson::BSONObjBuilder result;
    int rc = DataInterfaceMgr::getData(keyname, arguments.obj(), result);
    int timeout = 300;//default
    bson::BSONObj dataobjs = result.obj();
    if(rc == RFRC_SUCCESS)
    {
        int t = dataobjs.getIntField("SessionTimeout");
        if(t >= 30 && t <= 86400)
            timeout = t;
    }

    memset(&new_sess, 0, sizeof(new_sess));
    new_sess.valid = 1; 
    strncpy(new_sess.loginname, sess_in.login_name, sizeof(new_sess.loginname)-1);
    new_sess.logoff = 0; 
    new_sess.flag = 0; 
    new_sess.pamhandle  = sess_in.pam_handle;
    new_sess.aimsession = sess_in.aim_sessionid;
    new_sess.privilege  = sess_in.aim_privileges;
    new_sess.usrid      = sess_in.local_userid;;
    new_sess.expires = uptime + timeout;
    new_sess.lifetime = timeout;
    new_sess.pid = getpid();
    new_sess.pamreason = sess_in.reason_chgpwd;
    strncpy(new_sess.usrname, sess_in.display_name, sizeof(new_sess.usrname)-1);
    strncpy(new_sess.rf_sessid, uuid_str, sizeof(new_sess.rf_sessid)-1);
    strncpy(new_sess.remoteip, sess_in.remoteip, sizeof(new_sess.remoteip)-1);
    strncpy(new_sess.hdr_orig, sess_in.hdr_orig, sizeof(new_sess.hdr_orig)-1);

    int index = add_session_entry(&new_sess);

    RF_PRINT_DBG("new session[%d] %s/%d (0x%x/0x%x) : priv 0x%x, exp %u(%u), sid %s, pid %d, ip %s, orig %s\n", 
        index, new_sess.loginname, new_sess.usrid, new_sess.pamhandle, new_sess.aimsession,
        new_sess.privilege, new_sess.expires, new_sess.lifetime, 
        new_sess.rf_sessid, new_sess.pid, new_sess.remoteip, new_sess.hdr_orig);

    return index;
}

int PROTOCOL::open_session(char *session_token)
{
    char sid[64]={0};
    rf_usr_session session;
    if(!session_token || strlen(session_token) == 0)
        return RFRC_AUTH_FAILED;

    int ret = rf_auth_token_dec((char *)session_token, sid);
    if(ret)
        return RFRC_AUTH_FAILED;

    if(search_session_entry(sid, &session) < 0)
    {
        RF_PRINT("session %s not found\n", sid);
        return RFRC_AUTH_FAILED;
    }
    if(is_session_entry_logoff(sid))
    {
        RF_PRINT("session %s logoff\n", sid);
        return RFRC_AUTH_FAILED;
    }
    if(is_session_entry_expired(sid))
    {
        RF_PRINT("session %s expired\n", sid);
        set_session_logoff(sid);
        return RFRC_AUTH_FAILED;
    }

    // compare remote ipaddress?

    struct sysinfo s_info;
    if(sysinfo(&s_info) == 0)
        session.expires = s_info.uptime + session.lifetime;
    update_session_entry(&session);

    set_cur_session(session.pamhandle, session.aimsession, session.loginname, session.usrname, 
                    session.remoteip, session.privilege, session.usrid, session.pamreason, session.hdr_orig);

    RF_PRINT_DBG("open session user %s (0x%x/0x%x) : priv 0x%x, exp %u(%u), sid %s, pid %d, ip %s, orig %s\n", 
        session.loginname, session.pamhandle, session.aimsession,
        session.privilege, session.expires, session.lifetime, 
        session.rf_sessid, session.pid, session.remoteip, session.hdr_orig);


    return RFRC_SUCCESS;
}

int PROTOCOL::delete_session(string sid)
{
    set_session_logoff((char *)sid.c_str());
    return RFRC_SUCCESS;
}

int PROTOCOL::session_info(unsigned int slot, char *username, int *priv, char *sid, char *remoteip)
{
    rf_usr_session sess;
    int rc = search_session_slot(slot, &sess);
    if(rc != 0)
        return RFRC_FAILURE;
    if(username)
        strncpy(username, sess.usrname, sizeof(sess.usrname));
    if(priv)
        *priv = sess.privilege;
    if(sid)
        strncpy(sid, sess.rf_sessid, sizeof(sess.rf_sessid));
    if(remoteip)
        strncpy(remoteip, sess.remoteip, sizeof(sess.remoteip));

    return RFRC_SUCCESS;
}

}}
