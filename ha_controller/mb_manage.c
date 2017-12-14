#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include "mb_manage.h"
#define DRIVER "/dev/drcbd"
#define MAX_SHELL_STR_LEN 1024
static int s_driver_fd;


int mb_open_mng() {
    int ret = -1;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    snprintf(cmd, MAX_SHELL_STR_LEN, "%s", DRIVER);
    ret = open(cmd, O_RDWR);
    if (ret < 0) {
        printf("open driver:%s failed, and errno:%d, strerror: %s", DRIVER, errno, strerror(errno));
        return 1;

    }
    s_driver_fd = ret;
    return 0;

}

int get_driver_fd()
{
    return s_driver_fd;

}
