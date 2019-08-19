//---------------------------------------------------------------------
// <copyright file="ClassCommon.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

namespace snapper { namespace providers 
{
#define STD_LOG         "StandardLog"  //keep compatibility with Purley GA
#define EVENT_LOG       "EventLog"
#define AUDIT_LOG       "AuditLog"
#define ACTIVE_LOG      "ActiveLog"

#define FW_TYPE_UEFI        "UEFI"
#define FW_TYPE_UEFI_P      "UEFI-Primary"
#define FW_TYPE_UEFI_B      "UEFI-Backup"
#define FW_TYPE_BMC_ACT     "BMC-Active"
#define FW_TYPE_BMC_P       "BMC-Primary"
#define FW_TYPE_BMC_B       "BMC-Backup"
#define FW_TYPE_LXPM        "LXPM"
#define FW_TYPE_DRVWIN      "LXPMWindowsDrivers"
#define FW_TYPE_DRVLN       "LXPMLinuxDrivers"

#define FW_BUNDLE   "Bundle"
#define FW_ONBOARD  "ob"
#define FW_SLOT     "slot"
#define FW_PSU      "PSU"


#define NO_KEY           "@nokey_"
#define ACCKEY_CHASSIS   "1@Chassis"
#define ACCKEY_CS        "1@ComputerSystem"
#define ACCKEY_MANAGER   "1@Manager"

#define EVENTRETRY_MAX      10
#define EVENTINTERVAL_MAX   100

#define PREFIX_EXT         "EXT"
#define PREFIX_RDOC        "RDOC"
#define PREFIX_VMREMOTE    "Remote"
#define RDOC_VDISK_BASE    32

#define AIM_GENERATE_TEST_EVT   "rf_gen_test_event"

}}

