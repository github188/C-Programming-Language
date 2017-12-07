/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: common.h
 *  Author: zhouji
 *  Version: V1.0
 *  Date: 2017/07/06
 *  Description:    通用宏、常量的定义
 *
 *  History:
 *      <author>   <time>  <version>  <desc>        
 *       zhouji   17/07/06    1.0     构建这个模块
\************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/err.h>


#define IP_LEN                  16          /* IP地址字符串长度 */
#define MAX_TEXT_LEN            2048        /* 最大文本字符串长度 */
#define MAX_PATH_LEN            1024        /* 最大文件路径长度 */
#define MAX_SHELL_STR_LEN       1024        /* 最大shell执行命令长度 */

#define HOST_UUID_LEN           64          /* 生产服务器UUID长度 */
#define TACTICS_CONTENT_LEN     64          /* 标签点策略详情长度 */
#define TASK_NAME_LEN           32          /* 任务名称长度 */

#define NIC_NAME_LEN            16          /* 网卡名称长度 */
#define NIC_MAC_LEN             18          /* 网卡MAC地址长度 */

#define MAX_VOL_COUNT           8           /* 最大卷数量 */
#define VOL_UUID_LEN            64          /* 卷文件系统UUID长度 */
#define VOL_NAME_LEN            32          /* 卷名长度 */

#define MAX_APP_COUNT           4           /* 最大应用数量 */
#define APP_NAME_LEN            20          /* 应用名称长度 */
#define MAX_INS_COUNT           4           /* 最大（数据库）实例数量 */
#define INS_NAME_LEN            64          /* 实例名称长度 */

#define PATH_NAME_LEN           128         /* 路径名长度 */
#define OS_NAME_LEN             32          /* 操作系统名称长度 */
#define MAX_BL_SIZE             512         /* 引导记录的最大长度 */
#define MAX_NAME_LEN            64          /* 最大名称长度 */
#define DIGIT_MD5_LEN           32          /* md5摘要长度 */

#define MAX_NIC_COUNT           20          /* 一个服务器上网卡最大数量 */


#endif
