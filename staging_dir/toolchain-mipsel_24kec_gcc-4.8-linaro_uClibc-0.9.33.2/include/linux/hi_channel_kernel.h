#ifndef _HI_CHANNEL_KERNEL_H_
#define _HI_CHANNEL_KERNEL_H_

#include <linux/version.h>
#include <linux/netlink.h>

/*Netlink自定义多播组类型*/
#ifndef __KERNEL__
#define CTRLGRP_SYSLOG      0x1
#define CTRLGRP_APP_AUDIT_LOG	0x2
#endif/* __KERNEL__ */

/* CTRLnetlink multicast groups */
enum ctrlnetlink_groups {
	CTRLNLGRP_NONE,
#define CTRLNLGRP_NONE		CTRLNLGRP_NONE
	CTRLNLGRP_SYSLOG,
#define CTRLNLGRP_SYSLOG		CTRLNLGRP_SYSLOG
	CTRLNLGRP_APP_AUDIT_LOG,
#define CTRLNLGRP_APP_AUDIT_LOG		CTRLNLGRP_APP_AUDIT_LOG 
	__CTRLNLGRP_MAX
};
#define CTRLNLGRP_MAX	(__CTRLNLGRP_MAX - 1)

/*hi_channel_hook_add对应类型*/

#define KPROXY_CHANNEL_ID	NLMSG_MIN_TYPE+1

#define KPROSTAT_CHANNEL_ID	NLMSG_MIN_TYPE+2

#define HI_CHANNEL_DEMON_TYPE NLMSG_MIN_TYPE+3

#define XT_TIME_CHANNEL_ID NLMSG_MIN_TYPE+4

/*NF_INET_FORWARD*/
#define NF_IP_PRI_IPSTAT_IN  NF_IP_PRI_FILTER
#define NF_IP_PRI_APP_IDENTIFY NF_IP_PRI_FILTER+1
#define NF_IP_PRI_PC_DEVINFO NF_IP_PRI_FILTER+2


/*NF_INET_LOCAL_IN*/
#define NF_IP_PRI_PROSTAT_IN NF_IP_PRI_CONNTRACK_CONFIRM+1

/*NF_INET_POST_ROUTING*/
#define NF_IP_PRI_PROSTAT_OUT NF_IP_PRI_NAT_SRC-9
#define NF_IP_PRI_IPSTAT_OUT NF_IP_PRI_NAT_SRC - 8
#define NF_IP_PRI_APP_IDENTIFY_STAT NF_IP_PRI_CONNTRACK_CONFIRM+2

#ifdef __KERNEL__
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,7,0)
#   define SKB_PORTID(x) NETLINK_CB(x).portid
#else
#   define SKB_PORTID(x) NETLINK_CB(x).pid
#endif

typedef int (* HOOKFUN_T)(struct sk_buff *skb, struct nlmsghdr *nh);

typedef struct hook_list_s
{
	struct list_head        list;
	__u16 type;
	HOOKFUN_T pFun;
	atomic_t count;
}hook_list_t;

extern int hi_channel_hook_add(__u16 type, HOOKFUN_T pFun);
extern void hi_channel_hook_del(__u16 type);
extern int hi_channel_reply(struct sk_buff *in_skb, struct nlmsghdr *nh,
	const char* buf, int len);
extern int __init hi_channel_init(void);
extern void __exit hi_channel_exit(void);
#endif

#endif
