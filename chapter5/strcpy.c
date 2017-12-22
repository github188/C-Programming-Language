#include<stdio.h>
#include<string.h>
#define N 20

char *strcpy_s(const char *src, char *dest)
{
    while((*dest++=*src++)!='\0')
        ;
    return dest;
}

int main(int argc, char *argv[])
{
    //char *src="hello world";
    char dest[N];

    strcpy_s(argv[1], dest);
    //strcpy(dest, argv[1]);
    
    printf("dest:%s\n",dest);
    printf("dest:%s\n",strcpy_s(argv[1], dest));
}
