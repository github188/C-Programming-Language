/*************************************************************************
	> File Name: get_vol_size.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 11时32分28秒
 ************************************************************************/

#include<stdio.h>
//#include<sys/types.h>  /*提供类型pid_t,size_t的定义*/
//#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
unsigned long long getVolumeDiskSize(char *diskName) {
    int fd = open(diskName, O_RDONLY);
    unsigned long long size = -1;
    if (fd < 0) {
     return -1;        
    }
    size = lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET);
    close(fd);
    return size;

}

int main()
{
    unsigned long long size = getVolumeDiskSize("/dev/vda1");
    printf("%lld", size);
}
