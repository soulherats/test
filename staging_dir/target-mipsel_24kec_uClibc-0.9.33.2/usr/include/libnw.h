/******************************************************************************
 *
 * Copyright (c) 2013-2014 Beijing Geek-geek Technology Co., Ltd.
 * All rights reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Geek-geek Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Geek-geek Corporation.
 *
 * FILE NAME  :   libnw.h
 * VERSION    :   1.0
 * DESCRIPTION:   Command structure for command line utility.
 * AUTHOR     :	  Abu Cheng
 *
 ******************************************************************************/
#ifndef _LIBNW_H_
#define _LIBNW_H_

#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <nlwifi.h>

#define NW_BUFSIZE			12 * 1024
#define NULL            	((void *)0)

struct nw_data {
	int attr;
	int min;
	int max;
	int cnt;
	int len;
	char buf[NW_BUFSIZE];
};

struct nlattr ** nlwifi_parse(struct nl_msg *msg);
int nlwifi_get_cmd(const char *ifname, int nlcmd, int flags, int (*cb_func)(struct nl_msg *, void *), void *cb_arg);
int nlwifi_set_int_cmd(const char *ifname, int nlcmd, int attr, int val);
int nlwifi_set_str_cmd(const char *ifname, int nlcmd, int attr, const char *argv);
int nlwifi_set_mac_cmd(const char *ifname, int nlcmd, int attr, u_int8_t *macaddr);
int nlwifi_set_data(const char *ifname, int nlcmd, int attr, u_int8_t *macaddr, int len, void *data);
int nlwifi_set_appie(const char *ifname, const char *groupid, void *data, int len);
int nlwifi_tx_frame(const char *ifname, u_int32_t fctl, u_int8_t *macaddr, void *data, int len);
int nlwifi_event_register(int (*cb_func)(struct nl_msg *, void *), void *cb_arg);
int nlwifi_mgmt_register(int (*cb_func)(struct nl_msg *, void *), void *cb_arg);
int nlwifi_get_event_fd(void);
int nlwifi_get_mgmt_fd(void);
void *nlwifi_event_handle(const char *family, const char *group, int (*cb_func)(struct nl_msg *, void *), void *cb_arg);
void nlwifi_event_receive(void);
void nlwifi_mgmt_receive(void);

int mac_str_eth (const u_int8_t *buffer, u_int8_t *ether);
int nw_do_get_cmd(const char *ifname, const char *command, struct nw_data *data);
int nw_do_set_cmd(const char *ifname, const char *command, const char *argv);
void nw_help(void);

#endif /* _LIBNW_H_ */
