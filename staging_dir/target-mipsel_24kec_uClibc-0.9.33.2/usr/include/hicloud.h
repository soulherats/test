/*
 * Copyright (C) 2016 Elite Co., Ltd.
 */
#ifndef _HICLOUD_H_
#define _HICLOUD_H_

#include <sys/shm.h>
#include <sys/types.h>
#include "himsg.h"
#include "himsg_common.h"
#include "codec.h"
#include "string.h"
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_REPLY_LEN 256*1024
#define SDK_ERRORNO 10000


int hicloud_call(const char *service, const char *method, const vbs_map_t *args, vbs_map_t *ctx, int timeout, vbs_map_t *reply);

int hicloud_send(const char *from, const char *exchange, vbs_map_t *args, vbs_map_t *opts);

#ifdef __cplusplus
}
#endif

#endif /* _HICLOUD_H_ */
