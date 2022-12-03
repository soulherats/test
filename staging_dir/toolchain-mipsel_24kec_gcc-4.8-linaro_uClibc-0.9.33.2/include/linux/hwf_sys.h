#ifndef HWF_SYS_H
#define HWF_SYS_H

#ifdef __KERNEL__
extern int ios_get_mem_usage(void);
/* time related */
extern char *ios_get_current_localtime_nomat(void);
extern char *ios_get_current_localtime(void);
extern char *ios_get_current_utctime(void);
extern int ios_get_current_localtm(struct timespec *ts);
extern int ios_get_current_utctm(struct timespec *ts);
extern long ios_get_uptime(void);
extern char *ios_ctime(time_t timep);
extern int ios_get_current_minute(void);
#endif

#endif