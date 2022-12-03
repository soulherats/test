#ifndef __HWF_LOG_H__
#define	__HWF_LOG_H__
#include <linux/hwf_core.h>

enum hwf_log_level {
	HWF_EMERG	=	0,	/* system is unusable */ 
	HWF_ALERT	=	1,	/* action must be taken immediately */
	HWF_CRIT	=	2,	/* critical conditions */
	HWF_ERR		=	3,	/* error conditions */
	HWF_WARNING	=	4,	/* warning conditions */
	HWF_NOTICE	=	5,	/* normal but significant condition */		
	HWF_INFO	=	6,	/* informational */
	HWF_DEBUG	=	7,	/* debug-level messages */
	HWF_LOGNUM	=	8
};

extern void hwf_log_skb(const struct sk_buff *skb, const char *title);
extern int hwf_log_str(unsigned int level, enum hwf_module_id id, const char *func_name, unsigned int line, char *fmt, ...);
extern int hwf_log_errno(unsigned int level, enum hwf_module_id id, unsigned int line, unsigned char errno, const char *func_name, ...);
extern int hwf_log_normal(unsigned int level, enum hwf_module_id id, char *fmt, ...);
extern void hwf_log_skb_info(unsigned int level,enum hwf_module_id id,const struct sk_buff *skb,int flag,char * func);
#endif
