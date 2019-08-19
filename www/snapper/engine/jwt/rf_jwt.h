#ifndef __RF_JWT_H
#define __RF_JWT_H

#ifdef __cplusplus
extern  "C" {
#endif

#define MAX_AUTH_TOKEN_STR 1024
#define MAX_UUID_STR 48

char *rf_jwt_encode(char *uuid);
int rf_jwt_decode(char *token, char *uuid_o);
char *rf_jwt_dump(char *token);

char *rf_auth_token_enc(char *uuid);
int rf_auth_token_dec(char *token, char *uuid_o);

#ifdef __cplusplus
}
#endif


#endif // __RF_JWT_H

