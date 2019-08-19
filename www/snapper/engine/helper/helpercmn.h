#ifndef __HELPER_CMN_H
#define __HELPER_CMN_H

#ifdef __cplusplus
extern  "C" {
#endif

#define HELPER_LOG(fmt, args...)    \
do{                                    \
    printf(fmt, ## args);\
} while(0)

//////virtual media//////////
enum vmedia_cmd
{
    CMD_VM_CONNECT        = 1,
    CMD_VM_DISCONNECT     = 2,
    CMD_VM_MOUNT_ALL      = 3,
    CMD_VM_UMOUNT         = 4,

    CMD_RDOC_DOWNLOAD     = 5,
    CMD_RDOC_REMOVE       = 6,
    CMD_RDOC_MOUNT_ALL    = 7,
    CMD_RDOC_UMOUNT       = 8,
    CMD_RDOC_ADD_CFGFILE        = 9,
    CMD_RDOC_MOUNT_FROM_CFGFILE = 10,
    CMD_RDOC_UMOUNT_ALL   = 11,
    CMD_RDOC_OEM_MOUNT_FROM_URL = 12,

    CMD_MAX,
};


enum {
    RDMOUNT_SUPPORT_PROTOCOL_SAMBA = 0,
    RDMOUNT_SUPPORT_PROTOCOL_NFS = 1,
    RDMOUNT_SUPPORT_PROTOCOL_HTTP = 2,
    RDMOUNT_SUPPORT_PROTOCOL_HTTPS = 3,
    RDMOUNT_SUPPORT_PROTOCOL_FTP = 4,
    RDMOUNT_SUPPORT_PROTOCOL_SFTP = 5,
    RDMOUNT_SUPPORT_PROTOCOL_WEBUPLOAD = 6,
    RDMOUNT_SUPPORT_PROTOCOL_HTTPFUSE = 7,
};



//////firmware update//////////
typedef struct _fw_update_oem
{
    unsigned int fmerr;//fm::transaction::errors
    unsigned int fwtype;
    char target[64];
}fw_update_oem;

enum fw_target_type
{
    TARGET_T_PCI = 2,
    TARGET_T_PSU = 3,
//    TARGET_T_STLB = 4,
//    TARGET_T_M2   = 5,
    TARGET_T_BMC = 10,
    TARGET_T_UEFI = 11,
    TARGET_T_LXPM = 12,
    TARGET_T_WDRV = 13,
    TARGET_T_LDRV = 14,
};

#define PRIMARY_BANK    "primary"
#define BACKUP_BANK     "backup"


#ifdef __cplusplus
}
#endif

#endif // __HELPER_CMN_H
