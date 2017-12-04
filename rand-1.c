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
    int i, j, max=0, histogram[10]={0}; 
    gen_random(10);
    for (i = 0; i < N; i++) {
        histogram[a[i]]++;
    }
    for (i=0; i<10; i++) {
        if (histogram[i] > max) {
            max = histogram[i];
        }
    }

    for (i=0; i<10;i++) {
        printf("%d\t",i);
    }
    printf("\n");
    printf("\n");
    for(j=0; j<max; j++) { 
        for(i=0;i<10;i++){
            if (histogram[i]-j>0)
                printf("*\t");
            else
                printf(" \t");
        }
        printf("\n");
    }

    return 0;
}

