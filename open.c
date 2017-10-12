#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#define LOCAL_TASK_LV_PATH "test.txt"

int main()
{
    int fd;
    fd = open(LOCAL_TASK_LV_PATH, O_RDWR);
    printf("%d\n",fd);
}

