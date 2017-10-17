#include<stdio.h>
#include<errno.h>

int main(int argc, char ** argv)
{
    char cmd[64] = "/sbin/ip addr show dev \"eth0\" 2>/dev/null";
    FILE *fp = NULL;

    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("errorno:%d\n", errno);
    }   
    printf("%p\n", fp);
    pclose(fp);
}
