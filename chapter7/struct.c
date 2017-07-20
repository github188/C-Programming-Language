/*************************************************************************
	> File Name: struct.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 16时25分24秒
 ************************************************************************/

#include<stdio.h>
typedef struct point {
    int x;
    int y;
}point, *pt_point;

typedef struct map {
    point p;
}map;

void init_point(pt_point p)
{
    p->x = 1;
    p->y = 1;
}

int main()
{
    map m;
    init_point(&m.p);
    printf("%d\n", m.p.x);
    printf("%d\n", m.p.y);
    return 0;
}
