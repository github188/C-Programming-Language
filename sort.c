/*************************************************************************
	> File Name: sort.c
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Sep 2017 01:49:50 PM UTC
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int compare_integer(void const *a, void const *b)
{
    register int const *pa = a;
    register int const *pb = b;

    return *pa > *pb ? 1 : *pa < *pb ? -1 : 0;
}

int main()
{
    int * array;
    int n_value;
    int i;

    printf("How many values are there? ");
    if (scanf("%d", &n_value) != 1 || n_value <=0) {
        printf("Illagal number of values.\n");
        exit(EXIT_FAILURE);
    }

    /*分配内存*/
    array = malloc(n_value * sizeof(int));
    if (array == NULL) {
        printf("Can't get memory for that many values.\n");
        exit(EXIT_FAILURE);
    }

    /*读取这些数值*/
    for(i = 0; i < n_value; i+=1) {
        printf("?");
        if(scanf("%d", array+i) != 1) {
            printf("Error reading value #%d\n", i);
            free(array);
            exit(EXIT_FAILURE);
        }
    }

    qsort(array, n_value, sizeof(int), compare_integer);

    for(i = 0; i < n_value; i++) {
        printf("%d\n", array[i]);
    }

    free(array);
    return EXIT_SUCCESS;
}
