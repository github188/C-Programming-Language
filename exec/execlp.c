#include<unistd.h>
#include<stdlib.h>

int main(void)
{
    execlp("ps","ps","-o","pid,ppid,pgrp,session,tpgid,comm",NULL);
    perror("error  execlp");
    exit(1);
}
