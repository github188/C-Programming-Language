#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct msg{
    struct msg *next;
    int num;
};

struct msg *head;
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void *consumper(void *p)
{
    struct msg *mp;

    for(;;)
    {
        pthread_mutex_lock(&lock);
        while(head==NULL)
        {
            pthread_cond_wait(&has_product, &lock);
        }
        mp = head;
        head=head->next;
        pthread_mutex_unlock(&lock);
        printf("Consumpe %d\n", mp->num);
        free(mp);
        sleep(rand()%5);
    }
}

void *producer(void *p)
{
    struct msg *mp, *current;
    for (;;)
    {
        mp=malloc(sizeof(struct msg));
        mp->num=rand()%1000 + 1;
        printf("Produce %d\n", mp->num);
        pthread_mutex_lock(&lock);
        if (head==NULL)
        {
            mp->next=head;
            head=mp;
        }
        else
        {
            current=head;
            while (current->next != NULL)
            {
                current=current->next;
            }
            current->next=mp;
        }
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&has_product);
        sleep(rand()%5);
    }
}

int main(void)
{
    pthread_t pid, cid;
    srand(time(NULL));
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumper, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    return 0;
}
