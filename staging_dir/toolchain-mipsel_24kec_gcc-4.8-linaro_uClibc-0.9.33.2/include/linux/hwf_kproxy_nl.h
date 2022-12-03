
#ifndef _HWF_KPROXY_NL_H_
#define _HWF_KPROXY_NL_H_

#include <linux/netlink.h>

#define HWF_KPROXY_NL_BUFF_LEN	4096

enum hwf_kproxy_msg_type_e {
	HWF_KPROXY_MSG_FLAG = NLMSG_MIN_TYPE,
	HWF_KPROXY_MSG_HOST,
	HWF_KPROXY_MSG_FTYPE,
	HWF_KPROXY_MSG_ADDR_PORT,
	HWF_KPROXY_MSG_PORTAL,
	HWF_KPROXY_MSG_WYPORT,
	HWF_KPROXY_MSG_URL,
	HWF_KPROXY_MSG_RULE,
	HWF_KPROXY_MSG_HOST_TYPE,
	HWF_KPROXY_MSG_MD5,
	HWF_KPROXY_MSG_MAX,
	HWF_KPROXY_MSG_MASK = 0xFF,
};

enum hwf_kproxy_msg_action_e {
	HWF_KPROXY_ACTION_LIST = 0,
	HWF_KPROXY_ACTION_ADD,
	HWF_KPROXY_ACTION_DEL,
	HWF_KPROXY_ACTION_DEL_ALL,
	HWF_KPROXY_ACTION_DEL_BYNS,
	HWF_KPROXY_ACTION_MASK = 0xF,
};

enum hwf_kproxy_msg_lan_e {
	HWF_KPROXY_BR_LAN_MIN = 0,
	HWF_KPROXY_BR_LAN = HWF_KPROXY_BR_LAN_MIN,
	HWF_KPROXY_BR_LAN1,
	HWF_KPROXY_BR_LAN_MAX = HWF_KPROXY_BR_LAN1,
	HWF_KPROXY_BR_LAN_DEF = HWF_KPROXY_BR_LAN,
	HWF_KPROXY_LAN_MASK = 0xF,
};

#define for_each_lan(lan_num) for(lan_num = HWF_KPROXY_BR_LAN_MIN; lan_num <= HWF_KPROXY_BR_LAN_MAX; ++lan_num)
#define if_out_of_lan(lan_num) if(lan_num < HWF_KPROXY_BR_LAN_MIN || lan_num > HWF_KPROXY_BR_LAN_MAX)

#define HWF_KPROXY_MSG_TYPE(nlmsg_type)		((nlmsg_type >> 4) & HWF_KPROXY_MSG_MASK)
#define HWF_KPROXY_MSG_ACTION(nlmsg_type)	(nlmsg_type & HWF_KPROXY_ACTION_MASK)
#define HWF_KPROXY_MSG_LAN(nlmsg_type)		((nlmsg_type >> 12) & HWF_KPROXY_LAN_MASK)
#define HWF_KPROXY_NLMSG_TYPE(lan_num, type, action)	(((lan_num & HWF_KPROXY_LAN_MASK) << 12) + ((type & HWF_KPROXY_MSG_MASK) << 4) + (action & HWF_KPROXY_ACTION_MASK))

enum hwf_kproxy_flag_e {
	HWF_KPROXY_FLAG_MIN = 0,

	// Other flags can be added here.
	
	HWF_KPROXY_FLAG_MAX = 20,
};

#define HWF_KPROXY_HOST_MINLEN		3
#define HWF_KPROXY_HOST_MAXLEN		64
#define HWF_KPROXY_HOST_MAXNUM		128

#define HWF_KPROXY_FTYPE_MINLEN		2
#define HWF_KPROXY_FTYPE_MAXLEN		7
#define HWF_KPROXY_HTYPE_MAXLEN		24
#define	HWF_KPROXY_FTYPE_MAXNUM		8
#define	HWF_KPROXY_HTYPE_MAXNUM		8

struct hwf_kproxy_flag_s {
	unsigned long flag_bit;
} __attribute__((packed));

struct hwf_kproxy_host_s {
	unsigned short host_port;
	unsigned char host_len;
	unsigned char match_suffix: 1,
				  _host_matched: 1; // For debug.
	char rhost[HWF_KPROXY_HOST_MAXLEN];
} __attribute__((packed));

struct hwf_kproxy_ftype_s {
	unsigned char ftype_len: 7,
				  _ftype_matched: 1; // For debug.
	char ftype[HWF_KPROXY_FTYPE_MAXLEN];
} __attribute__((packed));

struct hwf_kproxy_addr_port_s {
	unsigned int ip;
	unsigned short port;
} __attribute__((packed));

struct hwf_kproxy_portal_s {
	unsigned int sip;
	unsigned int timeout;
} __attribute__((packed));

struct hwf_kproxy_htype_s{
	unsigned int ip;
	int mask_len;
	unsigned int dnat_ip;
	unsigned int port;
	char index;
	char htype_matched;
} __attribute__((packed));
#endif // _HWF_KPROXY_NL_H_

