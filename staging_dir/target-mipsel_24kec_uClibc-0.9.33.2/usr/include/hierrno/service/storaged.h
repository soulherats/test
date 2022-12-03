#ifndef __HIERRNO_SERVICE_STORAGED_H__
#define __HIERRNO_SERVICE_STORAGED_H__

#include "../hierrno.h"

/*
0x10: need action.
0x13: wrong device.
0x11: need device.
0x12: no such device.
0x14: instance already running
*/
#define HIERRNO_SERVICE_STORAGED_need_action                (HIERRNO_SERVICE_STORAGED | 0x10) //需要 action 参数
#define HIERRNO_SERVICE_STORAGED_need_device                (HIERRNO_SERVICE_STORAGED | 0x11) //需要 device 参数
#define HIERRNO_SERVICE_STORAGED_no_such_device             (HIERRNO_SERVICE_STORAGED | 0x12) //没有这个 device
#define HIERRNO_SERVICE_STORAGED_wrong_device               (HIERRNO_SERVICE_STORAGED | 0x13) //device 参数错误
#define HIERRNO_SERVICE_STORAGED_instance_already_running   (HIERRNO_SERVICE_STORAGED | 0x14) //已有实例在运行

/*
0x50: no storaged on this model
*/
#define HIERRNO_SERVICE_STORAGED_model_no_storaged          (HIERRNO_SERVICE_STORAGED | 0x50) //这个机型没有 storaged

#endif

