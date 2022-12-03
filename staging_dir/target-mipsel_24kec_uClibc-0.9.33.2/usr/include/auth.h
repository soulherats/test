/*
 * Copyright (c) 2013 Elite Co., Ltd.
 * Author: Hong Shen <sh@ikwcn.com>
 */

#ifndef AUTH_H_
#define AUTH_H_


#define TOKEN_LEN (32 + 1)
#define HWF_AUTH_TOKEN_MAX_LEN (99 + 1) // determined by auth server


#include <sys/types.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets a token from authentication server.
 *
 * @param app [in] string identifier of the client who calls this function
 * @param token [out] the space to hold the new token, at least TOKEN_LEN bytes
 *     are required, trailing '\0' is always included
 * @return the same as param token
 */
char* auth_get_token_v2(const char* app, char* token);

/*
 * Get a self-verification token from authentication servers.
 *
 * @app, the identify of caller.
 * @token, a buffer to hold a token, it MUST has a length of HWF_AUTH_TOKEN_MAX_LEN.
 *
 * return values:
 * On success, it returns a positive number to indicate the actual length of token, and token is copied into @token.
 * On failure, a negative number is returned which intimates an error code, @token is unpredictable.
 */
ssize_t auth_get_token_v3(const char *app, char *token);

/**
 * Gets a token from authentication server.
 *
 * @param app [in] string identifier of the client who calls this function
 * @param token [out] the space to hold the new token, at least TOKEN_LEN bytes
 *     are required, trailing '\0' is always included
 * @return the error code of failure, 0 if OK
 */
int auth_get_token_ex(const char* app, char* token);

/**
 * Gets the error message of the last time getting token.
 *
 * @return human readable error message
 */
char* auth_get_last_error();

/*
 */
int hmac_sha1_with_uuid(const char* buf, int buf_len, char* sha1_buf, int sha1_len);

#ifdef __cplusplus
}
#endif

#endif /* AUTH_H_ */
