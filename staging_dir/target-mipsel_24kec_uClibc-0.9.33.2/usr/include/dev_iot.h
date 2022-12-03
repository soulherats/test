#ifndef _DEV_IOT_H
#define _DEV_IOT_H

#include <libubox/kvlist.h>
#include <hierrno/device/iot_errno.h>


#define IOT_IP_MAXLEN 			16
#define IOT_MAC_MAXLEN 			20
#define IOT_VDNAME_MAXLEN 		32
#define IOT_ARGUMENT_MAXLEN  1024
#define IOT_DEVNAME_MAXLEN  	64
#define IOT_DEVID_MAXLEN		32
#define IOT_SSID_MAXLEN 		32
#define IOT_TYPE_MAXLEN			16
#define IOT_KEY_MAXLEN 			32
#define IOT_PRIVATE_KEY_MAXLEN    64
#define IOT_VALUE_MAXLEN 	        32
#define IOT_ADDR_MAXLEN			16
#define IOT_BUFFER_MAXLEN		1024
#define IOT_SAMEMAC_MAXIDCNT	256

#define IOT_AGING 3


#define Common_Value 0
#define Private_Value 1


#define Config_Param_Begin  "###"
#define Config_Param_End  ":::"

#define Key_Identify "key"
#define Value_Identify "value"
#define Trans_Identify "transfer_flag"

#define Identify_Len 16


#if (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4))
#   define UNUSED __attribute__((__unused__))
#else
#   define UNUSED
#endif

typedef enum
{
	IOT_ERR_SUCCESS 				= HIERRNO_SUCCESS,
	IOT_ERR_FAILED 					= HIERRNO_IOT_FAILED,
	IOT_ERR_ARGUMENT_ERROR			= HIERRNO_IOT_ARGUMENT_ERROR, 
	IOT_ERR_NOT_ENOUGH_MEMORY =HIERRNO_IOT_NOT_ENOUGH_MEMORY,
	IOT_ERR_EMPTY_DEVNAME=HIERRNO_IOT_EMPTY_DEVNAME,
	IOT_ERR_TOOLONG_DEVNAME=HIERRNO_IOT_TOOLONG_DEVNAME,
	IOT_ERR_NOT_FIND_IOT_VENDOR=HIERRNO_IOT_NOT_FIND_VENDOR,
	IOT_ERR_NOT_FIND_IOT_METHOD=HIERRNO_IOT_NOT_FIND_METHOD,
	IOT_ERR_PARAM_NO_KEY=HIERRNO_IOT_PARAM_NO_KEY,
	IOT_ERR_PARAM_NO_VALUE=HIERRNO_IOT_PARAM_NO_VALUE,
	IOT_ERR_MAX
}iot_err_t;


struct iot_info{
	int flag;
	int seq;
	char ip[IOT_IP_MAXLEN];
	char iot_id[IOT_DEVID_MAXLEN];
	char mac[IOT_MAC_MAXLEN];
	char dev_id[IOT_DEVID_MAXLEN];
	char name[IOT_DEVNAME_MAXLEN];
	char type[IOT_TYPE_MAXLEN];
	char vendor[IOT_VDNAME_MAXLEN];
	char group_id[IOT_DEVID_MAXLEN];
	char password[IOT_KEY_MAXLEN];
	char srcaddr[IOT_ADDR_MAXLEN];
	char dstaddr[IOT_ADDR_MAXLEN];
	int aging;  //老化次数
	char reserved[IOT_BUFFER_MAXLEN-sizeof(int)];
};

struct iot_driver_info {
	struct list_head	 list;
	char vendor_name[IOT_VDNAME_MAXLEN];
	int refcnt;
	void *handle;
	void *vendor_ops;
};

struct iot_vendor_info {
        char name[IOT_VDNAME_MAXLEN];
        int (*discover)(IN void *,OUT void *);
        int (*probe)(IN void *,OUT void *);
        struct key_value_list* (*get)(int *, const char *);
        int (*set)(const char *, const struct key_value_list *);
};

struct iot_param_info
{
    char common_key[IOT_KEY_MAXLEN];
    char private_key[IOT_KEY_MAXLEN];
    int flag; /*Common_Value:value not to be transfered Private_Value:value to be transfered*/
    struct kvlist *record_value;
};

struct iot_value_info
{
    char common_value[IOT_VALUE_MAXLEN];
    char private_value[IOT_VALUE_MAXLEN];
};

static inline int get_param_len(UNUSED struct kvlist *kv, UNUSED const void *data) {
	return sizeof(struct iot_param_info);
}

static inline int get_value_len(UNUSED struct kvlist *kv, UNUSED const void *data) {
	return sizeof(struct iot_value_info);
}

static inline void driver_hold(struct iot_driver_info *driver)
{
	driver->refcnt++;
}

static inline void driver_put(struct iot_driver_info *driver)
{
	driver->refcnt--;
}


struct event_subcallback_info{
	char name[IOT_VDNAME_MAXLEN];
	void (*dev_event_handle)(char *);
};

struct dev_event_info {
	char event_name[DEV_PATH_MAXLEN];
	int callback_count;
	struct event_subcallback_info *callback_list[DEV_VENDOR_MAXCNT];
};

//define in dev_interevent.c
void dev_interevent_Init(void);
void dev_interevent_PubMsg(IN char *event_name, IN char *event_msg);
void dev_interevent_RegisterCallBack(IN char *event_name, IN struct event_subcallback_info *callbackinfo);

//define in dev_sqlite.c
int dev_sqlite_Init(void);
void dev_sqlite_Fini(void);
int dev_sqlite_IsIotDev(IN const char *mac);
void dev_sqlite_DleteIotListByMac(IN char *mac);
void dev_sqlite_UpdateDevTab(IN struct iot_info *st_devinfo);
void dev_sqlite_GetIotList(IN char *mac, OUT struct iot_info *iotlist);
int dev_sqlite_GetIotInfo(IN char *iot_id, OUT struct iot_info *pst_iotinfo);

int dev_himsg_InitIotHandle(void);

//define in dev_iot.c
int dev_iot_Init(void);
void dev_iot_poll(void);
int dev_iot_DriverLoad(void);
int dev_iot_DriverInit(char *vendor_name);
int dev_iot_DriverFini(char *vendor_name);
void dev_iot_DeleteIotDevByMac(IN char *mac);
void dev_iot_UpdateListByMac(IN char *mac, IN char *ip);
void dev_iot_RegisterDriver(struct iot_vendor_info *ops);
int dev_iot_DiscoverHandle(OUT char *buf, IN const char *vendor,IN const char *argument);
int dev_iot_AddHandle(OUT char *buf, IN const char *vendor,IN const char *argument);
struct key_value * dev_iot_CreateKeyValue(IN const char *name, IN const char *value);
void dev_iot_FreeKeyValue(IN struct key_value *pst_keyvalue);
char *dev_iot_GetIotList(IN struct key_value_list *math_info);
void dev_iot_Updatelist(IN const struct iot_info *pst_iotinfo);
int dev_iot_GetNode(IN const char *iot_id, OUT struct iot_info *pst_iotinfo);
struct iot_driver_info *dev_iot_GetDriverInfoByName(IN const char *name);
int dev_iot_GetAttrHandle(OUT char *buf, IN const char *vendor, IN const char *id);
int dev_iot_SetAttrHandle(IN const char *vendor, IN const char *id, IN struct key_value_list *attr_array);

#endif /*_DEV_IOT_H*/
