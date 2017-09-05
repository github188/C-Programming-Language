#include<stdio.h>
#include<unistd.h>

int main()
{
    if (!access("/usr/local/capsheaf/client/conf/task_control1", F_OK))
    {
        printf("ok");
    }

}
