#include<stdio.h>
#include<stdlib.h>
#define N 20

int a[N];
void gen_random(int upper_bound)
{
    int i;
    for (i=0; i<N; i++) {
        a[i] = (rand() % upper_bound);
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
    int i, j; 
    gen_random(10); 
    printf("value\thow many\n"); 
    for (i = 0; i < 10; i++) {
        printf("%d\t%d\n", i, how_many(i));
    } 
    return 0;
}

