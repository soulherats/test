#ifndef IOS_SYSLOG_MODULE
#define IOS_SYSLOG_MODULE
enum log_modules
{
	MODULE_WEB_URL, 
	MODULE_AS_MAIL,
	MODULE_SYSTEM_NOTICE,
	MODULE_TRACK_DEBUG,
	MAX_MODULE_NUM
};


#define KEYMAP_ALT_F1		101
#define KEYMAP_ALT_F2		102
#define KEYMAP_ALT_F3		103
#define KEYMAP_CTRL_C		201
#define KEYMAP_CTRL_D		202
#define KEYMAP_CTRL_Z		203

enum
{
	SYSLOG_SKB_LEN = 1400,       //ip+mac+udp+data[1024]+more
	SYSLOG_RESERV_LEN = 1300,  //IP+mac+udp+data[1024]
	SYSLOG_MAX_DATA = 1000,
	SYSLOG_SOURCE_PORT = 514,
	SYSLOG_TTL = 60,
	MAX_SYSLOG_TIME_LEN = 20,
};

// track_debug module
enum dataflow_module
{
	TRACK_DEBUG_FLOWINFO = 0,
	TRACK_DEBUG_NAT,
	TRACK_DEBUG_URLFILTER,

	TRACK_DEBUG_DATAFLOW_MODULE_MAX
};


struct kernel_keymap_data
{
	int module_type;	
	int ketmap;		
}; 

struct syslog_config
{
	unsigned int addr;
	unsigned int port;
	unsigned int sec_addr;
	unsigned int sec_port;
	unsigned int enable;
	unsigned int mem_enable;
	unsigned int mail_enable;		
	unsigned int pad;
	unsigned int maxnumb;	
	unsigned int sendtime;		
	unsigned int kensendnumb;	//aleardy send message number
	unsigned int kensendtime;	//aleardy send time message number	
	unsigned char hostname[64];
};

struct syslog_data
{
	int type;
	int daemon;
	int priority;
	int location;
	char data[4000]; 
};

struct ios_syslog_stats
{
	u_int32_t klist_len;
	u_int32_t ulist_len;
	u_int32_t kdroped_cnt;
	u_int32_t udroped_cnt;
};

#define SYSLOGVERSION		1
#define MENUFROUI		    "D4EE07"

#define LOG_SERVER   	0x01
#define LOG_MEMORY		0x02
#define LOG_EMAIL		0x04
#define LOG_CONSOLE		0x08

#define APP_AUDIT_LOG_LOCATION (LOG_SERVER|LOG_MEMORY|LOG_EMAIL)

#ifdef __KERNEL__

enum hwf_syslog_err_code_e {
	HWF_SYSLOG_ERR_SUCCESS,
	HWF_SYSLOG_ERR_MAX
};

#define KSYSLOG_ERR(fmt, args...) hwf_log_str(HWF_ERR, HWF_MODULE_SYSLOG, __FUNCTION__, __LINE__, fmt, ##args)
#define KSYSLOG_LOG(fmt, args...) hwf_log_str(HWF_NOTICE, HWF_MODULE_SYSLOG, __FUNCTION__, __LINE__, fmt, ##args)
#define KSYSLOG_DBG(fmt, args...) hwf_log_str(HWF_DEBUG, HWF_MODULE_SYSLOG, __FUNCTION__, __LINE__, fmt, ##args)
#define KSYSLOG_SKB_INFO(skb,flag,func)          hwf_log_skb_info(HWF_DEBUG,HWF_MODULE_SYSLOG,skb,flag,func);

extern struct sk_buff_head ios_app_audit_log_ulist;

extern unsigned int ios_syslog_kernel_dropped;
extern unsigned int ios_syslog_user_dropped;
extern unsigned int ios_app_audit_log_dropped;

asmlinkage int ios_debug_out(const char *s, ...)
	__attribute__((format (printf, 1, 2)));

asmlinkage int ios_expt_log(const char *s, ...)
	__attribute__((format (printf, 1, 2)));
	
void ios_syslog(int module_type, int priority, const char *format, ...)
	__attribute__ ((format (printf, 3, 4)));

void ios_stream_syslog(int module_type, int priority, int location, const char *format, ...)
	__attribute__ ((format (printf, 4, 5)));
extern int make_send_stream_syslog(int module_type, int priority, int location, char *buf);
extern int make_send_stream_audit_log_syslog(int module_type, int priority, int location, char *buf); 

extern int make_send_syslog(int module_type, int priority, char *buf);
extern int send_data_in_kernel(int module_type, int priority, int location, char *buf);

#ifndef __IOS_ASSERT__ 
#define __IOS_ASSERT__
#define ios_assert(expr) \
	if(unlikely(!(expr))) {                                   \
		printk("Ios assertion failed! %s,%s,%s,line=%d\n", \
			#expr,__FILE__,__FUNCTION__,__LINE__);          \
		dump_stack();	\
	}
#endif
#endif  /* __KERNEL__ */

#endif