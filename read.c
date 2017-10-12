#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#define LOCAL_TASK_LV_PATH "test.txt"
size_t drc_read(int fd, void * buf, size_t len)
{
    char * buf_index = (char *)buf;            /* 读取缓冲区偏移指针*/
    size_t left_len = len;                      /* 剩余读取数据长度*/
    ssize_t read_len = 0;                        /* 每次读取数据*/
    ssize_t total_read_len = 0;                  /* 总共读取数据*/

    if (fd < 0)
    return -1;
    if (NULL == buf)
    return -2;
    if (len <= 0)
    return -3;

    while (left_len > 0) {
        read_len = read(fd, buf_index, left_len);
        if (read_len < 0) {
            if (errno != EINTR) {              /* 如果是系统中断错误则继续读取,否则返回错误*/
                     return -4;
                }

        } else if (read_len == 0) {
            perror("end of file");
            return read_len;

        } else {
            total_read_len = total_read_len + read_len;
            left_len = left_len - read_len;
            buf_index = buf_index + read_len;

        }

    }
    return len;

}
int main()
{
    int fd;
    void * buf = NULL;
    buf = malloc(sizeof(char)*2);

    fd = open(LOCAL_TASK_LV_PATH, O_RDWR);
    lseek(fd, 1, SEEK_SET);
    drc_read(fd, buf, 2);
    printf("%s\n", (char*)buf);
    printf("%d\n",fd);
}

