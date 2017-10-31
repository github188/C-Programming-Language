#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#define SECTOR_SIZE 512

int main(int argc, char ** argv)
{
    int fd;
    unsigned long long  size;
    unsigned long long o_sector_num;

    printf("%s\n", *(argv+1));
    fd = open(*(argv+1), O_RDONLY);
    if (fd < 0) {
        printf("open vol %s failed, errno:%d, strerror:%s.", *(argv+1), errno, strerror(errno));
        fd = 0;
        return -1;
    }
    size = lseek(fd, 0, SEEK_END);
    printf("size:%llu\n", size);
    o_sector_num = size>>9;
    printf("sectors_num:%llu\n", o_sector_num);
    return 0;
}
