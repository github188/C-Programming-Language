/*************************************************************************
	> File Name: mstrsstr.c
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Sep 2017 03:15:25 PM UTC
 ************************************************************************/

#include<stdio.h>
#include<string.h>

char * mystrstr(char const *s1, char const *s2)
{
    register char*last;
    register char*current;
    
    last = NULL;

    if(*s2 != '\0') {
        current = strstr(s1, s2);
        
        while(current != NULL) {
            last = current;
            current = strstr(last+1, s2);
        }
    }
    return last;
}

int main(int argc, char * argv[])
{
    char * value = NULL;
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    value = mystrstr(argv[1], argv[2]);
    printf("%p",value);
}
