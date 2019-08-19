/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#ifndef __RF_ERR_CODE_H
#define __RF_ERR_CODE_H

/* 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

typedef enum
{
/*************************************************
* common error code: 
*/

RFRC_SUCCESS                   = 0,
RFRC_FAILURE                   = 1,
RFRC_INVALID_PARAMS            = 2,
RFRC_INTERNAL_ERR              = 3,
RFRC_EXCEPTION                 = 4,
RFRC_ODATA_SEG                 = 5,
RFRC_AUTH_FAILED               = 6,
RFRC_METHOD_NOT_ALLOWED        = 7,
RFRC_DATA_NOT_FOUND            = 8,
RFRC_NOT_IMPLEMENTED           = 9,
RFRC_OUT_OF_RANGE              = 10,
RFRC_BUSY_WAIT                 = 11,
RFRC_INVALID_HEADER            = 12,
RFRC_INSUFFICIENT_PRIVILEGE    = 13,


/*************************************************
* data interface mgr error code: 100 - 
*/
RFRC_ADAM_GET_ERROR            = 100,
RFRC_AIM_GET_ERROR             = 101,
RFRC_DB_GET_ERROR              = 102,
RFRC_DB_SET_ERROR              = 103,
RFRC_ADAM_SET_ERROR            = 104,
RFRC_AIM_SET_ERROR             = 105,
RFRC_META_XML_ERROR            = 106,
RFRC_FUNC_GET_ERROR            = 107,
RFRC_FUNC_SET_ERROR            = 108,
RFRC_PROP_GET_ERROR            = 109,
RFRC_PROP_SET_ERROR            = 110,


/*************************************************
* authentication component error code: 150 - 200
*/
RFRC_PAM_ERROR                 = 150,
RFRC_PAM_ACCMGMT_FAILURE       = 151,
RFRC_PAM_AUTHTOK_REQD          = 152,
RFRC_PAM_PRIVILEGE             = 153,
RFRC_PAM_SESSION_ERROR         = 154,
RFRC_PAM_CLOSE_ERROR           = 155,

RFRC_AUTH_REQ_CHANGE_PASSWORD  = 160,
RFRC_AUTH_MISSING_LOGIN_PRIVI  = 161,
RFRC_AUTH_WRONG_USER_PASSWD    = 162,


/*************************************************
* fod function error code: 300 - 350
*/
RFRC_FOD_GETKEY_FAILURE        = 300,
RFRC_FOD_FOPEN_ERROR           = 301,
RFRC_FOD_KEYTYPE_NOTALLOW      = 302,
RFRC_FOD_IPMI_ERROR            = 303,
RFRC_FOD_IMPORT_ERROR          = 304,
RFRC_FOD_INVALID_INST          = 305,
RFRC_FOD_NO_KEY                = 306,
RFRC_FOD_EXCEPTION             = 307,
RFRC_FOD_EXPORT_ERROR          = 308,
RFRC_FOD_SYSCALL_ERROR         = 309,
RFRC_FOD_IMPORT_MT_ERROR          = 310,
RFRC_FOD_IMPORT_SN_ERROR          = 311,
RFRC_FOD_IMPORT_SIG_ERROR         = 312,
RFRC_FOD_IMPORT_EXPIRED_ERROR     = 313,
RFRC_FOD_IMPORT_USAGE_LIMIT_ERROR = 314,

/*************************************************
* vm/rdoc function error code: 351 - 400
*/
RFRC_VM_NO_SLOT             = 352,
RFRC_VM_MNTPOINT_ERR        = 353,
RFRC_VM_MNTFILE_ERR         = 354,
RFRC_VM_UNMOUNT_ERR         = 355,
RFRC_VM_RM_MOUNT_ERR        = 356,
RFRC_VM_RM_GET_IMG_ERR      = 357,

RFRC_HTML5_GET_IMG_ERR      = 361,

RFRC_RDOC_NO_SLOT           = 372,
RFRC_RDOC_DOWNLOAD_ERR      = 373,
RFRC_RDOC_GET_IMG_ERR       = 374,
RFRC_RDOC_MNTFILE_ERR       = 375,
RFRC_RDOC_UNMOUNT_ERR       = 376,

RFRC_KVM_SESSION_NUM_ERR    = 377,
RFRC_KVM_SESSION_LIST_ERR   = 378,
RFRC_KVM_SESSION_PREEMPT    = 379,
RFRC_KVM_SESSION_PREEMPTSTAT= 380,
RFRC_KVM_SESSION_CANCEL_PREEMPT  = 381,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          

RFRC_SCREEN_CAP_INTERNAL_ERR  = 390,
RFRC_SCREEN_CAP_NO_VIDEO_SIG  = 391,
RFRC_SCREEN_CAP_TIMEOUT       = 392,
RFRC_SCREEN_CAP_INPROGRESS    = 393,
RFRC_SCREEN_CAP_OUTOFMEM      = 394,

/*************************************************
* User  error code: 760 - 800
*/
RFRC_USER_ALREADY_EXIST                  = 760,
RFRC_USER_NOT_EXIST                      = 761,
RFRC_USER_AUTH_LEVEL_INVALID             = 762,
RFRC_USER_PRIVILEGES_INSUFFICIENT        = 763,
RFRC_USER_SM_GET_SNMPData_FAILED         = 764,
RFRC_USER_SM_SET_SNMPData_FAILED         = 765,
RFRC_USER_SM_GET_USERPW_FAILED           = 766,
RFRC_USER_SM_GET_USER_BY_IDPW_FAILED     = 767,
RFRC_USER_SM_SET_USERPW_FAILED           = 768,
RFRC_USER_SM_GET_USER_BY_NAME_FAILED     = 769,
RFRC_USER_SM_CLEAR_USER_FAILED           = 770,
RFRC_USER_GET_ADAM_DATA_FAILED           = 771,
RFRC_USER_UPDATE_ADAM_DATA_FAILED        = 772,
RFRC_USER_DELETE_ADAM_DATA_FAILED        = 773,
RFRC_USER_ID_INVALID                     = 774,
RFRC_USER_KEY_FILE_NOT_EXIST             = 775,
RFRC_USER_KEY_FILE_OPEN_FAILURE          = 776,
RFRC_USER_KEY_FILE_WRITE_EXIST           = 777,
RFRC_USER_ADAM_SET_FAILED                = 778,
RFRC_USER_ADAM_GET_FAILED                = 779,
RFRC_USER_KEY_INSTALL_FAILED             = 780,
RFRC_USER_KEY_ID_INVALID                 = 781,
RFRC_USER_SM_PASSWORD_WEAK	   		     = 782,
RFRC_USER_SM_PASSWORD_AGE_INVALID		 = 783,
RFRC_USER_SM_PASSWORD_REUSED             = 784,    
RFRC_USER_SM_PASSWORD_CHANGE_NOT_ALLOWED = 785,
RFRC_USER_SM_PASSWORD_CHANGE             = 786,
RFRC_USER_SM_PASSWORD_INTERVAL_INVALID   = 787,
RFRC_USER_SSH_KEY_INVALID_DATA           = 788,
RFRC_USER_SSH_KEY_USER_NOT_EXIST         = 789,
RFRC_USER_SSH_KEY_OVER_MAX_INPUT_LEN     = 790,
RFRC_USER_SSH_KEY_INVALID_KEY_INDEX      = 791,
RFRC_USER_SSH_KEY_SYS_KEY_FULL           = 792,
RFRC_USER_SSH_KEY_USR_KEY_FULL           = 793,
RFRC_USER_SSH_KEY_WRONG_KEY_FORMAT       = 794,
RFRC_USER_SSH_KEY_WRITE_KEY_ERR_FORMAT   = 795,
RFRC_USER_SSH_KEY_WRONG_ALLOWLIST_FORMAT = 796,
RFRC_USER_GET_ROLE_LIST_FAILURE          = 797,
RFRC_USER_CREATE_ROLE_NAME_DUPLICATE     = 798,
RFRC_USER_ROLE_NOT_CHANGABLE             = 799,
RFRC_USER_ROLE_NAME_NOT_FOUND            = 800,
RFRC_USER_ROLE_FUNC_FAILURE              = 801,
RFRC_USER_NO_ROLE_SLOT                   = 802,
RFRC_USER_NO_USER_SLOT                   = 803,
RFRC_USER_ROLE_IS_IN_USE                 = 804,


/*************************************************
* backup/restore  error code: 810-820
*/
RFRC_RESTORE_PASSPHRASE_MISMATCH         = 810,
RFRC_RESTORE_FILE_NOT_EXIST              = 811,
RFRC_RESTORE_AIM_NOT_AVAILABLE           = 812,
RFRC_RESTORE_TRANSFER_STATUS_NOT_OK      = 813,
RFRC_RESTORE_FAILED                      = 814,

/*************************************************
* Get/Set BiosAttributes  error code: 830-840
*/
RFRC_BIOS_ATTRIBUTE_NOT_EXIST            = 830,
RFRC_BIOS_ATTRIBUTE_VALUE_ERROR          = 831,


} RFEngineErrorCode;




#endif // __RF_ERR_CODE_H

