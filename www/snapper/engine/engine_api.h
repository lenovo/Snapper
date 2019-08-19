/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#ifndef _ENGINE_API_H
#define _ENGINE_API_H

#ifdef __cplusplus
extern  "C" {
#endif

#define RESP_HEADERS_LEN    2048
int snapper_init_engine(char *dir);
int sse_add_destination(unsigned int types, char *desturl, char *ctx, char *prot, char *subtype, char *hdrs, char *msgids, char *res);
int sse_del_destination(int id);
int sse_query_destination(int destid);
int authen_handle(int method, int *authtype, const char *uri_path, const char *auth, const char * session_token, const char * ip);
char * snapper_request_handle(char *uri, int method, char *headers, char *body, int *httpcode, int *rc, char *resp_headers);
char * snapper_request_schema_handle(char *uri, int method, char *headers, char *body, int *httpcode, int *rc, char *resp_headers);
char * snapper_request_handle_non_auth(char *uri, int method, char *headers, char *body, int *httpcode, int *rc, char *resp_headers);
void snapper_refresh_topology();

#ifdef __cplusplus
}
#endif

#endif
