#pragma once

#include <syslog.h>

#define DATA_HOST "127.0.0.1"
#define DATA_PORT 515
#define DATA_PREFIX "data@"

#define ERR	LOG_ERR
#define LOG	LOG_INFO
#define DBG	LOG_DEBUG

#define HWF_EMG(format, args...) hwf_log(LOG_EMERG, __FUNCTION__, __LINE__, format, ##args)
#define HWF_ALR(format, args...) hwf_log(LOG_ALERT, __FUNCTION__, __LINE__, format, ##args)
#define HWF_CRI(format, args...) hwf_log(LOG_CRIT, __FUNCTION__, __LINE__, format, ##args)
#define HWF_ERR(format, args...) hwf_log(LOG_ERR, __FUNCTION__, __LINE__, format, ##args)
#define HWF_WRN(format, args...) hwf_log(LOG_WARNING, __FUNCTION__, __LINE__, format, ##args)
#define HWF_NOT(format, args...) hwf_log(LOG_NOTICE, __FUNCTION__, __LINE__, format, ##args)
#define HWF_LOG(format, args...) hwf_log(LOG_INFO, __FUNCTION__, __LINE__, format, ##args)
#define HWF_DBG(format, args...) hwf_log(LOG_DEBUG, __FUNCTION__, __LINE__, format, ##args)

#define HWF_DAT(log) hwf_log_data(log)

extern int hwf_log_init_with_level(const char *program, int sig, int level);

/*set program name and signal to switch the cur_level*/
extern int hwf_log_init(const char *program, int sig);

/*reopen then syslog conn*/
extern void hwf_log_flush(void);

/*set the log_level to control the output log*/
extern void hwf_log_set_level(int level);

/*return the log_level that set by user*/
extern int hwf_log_get_level(void);

/*return current  log_leve*/
extern int hwf_log_get_cur_level(void);

extern void hwf_log(int level, const char *func, int line, const char *format, ...);

/* Send log to server */
extern int hwf_log_data(char* log);

/* Send log to server with custom tag */
extern int hwf_log_data_with_tag(char* tag, char* log);
