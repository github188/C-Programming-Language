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
}map, *pt_map;

void init_point(pt_line l)
{
    l->p.x = 1;
    l->p.y = 1;
}

int main()
{
    pt_map m;
    pt_line l;
    printf("111111\n");
    l->p.x = 1;
    printf("222222\n");
    l->p.y = 1;
    //init_point(&m.l);
    printf("ssssss");
    m->l = *l;
    printf("%d\n", m->l.p.x);
    printf("%d\n", m->l.p.y);
    return 0;
}
