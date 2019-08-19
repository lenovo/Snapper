#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#include <jwt.h>
#include "base64.h"
#include "rf_jwt.h"

#define JWT_KEY    "snapper-jwt.key"
#define JWT_ISS    "lenovo.com"
#define JWT_SUB    "Snapper"

// 128 bits key, 128 bits vector of AES
#define AES_KEY    "rf.token.aes.key"
#define AES_IV     "rf.token.aes.vec"

/*
encode like 
0eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpYXQiOjE1MTY4MTk3NzEsImlzcyI6Imxlbm92by5jb20iLCJzdWIiOiJTbmFwcGVyIn0.jRxukFo71R1xLQUAj4PirNdehYgAaoOFyA_8uW66I9Q
*/
char *rf_jwt_encode(char *uuid)
{
    jwt_t *jwt = NULL;
    int ret = 0;
    time_t cur_t = time(NULL);
    unsigned char key256[32] = JWT_KEY;
    char *out;

    if(!uuid)
        return NULL;
    if(strlen(uuid) > MAX_UUID_STR)
        uuid[MAX_UUID_STR] = 0;

    ret = jwt_new(&jwt);
    if(ret)
        return NULL;

    ret += jwt_set_alg(jwt, JWT_ALG_HS256, key256, strlen((const char *)key256));
    ret += jwt_add_grant_int(jwt, "iat", cur_t);
    ret += jwt_add_grant(jwt, "iss", JWT_ISS);
    ret += jwt_add_grant(jwt, "sub", JWT_SUB);
    ret += jwt_add_grant(jwt, "ref", uuid);
    if(ret)
    {
        jwt_free(jwt);
        return NULL;
    }

    out = jwt_encode_str(jwt);
    if(jwt)
        jwt_free(jwt);
    return out;
}

int rf_jwt_decode(char *token, char *uuid_o)
{
    jwt_t *jwt = NULL;
    int ret = 0;
    unsigned char key256[32] = JWT_KEY;
    const char *val;

    ret = jwt_decode(&jwt, token, key256, strlen((const char *)key256));    
    if(!ret && (val=jwt_get_grant(jwt, "iss")) != NULL)
    {
        //printf("iss:%s\n", val);
        if(strcmp(val, JWT_ISS))
            ret = -1;
    }
    if(!ret && (val=jwt_get_grant(jwt, "sub")) != NULL)
    {
        //printf("sub:%s\n", val);
        if(strcmp(val, JWT_SUB))
            ret = -1;
    }

    if(!ret && (val=jwt_get_grant(jwt, "ref")) != NULL && uuid_o != NULL)
    {
        //printf("ref:%s\n", val);
        strncpy(uuid_o, val, MAX_UUID_STR);
    }
    if(jwt)
        jwt_free(jwt);
    return ret;
}

/* dump like
{
    "typ": "JWT",
    "alg": "HS256"
}
.
{
    "iat": 1516819771,
    "iss": "lenovo.com",
    "sub": "Snapper"
}
*/
char *rf_jwt_dump(char *token)
{
    jwt_t *jwt = NULL;
    int ret = 0;
    unsigned char key256[32] = JWT_KEY;
    char *out;

    ret = jwt_decode(&jwt, token, key256, strlen((const char *)key256));    
    if(ret)
        return NULL;

    out = jwt_dump_str(jwt, 1);

    if(jwt)
        jwt_free(jwt);
    return out;
}

char *rf_auth_token_enc(char *uuid)
{
    int len = 0;
    int ciphertext_len = 0;
    int plaintext_len = 0;
    unsigned char *aes_key = (unsigned char *)AES_KEY;
    unsigned char *aes_iv  = (unsigned char *)AES_IV;
    unsigned char *plaintext = (unsigned char *)rf_jwt_encode(uuid);
    unsigned char *ciphertext = NULL;
    char *base64_token = NULL;
    EVP_CIPHER_CTX ctx;

    if(plaintext == NULL)
        return NULL;
    plaintext_len = strlen((char *)plaintext);
    ciphertext = malloc(MAX_AUTH_TOKEN_STR);

    EVP_CIPHER_CTX_init(&ctx);
    if (!EVP_EncryptInit(&ctx, EVP_aes_128_cbc(), aes_key, aes_iv))
    {
        printf("%s - EVP_EncryptInit failed: %s\n", __FUNCTION__, ERR_error_string(ERR_get_error(), NULL));
        goto CLEAN;
    }
    if (!EVP_EncryptUpdate(&ctx, ciphertext, &len, plaintext, plaintext_len))
    {
        printf("%s - EVP_EncryptUpdate failed: %s\n", __FUNCTION__, ERR_error_string(ERR_get_error(), NULL));
        goto CLEAN;
    }
    ciphertext_len = len;

    if (!EVP_EncryptFinal(&ctx, ciphertext+len, &len))
    {
        printf("%s - EVP_EncryptFinal failed: %s\n", __FUNCTION__, ERR_error_string(ERR_get_error(), NULL));
        goto CLEAN;
    }
    ciphertext_len += len;

    base64_token = malloc(MAX_AUTH_TOKEN_STR);
    jwt_Base64encode(base64_token, (const char *)ciphertext, ciphertext_len);
    printf("jwt plaintext:\n%s\n", plaintext);
    printf("auth token:\n%s\n", base64_token);

CLEAN:
    EVP_CIPHER_CTX_cleanup(&ctx);
    if(plaintext)
        free(plaintext);

    if(ciphertext)
        free(ciphertext);

    return base64_token;    
}

int rf_auth_token_dec(char *token, char *uuid_o)
{
    int ret = -1;
    int len = 0;
    int plaintext_len = 0;
    unsigned char *plaintext = NULL;
    unsigned char *ciphertext = NULL;
    int ciphertext_len = 0;
    unsigned char *aes_key = (unsigned char *)AES_KEY;
    unsigned char *aes_iv  = (unsigned char *)AES_IV;
    EVP_CIPHER_CTX ctx;

    if(token == NULL || strlen(token) == 0 || strlen(token) > 512) // assume < 512. otherwise overflow possibly
        return -1;
    ciphertext = malloc(MAX_AUTH_TOKEN_STR);
    ciphertext_len = jwt_Base64decode((char *)ciphertext, token);

    plaintext = malloc(MAX_AUTH_TOKEN_STR);
    memset(plaintext, 0, MAX_AUTH_TOKEN_STR);

    EVP_CIPHER_CTX_init(&ctx);
    EVP_CIPHER_CTX_set_padding(&ctx, 0);
    if (!EVP_DecryptInit(&ctx, EVP_aes_128_cbc(), aes_key, aes_iv))
    {
        printf("%s - EVP_DecryptInit failed: %s\n", __FUNCTION__, ERR_error_string(ERR_get_error(), NULL));
        goto DONE;
    }
    if (!EVP_DecryptUpdate(&ctx, plaintext, &len, ciphertext, ciphertext_len))
    {
        printf("%s - EVP_DecryptUpdate failed: %s\n", __FUNCTION__, ERR_error_string(ERR_get_error(), NULL));
        goto DONE;
    }
    plaintext_len = len;

    if (!EVP_DecryptFinal(&ctx, plaintext+len, &len))
    {
        printf("%s - EVP_DecryptFinal failed: %s\n", __FUNCTION__, ERR_error_string(ERR_get_error(), NULL));
        goto DONE;
    }
    plaintext_len += len;
    plaintext[plaintext_len] = 0;

    ret = rf_jwt_decode((char *)plaintext, uuid_o);
    printf("jwt plaintext dec: %d\n%s\n", ret, (char *)plaintext);

DONE:
    EVP_CIPHER_CTX_cleanup(&ctx);

    if(ciphertext)
        free(ciphertext);

    if(plaintext)
        free(plaintext);

    return ret;
}


