//---------------------------------------------------------------------
// <copyright file="sessions.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once

namespace snapper { namespace service
{

class CURRENT_SESSION
{
public:
    int pam_handle;
    int aim_sessionid;
    char login_name[64];
    char display_name[64];
    int aim_privileges;
    int local_userid;
    char remoteip[64];
    char hdr_orig[64];
    int reason_chgpwd;

    void clear()
    {
        pam_handle = 0;
        aim_sessionid = 0;
        login_name[0] = 0;
        display_name[0] = 0;
        aim_privileges = 0;
        local_userid = 0;
        remoteip[0] = 0;
        hdr_orig[0] = 0;
        reason_chgpwd = 0;
    }
};

//TODO session based login


}}
