//---------------------------------------------------------------------
// <copyright file="protocol.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once
#include "sessions.h"
#include <string.h>

namespace snapper { namespace service
{
#define R_CHGPWD_EXPIRED        1
#define R_CHGPWD_FORCE          2
class PROTOCOL
{
public:
    static int AUTH_BASIC;
    static int AUTH_SESSION;
    static int IDENT_SESSION;
    static CURRENT_SESSION cur_session;

public:
    static std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    static std::string base64_decode(std::string const& encoded_string);

    static int do_authenticate( char *service, char *user, char *pwd, char *remoteip, void **pam_handle, char **displayname, int *pam_err );
    static int do_login(char *service, char *user, char *pwd, char *family, char *remoteip, bool sessionless);
    static int do_logout(bool sessionless);
#ifdef __SIM_X86__
    static int do_login_x86(char *service, char *user, char *pwd, char *family, char *remoteip, bool sessionless);
    static int do_logout_x86(bool sessionless);
#endif

    static void set_cur_session(int handle, int aimid, char *loginname, char *displayname, char *remoteip, int privil, int uid, int pwdreason, char *orig);
    static CURRENT_SESSION & get_cur_session();
    static void clear_cur_session();

    static int avail_sessions_num();
    static std::vector<unsigned int> session_instances();
    static int add_new_session(CURRENT_SESSION &sess_in, string &token_out);
    static int open_session(char *session_token);
    static int delete_session(string sid);
    static int session_info(unsigned int slot, char *username, int *priv, char *sid, char *remoteip);

private:
    static const std::string base64_chars;
    static inline bool is_base64(unsigned char c) 
    {
          return (isalnum(c) || (c == '+') || (c == '/'));
    }

};

}}
