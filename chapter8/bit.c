//
// Created by tw on 2017/9/5.
//
#include <stdio.h>

int main()
{
    unsigned char flag = 2;
    printf("%d\n", flag & 01);
    printf("%d\n", !(flag & 01));
}