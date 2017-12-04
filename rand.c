#include<stdio.h>
#include<stdlib.h>
#define N 1000

int a[N];
void gen_random(int upper_bound)
{
    int i;
    for (i=0; i<N; i++) {
        a[i] = (rand() % upper_bound)+10;
    }
}

int how_many(int value)
{
    int i,count=0;
    for(i=0;i<N;i++) {
        if (a[i] == value) {
            ++count;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    int i; 
    gen_random(10); 
    printf("value\thow many\n"); 
    for (i = 10; i < 20; i++) 
        printf("%d\t%d\n", i, how_many(i)); 
    return 0;
}

