#ifndef APP_AUDIT_LOG_H
#define APP_AUDIT_LOG_H


#include <linux/if_ether.h>

#define MAX_HOST_LEN 256
#define MAX_UA_LEN 128
#define MAX_URI_LEN  512

typedef unsigned long long ullong;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct audit_http_log_info
{
	time_t time; 
	u8 type;
	//u32 srcip;
	u8 srcmac[ETH_ALEN];
	u8 host[MAX_HOST_LEN+1];
	//u8 ua[MAX_UA_LEN+1];
	//u8 uri[MAX_URI_LEN+1];
}__attribute__((packed))	audit_http_log;

#endif
