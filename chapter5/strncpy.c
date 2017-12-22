#include<stdio.h>
void strncpy_1(char *s, char *t, int n)
{
    while (*t && n-- > 0)
        *s++ = *t++;
    while (n-- > 0)
        *s++ = '\0';
}

int main()
{
    char s[10];
    char t[20] = "hello world";
    strncpy_1(s,t,11);
    printf("%s\n",s);
}
