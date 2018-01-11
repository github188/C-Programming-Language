#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_t ntid;

void printtids(const char * s)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int) pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void * arg)
{
    printtids(arg);
    return NULL;
}

int main(void)
{
    int err;
    err = pthread_create(&ntid, NULL, (void*)thr_fn, "new thread: ");
    if (err != 0)
    {
        fprintf(stderr, "can't create thread:%s",strerror(err));
        exit(1);
    }
    printtids("main thread: ");
    sleep(1);
    return 0;
}
