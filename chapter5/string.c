#include<stdio.h>
int main()
{
    char *string1 = "abcdef";
    char *string2 = "acde";
    char y[10];
    //char n[10];
    int count = 0;
    for (; *string2 != '\0';) {
        for (; *string1 != '\0';) {
            if (*string1 == *string2) {
                y[count++] = *string2;
                break;
            }
            string1++;
        }
        string2++;
    }
    printf("%s\n",y);
}
