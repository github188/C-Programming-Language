/*************************************************************************
	> File Name: size.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 21时55分56秒
 ************************************************************************/

#include<stdio.h>
#include<sys/statfs.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
    int fd;
    if(argc!=2){
        printf("argv !=2 \n");
        return -1;
    }
    fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        printf("open file wrong \n");
        return -1;
    }
     off_t off=lseek(fd,0,SEEK_END);
     //多少个G
     long long gs=off/1024/1024/1024;
     printf("size of  %d   %lld   %lld\n",sizeof(off_t),off,gs);
        return 0;
}
