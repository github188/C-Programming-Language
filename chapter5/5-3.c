#include<stdio.h>
void strcat_s(char *s, char *i) 
{
    while (*s)
         s++;
    while (*s++ = *i++)
        ;
}
int main()
{
    char s[20] = "hello";
    char i[10] = "world";
    strcat_s(s,i);
    printf("%s",s);
}
