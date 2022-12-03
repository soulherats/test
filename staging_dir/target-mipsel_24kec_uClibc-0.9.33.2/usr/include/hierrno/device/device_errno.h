#ifndef _Device_Errno_
#define _Device_Errno_

#include "../hierrno.h"

#define HIERRNO_DEVICE_FAILED   (HIERRNO_DEVICE | 0x01) //未知错误
#define HIERRNO_DEVICE_ARGUMENT_ERROR   (HIERRNO_DEVICE | 0x02) //参数错误
#define HIERRNO_DEVICE_NOT_ENOUGH_MEMORY  (HIERRNO_DEVICE | 0x03) //没有足够系统资源
#define HIERRNO_DEVICE_EMPTY_DEVNAME	   (HIERRNO_DEVICE | 0x05) //设备名称不能为空
#define HIERRNO_DEVICE_TOOLONG_DEVNAME	   (HIERRNO_DEVICE | 0x06) //设备名称不能超过30个字符
#endif
