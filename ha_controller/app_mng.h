/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: app_mng.h
 *  Author: zhouji
 *  Version: V1.0
 *  Date: 2017/07/10
 *  Description:    应用管理模块，用于完成对应用系统的控制
 * 
 *  Function List:
 *
 *  History:
 *      <author>   <time>  <version>  <desc>        
 *       zhouji   17/07/10    1.0     构建这个模块
\************************************************************************/
#ifndef _HA_APP_MNG_H_
#define _HA_APP_MNG_H_

#include "ddcp.h"

/* 应用操作返回结果 */
#define APP_SUCCESS                         0   /* 操作成功 */
#define APP_ERR_ARG                         1   /* 参数错误 */
#define APP_ERR_SCRIPT_NOT_EXIST            2   /* 脚本不存在 */
#define APP_ERR_SCRIPT_INACCESSIBLE         3   /* 脚本无权访问 */
#define APP_ERR_SCRIPT_EXEC_FAILED          4   /* 脚本执行失败 */
#define APP_ERR_FAILED_START                5   /* 应用启动失败 */
#define APP_ERR_FAILED_STOP                 6   /* 应用启动失败 */
#define APP_ERR_UNKNOWN                     20  /* 未知错误 */
#define APP_STATUS_RUNNING                  30  /* 应用状态： 正在运行中 */
#define APP_STATUS_STOPPED                  31  /* 应用状态： 已停止 */
#define APP_STATUS_UNKNOWN                  32  /* 应用状态： 未知状态 */

/*
 *  Function:   app_create()
 *  Description:创建应用系统管理数据
 *  Params:     app_type, __u8, 应用系统类型
 *              app_name, char *, 应用系统名称
 *              ins_count, __u8, 数据库应用实例数量
 *              db_instance, char **, 每个数据库应用实例名称
 *              start_script, char *, 应用启动脚本路径
 *              stop_script, char *, 应用停止脚本路径
 *              check_script, char *, 应用状态检测脚本路径
 *  Return:     __u32, 结果标识信息
 *  Others:     
 */
pt_bak_app_info app_create(__u8 app_type, char *app_name, __u8 ins_count, 
        char **db_instance, char * start_script, 
        char * stop_script, char * check_script);

/*
 *  Function:   app_start()
 *  Description:启动应用系统
 *  Params:     app_info, pt_bak_app_info, 应用系统详情
 *  Return:     __u32, 结果标识信息
 *  Others:     
 */
void app_destroy(pt_bak_app_info app_info);

/*
 *  Function:   app_start()
 *  Description:启动应用系统
 *  Params:     app_info, pt_bak_app_info, 应用系统详情
 *  Return:     __u32, 结果标识信息
 *  Others:     
 */
__u32 app_start(pt_bak_app_info app_info);

/*
 *  Function:   app_stop()
 *  Description:停止应用系统
 *  Params:     app_info, pt_bak_app_info, 应用系统详情
 *  Return:     __u32, 结果标识信息
 *  Others:     
 */
__u32 app_stop(pt_bak_app_info app_info);


/*
 *  Function:   app_check_status()
 *  Description:检测应用系统状态
 *  Params:     app_info, pt_bak_app_info, 应用系统详情
 *  Return:     __u32, 应用系统状态
 *  Others:     
 */
__u32 app_check_status(pt_bak_app_info app_info);


/*
 *  Function:   app_get_detail()
 *  Description:获取应用系统详情
 *  Params:     app_info, pt_bak_app_info, 应用系统详情
 *  Return:     char *, 成功获取到应用系统详情; NULL, 获取失败
 *  Others:     
 */
char * app_get_detail(__u8 app_type);


/*
 *  Function:   app_get_data_consistency_timepoint()
 *  Description:获取应用系统数据一致性时间点
 *  Params:     app_info, pt_bak_app_info, 应用系统详情
 *  Return:     __u64, 一致性应用时间点; 0，获取一致性时间点失败
 *  Others:     
 */
__u64 app_get_data_consistency_timepoint(pt_bak_app_info app_info);


/*
 *  Function:   get_app_info()
 *  Description:获取APP信息
 *  Params:     char *, app_name, app名称
 *  Params:     char *, o_info, app信息
 *  Return:     __u64, 一致性应用时间点; 0，获取一致性时间点失败
 *  Others:
 */
int get_app_info(char * app_name, char * o_info);



__u32 app_check_status_for_start(char * app_name, char * db_instance);
#endif
