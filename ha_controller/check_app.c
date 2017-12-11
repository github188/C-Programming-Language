#define __USE_GNU 1
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include"utils.h"
#define MAX_SHELL_STR_LEN 1024
#define PHP_PATH "/usr/local/capsheaf/fsdb/php/bin/php"
int mb_open(char* mb_vol, int* fd) {
    //int fd;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    snprintf(cmd, MAX_SHELL_STR_LEN, "%s", mb_vol);
    *fd = open(cmd, O_RDWR | O_DIRECT);
    if (fd < 0) {
        printf("open mass buffer:%s failed, and errno:%d, strerror: %s", mb_vol, errno, strerror(errno));
        fd = 0;
        return 1;

    }
    return 0;

}


int drc_system(char * cmd)
{
    int status;

    if (NULL == cmd)
    return -1;

    status = system(cmd);
    if (-1 == status) {                                        //system 执行失败   
        printf("Error in system, status == -1.");
        return -1;
    } else {                                                   //system执行成功,然后判断shell执行情况
        if (WIFEXITED(status)) {                               //shell命令执行正常终止,但执行结果未知
            if (0 == WEXITSTATUS(status)) {                    //shell命令执行成功
                return 0;
            } else {                                           //shell命令执行失败
                printf("Fail to execute [%s], exit code: %d", cmd, WEXITSTATUS(status));
                return -1;
            }
        } else {                                              //shell命令未能正常终止(被信号中断，被暂停，被kill，命令程序中bug(被信号杀死)等)
                printf("cmd is not exit normally");
                return -1;
        }
    } 

}



int main(int argc, char *argv[])
{
    int ret, fd, fds[2];
    char cmd[MAX_SHELL_STR_LEN] = {0};
    if (argc < 3) {
        printf("too few parameters\n");
        return 0;
    }

    ret = mb_open(argv[1], &fd);
    fds[0] = fd;
    snprintf(cmd, MAX_SHELL_STR_LEN, "%s appMng.php -t mysql -a -n mysqld", PHP_PATH);
    //ret = mypopen(cmd, 'r');
    if (exec_cmd(cmd, &ret, fds, 1) == -1) {
        printf("exec_cmd:%s failed",cmd);
        return 1;
    }
    if (ret==0) {
        printf("start app success.\n");
        return 0;
    }
    if (fd>0) {
        close(fd);
        fd=0;
    }
}
