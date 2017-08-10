/*************************************************************************
	> File Name: strtolow.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 23时12分57秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

void strtolow(char * str, char * o_str)
{
    for (; *str != '\0'; str++) {
        if (*str>64 && *str < 91) {
            *o_str=*str+32;
        }else if(*str > 96 && *str < 123) {
            *o_str = *str;
        }
        o_str++;
    }
}



int main(int argc, char *argv[])
{
    char* str = argv[1];
 //   char str[12] = "Capsheaf";
    char o_str[12] = {0};
    strtolow(str, o_str);
    printf("%s",o_str);
}
