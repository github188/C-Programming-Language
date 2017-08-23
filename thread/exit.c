//
// Created by tw on 2017/8/23.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct task_info {
    pthread_t son;
    int exit_flag;
}*pt_task, task;


int son(void * arg)
{
    unsigned long long count = 0;
    pt_task p_task = (pt_task)arg;
    if (!p_task->exit_flag) {
        printf("%d\n", ++count);
    }
}


int main()
{
    int ret;
    pt_task p_task = (pt_task)malloc(sizeof(task));
    p_task->exit_flag = 0;
    ret = pthread_create(&(p_task->son), NULL, son, (void *)p_task);
    if (ret) {
        printf("create thread failed. and result is %d\n", ret);
    }

    sleep(3);
    p_task->exit_flag = 1;

}
