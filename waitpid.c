#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid<0)
    {
        perror("fork error\n");
        exit(1);
    }
    else if (pid==0)
    {
        int i;
        for (i=3;i>0;i--)
        {
            printf("this is a child\n");
            sleep(1);
        }
        exit(3);
    }
    else 
    {
        int stat_val;
        waitpid(pid, &stat_val,0);
        if (WIFEXITED(stat_val))
        {
            printf("child exited with code %d\n",WEXITSTATUS(stat_val));
        }
        else if(WIFSIGNALED(stat_val))
        {
            printf("child terminated abnormally signal %d\n",WTERMSIG(stat_val));
        }
    }
    return 0;
}
