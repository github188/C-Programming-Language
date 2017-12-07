/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: app_mng.c
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

#include <stdio.h>
#include <unistd.h>
#include "log.h"
#include "ddcp.h"
#include "utils.h"
#include "app_mng.h"
#define PHP_PATH "/usr/local/capsheaf/fsdb/php/bin/php"
#define APP_SCRIPT_PATH "/usr/local/capsheaf/client/bin/DBOperation/appMng.php"


/*
 *  Function:   _check_file_access()
 *  Description:检测文件是否存在
 *  Params:     file_path, const char *, 文件路径
 *  Return:     __s32: 0, 成功; -1, 失败
 *  Others:     
 */
static __s32 _check_file_access(const char * file_path) 
{
    if (access(file_path, R_OK) != -1){
        return 0;
    }
    else {
        return -1;
    }
}



__u32 app_start(pt_bak_app_info app_info) 
{
    __s32   ret = -1;
    __s32   i = 0;
    char    shell_cmd[MAX_SHELL_STR_LEN] = {0};
    log_write(LOG_DEBUG5, "begin to start app");
    if (app_info == NULL) {
        return APP_ERR_ARG;
    }   

/*    if (_check_file_access(app_info->check_script) == -1
            || _check_file_access(app_info->start_script) == -1) {
        return APP_ERR_SCRIPT_NOT_EXIST;
    }*/

    /* 首先检测应用的状态，若状态为停止状态，则需要启动该应用 */
    for (i = 0; i < app_info->ins_count; i++) {
        ret = app_check_status_for_start(app_info->app_name, app_info->db_instance[i]);
        log_write(LOG_DEBUG5, "app status is %d", ret);
        if (ret == APP_STATUS_RUNNING) {
            if (i == app_info->ins_count - 1) {
                return APP_SUCCESS;
            } else {
                continue;
            }
        } else if (ret != APP_STATUS_STOPPED) {
            return ret;
        }

        /*
         *  运行启动应用系统脚本，启动应用系统. 根据脚本返回值，判断是否启动成功：
         *      返回0， 表示启动成功；
         *      返回-1， 表示启动失败；
         *      返回其他值，表示未知错误
         */
        snprintf(shell_cmd, sizeof(shell_cmd), "%s %s -t %s -a -n %s", PHP_PATH, APP_SCRIPT_PATH, app_info->app_name,
                 app_info->db_instance[i]); /* TODO: 补充完整 */
        log_write(LOG_DEBUG5, "shell_cmd:%s", shell_cmd);
        if (exec_cmd(shell_cmd, &ret, NULL, NULL) == -1) {
            return APP_ERR_SCRIPT_EXEC_FAILED;
        } else if (ret == -1) {
            return APP_ERR_FAILED_START;
        } else if (ret != 0) {
            return APP_ERR_UNKNOWN;
        }
    }

    return APP_SUCCESS;
}


__u32 app_check_status(pt_bak_app_info app_info) 
{
    char   shell_cmd[MAX_SHELL_STR_LEN] = {0};
    __s32  cmd_ret;
    __s32  i;

    if (app_info == NULL) {
        return APP_ERR_ARG;
    }

/*    if (_check_file_access(app_info->check_script) == -1) {
        return APP_ERR_SCRIPT_NOT_EXIST;
    }*/

    /*  
     *  运行查询应用系统状态脚本，获取应用系统状态. 根据脚本返回值，判断当前应用系统状态：
     *      返回30， 表示应用正在运行中； 
     *      返回31， 表示应用已停止； 
     *      返回其他值，表示未知错误
     */
    for (i = 0; i < app_info->ins_count; i++) {
        snprintf(shell_cmd, sizeof(shell_cmd), "%s %s -t %s -u -n %s", PHP_PATH, APP_SCRIPT_PATH, app_info->app_name,
                 app_info->db_instance[i]); /* TODO: 补充完整 */
        log_write(LOG_DEBUG5, "shell_cmd:%s", shell_cmd);
        if (exec_cmd(shell_cmd, &cmd_ret, NULL, NULL) == -1) {
            log_write(LOG_DEBUG5, "failed to exec shell cmd `%s`.", shell_cmd);
            return APP_ERR_SCRIPT_EXEC_FAILED;
        }

        if (cmd_ret == APP_STATUS_UNKNOWN) {
            log_write(LOG_DEBUG5, "exec shell cmd `%s`, get unknown status: %d.", shell_cmd, cmd_ret);
            return APP_ERR_UNKNOWN;
        } else if (cmd_ret == APP_STATUS_STOPPED) {
            log_write(LOG_DEBUG5, "exec shell cmd `%s`, get stopped status: %d.", shell_cmd, cmd_ret);
            return cmd_ret;
        }
    }

    return cmd_ret;
}



__u32 app_check_status_for_start(char * app_name, char * db_instance)
{
    char   shell_cmd[MAX_SHELL_STR_LEN] = {0};
    __s32  cmd_ret;

    if (app_name == NULL || db_instance == NULL) {
        return APP_ERR_ARG;
    }

/*    if (_check_file_access(app_info->check_script) == -1) {
        return APP_ERR_SCRIPT_NOT_EXIST;
    }*/

    /*
     *  运行查询应用系统状态脚本，获取应用系统状态. 根据脚本返回值，判断当前应用系统状态：
     *      返回30， 表示应用正在运行中；
     *      返回31， 表示应用已停止；
     *      返回其他值，表示未知错误
     */
    snprintf(shell_cmd, sizeof(shell_cmd), "%s %s -t %s -u -n %s", PHP_PATH, APP_SCRIPT_PATH, app_name, db_instance);
    /* TODO: 补充完整 */
    log_write(LOG_DEBUG5, "shell_cmd is %s", shell_cmd);
    if (exec_cmd(shell_cmd, &cmd_ret, NULL, NULL) == -1) {
        log_write(LOG_DEBUG5, "failed to exec shell cmd `%s`.", shell_cmd);
        return APP_ERR_SCRIPT_EXEC_FAILED;
    }

    if (cmd_ret == APP_STATUS_UNKNOWN) {
        log_write(LOG_DEBUG5, "exec shell cmd `%s`, get unknown status: %d.", shell_cmd, cmd_ret);
        return APP_ERR_UNKNOWN;
    }

    return cmd_ret;
}


__u32 app_stop(pt_bak_app_info app_info) 
{
    __s32   ret = -1;
    __s32   i;
    char    shell_cmd[MAX_SHELL_STR_LEN] = {0};
    log_write(LOG_DEBUG5, "start to stop app");
    if (app_info == NULL) {
        return APP_ERR_ARG;
    }   

/*    if (_check_file_access(app_info->check_script) == -1
            || _check_file_access(app_info->start_script) == -1) {
        return APP_ERR_SCRIPT_NOT_EXIST;
    }*/

    /* 首先检测应用的状态，若状态为正在运行中状态，则需要停止该应用 */
    for (i = 0; i < app_info->ins_count; i++) {
        ret = app_check_status_for_start(app_info->app_name, app_info->db_instance[i]);
        if (ret == APP_STATUS_STOPPED) {
            if (i == app_info->ins_count - 1) {
                return APP_SUCCESS;
            } else {
                continue;
            }
        } else if (ret != APP_STATUS_RUNNING) {
            return ret;
        }

        /*
         *  运行停止应用系统脚本，停止应用系统. 根据脚本返回值，判断是否停止成功：
         *      返回0， 表示停止成功；
         *      返回-1， 表示停止失败；
         *      返回其他值，表示未知错误
         */
        snprintf(shell_cmd, sizeof(shell_cmd), "%s %s -t %s -o -n %s", PHP_PATH, APP_SCRIPT_PATH, app_info->app_name,
                 app_info->db_instance[i]); /* TODO: 补充完整 */
        log_write(LOG_DEBUG5, "shell_cmd:%s", shell_cmd);
        if (exec_cmd(shell_cmd, &ret, NULL, NULL) == -1) {
            return APP_ERR_SCRIPT_EXEC_FAILED;
        } else if (ret == -1) {
            return APP_ERR_FAILED_STOP;
        } else if (ret != 0) {
            return APP_ERR_UNKNOWN;
        }
    }
    return APP_SUCCESS;
}

char * app_get_detail(__u8 app_type) {
    if (app_type >= APP_TYPE_MAX) {
        return NULL;
    }

    /* TODO: 当前由平台实现 */
    return NULL;
}


__u64 app_get_data_consistency_timepoint(pt_bak_app_info app_info) 
{
    if (app_info == 0 || app_info->app_type >= APP_TYPE_OTHER) {
        return 0;
    }

    /* TODO: 目前未做一致性检测 */
    return 0;
}

pt_bak_app_info app_create(__u8 app_type, char *app_name, __u8 ins_count, 
        char **db_instance, char * start_script, 
        char * stop_script, char * check_script)
{
    pt_bak_app_info app_info;
    __u32           i = 0;

    if (app_type >= APP_TYPE_MAX 
            || start_script == NULL 
            || stop_script == NULL
            || check_script == NULL
            || (app_type < APP_TYPE_OTHER 
                && (ins_count <= 0 || db_instance == NULL || ins_count > MAX_INS_COUNT))) {
        return NULL;
    }

    app_info = malloc(sizeof(bak_app_info));
    if (app_info == NULL) {
        log_write(LOG_DEBUG5, "failed to mallco bak_app_info.");
        return NULL;
    }

    memset(app_info, 0, sizeof(bak_app_info));
    app_info->app_type = app_type;
    snprintf(app_info->app_name, APP_NAME_LEN, "%s", app_name);
    app_info->ins_count = ins_count;
    for (i=0; i < ins_count && i < MAX_INS_COUNT; i++) {
        snprintf(app_info->db_instance[i], INS_NAME_LEN, "%s", db_instance[i]);
    }
    snprintf(app_info->start_script, PATH_NAME_LEN, "%s", start_script);
    snprintf(app_info->stop_script, PATH_NAME_LEN, "%s", stop_script);
    snprintf(app_info->check_script, PATH_NAME_LEN, "%s", check_script);

    return app_info;
}


void app_destroy(pt_bak_app_info app_info)
{
    if (app_info == NULL) {
        return ;
    }

    free(app_info);
}


int get_app_info(char * db_name, char * o_info)
{
    char cmd[128] = {0};
    FILE * file_temp = NULL;
    char parse_buf[128] = {0};

    snprintf(cmd, 128, "%s %s -t %s -g", PHP_PATH, APP_SCRIPT_PATH, db_name);
    log_write(LOG_DEBUG5, "cmd:%s", cmd);
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;
    }
    log_write(LOG_DEBUG5, "file_temp:%s", file_temp);
    while (!feof(file_temp)) {
        if(NULL != fgets(parse_buf, 128, file_temp)) {
            if (parse_buf[0] == '&') {
                log_write(LOG_DEBUG5, "parse_buf:%s", parse_buf);
                strncpy(o_info, parse_buf, strlen(parse_buf));
            }
        }
    }
    pclose(file_temp);
    return 1;
}
