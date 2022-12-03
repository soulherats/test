/*******************************************************************************
  Copyright (C), 2015-2050, GeekGeek Tech. Co., Ltd.
  Description: himsg common
  History   :
    1. 2015-11-24 hnan create

  Others:
*******************************************************************************/ 
#ifndef __HIMSG_COMMON_H__
#define __HIMSG_COMMON_H__

#include <hierrno/service/himsg.h>

#ifndef HIMSG_TRUE
#define HIMSG_TRUE   (1)
#endif

#ifndef HIMSG_FALSE 
#define HIMSG_FALSE  (!HIMSG_TRUE)
#endif


#define HIMSG_ADDR_HIMSGD        "/var/run/himsg_sock"
//#define HIMSG_ADDR_HIMSGD        "/home/hnan/work/himsg/himsg_sock"
#define HIMSG_ADDR_MAX_LENGTH    64

#define HIMSG_INTEREST_DIR_EVENT_SHELL        "/etc/himsg/hotplug"
//#define HIMSG_INTEREST_DIR_EVENT_SHELL        "/home/hnan/work/himsg/hotplug"

#define HIMSG_EVENT_EXEC_SHELL        "/etc/himsg/himsg-call"
//#define HIMSG_EVENT_EXEC_SHELL        "/home/hnan/work/himsg/himsg-call"

#define HIMSG_TIMEOUT  3000

typedef enum
{
    HIMSG_RET_SUCCESS                = HIERRNO_SUCCESS,
    HIMSG_RET_INVALID_ARGUMENTS      = HIERRNO_RET_INVALID_ARGUMENTS,
    HIMSG_RET_INTERNAL_ERROR         = HIERRNO_RET_INTERNAL_ERROR,
    HIMSG_RET_RESOURCE_EXCEEDED      = HIERRNO_RET_RESOURCE_EXCEEDED,
    HIMSG_RET_DISCONNECTED           = HIERRNO_RET_DISCONNECTED,
    HIMSG_RET_TIMED_OUT              = HIERRNO_RET_TIMED_OUT,
    HIMSG_RET_DUPLICATE_REGISTER     = HIERRNO_RET_DUPLICATE_REGISTER,
    HIMSG_RET_UNINITIALIZED          = HIERRNO_RET_UNINITIALIZED,
    HIMSG_RET_CALLBACK_NOT_FOUND     = HIERRNO_RET_CALLBACK_NOT_FOUND,
    HIMSG_RET_UNKNOWN_TYPE           = HIERRNO_RET_UNKNOWN_TYPE,
    HIMSG_RET_OBJECT_NOT_FOUND       = HIERRNO_RET_OBJECT_NOT_FOUND,
    HIMSG_RET_EVENT_NOT_FOUND        = HIERRNO_RET_EVENT_NOT_FOUND
} himsg_ret_t;

#endif
