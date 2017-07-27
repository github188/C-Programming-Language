/*************************************************************************
	> File Name: error.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 16时04分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdarg.h>

void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
