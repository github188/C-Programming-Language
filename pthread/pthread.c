/*************************************************************************
	> File Name: pthread.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Sep 2017 01:13:22 PM UTC
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t pth[2];

void *print_message(void *argv)
{
    printf("This is in thread %x!\n", *((pthread_t *)argv));

    if(&pth[0] == argv)
    {
        sleep(1);
        pthread_exit("1 thread exit!");

    }
    else 
    {
        sleep(10);
        pthread_exit("2 thread exit!");

    }

}

int main(void)
{
    void *returnValue;

    printf("This is in main function BEFORE pthread create!\n");
    pthread_create(&pth[0], NULL, &print_message, &pth[0]);
    pthread_create(&pth[1], NULL, &print_message, &pth[1]);
    printf("This is in main function AFTER pthread create %x!\n", pth[0]);
    pthread_join(pth[0], &returnValue);
    printf("This is in main function AFTER pthread join 1\n");
    pthread_join(pth[1], &returnValue);
    printf("This is in main function returnValue=%s\n", returnValue);
    printf("This is in main function AFTER pthread join\n");
    return 0;

}
