#ifndef __HIERRNO_HOMECLOUD_DOWNLOADX_H__
#define __HIERRNO_HOMECLOUD_DOWNLOADX_H__

#include "../hierrno.h"

/*
0x10: etm_api_miss
0x11: etm_not_running
0x12: etm_no_response
*/
#define HIERRNO_HOMECLOUD_DOWNLOADX_etm_api_miss    (HIERRNO_HOMECLOUD_DOWNLOADX | 0x10) //hiwifi.etm 模块不存在
#define HIERRNO_HOMECLOUD_DOWNLOADX_etm_not_running (HIERRNO_HOMECLOUD_DOWNLOADX | 0x11) //etm 未运行
#define HIERRNO_HOMECLOUD_DOWNLOADX_etm_no_response (HIERRNO_HOMECLOUD_DOWNLOADX | 0x12) //etm 没有回应


#endif

