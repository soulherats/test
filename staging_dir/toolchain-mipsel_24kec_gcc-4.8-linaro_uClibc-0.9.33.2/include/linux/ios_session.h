#ifndef _HIWIFI_NF_CONNTRACK_H
#define _HIWIFI_NF_CONNTRACK_H

#include <linux/types.h>

#define Max_Len 32

#define INIT_MAX   (~0)

#ifdef __KERNEL__

/* from ip_conntrack_common.h */
enum ip_conntrack_flag_status {
	// 这是HA 备份切过去的连接, 不检查窗口
	IPS_FLAG_IGNORE_TCP_WINDOWS_BIT = 0,
	IPS_FLAG_IGNORE_TCP_WINDOWS = (1 << IPS_FLAG_IGNORE_TCP_WINDOWS_BIT),

	// HA 备份许可
	IPS_FLAG_HA_SYNC_PERMISSION_BIT = 1,
	IPS_FLAG_HA_SYNC_PERMISSION = (1 << IPS_FLAG_HA_SYNC_PERMISSION_BIT),

	// 备份的conntrack 标志, 表示备份过来后还没用过
	IPS_FLAG_HA_SYNC_BACKUP_BIT = 2,
	IPS_FLAG_HA_SYNC_BACKUP = (1 << IPS_FLAG_HA_SYNC_BACKUP_BIT),

	// 主主模式下删除动作不再备份
	IPS_FLAG_HA_NO_SYNC_DEL_BIT = 3,
	IPS_FLAG_HA_NO_SYNC_DEL = (1 << IPS_FLAG_HA_NO_SYNC_DEL_BIT),

	// P2P Limit no effect
	IPS_FLAG_ECC_NO_CHECK_BIT = 4,
	IPS_FLAG_ECC_NO_CHECK = (1 << IPS_FLAG_ECC_NO_CHECK_BIT),

	// GUISH 打印标志
	IPS_FLAG_XML_DUMP_BIT = 5,
	IPS_FLAG_XML_DUMP = (1 << IPS_FLAG_XML_DUMP_BIT),

	// 首页应用协议流量统计WEB
	IPS_FLAG_XML_WEB_FLOW_BIT = 6,
	IPS_FLAG_XML_WEB_FLOW = (1 << IPS_FLAG_XML_WEB_FLOW_BIT),

	// 首页应用协议流量统计eMail
	IPS_FLAG_XML_EMAIL_FLOW_BIT = 7,
	IPS_FLAG_XML_EMAIL_FLOW = (1 << IPS_FLAG_XML_EMAIL_FLOW_BIT),

	// 首页应用协议流量统计FTP
	IPS_FLAG_XML_FTP_FLOW_BIT = 8,
	IPS_FLAG_XML_FTP_FLOW = (1 << IPS_FLAG_XML_FTP_FLOW_BIT),

	// 首页应用协议流量统计other
	IPS_FLAG_XML_OTHER_FLOW_BIT = 9,
	IPS_FLAG_XML_OTHER_FLOW = (1 << IPS_FLAG_XML_OTHER_FLOW_BIT),

	// 首页应用协议流量统计UDP
	IPS_FLAG_XML_UDP_FLOW_BIT = 10,
	IPS_FLAG_XML_UDP_FLOW = (1 << IPS_FLAG_XML_UDP_FLOW_BIT),

	// 图形化DEBUG标志位
	IPS_FLAG_TRACK_DEBUG_BIT = 11,
	IPS_FLAG_TRACK_DEBUG = (1 << IPS_FLAG_TRACK_DEBUG_BIT),

	// 不需要图形化DEBUG标志位
	IPS_FLAG_NO_TRACK_DEBUG_BIT = 12,
	IPS_FLAG_NO_TRACK_DEBUG = (1 << IPS_FLAG_NO_TRACK_DEBUG_BIT),

	// 抓包标志位
	IPS_FLAG_CAPTURE_FILTER_BIT = 13,
	IPS_FLAG_CAPTURE_FILTER = (1 << IPS_FLAG_CAPTURE_FILTER_BIT),

	//ct的fw_appid即应用协议的ID是否修改 标志位
	CT_APPID_MOD_BIT = 14,
	CT_APPID_MOD = (1 << CT_APPID_MOD_BIT),

	IPS_FLAG_IS_VOIP_SE_BIT = 15,
	IPS_FLAG_IS_VOIP_SE = (1 << IPS_FLAG_IS_VOIP_SE_BIT),

	//是否记录过日志标志位
	CT_APP_AUDIT_LOG_BIT = 16,
	CT_APP_AUDIT_LOG = (1 << CT_APP_AUDIT_LOG_BIT),

	CT_APP_AUDIT_LOG_URL_BIT = 17,
	CT_APP_AUDIT_LOG_URL = (1 << CT_APP_AUDIT_LOG_URL_BIT),	

	CT_APP_AUDIT_WITHOUT_LOG_BIT = 18,
	CT_APP_AUDIT_WITHOUT_LOG = (1 << CT_APP_AUDIT_WITHOUT_LOG_BIT),
	//会话识别为基础协议(HTTP/HTTPS)
	CT_APPID_BASE_PROTO_BIT = 19,
	CT_APPID_BASE_PROTO = (1 << CT_APPID_BASE_PROTO_BIT),
	//会话识别未识别为任何协议
	CT_APPID_OTHER_PROTO_BIT = 20,
	CT_APPID_OTHER_PROTO = (1 << CT_APPID_OTHER_PROTO_BIT),
	
	// Test use
	IPS_FLAG_TMP_TEST_BIT = 31,
	IPS_FLAG_TMP_TEST = (1 << IPS_FLAG_TMP_TEST_BIT),
};

#define IP_CT_FW_STATUS_IS_LOCAL	0x01 //锟斤拷锟斤拷锟斤拷锟斤拷锟缴憋拷锟斤拷锟斤拷锟斤拷锟巾獥斫憋拷锟斤拷锟侥憋拷锟侥斤拷锟斤拷锟?
#define IP_CT_FW_STATUS_THR_SE	0x02 //锟斤拷锟斤拷锟斤拷锟窖撅拷锟酵革拷锟斤拷SE锟斤拷
#define IP_CT_FW_STATUS_DROP		0x04 //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define IP_CT_FW_STATUS_WEB_AUTH_OK     0x10   // web auth ok
#define IP_CT_FW_STATUS_NAT_LOG	0x20	//没锟叫好办法,锟饺凤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define IP_CT_FW_STATUS_UNAUTH_RD 0x40
#define IP_CT_FW_STATUS_FILTER_PROXY	0x80 //filter http proxy
#define IP_CT_FW_STATUS_QQ_LOGIN           0x100
#define IP_CT_FW_STATUS_QQ_LOGOUT          0x200
#define IP_CT_FW_STATUS_BLACKLIST_CTRL     0x400
#define IP_CT_FW_STATUS_QQ_GAME           0x800
#define IP_CT_FW_STATUS_RESET		0x1000	//RESET
#define IP_CT_FW_STATUS_AV_LOGED    0x4000   //the log of av has been loged
#define IP_CT_FW_STATUS_CC_OK		0x8000	// 锟斤拷锟斤拷锟斤拷锟斤拷状态锟斤拷锟斤拷
#define IP_CT_FW_IPMAC_CHECK_OK	0x10000	// IP-MAC锟巾畾砀硷拷锟斤拷OK
#define IP_CT_FW_NOT_UP_TO_SE         0x20000
#define IP_CT_SEND_P2P_LOG         0x40000
#define IP_CT_FW_STATUS_END		0x80000000

#define APP_L4_PROTONUM_START 200000
#define APP_ID_MAX	100000

#define CT_APPID_MOD_SET(ct)		(ct->flag_status|= CT_APPID_MOD)
#define CT_APPID_MOD_UNSET(ct)		(ct->flag_status &= ~CT_APPID_MOD)
#define IS_CT_APPID_MOD(ct)          (ct->flag_status & CT_APPID_MOD) 


#define CT_APP_AUDIT_LOG_SET(ct)		(ct->flag_status |= CT_APP_AUDIT_LOG)
#define CT_APP_AUDIT_LOG_UNSET(ct)		(ct->flag_status &= ~CT_APP_AUDIT_LOG)
#define IS_CT_APP_AUDIT_LOG(ct)          (ct->flag_status & CT_APP_AUDIT_LOG) 

#define CT_APP_AUDIT_LOG_URL_SET(ct)		(ct->flag_status |= CT_APP_AUDIT_LOG_URL)
#define CT_APP_AUDIT_LOG_URL_UNSET(ct)		(ct->flag_status &= ~CT_APP_AUDIT_LOG_URL)
#define IS_CT_APP_AUDIT_LOG_URL(ct)     (ct->flag_status & CT_APP_AUDIT_LOG_URL) 
#define CT_APPID_BASE_PROTO_SET(ct) 	(ct->flag_status |= CT_APPID_BASE_PROTO)
#define CT_APPID_BASE_PROTO_UNSET(ct) 	(ct->flag_status &= ~CT_APPID_BASE_PROTO)
#define IS_CT_APPID_BASE_PROTO(ct) 		(ct->flag_status & CT_APPID_BASE_PROTO)

#define CT_APPID_OTHER_PROTO_SET(ct)	(ct->flag_status |= CT_APPID_OTHER_PROTO)
#define CT_APPID_OTHER_PROTO_UNSET(ct)	(ct->flag_status &= ~CT_APPID_OTHER_PROTO)
#define IS_CT_APPID_OTHER_PROTO(ct)		(ct->flag_status & CT_APPID_OTHER_PROTO)


#define CT_APP_AUDIT_WITHOUT_LOG_SET(ct)		(ct->flag_status |= CT_APP_AUDIT_WITHOUT_LOG)
#define IS_CT_APP_AUDIT_WITHOUT_LOG(ct)          (ct->flag_status & CT_APP_AUDIT_WITHOUT_LOG) 


#define CT_WLOCK(ct) 	spin_lock_bh(&(ct)->lock)
#define CT_WUNLOCK(ct) 	spin_unlock_bh(&(ct)->lock)
#define CT_RLOCK(ct) 	spin_lock_bh(&(ct)->lock)
#define CT_RUNLOCK(ct) 	spin_unlock_bh(&(ct)->lock)

enum stat_audit_proto_type
{
    app_http = 0,
    app_p2p,
    app_smedia,
    app_im,
    app_game,
    app_stock, 
    app_email,
    app_remote_ctrl,
    app_voip,
    app_file_share,
    app_basic,
    app_other,
    app_max,
};

struct app_stat_info
{
	struct list_head list;
	uint32_t appid;
	uint16_t dev_count;
	struct list_head *srcip_list; 
};

struct srcip_stat_info
{
	struct list_head list;
	uint32_t src_ip;
	unsigned long long byte_in;
	unsigned long long byte_out;
};

struct pc_dev_info{
	unsigned char mac[ETH_ALEN];
	uint32_t ip;
	unsigned char device_type[Max_Len];
	unsigned char device_brand[Max_Len];
	unsigned char os_version[Max_Len];
};

struct pc_dev_info_config{
	struct list_head list;
	char	dev_name[IFNAMSIZ];
	unsigned char srcmac[ETH_ALEN];
	uint32_t ip;
	unsigned char device_type[Max_Len];
	unsigned char device_brand[Max_Len];
	unsigned char os_version[Max_Len];
	time_t time;
};

struct fw_conntrack_cnt_proto_infor
{
	struct list_head list; 
	unsigned int proto;
	unsigned int conn_num; 
	unsigned long byte_in; 
	unsigned long byte_in_old;
	unsigned long byte_in_new;
	unsigned long byte_out;
	unsigned long byte_out_old;
	unsigned long byte_out_new;
};

struct conntrack_flow_info_for_snmp
{
	struct list_head list;
	unsigned int count;    
	unsigned int ip;	
	unsigned int fw_appid;
	unsigned long  start_time;
	unsigned int dst_port;
	unsigned int proto_type;
	unsigned long byte_count_in;
	unsigned long byte_count_in_old;
	unsigned long byte_count_in_new;	
	unsigned long byte_count_out;
	unsigned long byte_count_out_old;
	unsigned long byte_count_out_new;		
};

struct conntrack_event_log_by_sip_appproto
{
	struct list_head list;
	unsigned int count;    
	unsigned int ip;	
	unsigned int fw_appid;
	unsigned long  start_time;
};

#define FLOW_STAT_TENMIN_ARRAYS_NUM 61
#define FLOW_STAT_ALLDAY_ARRAYS_NUM 73
#define FLOW_STAT_ONEHOUR_ARRAYS_NUM 61

struct fw_conntrack_history_flow_stat_infor
{
	unsigned long byte_in_flow; //涓婅娴侀噺
	unsigned long byte_out_flow; //涓嬭娴侀噺
};

struct fw_conntrack_history_flow_stat
{ 
	struct list_head list;
	int count;                                     //会话引用计数
	unsigned int condition_sip;    
	unsigned int condition_proto;
	unsigned long byte_in; 
	unsigned long byte_out;
};

#endif /* __KERNEL__ */

/* MODULE slot which need ip conntrack */
#define IP_CT_MOD_POLICY		0
#define IP_CT_MOD_NAT			1
#define IP_CT_MOD_INSPECT		2
#define IP_CT_MOD_DEFEND		3
#define IP_CT_MOD_SYNCOOKIE	4
#define IP_CT_MOD_SMTP_FILTER	5
#define IP_CT_MOD_URL_FILTER	6
#define IP_CT_MOD_LAC			7
#define IP_CT_MOD_ANTIFLOOD	8
#define IP_CT_MOD_MMQ			9
#define IP_CT_MOD_TMPBLK		10
#define IP_CT_MOD_TRAFFICLIMIT		11
#define IP_CT_MOD_DSCPMOD        12
#define IP_CT_MOD_ANTI_SPAM	13
#define IP_CT_MOD_NAC			14
#define IP_CT_MOD_WEB_REDIRECT	15
#define IP_CT_MOD_MAC_ADDR_FILTER 16
#define IP_CT_MOD_ACL_IPV6 17

#define FW_NF_STATUS_SHOW		0
#define FW_POLICY_SERVICE_ENABLE	1
#define FW_POLICY_SERVICE_DISABLE	2
#define FW_LAC_SERVICE_ENABLE		3
#define FW_LAC_SERVICE_DISABLE	4


#endif /*_HIWIFI_NF_CONNTRACK_H*/

