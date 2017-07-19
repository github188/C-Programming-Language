/*************************************************************************
	> File Name: 7-2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 23时08分29秒
 ************************************************************************/

#include<stdio.h>
#include<ctype.h>

#define MAXLINE 100
#define OCTLEN  6

int main()
{
    int c, pos;
    int inc(int pos, int n);

    pos = 0;

    while ((c = getchar()) != EOF) {
        if (iscntrl(c) || c == ' ') {
            pos = inc(pos, OCTLEN);
            printf("%03o ", c);
            if (c == '\n') {
                pos = 0;
                putchar('\n');
            }
        } else {
            pos = inc(pos, 1);
            putchar(c);
        }
    }
    return 0;
}

int inc(int pos, int n)
{
    if (pos+n<MAXLINE) {
        return pos + n;
    } else {
        putchar('\n');
        return n;
    }
}
