/*************************************************************************
	> File Name: atoi.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月14日 星期五 15时16分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main()
{
    char * num_str = "1048576";
    int num;

    num = atoi(num_str);
    printf("%d",num);
    return 0;
}
