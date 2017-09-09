#include<stdio.h>
#include<stdlib.h>
size_t strlen(char * string)
{
    int length = 0;
    while (*string++ != '\0') 
         length+=1;
    return length;
}

int main(int argc, char * argv[])
{
    int length;

    length = strlen(argv[1]);
    printf("%d\n", length);

}


