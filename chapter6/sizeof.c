#include<stdio.h>
int main()
{
    struct size{
        char c;
        int i;
    };
    int size = 0;
    size = sizeof(struct size);
    printf("%d\n",size);
}
