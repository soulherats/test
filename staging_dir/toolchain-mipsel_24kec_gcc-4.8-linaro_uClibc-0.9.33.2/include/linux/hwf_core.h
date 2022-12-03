#ifndef __HWF_CORE_H__
#define __HWF_CORE_H__
#include <linux/proc_fs.h>
#include <linux/hwf_core_userspace.h>
#include <linux/hwf_panic_logger.h>

#define HWF_BUF_SIZE		256
#define HWF_LOG_CTL_SIZE	2

#define HWF_ACTION_LEN		3
#define HWF_ACTION_SIZE		((1<<HWF_ACTION_LEN))

enum hwf_module_id {
	HWF_MODULE_CORE,
	HWF_MODULE_KPROXY,
	HWF_MODULE_SQOS,
	HWF_MODULE_PROSTAT,
	HWF_MODULE_IPSTAT,
	HWF_MODULE_DPI,
	HWF_MODULE_SYSLOG,	
	HWF_MODULE_XT_TIME_CONF,
	HWF_MODULE_KSPEED,
	HWF_MODULE_NUM
};

struct hwf_module_info {
	enum hwf_module_id		id;
	const char				*name;
	unsigned short			err_num;
	const char				**err_str;
	const char				*log_name;
	unsigned int			log_level;
	struct ctl_table		log_ctl[HWF_LOG_CTL_SIZE];
	struct hwf_panic_info	panic_info;
	struct ctl_table_header *log_ctl_header;
}; 

#ifndef NO_HIWIFI_EXT
//Max size of hwf_ct_ext_s must be 8 bytes.
struct hwf_ct_ext_s {
	void *					syn_skb;			//For kproxy, this must be ahead of any other member
	unsigned int			user_id: 8;			// For Smartqos
	unsigned int			priority: 2;		// For Smartqos
	unsigned int			is_guest: 1;		// For Smartqos
	unsigned int			is_stat_only: 2;	// For Smartqos
	unsigned int			is_marked: 1;		// For Smartqos
	unsigned int			ct_state: 2;			// For Kproxy
} __attribute__((packed));
#define HWF_CT_EXT(__ct)	((struct hwf_ct_ext_s *)((__ct)->hwf_ext))

//Max size of hwf_skb_ext_s must be 16 bytes.
struct hwf_skb_ext_s {
	__u32 					init_seq;			//For Kproxy, this must be ahead of any other member
    unsigned short 			pkt_len;
    unsigned int		 	is_guest: 1;
    unsigned int			is_stat_only: 1;
    unsigned int			is_lan: 1;
    unsigned int			priority: 2;
    unsigned int			user_id: 8;
	unsigned int			action_type: HWF_ACTION_LEN;		//record kproxy action
    void *					user;
};
#define HWF_SKB_EXT(__skb)	((struct hwf_skb_ext_s *)((__skb)->hwf_ext))	

#endif

extern int hwf_core_register_module(struct hwf_module_info *module);
extern void hwf_core_unregister_module(const struct hwf_module_info *module);

#endif
