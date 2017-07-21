/*************************************************************************
	> File Name: 7-5.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 23时06分06秒
 ************************************************************************/

#include<stdio.h>
#include<ctype.h>

#define NUMBER '0'

int getop(char s[])
{
    int c, rc;
    float f;

    while ((rc = scanf("%c", &c)) != EOF) {
        if ((s[0] = c) != ' ' && c != '\t')
            break;
    }
    s[1] = '\0';
    if (rc == EOF) {
        return EOF;
    } else if (isdigit(c) && c != '.') {
        return c;
    }
    ungetc(c, stdin);
    scanf("%f", &f);
    sprintf(s, "%f", f);
    return NUMBER;
}

int main()
{
    char s[100];
    getop(s);
}
