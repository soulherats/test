#ifndef __HIERRNO_SERVICE_APMGR_H__
#define __HIERRNO_SERVICE_APMGR_H__

#include "../hierrno.h"

#define HIERRNO_SERVICE_APMGR_FAILED                    (HIERRNO_SERVICE_APMGR | 0x1) //未知错误
#define HIERRNO_SERVICE_APMGR_NO_ENOUGH_MEMORY          (HIERRNO_SERVICE_APMGR | 0x2) //内存不足
#define HIERRNO_SERVICE_APMGR_WIRELESS_CONFIG_ERROR     (HIERRNO_SERVICE_APMGR | 0x3) //无线配置失败
#define HIERRNO_SERVICE_APMGR_ARGUMENT_ERROR            (HIERRNO_SERVICE_APMGR | 0x4) //参数错误
#define HIERRNO_SERVICE_APMGR_LOAD_WIRELESS_ERROR       (HIERRNO_SERVICE_APMGR | 0x5) //加载无线配置失败
#define HIERRNO_SERVICE_APMGR_FASTLINK_LIST_FAILED      (HIERRNO_SERVICE_APMGR | 0x06) //取得快连设备列表错误
#define HIERRNO_SERVICE_APMGR_FASTLINK_NOT_FOUND        (HIERRNO_SERVICE_APMGR | 0x07) //快连设备没有找到
#define HIERRNO_SERVICE_APMGR_FASTLINK_ALLOW_FAILED     (HIERRNO_SERVICE_APMGR | 0x08) //快连设备准入失败
#define HIERRNO_SERVICE_APMGR_SCAN_2G_START_FAILED      (HIERRNO_SERVICE_APMGR | 0x09) //开启2G扫描失败
#define HIERRNO_SERVICE_APMGR_SCAN_5G_START_FAILED      (HIERRNO_SERVICE_APMGR | 0x0a) //开启5G扫描失败
#define HIERRNO_SERVICE_APMGR_SCAN_RESULT_FAILTER_ERROR (HIERRNO_SERVICE_APMGR | 0x0b) //过滤扫描结果失败
#define HIERRNO_SERVICE_APMGR_SET_UPLINK_FAILED         (HIERRNO_SERVICE_APMGR | 0x0c) //设置无线上行链路失败
#define HIERRNO_SERVICE_APMGR_NOT_SUPPORT               (HIERRNO_SERVICE_APMGR | 0x0d) //功能不支持
#define HIERRNO_SERVICE_APMGR_FASTLINK_DEV_ALOWING      (HIERRNO_SERVICE_APMGR | 0x0e) //请稍后再试,有设备准入中

#endif