//
// Created by tw on 2017/8/22.
//
#include <stdio.h>
#include <stdlib.h>
#define POINT_NUM 3
typedef struct point{
    int x;
    int y;
}*pt_point, point;

pt_point get_point()
{
    int i;
    pt_point p_point = NULL;

    p_point = (pt_point)malloc(sizeof(point) * POINT_NUM);
    for (i = 0; i < POINT_NUM; i++) {
        (p_point+i)->x = i;
        (p_point+i)->y = i;
    }
    return p_point;
}


void print_point(pt_point p_point)
{
    printf("x:%d, y:%d\n",p_point->x, p_point->y);
}



int main()
{
    int i;
    pt_point p_point = get_point();
    for (i = 0; i < POINT_NUM; i++) {
        print_point(p_point+i);
    }

}