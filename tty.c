#include<stdio.h>
#include<unistd.h>

int main(void)
{
    printf("fd0: %s\n",ttyname(0));
    printf("fd1: %s\n",ttyname(1));
    printf("fd2: %s\n",ttyname(2));
    return 0;
}
