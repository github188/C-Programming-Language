#include<stdio.h>
int main()
{
    char *string1 = "abcdef";
    char *string2 = "abx";
    char y[10];
    //char n[10];
    int count;
    for (; *string1 == *string2; string1++,string2++)
        y[count++] = *string1;
    printf("%s\n",y);
}
