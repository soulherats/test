#ifndef __IOT_LIBS_H
#define __IOT_LIBS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <libubox/list.h>
#include <hierrno/device/device_errno.h>
#include <json/json.h>
#include "hwf_log.h"


typedef enum
{
	DEVICED_ERR_SUCCESS 				= HIERRNO_SUCCESS,
	DEVICED_ERR_FAILED 					= HIERRNO_DEVICE_FAILED,
	DEVICED_ERR_ARGUMENT_ERROR			= HIERRNO_DEVICE_ARGUMENT_ERROR, 
	DEVICED_ERR_NOT_ENOUGH_MEMORY =HIERRNO_DEVICE_NOT_ENOUGH_MEMORY,
	DEVICED_ERR_EMPTY_DEVNAME=HIERRNO_DEVICE_EMPTY_DEVNAME,
	DEVICED_ERR_TOOLONG_DEVNAME=HIERRNO_DEVICE_TOOLONG_DEVNAME,
	DEVICED_ERR_MAX
}qos_err_t;


#define IN
#define OUT
#define INOUT

#define DEV_TRUE 1
#define DEV_FALSE 0

#define DEV_INVALIED_CODE   0xFFFFFFFF
#define DEV_GUEST_FALG		0
#define DEV_MASTER_FLAG		1

#define DEVICED_AGING			3
#define DEVICED_TRUE			1
#define DEVICED_FALSE			0


#define USB_WEBCAM_AGING	2

#define Lib_Path_Len 128

#define WIFI_24G  			0
#define WIFI_5G   			1

#define DEV_ONLINE			1
#define DEV_OFFLINE			0

#define DEV_TIMER_TIME	2

#define DEV_INLINE_BYWIRE 		0
#define DEV_INLINE_BYWIRELESS 	1
#define DEV_INLINE_BYAPWIRELESS 2

#define DEV_STATION_MODEL 		0
#define DEV_IOT_MODEL 			1
#define DEV_AP_MODEL 			2
#define DEV_STATELLITE_MODEL 	3

#define DEV_IOT_LISTOPTIONCNT	9
#define DEV_MACOUI_MACCNT 		16
#define DEV_VENDOR_MAXCNT 		32

#define DEV_IP_MAXLEN 			16
#define DEV_MAC_MAXLEN 			20
#define DEV_TYPE_MAXLEN                 16
#define DEV_VERS_MAXLEN			16
#define DEV_SSID_MAXLEN 		32
#define DEV_EVENT_MAXCNT		16
#define DEV_KEY_MAXLEN 			32
#define DEV_VALUE_MAXLEN		32
#define DEV_IFNAME_MAXLEN 		32
#define DEV_TIMESTR_MAXLEN		32
#define DEV_PATH_MAXLEN			64
#define DEV_DEVNAME_MAXLEN  	64
#define DEV_BUFFER_MAXLEN		1024
#define DEV_COMMAND_MAXLEN 		1024

#define EVENT_LOCAL_WIRELESS_ASSOC    	"wireless.assoc"
#define EVENT_LOCAL_WIRELESS_DISASSOC 	"wireless.disassoc"
#define EVENT_REMOTE_WIRELESS_ASSOC 	"service.apmgr.wireless_updown"
#define EVENT_AP_WIRELESS_ASSOC 	"service.apmgr.wireless_sta"
#define EVENT_AP_WIRE_ASSOC 	"service.apmgr.wired_sta"


#define Online_Status  "online"
#define Offline_Status  "offline"

#define Router_Name "router"
#define Ap_Name "ap"
#define Star_Name "star"

#define Dev_Unkown  0
#define Dev_Route 1
#define Dev_Ap 2 
#define Dev_Star 3
#define Dev_Station 4



#define IOT_DEV_TAB  "dev_tab"
#define DEV_HISTORY_PATH "/var/deviced"
#define IOT_DATABASE "/etc/iot/iot_dev.db"
#define DEVLIST_CACHE_PATH "/var/deviced_cache"

#define Fast_Poll_Time 2 /*wireless stat in hnat*/
#define Poll_Time 10

#define Jitter_Time 300

#define Station_Max 500


/*本地保存的历史天数*/
#define DEV_HISTORY_DAYS  3

#define Event_Info "event"
#define Poll_Info "poll"

#define HNAT_Enable 1
#define HNAT_Disable 0

#define Max_Rssi 0
#define Min_Rssi -100


#define Dev_Master 1
#define Dev_Guest 0

enum
{
	Mode_Unkown=0,
	Mode_Router=1,
	Mode_Ap=2,
	Mode_Star=3
};

extern int Route_Mode;

extern int dev_conn_mqtt;
extern int poll_frequency;
extern struct mosquitto *dev_mosq;
extern int aging_count;


struct key_value {
	char name[DEV_KEY_MAXLEN];
	char value[DEV_VALUE_MAXLEN];
};

struct key_value_list {
	int keyvalue_cnt;
	struct key_value *keyvalue_list;
};


/*size:240 bytes*/
struct station_info{
	int rssi; //信号强度
	int aging; //老化次数
	int online; //是否是在线 1表示在线, 0表示离线
	int master; //是否是主网络 1表示主网络, 0表示访客
	int init; //是否是初始化状态，即是否完成首次安装
	int station_count; //ap or 极卫星上连接的设备数量
	time_t last_online; //最近一次上线时间
	time_t last_offline; //最近一次离线时间
	time_t first_online; //第一次上线时间
	int history_bytes_update; //判断历史统计流量是否更新的flag
	unsigned long long txbytes; //最近一次上线到当前的下行流量统计
	unsigned long long rxbytes; //最近一次上线到当前的上线流量统计
	unsigned long long history_txbytes; //从路由器启动到当前设备累积下行流量
	unsigned long long history_rxbytes; //从路由器启动到当前设备累积上行流量
	char con_type[DEV_TYPE_MAXLEN]; //设备连接类型 wire(有线)|2.4G|5G
	char mac[DEV_MAC_MAXLEN]; //mac地址
	char ip[DEV_IP_MAXLEN]; //ip 地址
	char name[DEV_DEVNAME_MAXLEN]; //设备名称
	char type[DEV_TYPE_MAXLEN]; //设备类型 station|router|ap|star|iot 
	char conn_ap[DEV_MAC_MAXLEN]; //设备接入点mac地址
	char conn_aptype[DEV_TYPE_MAXLEN]; //设备接入点类型
	int aging_time;/*终端老化次数，对于arp表项一直存在的
				情况超过老化次数则认为上线*/
	
};


struct ap_info{
	int aging;/*老化次数，默认为3*/
	int init;/*是否可切换为ap 1:可切换 0:不可切换*/
	int have_5g;/*是否支持5G*/
	int lan_cnt;/*有线lan口数量*/
	int station_count; //ap or 极卫星上连接的设备数量
	int wireless_sta_count;//ap or极卫星上无线终端数量
	int level; /*ap的层级*/
	int rssi;/*ap or star的信号强度*/
	char type[DEV_TYPE_MAXLEN]; /*接入路由器的类型 router/ap/start*/
	char con_type[DEV_TYPE_MAXLEN]; /*ap的连接类型 wire/2.4G/5G*/
	char mac[DEV_MAC_MAXLEN];
	char base_mac[DEV_MAC_MAXLEN];
	char mac_2gup[DEV_MAC_MAXLEN];
	char mac_5gup[DEV_MAC_MAXLEN];
	char lan1_mac[DEV_MAC_MAXLEN];
	char ip[DEV_IP_MAXLEN];
	char name[DEV_DEVNAME_MAXLEN];/*自定义设备名称*/
	char model[DEV_TYPE_MAXLEN];/*设备型号*/
	char version[DEV_VERS_MAXLEN];/*rom版本*/
	char sub_model[DEV_TYPE_MAXLEN];/*设备子型号*/
	struct list_head stalist_head;
};


//define in dev_station.c
int dev_station_Init(void);
void dev_station_Fini(void);
void dev_station_AgingStalist(void);
void dev_station_DestoryTmpStalist(void);
//int dev_station_IsOnline(IN const char *mac);
char *dev_station_GetOnlineCntStat(void);
void dev_station_UpdateasAp(IN struct ap_info *ap_info);
void dev_station_GetRouterMac(OUT char *router_mac);
void dev_station_UpdateTmpStalistToStalist(void);
char *dev_station_GetStalist(struct key_value_list *math_info);
void dev_station_InitStaInfo(OUT void *);
void dev_station_GetStaRecord(OUT char *buf, IN char *mac, IN char *date);
void dev_station_UpdateStalist(IN const struct station_info *pst_stainfo);
//void dev_station_GetLastHistory(char *mac, time_t *lastonline, time_t *lastoffline);
void dev_station_UpdateTmpStalist(IN const struct station_info *pst_stainfo);

int dev_uci_IsDenyList(IN char *mac);
int dev_uci_GetMasterWifi(OUT char *ssid, OUT char *key);
int dev_uci_GetGeeMacOui(char **macoui);
int dev_uci_GetIfname(IN const char *ifnametype, OUT char *ifname);

void dev_handle_UpdateCache(void);
void dev_handle_UpdateDevlist(void);
int dev_handle_GetBssid(OUT char *bssid);
int dev_handle_GetBcast(OUT char *bcast);
void dev_handle_updatestastatus(void);
void dev_handle_UpdateDevHistory(void);
char *dev_handle_GetHistoryIndex(IN int *rc);
void dev_handle_SpecialChar(INOUT char *src);
void dev_handle_GetRouterMac(OUT char *router_mac);
void dev_handle_GetIpByMac(IN const char *mac, OUT char *ip);
void dev_handle_StrToupper(IN const char *str, OUT char *dst);
void dev_handle_FromatmacTodb(IN const char *str, OUT char *mac);
char *dev_handle_ReadDevCache(IN struct key_value_list *math_info);
void dev_handle_GetApWanMac(IN char *bdinfo_mac, OUT char *wan_mac);
void dev_handle_GetDevName(OUT char *dev_name, IN const char *dev_mac);
void dev_handle_GetApBdInfoMac(IN char *wan_mac, OUT char *bdinfo_mac);
int dev_handle_SaveToDevNameFile(IN const char *mac, IN const char *name);
int dev_handle_DelDevNameFromFile(IN const char *mac);
void dev_handle_LocalWirelessStaEvent(IN struct json_object *msg_obj, IN const char *action);
void dev_handle_RemoteWirelessStaEvent(IN struct json_object *msg_obj);
void dev_handle_ApWirelessStaEvent(IN struct json_object *msg_obj);
void dev_handle_ApWireStaEvent(IN struct json_object *msg_obj);
void dev_handle_PackResMsg(OUT char *buf, IN const char *error_info, IN int rc,IN const char *response);
void dev_handle_PackNameChangeMsg(IN char *name, IN char *mac, OUT char *msg);
void dev_handle_WriteStaHistory(IN const char *day_path, IN int flag, IN time_t timestamp);
void dev_handle_ParseOneHistory(IN char *historystr, OUT time_t *onlinetime, OUT time_t *offlinetime);
void dev_handle_GetLastHistory(IN const char *history_path, OUT time_t *last_online, OUT time_t *last_offline);
void dev_hanlde_GetWirelessStalistInAp(IN char *apmac, IN char *ifname, IN int master, IN char *con_type, IN char *con_aptype);

void dev_handle_ConnRecord_Update(IN struct station_info *pst_stainfo,IN int status,IN time_t time);
struct station_info *dev_station_GetSta(IN const char *mac);

struct json_object * json_tokener_parse_len(const char *msg,int len);

//dev_himsg.c
int dev_himsg_Init(void);
void dev_himsg_Fini(void);
void dev_himsg_PubEvent(IN char *msg, IN char *topic);

//dev_station.c
void *dev_handle_poll(void *data);

void *dev_time_sync(void *data);

extern void* thread_himsg_event(void* arg);


//dev_sqlite.c

//dev_ap.c
int dev_ap_Init(void);
void dev_ap_Fini(void);
void dev_ap_AgingAplist(void);
char *dev_ap_GetAplist(OUT int *rc);
void dev_ap_GetWirelessStalist(void);
void dev_ap_UpdateAplist(IN const struct ap_info *pst_apinfo);
void dev_handle_Update_Sta_ConAp(const char *mac,struct ap_info *pst_apinfo,char *con_type);


void debug_station_info(IN char *func,IN struct station_info *stainfo);

void arp_stale_flush();


#endif /*__IOT_LIBS_H*/

