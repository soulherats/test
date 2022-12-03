#ifndef __HIERRNO_WIRELESS_H__
#define __HIERRNO_WIRELESS_H__

#include "../hierrno.h"

/*
0x01: Unknown Error
0x02: Agument Error
0x03: Netlink failed
0x04: Read failed
*/

#define HIERRNO_WIRELESS_ERR_UNKNOWN			(HIERRNO_WIRELESS | 0x01) //未知错误
#define HIERRNO_WIRELESS_ERR_ARGUMENT			(HIERRNO_WIRELESS | 0x02) //参数错误
#define HIERRNO_WIRELESS_ERR_NLWIFI				(HIERRNO_WIRELESS | 0x03) //设置失败
#define HIERRNO_WIRELESS_ERR_LOAD				(HIERRNO_WIRELESS | 0x04) //读取失败

#endif
