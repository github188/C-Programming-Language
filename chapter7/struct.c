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

typedef struct line {
    point p;
}line, *pt_line;


typedef struct map {
    line l;
}map;

void init_point(pt_line l)
{
    l->p.x = 1;
    l->p.y = 1;
}

int main()
{
    map m;
    line l;
    l.p.x = 1;
    l.p.y = 1;
    m.l = l;
    //init_point(&m.l);
    printf("%d\n", m.l.p.x);
    printf("%d\n", m.l.p.y);
    return 0;
}
