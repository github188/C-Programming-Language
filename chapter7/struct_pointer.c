/*************************************************************************
	> File Name: struct_pointer.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 18时52分26秒
 ************************************************************************/

#include<stdio.h>
#define x_of_point(type) ((type).x)
#define y_of_point(type) ((type).y)



typedef struct point {
    int x;
    int y;
}point, *pt_point;


int main()
{
    pt_point p;
    (*p).x;
}
