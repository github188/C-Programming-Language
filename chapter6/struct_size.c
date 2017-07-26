/*************************************************************************
	> File Name: struct_size.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 14时14分19秒
 ************************************************************************/

#include<stdio.h>

typedef struct point {
    int x;
    int y;
} point,*pt_point;

int main()
{
    char buf[sizeof(point)] = "12";
    printf("%s", buf);
}
