/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: utils.h
 *  Author: zhouji
 *  Version: V1.0
 *  Date: 2017/07/11
 *  Description:    通用工具类函数接口
 * 
 *  Function List:
 *
 *  History:
 *      <author>   <time>  <version>  <desc>        
 *       zhouji   17/07/10    1.0     构建这个模块
\************************************************************************/

#ifndef _HA_UTILS_H_
#define _HA_UTILS_H_

#include "num_types.h"

/*
 *  Function:   exec_cmd()
 *  Description:执行shell脚本命令，并处理每行标准输出，返回脚本输出结果
 *  Params:     shell_cmd, const char *, 脚本命令
 *              o_ret, int *, 存储脚本输出结果
 *              process_lien, void (*)(const char *, void *), 回调函数，用于处理脚
 *                      本命令的每行输出
 *              argv, void *, 传递给回调函数的参数
 *  Return:     int: 0, 表示成功; -1, 表示失败
 *  Others:     
 */
int exec_cmd(const char *shell_cmd, int * o_ret, 
        void (*process_line)(const char *line, void *argv), void *argv);

#endif
