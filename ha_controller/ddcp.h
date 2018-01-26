/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: ddcp.h
 *  Author: zhouji
 *  Version: V1.0
 *  Date: 2017/07/06
 *  Description:    定义代理端与灾备机，监控中心与代理端，监控中心与灾备机
 *                  之间的通信协议规范
 * 
 *  Function List:
 *
 *  History:
 *      <author>   <time>  <version>  <desc>        
 *       zhouji   17/07/06    1.0     构建这个模块
\************************************************************************/


#ifndef _DDCP_H_
#define _DDCP_H_ 

#include "common.h"
#include "num_types.h"


/* 设置内存对齐方式为1字节对齐，保证客户端、服务端交互时，数据长度的一致性*/
#pragma pack(push)
#pragma pack(1)

/*
 *  任务状态的定义
 */
typedef enum _task_status_e{
	TASK_STATUS_CREATE = 0,                             //新建任务
	TASK_STATUS_FULL_SYNC_VOL,                          //在线同步数据（完全同步）
	TASK_STATUS_DIFF_SYNC_VOL,                          //在线同步数据（差异同步）
	TASK_STATUS_PH_PROVIDE_SVC,                         //生产服务器提供服务
	TASK_STATUS_IMPORTING_SYNC_DATA,                    //导入离线同步数据
	TASK_STATUS_WAITING_PH_START,                       //等待生产服务器启动
	TASK_STATUS_SVC_STOPED,                             //服务停止
	TASK_STATUS_MOVEBACKING_SVC_MIRROR_DIFF,			//正在回切(镜像恢复阶段（差异恢复）)
	TASK_STATUS_MOVEBACKING_SVC_MIRROR_FULL,			//正在回切(镜像恢复阶段（完全恢复）)
	TASK_STATUS_MOVEBACKING_SVC_CHANGE,					//正在回切（变化数据恢复阶段）
	TASK_STATUS_TAKEOVERING_SVC,                        //正在接管
	TASK_STATUS_DRH_PROVIDE_SVC,                        //灾备机提供服务
	TASK_STATUS_EXPORTING_RECOVER_DATA,                 //导出恢复数据
	TASK_STATUS_WAITING_TO_FINISH,                      //等待回切完成
	TASK_STATUS_STOPPING,                               //正在停止任务
	TASK_STATUS_STOPPED,                                //停止任务
	TASK_STATUS_DELETING,                               //正在删除任务

	TASK_STATUS_MAX                                     //大于等于该值，为错误状态
}task_status_e;


/*
 *  任务错误状态的定义
 */
typedef enum _task_err_status_e{
    TASK_ERR_STATUS_NO_ERR = 0,                         //无错误
    TASK_ERR_STATUS_DRC_NETCARD_ERR,					//灾备机网卡有问题
    TASK_ERR_STATUS_DRC_NO_MEM,							//灾备机内存不足
}task_err_status_e;

/*
 *  标签点类型的定义
 */
typedef enum _label_type_e{
    LABEL_TYPE_MANUAL = 1,							//手动标签点
    LABEL_TYPE_ATUO,								//自动标签点
    LABEL_TYPE_CONSIST,								//一致性标签点
}label_type_e;



/*
 *  DDCP请求消息，协议头部
 */
typedef struct _ddcp_hdr {
    __u8      packet_type:4,    /* 包类型 */
              sender_role:4;    /* 发送者角色 */
    __u8      control_cmd;      /* 控制码 */
    __u32     task_id;          /* 任务ID */
    __u32     packet_len;       /* 协议数据长度 */
    char      packet[0];        /* 指向协议数据 */
}ddcp_hdr, *pt_ddcp_hdr;


/*
 *  DDCP请求消息，协议头包类型packet_type定义
 */
typedef enum _ddcp_type_e{
    DDCP_TYPE_CONTROL =0,               /* 控制数据 */
    DDCP_TYPE_REQUEST,                  /* 请求信息 */
    DDCP_TYPE_DATA,                     /* 数据 */
    DDCP_TYPE_HEART_BEAT,               /* 心跳包 */
    DDCP_TYPE_RSP,                      /* 响应包 */
    
    /*
     *  文本数据（用于平台之间的通信）
     *  其协议数据格式为：
     *          cmd:消息控制码&参数名1:参数值1[&….]
     *  针对该类型请求消息的响应消息格式为：
     *          cmd:消息控制码&status:状态码&参数名1:参数值1[&….]
     */
    DDCP_TYPE_STRING = 10
}ddcp_type_e;

/*
 *  DDCP请求消息，协议头发送者角色sender_role定义
 */
typedef enum _ddcp_cmd_sender_role_e{
    DDCP_ROLE_PRODUCT_HOST = 1,         /* 生产服务器 */
    DDCP_ROLE_DISASTER_RECOVERY_HOST,   /* 容灾服务器 */
    DDCP_ROLE_DRILL_HOST,               /* 演练服务器 */
    DDCP_ROLE_MONITOR_CENTER,           /* 监控中心 */
    DDCP_ROLE_DISASTER_RECOVERY_CENTER  /* 灾备机 */
}ddcp_cmd_sender_role_e;

/* 
 *  DDCP请求消息，协议头控制码control_cmd定义
 */
typedef enum _ddcp_cmd_e{
    /* --- 用于type为TYPE_CONTROL的cmd命令号 --- */
    DDCP_CMD_CREATE_TASK = 0,               /* 创建任务 */
    DDCP_CMD_START_TASK,                    /* 开始任务 */
    DDCP_CMD_DIFF_SYNC_SYS_VOL,             /* 请求差异同步系统卷 */
    DDCP_CMD_FULL_SYNC_SYS_VOL,             /* 请求完全同步系统卷 */
    DDCP_CMD_DIFF_SYNC_VOL,                 /* 开始差异同步1个卷 */
    DDCP_CMD_FULL_SYNC_VOL,                 /* 开始完全同步1个卷 */
    DDCP_CMD_START_BACKUP,                  /* 开始实时备份数据 */
    DDCP_CMD_MANUAL_SET_LABEL,              /* 手动设置标签点 */
    DDCP_CMD_AUTO_SET_LABEL,                /* 自动设置标签点 */
    DDCP_CMD_AUTO_SET_CONSIST_LABEL,        /* 自动设置数据一致性时间标签点 */
    DDCP_CMD_TAKE_OVER_APP,                 /* 接管服务 */
    DDCP_CMD_TAKE_OVER_APP_FINISH,          /* 接管服务完全 */
    DDCP_CMD_MOVE_BACK_APP,                 /* 回切服务 */
    DDCP_CMD_MONITOR_VOL_CHANGE,            /* 请求监控卷变化 */
    DDCP_CMD_FULL_RECOVER_MIRROR_DATA,      /* 完全恢复镜像数据 */
    DDCP_CMD_DIFF_RECOVER_MIRROR_DATA,      /* 差异恢复镜像数据 */
    DDCP_CMD_FULL_RECOVER_VOL,              /* 完全恢复1个卷 */
    DDCP_CMD_DIFF_RECOVER_VOL,              /* 差异恢复1个卷 */
    DDCP_CMD_RECOVER_MIRROR_DATA_FINISH,    /* 镜像数据恢复完成 */
    DDCP_CMD_STOP_APP_AND_SEND_CHANGE,      /* 请求停止应用&开始发送变化数据 */
    DDCP_CMD_SEND_CHANGE_RECORD_FINISH,     /* 发送变化数据完成 */
    DDCP_CMD_RECOVER_CHANGE_RECORD,         /* 恢复变化数据 */
    DDCP_CMD_RECOVER_CHANGE_RECORD_FINISH,  /* 恢复变化数据完成 */
    DDCP_CMD_STOP_TASK,                     /* 停止任务 */
    DDCP_CMD_DESTROY_TASK,                  /* 删除任务 */
    DDCP_CMD_IMPORT_OFFLINE_SYNC_DATA,      /* 导入离线同步数据 */
    DDCP_CMD_EXPORT_RECOVER_DATA,           /* 导出离线恢复的数据 */
    DDCP_CMD_CREATE_DRILL_HOST,             /* 开始服务演练 */
    DDCP_CMD_DESTROY_DRILL_HOST,            /* 取消服务演练 */
    DDCP_CMD_DELETE_BAKSET,                 /* 删除备份集 */
    DDCP_CMD_CREATE_CONN_CONTROL,           /* 代理端要求建立控制连 */
    DDCP_CMD_CREATE_CONN_CHANGE_RECORD,     /* 代理端要求建立数据连接（传输变化数据） */
    DDCP_CMD_CREATE_CONN_SYNC_RECOVER,      /* 代理端要求建立数据连接（传输同步数据|镜像恢复数据） */
    DDCP_CMD_CREATE_CONN_MONITOR,           /* 代理端要求建立监听连接 */
    DDCP_CMD_STOP_APP,                      /* 请求停止应用 */
    DDCP_CMD_START_VM,                      //要求启动虚拟机
    DDCP_CMD_STOP_VM,                       //要求关闭虚拟机
    DDCP_CMD_RESTART_VM,                    //要求重启虚拟机


    /* --- 用于type为TYPE_REQUEST的cmd命令号 --- */
    DDCP_CMD_DIFF_SYNC_MD5 = 100,           /* 差异同步中请求对比MD5 */
    DDCP_CMD_DIFF_RECOVER_MD5,              /* 差异恢复中请求对比MD5 */
    DDCP_CMD_GET_RECOVER_DATA,              /* 恢复数据 */
    DDCP_CMD_GET_NIC_INFO,                  /* 获取网卡信息 */
    DDCP_CMD_CHECK_COMPUTRES_ENOUGH,        /* 检测虚拟计算容量 */
    
    /* --- 用于type为TYPE_DATA的cmd命令号 --- */
    DDCP_CMD_SEND_SYNC_DATA = 120,          /* 同步的数据(差异同步或完全同步) */
    DDCP_CMD_CHANGE_RECORD,                 /* 实时变化的数据 */
    
    /* --- 用于type为TYPE_HEART_BEAT的cmd命令号 --- */
    DDCP_CMD_HEART_BEAT = 150               /* 心跳数据包 */
    
    /* --- 用于type为TYPE_STRING的cmd命令号 --- */
    
}ddcp_control_cmd_e;

/*
 * 对连接类型的定义
 */

typedef enum _ddcp_conn_type{
    CONN_TYPE_UNKNOWN = 0,          /* 未知 */
    CONN_TYPE_CONTROL,              /* 控制连接 */
    CONN_TYPE_CHANGE_RECORD,        /* 数据连接（传输变化数据） */
    CONN_TYPE_SYNC_RECOVER,         /* 数据连接（传输同步数据|镜像恢复数据） */
    CONN_TYPE_MONITOR,              /* 监听连接 */
}ddcp_conn_type_e;

/*
 *  针对packet_type不为TYPE_STRING的DDCP请求消息，DDCP响应消息的协议头部
 */
typedef struct _ddcp_rsp_hdr{
    __u64   packet_no;              /* 响应包号 */
    __u32   task_id;                /* 任务ID */
    __u8    status;                 /* 响应结果 */
    __u32   packet_len;             /* 响应数据详情长度 */
    char    packet[0];              /* 指向响应数据详情 */
}ddcp_rsp_hdr, *pt_ddcp_rsp_hdr;

/*
 *  DDCP响应消息，协议头部响应结果status的定义
 */
typedef enum _ddcp_rsp_status_e{
    /* --- 成功处理 --- */
    DDCP_STATUS_SUCCESS = 0,                     /* 操作成功 */
    DDCP_STATUS_DATA_MD5_SAME = 1,               /* 数据MD5值相同 */
    DDCP_STATUS_DATA_MD5_DIFF = 2,               /* 数据MD5值不同 */
    /* 还可补充其他信息 */
    DDCP_STATUS_SUCCESS_MAX = 20,                /* 成功处理的最大值 */
    
    /* --- 错误信息 --- */
    DDCP_STATUS_ERR_UNKNOWN_TYPE = 30,          /* 不存在的类型 */
	DDCP_STATUS_ERR_UNKNOWN_CONTROL_CMD,        /* 不存在的控制命令 */
	DDCP_STATUS_ERR_UNKNOWN_ROLE,               /* 不存在的发送者角色 */

	DDCP_STATUS_ERR_NO_ENOUGH_RES_CPU,          /* 虚拟CPU资源资源不足 */
	DDCP_STATUS_ERR_NO_ENOUGH_RES_MEM,          /* 虚拟内存资源资源不足 */
	/* 补充... ... */
	DDCP_STATUS_ERR_DATA,                      	/* 发送过来的数据有误，无法识别 */
	DDCP_STATUS_ERR_TASK_STATUS,               	/* 发送的数据和任务状态对应不上 */
	DDCP_STATUS_ERR_NOTASK,                   	/* 没有这个任务 */
	DDCP_STATUS_ERR_DB_OP_FAILED,              	/* 数据库操作失败 */
	DDCP_STATUS_ERR_NOSPACE,					/* 存储空间不足 */
	DDCP_STATUS_ERR_NO_OFFLINE_DEVICE,			/* 离线存储介质未就绪 */
	DDCP_STATUS_ERR_OFFLINEDEVICE_NOSPACE,		/* 离线存储介质空间不足 */
	DDCP_STATUS_ERR_DRC_NETCARD_ERR,            /* 灾备机网卡有问题 */
	DDCP_STATUS_ERR_ALREADY_DRILL,            	/* 已有演练在进行中 */
	DDCP_STATUS_ERR_NO_DRILL,            		/* 没有演练在进行中 */
	DDCP_STATUS_ERR_BAKSET_USING,            	/* 此备份集正在被使用中 */
	DDCP_STATUS_ERR_OFFLINESYNC_INFO_ERR,		/* 离线同步信息不匹配或者有问题 */
	DDCP_STATUS_ERR_DRILL_NOT_STOP,            	/* 删除失败，有演练正在运行 */
	DDCP_STATUS_ERR_VM_NOT_ONLINE,            	/* 和虚拟容灾服务器的通信失败 */
	DDCP_STATUS_ERR_NO_MEM,            			/* 灾备机内存不足 */
	DDCP_STATUS_ERR_NO_VM,            			/* 不存在虚拟机 */

    //add by lzn
    DDCP_STATUS_ERR_MALLOC_ERROR,				/* 初始化变量分配空间失败*/
    DDCP_STATUS_ERR_SEND_AND_RECEIVE_ERROR,		/* 发送接收数据失败*/
    DDCP_STATUS_ERR_START_MONITOR_ERROR,		/* 开启卷过滤驱动失败*/
    DDCP_STATUS_ERR_START_SYS_ERROR,			/* 启动同步线程失败*/
    DDCP_STATUS_ERR_SYS_ERROR,					/* 同步数据失败*/

    //add by tw
    DDCP_STATUS_ERR_RECV_DATA,                  /* 接收数据失败 */
    DDCP_STATUS_ERR_UNKNOWN_STRING_CMD,         /* 不存在的DDCP string cmd命令 */
	DDCP_STATUS_ERR_TASK_ALRENDY_EXSIT,         /* 任务已经存在 */
	DDCP_STATUS_ERR_CONNECT_DRC,                /* 连接到灾备机失败*/
	DDCP_STATUS_ERR_DOWNLOAD_TASK,         		/* 下载任务信息失败*/
	DDCP_STATUS_ERR_SYNC_THREAD,                /* 同步线程出错--数据同步失败*/
	DDCP_STATUS_ERR_OP_MONITOR_DRIVE,           /* 操作监控驱动程序有误 */
	DDCP_STATUS_ERR_SAVE_TASKINFO,              /* 保存-修改任务信息失败 */
	DDCP_STATUS_ERR_TASK_IS_RUNNING,            /* 任务正在运行 */
	DDCP_STATUS_ERR_HEART_BEAT,                 /* 心跳检测失败 */
	DDCP_STATUS_ERR_RECOVERY,                   /* 任务恢复失败--备份卷中有系统盘，不能在线回切 */
	DDCP_STATUS_ERR_MONITOR_THREAD,             /* 创建监听线程失败 */
	DDCP_STATUS_ERR_NOT_SYS_VOL,                /* 不是系统卷*/
	DDCP_STATUS_ERR_THREAD,                     /* 创建同步系统卷线程失败*/
	DDCP_STATUS_ERR_STOP_APP,                   /* 停止应用失败 */
	DDCP_STATUS_ERR_UMOUNT_VOL                  /* 卸载卷失败 */
}ddcp_rsp_status_e;


/* -------------------- DDCP请求消息 协议数据 -------------------- */
/*
 *  新建任务请求中，备份卷详情
 */
typedef struct _bak_vol_info{
    char            vol_name[VOL_NAME_LEN];         /* 卷名称 */
    __u64           vol_size;                       /* 卷大小 */
    __u64           vol_val_size;                   /* 卷有效数据空间大小 */
    __u16           vol_fs_type;                    /* 卷文件系统类型 */
    char            mount_point[PATH_NAME_LEN];     /* 卷挂载路径 */
    char            vol_uuid[VOL_UUID_LEN];         /* 卷文件系统UUID */
    /*
     *  标识信息，第1低位表示是否为启动卷
     *            第2低位表示是否需要备份
     */
#define check_is_bootable(bak_vol)  (bak_vol)->flag & 0x01
#define check_is_backup(bak_vol)    (bak_vol)->flag & 0x02
#define vol_set_bootable_bit(bak_vol)  (bak_vol)->flag |= 0x01
#define vol_set_backup_bit(bak_vol)    (bak_vol)->flag |= 0x02
    __u8            flag;
}bak_vol_info, *pt_bak_vol_info;

/*
 *  卷文件系统类型
 */
typedef enum _vol_fs_type_e{
    VOL_FS_TYPE_FAT32 = 0,                          /* FAT32 */
    VOL_FS_TYPE_NTFS,                               /* NTFS */
    VOL_FS_TYPE_XFS,                                /* XFS */
    VOL_FS_TYPE_EXT4,                               /* EXT4 */
    VOL_FS_TYPE_EXT3,                               /* EXT3 */
    
    VOL_FS_TYPE_UNKNOWN = 200                       /* 未知文件系统类型 */
    /*  补充其他 */
}vol_fs_type_e;
 
/*
 *  备份应用系统类型
 */
typedef enum _app_type_e{
    APP_TYPE_ORACLE = 0,                            /* ORACLE数据库 */
    APP_TYPE_SQLSERVER = 1,                         /* SQL SERVER数据库 */
    APP_TYPE_MYSQL = 2,                             /* MYSQL数据库 */
    APP_TYPE_OTHER = 3,                             /* 其他未知应用系统 */

    APP_TYPE_MAX                                    /* 类型总数 */
}app_type_e;
 
/*
 *  新建任务请求中，备份应用系统详情
 */
typedef struct _bak_app_info{
    __u8  app_type;                                 /* 应用系统类型：见app_type_e中的定义 */
    char  app_name[APP_NAME_LEN];                   /* 应用系统名称 */
    __u8  ins_count;                                /* 数据库应用实例数量 */
    char  db_instance[MAX_INS_COUNT][INS_NAME_LEN]; /* 数据库应用实例名称 */

    char  start_script[PATH_NAME_LEN];              /* 应用启动脚本路径 */
    char  stop_script[PATH_NAME_LEN];               /* 应用停止脚本路径 */
    char  check_script[PATH_NAME_LEN];              /* 应用状态检查脚本路径 */
}bak_app_info, *pt_bak_app_info;

/*
 *  DDCP请求消息，协议数据：新建任务请求；其中协议头部字段值如下：
 *      task_type: TYPE_CONTROL
 *      control_cmd: CMD_CREATE_TASK
 */
typedef struct _ddcp_p1_new_task
{
    __u32           user_id;                        /* 管理员用户ID */
    char            product_uuid[HOST_UUID_LEN];    /* 生产服务器UUID */

    __u32           bak_vol_count;                  /* 备份卷数量 */
    bak_vol_info    bak_vols[MAX_VOL_COUNT];        /* 备份卷信息 */

    __u8  app_count;                                /* 备份应用系统数量 */
    bak_app_info    bak_apps[MAX_APP_COUNT];        /* 备份应用系统详情 */

    __u32           hb_interval;                    /* 心跳检测时间 */
    __u32           hb_disconn;                     /* 宕机标准 */
    char            virt_ip[IP_LEN];                /* 虚拟IP地址 */
    char            virt_ip_netmask[IP_LEN];        /* 虚拟IP子网掩码 */
    char            default_gw[IP_LEN];             /* 默认网关 */

    char            product_svcnic_name[NIC_NAME_LEN];/* 生产服务器服务接口名称 */
    char            product_svcnic_mac[NIC_MAC_LEN];/* 生产服务器服务接口MAC地址 */
    char            drc_svcnic_name[NIC_NAME_LEN];  /* 灾备机服务接口名称 */
    char            drc_svcnic_mac[NIC_MAC_LEN];   /* 灾备机服务接口MAC地址 */

    __u8            svc_takeover_method;            /* 服务接管方式 */
    __u8            tactics_type;                   /* 标签点策略类型 */
    char            tactics_content[TACTICS_CONTENT_LEN];/* 标签点策略详情 */
    __u32           reserve_bakset;                 /* 备份集最大归档数量 */
    __u32           virt_cpu;                       /* 虚拟CPU资源 */
    __u32           virt_mem;                       /* 虚拟内存资源 */
    char            task_name[TASK_NAME_LEN];       /* 任务名称 */
    char            product_os[OS_NAME_LEN];        /* 生产服务器操作系统 */

    __u8            ssl_enable;                     /* 灾备机HA服务是否启用SSL */
    __u8            compress_enable;                 /* 灾备机HA服务是否启用压缩 */
    __u8            is_support_cdp;                 /* 备份卷是否需要CDP */

#define SYS_PARTIOTION_TYPE_MBR     /* MBR分区 */
#define SYS_PARTIOTION_TYPE_GPT     /* GPT分区 */
    __u8            sys_partition_type;             /* 系统分区类型 */
    __u16           boot_loader_size;               /* 启动盘启动记录大小 */
    char            boot_loader_record[MAX_BL_SIZE];/* 启动盘启动记录详情 */
}ddcp_p1_new_task, *pt_ddcp_p1_new_task;


 
/*
 * DDCP请求消息，协议数据：心跳包。其中协议头部字段值如下：
 *      task_type: TYPE_HEART_BEAT
 *      control_cmd: CMD_HEART_BEAT
 */
typedef struct _ddcp_p1_heart_beat{
    __u8            product_task_status;            /* 代理端任务状态 */
    __u64           timestamp;                      /* 代理端最新时间点戳 */

#define PRODUCT_HEALTH_INVALID          6           /* 健康状态：无效 */
#define PRODUCT_HEALTH_HEALTHY          1           /* 健康状态：健康 */
#define PRODUCT_HEALTH_NIC_FAULT        2           /* 健康状态：网卡故障 */
#define PRODUCT_HEALTH_APP_FAULT        3           /* 健康状态：应用系统故障 */
#define PRODUCT_HEALTH_NIC_APP_FAULT    4           /* 健康状态：网卡&应用系统故障 */
#define PRODUCT_HEALTH_NO_HEARTBEAT     5           /* 健康状态：心跳断开 */

    __u8            product_health;                 /* 代理端健康状态 */
    __u32           packet_len;                     /* 包长度=sizeof(fault_info)*故障数量 */
    char            packet[0];                      /* 包详情 */
}ddcp_p1_heart_beat, *pt_ddcp_p1_heart_beat;
 
/*
 *  故障详情
 */
typedef struct _fault_info{
#define FAULT_TYPE_NIC  0                           /* 故障类型：网卡故障 */
#define FAULT_TYPE_APP  1                           /* 故障类型：应用故障  */
    __u8            fault_type;                     /* 故障类型 */
    char            name[MAX_NAME_LEN];             /* 故障网卡或故障应用系统名称（含实例名称） */

#define FAULT_REASON_NIC_DOWN           0           /* 网卡未启动 */
#define FAULT_REASON_NIC_NO_CARRIER     1           /* 网卡掉线 */
#define FALUT_REASON_APP_CANNOT_START   2           /* 应用系统无法启动，补充其他原因 */
    __u8            reason;                         /* 故障原因，根据具体故障类型，来确认故障原因 */
}fault_info, *pt_fault_info;
 
/*
 *  DDCP请求消息，协议数据：变化数据包。其中协议头部字段值如下：
 *      task_type: TYPE_DATA
 *      control_cmd: CMD_CHANGE_RECORD
 */
typedef struct _ddcp_p1_change_record{
    __u32           packet_no;                      /* 包编号 */
    __u64           timestamp;                      /* 改变时间 */
    char            vol_name[VOL_NAME_LEN];         /* 变化数据的所属卷的卷名称 */
    __u64           offset;                         /* 变化数据相对卷的开始偏移值 */
    __u32           data_len;                       /* 变化数据的长度，单位字节 */
    char            data[0];                        /* 改变后的数据 */
}ddcp_p1_change_record, *pt_ddcp_p1_change_record; 
 
 
/*
 *  DDCP请求消息，协议数据：开始同步卷n请求。其中协议头部字段值如下：
 *      task_type: TYPE_CONTROL
 *      control_cmd: CMD_DIFF_SYNC || CMD_FULL_SYNC
 */
typedef struct _ddcp_p1_vol_info{
    char            vol_name[VOL_NAME_LEN];         /* 同步卷名称 */
    __u64           offset;                         /* 开始同步的卷偏移 */

    /* 
     *  标识信息，第1低位表示是否为启动卷
     *            第2低位表示是否需要备份
     */
    __u8            flag;
}ddcp_p1_vol_info, *pt_ddcp_p1_vol_info;
 
 
/*
 *  DDCP请求消息，协议数据：同步数据m请求。其中协议头部字段值如下：
 *      task_type: TYPE_DATA
 *      control_cmd: CMD_SEND_SYNC_DATA 
 */
typedef struct _ddcp_p1_vol_data{
    union{
        __u64           packet_no;                      /* 数据包编号，即数据在卷上起始偏移值 */
        __u64           offset;                         /* 起始偏移值 */
    };
    __u32           data_len;                       /* 数据长度 */
    char            data[0];                        /* 发送的数据 */
}ddcp_p1_vol_data, *pt_ddcp_p1_vol_data;
 
 
/*
 *  DDCP请求消息，协议数据：同步数据m md5值对比请求。其中协议头部字段值如下：
 *      task_type: TYPE_DATA 
 *      control_cmd: CMD_SEND_SYNC_DATA
 */
typedef struct _ddcp_p1_data_md5_req{
    union{
        __u64           packet_no;                      /* 数据包编号，即数据在卷上起始偏移值 */
        __u64           offset;                         /* 起始偏移值 */
    };
    __u32           packet_len;                     /* 所属数据的长度 */
    char            md5[DIGIT_MD5_LEN];             /* 所属数据的MD5值 */
}ddcp_p1_data_md5_req, *pt_ddcp_p1_data_md5_req;
 
 
/*
 *  DDCP请求消息，协议数据：恢复数据m请求。其中协议头部字段值如下：
 *      task_type: TYPE_REQUEST
 *      control_cmd: CMD_GET_RECOVER_DATA
 */
typedef struct _ddcp_p1_data_recover{
	union{
    	__u64           packet_no;                      /* 数据包编号，即请求的数据起始偏移 */
		__u64           offset;                      /* 数据包编号，即请求的数据起始偏移 */
	};
    __u32           data_len;                       /* 请求的数据长度（当为0，表示结束） */
}ddcp_p1_data_recover, *pt_ddcp_p1_data_recover;
 
 
/* -------------------- DDCP响应消息 协议数据 -------------------- */
/*
 *  DDCP响应消息，响应数据详情：新建任务响应
 */
typedef struct _ddcp_rsp_p1_new_task{ 
    __u32       task_id;                            /* 新建的任务的任务ID */

    char        drh_svc_MAC[NIC_MAC_LEN];           /* 虚拟容灾服务器的业务接口MAC地址 */
    char        drh_hb_MAC[NIC_MAC_LEN];            /* 虚拟容灾服务器的心跳接口MAC地址 */
    char        drh_hb_ip[IP_LEN];                  /* 虚拟容灾服务器的心跳接口IP地址 */
    char        drh_hb_netmask[IP_LEN];             /* 虚拟容灾服务器的心跳IP子网掩码 */

    char        drc_hb_ip_2drh[IP_LEN];             /* 灾备机与虚拟容灾服务器通信的心跳接口IP地址 */
}ddcp_rsp_p1_new_task, *pt_ddcp_rsp_p1_new_task;
 

/*
 *  DDCP响应消息，响应数据详情：网卡详情
 */
typedef struct _ddcp_rsp_p1_nic_info {
    __u8    nic_count;                              /* 网卡数量 */
    char    nic_name[MAX_NIC_COUNT][NIC_NAME_LEN];  /* 网卡名称 */
    char    nic_mac[MAX_NIC_COUNT][NIC_MAC_LEN];    /* 网卡MAC地址 */

/* 网卡状态，可能与其他文件中的冲突。保持全工程一致 */
#ifndef NIC_STATUS_CARRIER
#define NIC_STATUS_CARRIER      21                  /* 网卡处于连接状态 */
#define NIC_STATUS_NO_CARRIER   22                  /* 网卡处于未连接状态 */
#define NIC_STATUS_DOWN         23                  /* 网卡未启动 */
#endif

    __u8    nic_status[MAX_NIC_COUNT];              /* 网卡状态 */
}ddcp_rsp_p1_nic_info, *pt_ddcp_rsp_p1_nic_info; 

/*
 *  DDCP响应消息，响应数据详情：恢复数据
 */
typedef  ddcp_p1_vol_data ddcp_rsp_p1_vol_data;

#pragma pack(pop)
 
#endif
