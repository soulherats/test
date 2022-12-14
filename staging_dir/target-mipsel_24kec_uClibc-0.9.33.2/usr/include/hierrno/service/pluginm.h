#ifndef __HIERRNO_SERVICE_HISCRIPT_H__
#define __HIERRNO_SERVICE_HISCRIPT_H__

#include "../hierrno.h"

#define HIERRNO_SERVICE_PLUGINM_SYSERR                  (HIERRNO_SERVICE_PLUGINM | 0x01) //系统错误
#define HIERRNO_SERVICE_PLUGINM_NOMEM                   (HIERRNO_SERVICE_PLUGINM | 0x02) //内存不足
#define HIERRNO_SERVICE_PLUGINM_INTERNAL                (HIERRNO_SERVICE_PLUGINM | 0x03) //内部错误
#define HIERRNO_SERVICE_PLUGINM_NOMETHOD                (HIERRNO_SERVICE_PLUGINM | 0x04) //没有此方法
#define HIERRNO_SERVICE_PLUGINM_INVARG                  (HIERRNO_SERVICE_PLUGINM | 0x05) //非法参数
#define HIERRNO_SERVICE_PLUGINM_NOTJSON                 (HIERRNO_SERVICE_PLUGINM | 0x06) //输入非JSON
#define HIERRNO_SERVICE_PLUGINM_NOPLUGIN                (HIERRNO_SERVICE_PLUGINM | 0x07) //没有此插件
#define HIERRNO_SERVICE_PLUGINM_TIMEOUT                 (HIERRNO_SERVICE_PLUGINM | 0x08) //操作超时
#define HIERRNO_SERVICE_PLUGINM_FS_EXIST                (HIERRNO_SERVICE_PLUGINM | 0x09) //文件冲突
#define HIERRNO_SERVICE_PLUGINM_STORAGED                (HIERRNO_SERVICE_PLUGINM | 0x0A) //存储管理器错误
#define HIERRNO_SERVICE_PLUGINM_MOUNTS                  (HIERRNO_SERVICE_PLUGINM | 0x0B) //挂载错误
#define HIERRNO_SERVICE_PLUGINM_METHOD_REGISTERED       (HIERRNO_SERVICE_PLUGINM | 0x0C) //方法重复注册
#define HIERRNO_SERVICE_PLUGINM_HIMSG                   (HIERRNO_SERVICE_PLUGINM | 0x0D) //Himsg错误
#define HIERRNO_SERVICE_PLUGINM_MANIFEST                (HIERRNO_SERVICE_PLUGINM | 0x0E) //manifest文件错误
#define HIERRNO_SERVICE_PLUGINM_REQNSAT                 (HIERRNO_SERVICE_PLUGINM | 0x0F) //不满足需求
#define HIERRNO_SERVICE_PLUGINM_ROMVNSAT                (HIERRNO_SERVICE_PLUGINM | 0x10) //系统版本不满足需求
#define HIERRNO_SERVICE_PLUGINM_NOSPACE                 (HIERRNO_SERVICE_PLUGINM | 0x11) //剩余空间不满足需求
#define HIERRNO_SERVICE_PLUGINM_NOSTORAGE               (HIERRNO_SERVICE_PLUGINM | 0x12) //存储设备不满足需求
#define HIERRNO_SERVICE_PLUGINM_INVSHARED               (HIERRNO_SERVICE_PLUGINM | 0x13) //非法共享文件夹
#define HIERRNO_SERVICE_PLUGINM_PLUGIN_BUSY             (HIERRNO_SERVICE_PLUGINM | 0x14) //插件忙
#define HIERRNO_SERVICE_PLUGINM_PLUGIN_WRONG_STATE      (HIERRNO_SERVICE_PLUGINM | 0x15) //插件处于错误状态
#define HIERRNO_SERVICE_PLUGINM_PLUGIN_NOSUPPORT        (HIERRNO_SERVICE_PLUGINM | 0x16) //插件不支持此操作
#define HIERRNO_SERVICE_PLUGINM_CGROUP                  (HIERRNO_SERVICE_PLUGINM | 0x17) //Cgroup错误
#define HIERRNO_SERVICE_PLUGINM_ETASKQ                  (HIERRNO_SERVICE_PLUGINM | 0x18) //任务队列错误
#define HIERRNO_SERVICE_PLUGINM_ECURL                   (HIERRNO_SERVICE_PLUGINM | 0x19) //cURL错误
#define HIERRNO_SERVICE_PLUGINM_BADPKG                  (HIERRNO_SERVICE_PLUGINM | 0x1A) //文件非插件安装包或已损坏
#define HIERRNO_SERVICE_PLUGINM_ESSL                    (HIERRNO_SERVICE_PLUGINM | 0x1B) //SSL错误
#define HIERRNO_SERVICE_PLUGINM_NOPERM                  (HIERRNO_SERVICE_PLUGINM | 0x1C) //插件没有此权限
#define HIERRNO_SERVICE_PLUGINM_EPSCRIPT                (HIERRNO_SERVICE_PLUGINM | 0x1D) //插件script脚本执行失败
#define HIERRNO_SERVICE_PLUGINM_EPAPI                   (HIERRNO_SERVICE_PLUGINM | 0x1E) //插件接口执行失败

#endif
