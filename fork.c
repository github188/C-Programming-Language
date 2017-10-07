//
// Created by 谭伟 on 2017/10/5.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char ** argv)
{
    pid_t pid;
    int cnt = 0;

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("The returned value is %d\nIn child process!!\nMy PID is %d\n",
               pid, getpid());
        cnt++;
    } else {
        printf("The returned value is %d\nIn father process!!\nMy PID is %d\n",
               pid, getpid());
        cnt++;
    }
    printf("cnt = %d\n", cnt);

    return 0;
}