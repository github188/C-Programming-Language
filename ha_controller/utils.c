/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: utils.c
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

#include <stdio.h>
#include <errno.h>
#include <string.h>
//#include "log.h"
//#include "common.h"
#include "utils.h"
#define MAX_TEXT_LEN 2048
int exec_cmd(const char *shell_cmd, int * o_ret, 
        void (*process_line)(const char *line, void *argv), void *argv)
{
    FILE *cmd_fd = NULL;
    char buf_line[MAX_TEXT_LEN] = {0};
    int ret;
    

    if (shell_cmd == NULL) {
        return -1;
    }

    cmd_fd = popen(shell_cmd, "r");
    if (cmd_fd == NULL) {
        printf("failed to popen shell cmd `%s`, errno:%d, strerror: %s.", shell_cmd, errno, strerror(errno));
        return -1;
    }

    if (process_line) {
        while(fgets(buf_line, sizeof(buf_line), cmd_fd)) {
            while (buf_line[strlen(buf_line) - 1] == '\n') {
                buf_line[strlen(buf_line) - 1] = '\0';
            }
            process_line(buf_line, argv);
            memset(buf_line, 0, sizeof(buf_line));
        }
    }

    ret = pclose(cmd_fd);
    if (o_ret) {
        /* TODO:根据实验结果，shell_cmd执行的返回结果与pclose的返回结果关系如下 */
        *o_ret = ret >> 8;
    }
    if (ret == -1) {
        return -1;
    }

    return 0;
}
