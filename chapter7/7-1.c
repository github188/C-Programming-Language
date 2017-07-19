/*************************************************************************
	> File Name: 7-1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 23时09分18秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char * argv[])
{
    int c;
    printf("%s\n", argv[0]);
    if (strcmp(argv[0], "lower") == 0) {
        while ((c = getchar()) != EOF) {
            putchar(tolower(c));
        }
    } else {
        while ((c = getchar()) != EOF) {
            putchar(toupper(c));
        }
    }
    return 0;
}
