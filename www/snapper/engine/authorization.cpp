//---------------------------------------------------------------------
// <copyright file="authorization.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <security/pam_appl.h>

#include "bson/bson.h"
#include "bson/util/json.h"

#include "protocol.h"
#include "rf_shm_session.h"
#include "rf_engine_error.h"
#include "rf_debug.h"


using namespace ::std;

namespace snapper { namespace service
{

/************************************************************
 * base64 encode/decode
 ***********************************************************/
int PROTOCOL::AUTH_BASIC = 1;
int PROTOCOL::AUTH_SESSION = 2;
int PROTOCOL::IDENT_SESSION = 3;

const std::string PROTOCOL::base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string PROTOCOL::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) 
{
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string PROTOCOL::base64_decode(std::string const& encoded_string) 
{
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
/************************************************************
 * pam conversation callback
 ***********************************************************/

#ifdef __cplusplus
extern  "C" {
#endif
int conversation(int num_msg, const struct pam_message **msg,
		struct pam_response **resp, void *appdata_ptr)
{
    struct pam_response *reply = NULL;
    char *pwd = NULL;
    char *buf = NULL;
    int i = 0;

    *resp = NULL;

    if (appdata_ptr == NULL) {
        return (PAM_CONV_ERR);
    }

    if (num_msg <= 0 || num_msg > PAM_MAX_NUM_MSG) {
        return (PAM_CONV_ERR);
    }

    if ((reply = (struct pam_response *)calloc(num_msg, sizeof(*reply))) == NULL) {
        return (PAM_CONV_ERR);
    }
    for(i = 0; i < num_msg; ++i) {
        switch(msg[i]->msg_style) {
            case PAM_PROMPT_ECHO_OFF:
                pwd = *(char**)appdata_ptr;
                buf = (char *)malloc(strlen(pwd) + 1);
                if (buf == NULL) {
                    goto fail;
                }
                strcpy(buf, pwd);
                reply[i].resp = buf;
                reply[i].resp_retcode = 0;
                RF_PRINT_DBG("%s: %s", __FUNCTION__, buf);
                break;
            case PAM_PROMPT_ECHO_ON:
                break;
            case PAM_ERROR_MSG:
                break;
            case PAM_TEXT_INFO:
                RF_PRINT_DBG("PAM_TEXT_INFO: %s", msg[i]->msg);
                break;
            default:
                goto fail;
        }
    }
    *resp = reply;
    return (PAM_SUCCESS);

fail:
    RF_PRINT_DBG("pam_conv failed: %d\n", msg[i]->msg_style);
    for(i = 0; i < num_msg; i++) {
        if (reply[i].resp != NULL)
            free(reply[i].resp);
    }
    free(reply);
    return (PAM_CONV_ERR);
}

#ifdef __cplusplus
}
#endif



/************************************************************
 * authenticate user credential
 * 
 ***********************************************************/

int PROTOCOL::do_authenticate( char *service, char *user, char *pwd, char *remoteip, void **pam_handle, char **displayname, int *pam_err )
{
    pam_handle_t* pamh = NULL;
    struct pam_conv conv = {conversation, &pwd};
    int ret;

    *pam_err = 0;
    if ((ret = pam_start(service, user, &conv, &pamh)) != PAM_SUCCESS) {
        RF_PRINT_DBG("Pam start failed: %d\n", ret);
        *pam_err = ret;
        *pam_handle = NULL;
        return RFRC_PAM_ERROR;
    }

    if ((ret = pam_set_item(pamh, PAM_RHOST, remoteip)) != PAM_SUCCESS) {
        RF_PRINT_DBG("Set ip failed: %d\n", ret);
        *pam_err = ret;
        pam_end(pamh, ret);
        *pam_handle = NULL;
        return RFRC_PAM_ERROR;
    }

    ret = pam_authenticate(pamh, PAM_SILENT);  
    RF_PRINT_DBG("PAM Authentication result: %d\n", ret);
    if( ret == PAM_SUCCESS )
    {
        RF_PRINT_DBG("Login: (%s, %s, %s)\n", service, remoteip, user);
        ret = pam_acct_mgmt(pamh, 0);
        if (ret != PAM_SUCCESS && ret != PAM_NEW_AUTHTOK_REQD) {
            RF_PRINT_DBG("pam_acct_mgmt failed to register new session: %d\n", ret);
            *pam_err = ret;
            pam_end(pamh, ret);
            *pam_handle = NULL;
            return RFRC_PAM_ACCMGMT_FAILURE;
        }

        int result = RFRC_SUCCESS;
        if(ret == PAM_NEW_AUTHTOK_REQD) 
            result = RFRC_PAM_AUTHTOK_REQD;

        *pam_handle = (void *)pamh;

        *displayname=NULL;
        pam_get_item(pamh, PAM_USER, (const void **)displayname);
        *pam_err = ret;
        RF_PRINT_DBG("PAM_USER: %s  ret: %d\n", *displayname, ret);

        return result;
    }
    else
    {
        pam_end(pamh, ret);
        *pam_err = ret;
        *pam_handle = NULL;
        return RFRC_PAM_ERROR;
    }
}

int PROTOCOL::do_login(char *service, char *user, char *pwd, char *family, char *remoteip, bool sessionless)
{
    char *displayname = NULL;
    int reasonCode = 0;
    pam_handle_t* pamhdlr = NULL;
    int ret = RFRC_SUCCESS, rc, pamerr;
    int aimSessionId = -1;

    rc = do_authenticate(service, user, pwd, remoteip, (void **)&pamhdlr, &displayname, &pamerr);
    if(rc == RFRC_SUCCESS || rc ==  RFRC_PAM_AUTHTOK_REQD)
    {
        if(rc == RFRC_PAM_AUTHTOK_REQD)
        {
            ret = RFRC_AUTH_REQ_CHANGE_PASSWORD;
            const char* reqPWCauseStr = pam_getenv( pamhdlr, "REQ_CHG_PW_CAUSE");
            if (strcmp(reqPWCauseStr, "PWEXPIRED")==0) 
            {
               reasonCode = R_CHGPWD_EXPIRED;//password expired
            }
            else 
            {
               reasonCode = R_CHGPWD_FORCE;//force change
            }
            RF_PRINT_DBG("doLogin RC_PAM_AUTHTOK_REQD reason:%s (%d)\n",  reqPWCauseStr, reasonCode);
        }

        // start pam session
        rc = PAM_SUCCESS;
        if(sessionless == false)
            rc = pam_open_session( pamhdlr, 0 );
        if( rc == PAM_SUCCESS )
        {
            aimSessionId = SESSIONLESS_ID; //fix session id for sessionless
            if(sessionless == false)
            {
                const char* sid = pam_getenv( pamhdlr, "SESSION_ID" );
                if(sid)
                    sscanf( sid, "%i", &aimSessionId );
            }

            const char* privVal = pam_getenv( pamhdlr, "PRIVILEGES");
            const char* authStr = pam_getenv( pamhdlr, "AUTHENTICATED");
            if( authStr == NULL || privVal==NULL)
            {
                if(sessionless == false)
                    pam_close_session( pamhdlr, 0 );
                pam_end(pamhdlr, 0);
                ret = RFRC_PAM_PRIVILEGE;
            }
            else
            {
                int privileges = atoi(privVal);
                int localUserID = 0;										
                if(strcmp(authStr, "LOCAL") == 0)
                {
/*
remove
*/
                }
                else
                    RF_PRINT_DBG("doLogin (pid %d) LDAP user, privilieges:%d, name:%s\n", getpid(), privileges, displayname);

                set_cur_session((long)pamhdlr, aimSessionId, user, displayname, remoteip, privileges, localUserID, reasonCode, NULL);
                return ret;
            }

        }
        else
        {
            RF_PRINT_DBG("%s[%d] failed to open pam session. may exceed max sessions (rc=%d)\n",__FUNCTION__,__LINE__, rc);
            pam_end(pamhdlr, rc);
            ret = RFRC_PAM_SESSION_ERROR;
        }
    }
    else
    {
        //handle authenthicate failure to error code
        int is_ite = 0;
        if (family && !strcmp(family, "iteblade"))
            is_ite = 1;

        ret = rc;
        switch(pamerr)
        {
            case PAM_PERM_DENIED:
                ret = RFRC_AUTH_MISSING_LOGIN_PRIVI;
                break;
            case PAM_AUTH_ERR:
                if(!is_ite)
                    ret = RFRC_AUTH_WRONG_USER_PASSWD;
                break;
            default:
                break;
        }
    }

    //int locktime = GetUserFailTooManyTimes(user);
    return ret;

}

int PROTOCOL::do_logout(bool sessionless)
{
    int rc = RFRC_SUCCESS, ret;
    CURRENT_SESSION current = get_cur_session();
    pam_handle_t* pamHandle = (pam_handle_t*)(current.pam_handle);
    if( pamHandle != NULL )
    {
        RF_PRINT_DBG("logout of pam %d for user %s", current.pam_handle, current.display_name);
        if(sessionless == false && (ret = pam_close_session( pamHandle, 0 )) != PAM_SUCCESS)
        {
            RF_PRINT("failed to close session of pam %d for user %s", current.pam_handle, current.display_name);
            rc = RFRC_PAM_CLOSE_ERROR;
        }
        if(pam_end( pamHandle, ret) != PAM_SUCCESS)
        {
            RF_PRINT("failed to end pam %d for user %s", current.pam_handle, current.display_name);
            rc = RFRC_PAM_CLOSE_ERROR;
        }
    }

    return rc;
}

#ifdef __SIM_X86__

int PROTOCOL::do_login_x86(char *service, char *user, char *pwd, char *family, char *remoteip, bool sessionless)
{
    //fake pam data
    map<string, string> account;
    account["USERID"] = "redf1sh";
    account["USERID0"] = "redf1sh0";
    account["USERID1"] = "redf1sh1";
    account["USERID2"] = "redf1sh2";
    static unsigned int pamhdlr_pool = 0x12345670;
    static unsigned int session_pool = 0x100;

    pam_handle_t* pamhdlr = NULL;
    int aimSessionId = -1;

    if(account.find(user) == account.end())
        return RFRC_PAM_ERROR;
    if(account[user].compare(pwd))
        return RFRC_PAM_ERROR;
    pamhdlr = (pam_handle_t*)pamhdlr_pool++;

    aimSessionId = SESSIONLESS_ID; //fix session id for sessionless
    if(sessionless == false)
    {
        aimSessionId = session_pool++;
    }

    int privileges = 2; //always supervisor
    int localUserID = (pamhdlr_pool%12);
    RF_PRINT_DBG("doLogin (pid %d) UserID:%d, privilieges:%d, name:%s\n", getpid(), localUserID, privileges, user);
    set_cur_session((long)pamhdlr, aimSessionId, user, user, remoteip, privileges, localUserID, 0, NULL);

    return RFRC_SUCCESS;
}

int PROTOCOL::do_logout_x86(bool sessionless)
{
    CURRENT_SESSION current = get_cur_session();
    pam_handle_t* pamHandle = (pam_handle_t*)(current.pam_handle);
    if( pamHandle != NULL )
    {
        RF_PRINT_DBG("logout of pam %d for user %s", current.pam_handle, current.display_name);
    }
    return RFRC_SUCCESS;
}

#endif



}}
