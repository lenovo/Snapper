//---------------------------------------------------------------------
// <copyright file="cache_common.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#ifndef __CACHE_COMMON_H__
#define __CACHE_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_REFRESH_BITS      128
#define MAX_REFRESH_BYTES     (MAX_REFRESH_BITS/8)

//data types mapped to bit number
enum refresh_data_type
{
    REFRESH_RESC_SESSION         = 0x0,
    REFRESH_RESC_TASK,
    REFRESH_TBL_IPMIPROP_ADC,
    REFRESH_TBL_IPMIPROP_V2_FWTBL,

    REFRESH_TBL_STORAGE,
    REFRESH_TBL_NVME,
    REFRESH_TBL_VPDFRU,
    REFRESH_TBL_CPU,

    //8
    REFRESH_TBL_MEM,
    REFRESH_TBL_PCI,
    REFRESH_TBL_PCINET,
    REFRESH_TBL_PCIGPU,

    REFRESH_TBL_PCICHIP,
    REFRESH_TBL_PCIBRG,
    REFRESH_TBL_PCICFG,
    REFRESH_TBL_PCIPORT_LOGIC,

    //16
    REFRESH_TBL_PCIPORT_PHY,
    REFRESH_TBL_PCIPORT_STAT,
    REFRESH_TBL_PCIPORTS,
    REFRESH_TBL_EVENTDEST,

    REFRESH_AIM_EVENTLOG,
    REFRESH_AIM_VPDFRU,
    REFRESH_AIM_VPDCOMP,
    REFRESH_AIM_OSINET,

    //24
    REFRESH_RESC_VMDISK,
    REFRESH_ADAM_NETPROTO,
    REFRESH_ADAM_SERVERPROP,
    REFRESH_ADAM_CLOCK,

    REFRESH_ADAM_SECURITY_CFG,
    REFRESH_ADAM_WEBGUI_CFG,
    REFRESH_ADAM_ALERT_RECIPIENTS,
    REFRESH_PROCSYNC_VPDD,

    //32
    REFRESH_INOTIFY_NETWORK,
    REFRESH_INOTIFY_BIOS,
    REFRESH_INOTIFY_BIOS_PENDING,
    REFRESH_INOTIFY_FOD,

    //40
    REFRESH_TBL_ROLE = 40,
    REFRESH_TBL_USER_ROLE_MAP,

    REFRESH_MAX = MAX_REFRESH_BITS
};


#ifdef __cplusplus
};
#endif

#endif


