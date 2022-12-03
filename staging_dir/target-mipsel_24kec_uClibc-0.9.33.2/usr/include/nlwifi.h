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
 * FILE NAME  :   nlwifi.h
 * VERSION    :   1.0
 * DESCRIPTION:   This is the hiwifi netlink-based configuration interface.
 * AUTHOR     :	  Abu Cheng
 *
 ******************************************************************************/
#ifndef _NLWIFI_H_
#define _NLWIFI_H_

#include <linux/types.h>
	
enum {
	NLWIFI_CMD_UNSPEC,

	NLWIFI_CMD_DEV_UP,
	NLWIFI_CMD_STATUS,
	NLWIFI_CMD_QUALITY,
	NLWIFI_CMD_DBG,

	NLWIFI_CMD_NRT,
	NLWIFI_CMD_RST,
	NLWIFI_CMD_TX99,
	NLWIFI_CMD_GAIN,
	NLWIFI_CMD_FERR,
	NLWIFI_CMD_TXCHAIN,
	NLWIFI_CMD_RXCHAIN,
	NLWIFI_CMD_RXNRT,
	NLWIFI_CMD_CALDATA,

	NLWIFI_CMD_AP_MODE,
	NLWIFI_CMD_HWMODE,
	NLWIFI_CMD_HTBW,
	NLWIFI_CMD_BUSY_TIME,
	NLWIFI_CMD_VGA,
	NLWIFI_CMD_LOWRSSI,
	NLWIFI_CMD_COUNTRY,
	NLWIFI_CMD_CHANNEL,
	NLWIFI_CMD_CHEXT,
	NLWIFI_CMD_SSID,
	NLWIFI_CMD_BSSID,
	NLWIFI_CMD_DEVID,
	NLWIFI_CMD_HIDDEN,
	NLWIFI_CMD_AP_ISOLATE,
	NLWIFI_CMD_TX_PWR,
	NLWIFI_CMD_ACL_POLICY,
	NLWIFI_CMD_ACL_LIST,
	NLWIFI_CMD_ACL_CLEAR,
	NLWIFI_CMD_ACL_CHECK,
	NLWIFI_CMD_AUTH_TYPE,
	NLWIFI_CMD_KEY,
	NLWIFI_CMD_PMK,
	NLWIFI_CMD_STA_LIST,
	NLWIFI_CMD_SCAN,
	NLWIFI_CMD_WSC_ON,
	NLWIFI_CMD_WSC_OFF,
	NLWIFI_CMD_REPEATER,
	NLWIFI_CMD_SMT,
	NLWIFI_CMD_LED,
	NLWIFI_CMD_DEAUTH,
	NLWIFI_CMD_DENY,
	NLWIFI_CMD_AUTHRESP,

	NLWIFI_CMD_AP_LIST,
	NLWIFI_CMD_CH_LIST,
	NLWIFI_CMD_WDS_LIST,

	NLWIFI_CMD_APPIE,
	NLWIFI_CMD_TX_EAP,
	NLWIFI_CMD_TX_FRAME,
	NLWIFI_CMD_EVENT,

	__NLWIFI_CMD_MAX,
	NLWIFI_CMD_MAX = __NLWIFI_CMD_MAX - 1
};
	
enum {
	NLWIFI_ATTR_UNSPEC,
	NLWIFI_ATTR_IFNAME,
	NLWIFI_ATTR_VALUE,
	NLWIFI_ATTR_BUF,
	NLWIFI_ATTR_HWMODE,
	NLWIFI_ATTR_HTBW,
	NLWIFI_ATTR_CHANNEL,
	NLWIFI_ATTR_CHANNEL_TYPE,
	NLWIFI_ATTR_CHANNEL_LIST,
	NLWIFI_ATTR_COUNTRY,
	NLWIFI_ATTR_MAC,
	NLWIFI_ATTR_KEY,
	NLWIFI_ATTR_SSID,
	NLWIFI_ATTR_AUTH_TYPE,
	NLWIFI_ATTR_ACL,
	NLWIFI_ATTR_FRAME,
	NLWIFI_ATTR_ANTENNA_TX,
	NLWIFI_ATTR_ANTENNA_RX,
	NLWIFI_ATTR_MCAST_RATE,
	NLWIFI_ATTR_STA_INFO,
	NLWIFI_ATTR_AP_INFO,
	NLWIFI_ATTR_WDS_INFO,
	NLWIFI_ATTR_BUSY_INFO,
	NLWIFI_ATTR_ACTION,
	NLWIFI_ATTR_CALDATA,
	NLWIFI_ATTR_REPEATER,
	NLWIFI_ATTR_SMT,
	NLWIFI_ATTR_DEVID,
	NLWIFI_ATTR_GROUPID,
	NLWIFI_ATTR_RSSI0,
	NLWIFI_ATTR_RSSI1,

	NLWIFI_ATTR_EAP,
	NLWIFI_ATTR_ACT,
	NLWIFI_ATTR_EVENT,
	NLWIFI_ATTR_PROBE,
	NLWIFI_ATTR_QUALITY,
	NLWIFI_ATTR_PROFILE,
	NLWIFI_ATTR_SMTINFO,
	NLWIFI_ATTR_JOYLINK,
	NLWIFI_ATTR_UPLUS,

	NLWIFI_ATTR_BSSID,
	NLWIFI_ATTR_DADDR,
	NLWIFI_ATTR_SADDR,

	__NLWIFI_ATTR_MAX,
	NLWIFI_ATTR_MAX = __NLWIFI_ATTR_MAX - 1
};

#define MAC_ADDR_LEN 				6

typedef struct
{
	u_int8_t		macaddr[MAC_ADDR_LEN];
	u_int8_t		rssi;
} mac_entry_t;

typedef struct
{
	u_int8_t		mac[MAC_ADDR_LEN];	 /*STA µÄMACµØÖ·*/
	char			mode[8];
	char			bw[8];
	u_int8_t		inact;
	u_int8_t		ccq;
	int8_t		avgrssi;
	int8_t		rssi[3];
	u_int8_t		pwr;
	u_int8_t		rpt;
	u_int8_t		mimops;
	u_int8_t		rxs;
	u_int32_t		txrate;
	u_int32_t		rxrate;
	u_int32_t		assoctime;
	u_int64_t		txbytes;
	u_int64_t		rxbytes;
} sta_info_t;

typedef struct
{
	u_int8_t		wdsmac[MAC_ADDR_LEN];	 /* WDS MAC */
	u_int8_t		stamac[MAC_ADDR_LEN];	 /* STA MAC */
	u_int32_t		inact;
} wds_info_t;

typedef struct
{
	u_int8_t		bssid[MAC_ADDR_LEN];
	char	 		ssid[32 + 1];	
	u_int8_t		rssi;
	u_int8_t		channel;
	u_int8_t		rpt;
	char			bgn[10];
	char			auth[16];
	char			cwm[8];
	u_int32_t		groupid;
} ap_info_t;

typedef struct
{
	u_int8_t cnt;
	u_int8_t channel[54];
	u_int8_t busytime[54];
} busy_info_t;

typedef struct
{
	u_int8_t cnt;
	u_int8_t channel[54];
	u_int32_t quality[54];
} chan_list_t;

struct nlwifi_ops {
	void			(*pre_call)(void *priv);
	void			(*post_call)(void *priv);
	void			(*shut_down)(void *priv);
	unsigned long	(*get_traffic)(void *priv);
	unsigned int	(*get_quality)(void *priv);
	int				(*set_up)(void *priv, int up);
	int				(*set_nrt)(void *priv, int nrt);
	int				(*set_rst)(void *priv);
	int				(*set_tx99)(void *priv, u_int32_t txrate);
	int				(*set_gain)(void *priv, u_int32_t gain);
	int				(*set_ferr)(void *priv, u_int32_t ferr);
	int				(*set_tx_chain)(void *priv, u_int32_t txchain);
	int				(*set_rx_chain)(void *priv, u_int32_t rxchain);
	int				(*get_rxnrt)(void *priv);
	int				(*set_rxnrt)(void *priv, u_int32_t rxnrt);
	int				(*get_caldata)(void *priv, void *data);
	int				(*get_dbg)(void *priv);
	int				(*set_dbg)(void *priv, int level);
	int				(*get_status)(void *priv, char *ifname);
	int				(*get_apmode)(void *priv, char *ifname);
	int				(*set_apmode)(void *priv, char *ifname, int apmode);
	int				(*get_hwmode)(void *priv, char *hwmode);
	int				(*set_hwmode)(void *priv, char *hwmode);
	int				(*get_htbw)(void *priv, char *htbw);
	int				(*set_htbw)(void *priv, char *htbw);
	int				(*get_busytime)(void *priv, busy_info_t *busyinfo);
	int				(*get_vga)(void *priv);
	int				(*set_vga)(void *priv, int val);
	int				(*get_lowrssi)(void *priv, char *ifname);
	int				(*set_lowrssi)(void *priv, char *ifname, int rssi);
	int				(*set_country)(void *priv, char *country);
	int				(*get_chlist)(void *priv, chan_list_t *chlist);
	int				(*get_channel)(void *priv);
	int				(*set_channel)(void *priv, int channel, int chextoffset);
	int				(*get_chext)(void *priv);
	int				(*set_chext)(void *priv, int chextoffset);
	int				(*get_ssid)(void *priv, char *ifname, u_int8_t *ssid, int *ssid_len);
	int				(*set_ssid)(void *priv, char *ifname, u_int8_t *ssid, int ssid_len);
	int				(*get_bssid)(void *priv, char *ifname, u_int8_t *bssid);
	int				(*set_bssid)(void *priv, char *ifname, u_int8_t *bssid);
	int				(*set_devid)(void *priv, unsigned int devid);
	int				(*get_hidden)(void *priv, char *ifname);
	int				(*set_hidden)(void *priv, char *ifname, int enabled);
	int				(*get_isolate)(void *priv, char *ifname);
	int				(*set_isolate)(void *priv, char *ifname, int enabled);
	int				(*get_txpwr)(void *priv);
	int				(*set_txpwr)(void *priv, int txpwr);
	int				(*get_policy)(void *priv, char *ifname, char *policy);
	int				(*set_policy)(void *priv, char *ifname, char *policy);
	int				(*dump_acllist)(void *priv, char *ifname, int idx, u_int8_t *macaddr);
	int				(*add_aclmac)(void *priv, char *ifname, u_int8_t *macaddr);
	int				(*clr_aclmac)(void *priv, char *ifname);
	int				(*chk_aclmac)(void *priv, char *ifname);
	int				(*get_authtype)(void *priv, char *ifname, char *authtype);
	int				(*set_authtype)(void *priv, char *ifname, char *authtype);
	int				(*get_key)(void *priv, char *ifname, char *key);
	int				(*set_key)(void *priv, char *ifname, u_int8_t *key, int key_len);
	int				(*set_pmk)(void *priv, u_int8_t *macaddr, u_int8_t *pmk);
	int				(*dump_stainfo)(void *priv, char *ifname, int idx, sta_info_t *stainfo);
	int				(*dump_apinfo)(void *priv, int idx, ap_info_t *apinfo);
	int				(*dump_wdsinfo)(void *priv, int idx, wds_info_t *wdsinfo);
	int				(*set_scan)(void *priv, u_int8_t *ssid, int ssid_len);
	int				(*set_wsc_on)(void *priv, char *ifname, u_int8_t *reqaddr);
	int				(*set_wsc_off)(void *priv, char *ifname);
	int				(*set_deauth)(void *priv, char *ifname, u_int8_t *macaddr);
	int				(*set_deny)(void *priv, u_int8_t *macaddr);
	int				(*set_authresp)(void *priv, u_int8_t *macaddr);
	int				(*get_repeater)(void *priv);
	int				(*set_repeater)(void *priv, int enabled);
	int				(*get_smt)(void *priv);
	int				(*set_smt)(void *priv, int enabled);
	int				(*tx_eap)(void *priv, u_int8_t *macaddr, u_int8_t *data, int data_len);
	int				(*set_appie)(void *priv, char *ifname, u_int8_t *data, int data_len);
	int				(*tx_frame)(void *priv, u_int32_t fctl, u_int8_t *macaddr, u_int8_t *data, int data_len);
};

extern int nlwifi_register_dev(const char *devname, void *priv, struct nlwifi_ops *ops);
extern void nlwifi_unregister_dev(const char *devname);
extern int nlwifi_eap_notify(const char *ifname, u_int8_t *macaddr, u_int8_t *data, u_int32_t len);
extern int nlwifi_action_notify(const char *ifname, u_int8_t *macaddr, const char *action);
extern int nlwifi_event_notify(const char *ifname, u_int8_t *macaddr, const char *action, const char *data);
extern int nlwifi_probe_notify(const char *ifname, u_int8_t *macaddr, unsigned int devid, int rssi);
extern int nlwifi_profile_notify(const char *ifname, u_int8_t *macaddr, const char *ssid, const char *key, const char *auth, char *groupid);
extern int nlwifi_smtinfo_notify(const char *ifname, u_int8_t *bssid, u_int8_t *daddr, u_int8_t *saddr);
extern int nlwifi_joylink_notify(const char *ifname, u_int8_t *bssid, u_int8_t *ssid,
	u_int8_t ssidlen, u_int8_t *spec, u_int8_t speclen, u_int8_t rssi0, u_int8_t rssi1);
extern int nlwifi_uplus_notify(const char *ifname, u_int8_t *bssid, u_int8_t *ssid, u_int8_t ssidlen, u_int8_t rssi);
#endif /* _NLWIFI_H_ */
