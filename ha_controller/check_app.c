#define __USE_GNU 1
#include<stdio.h>
//#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include"utils.h"
#define MAX_SHELL_STR_LEN 1024
#define PHP_PATH "/usr/local/capsheaf/fsdb/php/bin/php"
int mb_open(char* mb_vol, int fd) {
    //int fd;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    snprintf(cmd, MAX_SHELL_STR_LEN, "%s", mb_vol);
    fd = open(cmd, O_RDWR | O_DIRECT);
    if (fd < 0) {
        printf("open mass buffer:%s failed, and errno:%d, strerror: %s", mb_vol, errno, strerror(errno));
        fd = 0;
        return 1;

    }
    return 0;

}

int main(int argc, char *argv[])
{
    int ret, fd;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    if (argc < 3) {
        printf("too few parameters\n");
        return 0;
    }

    ret = mb_open(argv[1], fd);

    snprintf(cmd, MAX_SHELL_STR_LEN, "%s appMng.php -t mysql -a -n mysqld", PHP_PATH);
    if (exec_cmd(cmd, &ret, NULL, NULL) == -1) {
        printf("exec_cmd:%s failed",cmd);
        return 1;
    }
    if (ret==0) {
        printf("start app success.\n");
        return 0;
    }
}
