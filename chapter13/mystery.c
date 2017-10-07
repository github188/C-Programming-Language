//
// Created by 谭伟 on 2017/10/6.
//
#include <stdio.h>
#include <stdlib.h>

void mystery(int n)
{
    n += 5;
    n /= 10;
    printf("%s\n", "**********" + 10 - n);
}

int main(int argc, char ** argv)
{
    while(*++argv != NULL) {
        printf("%s\n", *argv);
        mystery(atoi(*argv));
//        printf("%d\n", **argv);
    }

}
