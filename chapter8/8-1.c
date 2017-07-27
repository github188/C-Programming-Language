/*************************************************************************
	> File Name: 8-1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 15时36分47秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<syscalls.h>
//#include<sys/syscall.h>


void error(char * fmt, ...);

int main(int argc, char * argv[])
{
    int fd;
    void filecopy(int ifd, int ofd);

    if (argc == 1) {
        filecopy(0,1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1)
               error("cat: can't open %s", *argv);
            else {
               filecopy(fd, 1);
               close(fd);
            }
        }
    }
    return 0;
}

void filecopy(int ifd, int ofd)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(ifd, buf, BUFFSIZE)) > 0)
        if (write(ofd, buf, n) != n)
            error("cat: write error");
}


