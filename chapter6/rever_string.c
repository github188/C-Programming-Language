/*************************************************************************
	> File Name: rever_string.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Sep 2017 07:31:31 AM UTC
 ************************************************************************/

#include<stdio.h>

void reverse_string(char * str)
{
    char *last_char;
    for(last_char = str; *last_char!='\0'; last_char++)
        ;
    last_char--;

    while(str<last_char) {
        char temp;
        temp = *str;
        *str++ = *last_char;
        *last_char-- = temp;
    }
}

int main(int argc, char ** argv)
{
    reverse_string(*(argv + 1));
    printf("%s\n", *(argv+1));
}
