/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#ifndef __RF_TYPES_H
#define __RF_TYPES_H

/*
#ifdef TRUE
#undef TRUE
#endif
#define TRUE 0x01

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0x00
*/

#define BUILD_RC(rc)  Py_BuildValue("{s:i}","return",rc)
#define BUILD_RESP(resp,resphdrs,httpcode,err)  Py_BuildValue("{s:s,s:s,s:I,s:I}","response",resp,"headers",resphdrs,"http_status",httpcode,"error",err)
/*
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int  uint32_t;
*/

#endif // __RF_TYPES_H
