#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv)
{
    uid_t uid; 
    uid = getuid();
    printf("%d\n",uid);
}
