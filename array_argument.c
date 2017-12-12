#include<stdio.h>
#include<stdlib.h>
int init_array(int array[], int num)
{
    int i;
    for (i=0; i<num; i++) {
        array[i] = rand();
    }
    return 0;
}

int main()
{
    int array[5] = {0};
    int ret, i;
    ret = init_array(array, 5);
    for (i=0;i<5;i++) {
        printf("array[%d]: %d\n",i,array[i]);
    }
    return 0;
}
