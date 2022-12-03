#ifndef HWF_KDPI_NL_H
#define HWF_KDPI_NL_H
#include <linux/netlink.h>


#define MAX_RULE_INDEX 32

#define AC_BITMAP_STATE_NUM_RATIO 16
#define  BUFF_SET_SIZE  10


#define PORT_EQUAL 0
#define PORT_LARGER 1
#define PORT_LESS 2
#define PORT_NOT_INCLUDE 3
#define SPORT     0
#define DPORT     1
#define DPI_FP_MAX_NUM           65536         /*固定端口最大端口数*/
#define DPI_RULE_MAX_NUM           2000

#define MAX_FIXED_NUM 8
#define MAX_FINGER_NODE	32
#define MAX_CHAR_NUM 8

#define IN_INCLUDE	1    /* type = "vm" */
#define NOT_INCLUDE	2    /* op = '~' */
#define ADVANCE_SECURITY_DEBUG_ON  (1 << 0)
#define ADVANCE_SECURITY_DEBUG_OFF (1 << 1)

#define DPI_BUF_MAX 8192


typedef unsigned long long ullong;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;

enum vnic_devcmd_error {
	ERR_SUCCESS = 0,
	ERR_EINVAL = 1,
	ERR_EFAULT = 2,
	ERR_EPERM = 3,
	ERR_EBUSY = 4,
	ERR_ECMDUNKNOWN = 5,
	ERR_EBADSTATE = 6,
	ERR_ENOMEM = 7,
	ERR_ETIMEDOUT = 8,
	ERR_ELINKDOWN = 9,
};


/* Types of messages */

enum {
		CTRL_BASE	= 16,
		CTRL_ADVANCE_GET_GLOBAL_VAR,
		CTRL_ADVANCE_AC_ENGINE_INIT,
		CTRL_ADVANCE_SECURITY_RULE_DOWNLOAD,
		CTRL_ADVANCE_FIXED_PORT,
		CTRL_ADVANCE_SECURITY_FULL_STATES,
		CTRL_ADVANCE_SECURITY_AC_ENGINE,
		CTRL_ADVANCE_SECURITY_TIMESTAMP_DEBUG_SWITCH,
		CTRL_ADVANCE_SECURITY_AC_INFO,
		CTRL_APP_IDENTIFY_STAT_DUMP,
		CTRL_MAX,
};

/*
*  状态转换存储算法类型
*/
enum ac_mem
{
	AC_DFA_FULL,
	AC_NFA_BITMAP,
	AC_DFA_FULL_NFA_BITMAP_MIXED,
};

typedef enum app_signature_ac_io_type
{
    APP_SIGNATURE_AC_IO_STATE_NUM = 1,     /* AC 状态机个数 */
    APP_SIGNATURE_AC_IO_TRANS_TABLE = 2,   /* AC 转换表 */
    APP_SIGNATURE_AC_IO_MATCH_TABLE = 3,   /* AC 匹配表 */
    APP_FIX_PORT_TABLE = 4,
} app_signature_ac_io_type_e;


typedef struct app_signature_ac_trans_state
{
    u32   state;
    u32   fail_state;
    u32   next_state_num;
} app_signature_ac_trans_state_s;


typedef struct app_signature_ac_match_state
{
    u32   state;      /* AC子引擎终状态 */
    u16 res_len;    /* 需要保存的长度 */
    u16 id_num;     /* 该终状态下的检测规则ID个数 */
} app_signature_ac_match_state_s;


typedef struct app_signature_ac_id
{
	u32   signature_id;
	u32   parent_id;
	u16  rule_index[MAX_RULE_INDEX];
	u8  sig_natrue_index;
} app_signature_ac_id_s;

typedef struct app_sig_ac_spec
{
    u32 ac_method;
    u32 ac_threshold_state;
}app_sig_ac_spec_s;

typedef struct rule_node{
	u32     ac_id;
	u32		rule_index;
	//	char		*sign;   //留着验证注册是否正确，如果准确无误了，就可以去掉了?
	int32_t	sign_len;
	u8		match_dir;
	u32		offset;
	u32      within;
	u8		op_type;
}rule_node_t;

typedef struct rule_port
{
	u16	tdp_port[MAX_FIXED_NUM];    
	u8   flag;
}rule_port_t;

typedef struct rule_table{
	rule_node_t	sig_nature[MAX_FINGER_NODE];
	rule_port_t	dport;    
	rule_port_t	sport;
	u32  	payload_len;
	u32		ruleid;
	u32		proto_id;
	u32        parent_proto;
	u8		finger_direc;
	u8		proto_discover_type;
	u8		proto_preference;
	u8		proto_level;
	u8          before_state;
	u8          current_state;
	int          valid_sig_num;
	//int		sig_nature_num;
}rule_table_t;

typedef struct app_signature_ac_head
{
    u8 type;
    u8 engine_type;
    u16 count;
} app_signature_ac_head_s;

typedef struct app_signature_ac_state_num
{
	u32 method;
    	u32 threshold_state;
    	u32 num_states;
    	u32 min_final_state;
    	u32 match_count;
    	u32 bitmap_count;
} app_signature_ac_state_num_s;

typedef struct download_rule_table{
	rule_node_t	sig_nature[MAX_FINGER_NODE];
	rule_port_t	dport;    
	rule_port_t	sport;
	u32  	payload_len;
	u32		ruleid;
	u32		proto_id;
	u32         parent_proto;
	u32		finger_direc;
	u16         rule_index;
	u8		proto_discover_type;
	u8 		proto_preference;
	u8		proto_level;
	u8           before_state;
	u8           current_state;
	int		valid_sig_num;
	//	int		sig_nature_num;
}download_rule_table_t;


typedef struct {
	u32 app_id;
	u32 src_ip;
	ullong upload;
	ullong download;
} dpi_res; // record read from kernel


#endif /*HWF_KDPI_NL_H*/