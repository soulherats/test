/*
 * libtw: turbo wireless common library
 * Copyright (C) 2012 Elite Co., Ltd.
 * Author: LIKAI <kai@ikwcn.com>
 */
#ifndef _TW_H_
#define _TW_H_

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#define VERSION_LEN			4
#define RSA_PUB_KEY_LEN		252
#define ENC_DES_KEY_LEN		128
#define TXT_FAC_INFO_LEN	2048
#define RESERVED1_LEN		5120
#define ENC_INFO_LEN		8192
#define RESERVED2_LEN		40960
#define MD5_SUM_LEN			640

#define BDINFO_ENTRY_NAME_LEN		(64+1)
#define BDINFO_ENTRY_VAL_LEN		(128+1)
#define BDINFO_ENTRY_LIST_LEN		(TXT_FAC_INFO_LEN + ENC_INFO_LEN * 2 + 1)
/*
 * system informations
 */
#define MAX_MAC_LENGTH 13
#define MAX_VERSION_LENGTH 64
#define MAX_MODEL_LENGTH 32
#define MAX_BOARD_LENGTH 32
#define MAX_PCBA_LENGTH 32
#define MAX_UUID_LENGTH 37
#define MAX_COUNTRY_LENGTH	32
#define MAX_MAC_COLON_LENGTH	18
#define MAX_MAC_DEVICE_ID_LENGTH	32

#define TW_DEFAULT_MAC				"D4EE07000000"
#define TW_DEFAULT_MAC_COLON		"D4:EE:07:00:00:00"
#define TW_DEFAULT_UUID				"00000000-0000-0000-0000-d4ee07000000"
#define TW_DEFAULT_COUNTRY			"CN"

char *tw_get_mac(char *mac);
char *tw_get_version(char *version);
char *tw_get_model(char *model);
char *tw_get_board(char *board);
char *tw_get_pcba(char *pcba);
char *tw_get_uuid(char *uuid);
char *tw_get_country(char *country);
char *tw_get_deviceid(char *device_id);
char *tw_get_mac_colon(char *mac);
int64_t tw_get_totalram(void);
int tw_version(void);
int tw_list_entry(char *list);
int tw_check_md5(void);
int tw_check_bdinfo(void);

/*
 * Function for encoding cmagent.send payload
 */
typedef enum cmagent_send_request_qos_e {
	CMAGENT_SEND_REQUEST_QOS_LOCAL,         // 消息被cmagent正确处理后, 立刻返回成功
	CMAGENT_SEND_REQUEST_QOS_NETWORK,       // 消息被cmagent正确发送后, 立刻返回成功
	CMAGENT_SEND_REQUEST_QOS_CLOUD,         // 消息被云端接收后, 立刻返回成功
} cmagent_send_request_qos_t;

typedef char *cmagent_send_request_header_t[2];

typedef struct cmagent_send_request_s {
	char *from;                             // 必填, 消息发送者
	char *to;                               // 必填, 消息接收者
	char *key;                              // 选填, 消息类型, 或者消息关键字
	cmagent_send_request_qos_t     qos;     // 必填, 默认是CMAGENT_SEND_REQUEST_QOS_LOCAL, 即为0.
	cmagent_send_request_header_t *headers; // 选填, 其他扩展字段
	char *body;                             // 选填, 要发送的消息.
	size_t body_len;                        // 必填, 要发送的消息的大小.
} cmagent_send_request_t;

ssize_t tw_encode_cmagent_send_request(char *buffer, size_t size, const cmagent_send_request_t *request);

#endif /* _TW_H_ */
