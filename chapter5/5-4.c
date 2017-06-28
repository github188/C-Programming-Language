#include<stdio.h>
int strend(char *s, char *t)
{
    char *bs = s;
    char *bt = t;
    
    for (; *s; s++)
        ;
    for (; *t; t++)
        ;
    for (; *s == *t; s--, t--)
        if (t == bt || s == bs)
            break;
    if (*s == *t && t == bt && *s != '\0')
        return 1;
    else 
        return 0;
}

int main()
{
    char *s = "could";
    char *t = "ould";
    int flag;
    
    flag = strend(s,t);
    printf("%d\n",flag);
    return 0;
}
