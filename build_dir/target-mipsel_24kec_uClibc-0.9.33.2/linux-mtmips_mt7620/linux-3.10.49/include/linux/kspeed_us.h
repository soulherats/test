#ifndef _KSPEED_US_H
#define _KSPEED_US_H

#define MAX_NAME_LEN 16

#define MAX_CONTENT_TYPE_LEN 128

#define MAX_DOWNLOAD_URL_NUM 8

#define MAX_DOWNLOAD_PARAL_NUM 16


#define    HWF_HOST_NAME_LEN         128
#define     MAX_URI_LEN 256


#define KSPEED_NL_BUFF_LEN	1024

#define MAX_GET_HEADER_LEN 512
#define MAX_HEADER_LEN 2048

#define MAX_HTTP_RCV_LEN 4096

#define Download_Port 80

#define Max_Time 5


#define    HTTP_HEADER_GET              "GET %s HTTP/1.1\r\n" \
"Host: %s\r\n" \
"Connection: close\r\n" \
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.116 Safari/537.36\r\n" \
"Accept: */*\r\n" \
"\r\n"


enum hwf_kspeed_msg_action_e {
	HWF_KSPEED_ACTION_START=0,
	HWF_KSPEED_ACTION_STOP,
	HWF_KSPEED_ACTION_GET,
	HWF_KSPEED_ACTION_MASK = 0x0F,
};

enum kspeed_err_code_e {
        HWF_KSPEED_ERR_SUCCESS=0,
        HWF_KSPEED_ERR_PARAM=1,
        HWF_KSPEED_ERR_FAILED,
	HWF_KSPEED_ERR_CON_FAILED,
	HWF_KSPEED_ERR_MAX
};

#define HWF_KSPEED_NTLINK_MASK  0xFF

#define HWF_KSPEED_MSG_ACTION(nlmsg_type)	(nlmsg_type & HWF_KSPEED_ACTION_MASK)

#define HWF_KSPEED_MSG_TYPE(nlmsg_type)	((nlmsg_type>>8) & HWF_KSPEED_NTLINK_MASK)

#define HWF_KSPEED_NLMSG_TYPE(type, action)	(((type & HWF_KSPEED_NTLINK_MASK) << 8) + (action & HWF_KSPEED_ACTION_MASK))

#define Speed_Running 0
#define Speed_Completed 1
#define Speed_Msg(status)  (status==Speed_Running?"running":"finish")

typedef unsigned long long ullong;

/*http响应头*/
struct resp_header
{
    int status_code;//HTTP/1.1 '200' OK
    char content_type[MAX_CONTENT_TYPE_LEN];//Content-Type: application/gzip
    long content_length;//Content-Length: 11683079
};

struct download_info {
     struct sockaddr_in sa; /*url对应ip*/
     char host[HWF_HOST_NAME_LEN];
     char uri[MAX_URI_LEN];  /*有效url*/
};

struct download_param {
     int url_num;
     int parrallel_num;
     char dev_name[MAX_NAME_LEN];
};

struct download_result {
     int status;
     ullong speed;
};

#endif /*_KSPEED_US_H*/
