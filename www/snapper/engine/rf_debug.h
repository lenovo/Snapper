/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#ifndef __SNAPPER_DEBUG_H
#define __SNAPPER_DEBUG_H

//#include <syslog.h>
#ifdef __cplusplus
extern  "C" {
#endif


#define RF_LOGLVL_TRACE   3
#define RF_LOGLVL_INFO    2
#define RF_LOGLVL_WARN    1
#define RF_LOGLVL_ERROR   0

extern int g_engine_loglvl;

//#define trc_print(fmt, args...) trc_log(trace_webapp, fmt, ## args)

#define RF_PRINT_ERR(fmt, args...)     \
do{                                    \
    if(g_engine_loglvl >= RF_LOGLVL_ERROR){\
        printf(fmt, ## args);\
    }\
} while(0)


#define RF_PRINT_WARN(fmt, args...)    \
do{                                    \
    if(g_engine_loglvl >= RF_LOGLVL_WARN){\
        printf(fmt, ## args);\
    }\
} while(0)


#define RF_PRINT(fmt, args...)         \
do{                                    \
    if(g_engine_loglvl >= RF_LOGLVL_INFO){\
        printf(fmt, ## args);\
    }\
} while(0)


#define RF_PRINT_DBG(fmt, args...)     \
do{                                    \
    if(g_engine_loglvl >= RF_LOGLVL_TRACE){\
        printf(fmt, ## args);\
    }\
} while(0)



//#define PRT_EMERG(fmt, args...)      syslog(LOG_EMERG, "WebAPP(%s:%d:%s) "fmt, __FILE__, __LINE__, __FUNCTION__, ##args)


#ifdef __cplusplus
}
#endif

#endif // __SNAPPER_DEBUG_H
