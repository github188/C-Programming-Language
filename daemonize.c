#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void deamonize(void)
{
    pid_t pid;
    
    if (pid=fork()<0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid != 0)
    {
        exit(0);
    }

    setsid();
    if (chdir("/")<0)
    {
        perror("chdir");
        exit(1);
    }
    close(0);
    open("/dev/null",O_RDONLY);
    dup2(0,1);
    dup2(0,2);
}

int main(void)
{
    deamonize();
    while(1);
}
