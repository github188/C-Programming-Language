#include<stdio.h>

int countbit(unsigned int x)
{
    int count = 0;
    while(x>0)
    {
        if (x & 1) {
            count++;
        }
        x=x>>1;
    }
    return count;
}

int main(int argc, char * argv[])
{
    int count = 0;
    unsigned int num;
    if (argc < 2) {
        printf("too few parameters.\n");
        return 1;
    }
    
    num = atoi(argv[1]);
    count = countbit(num);
    printf("count is %d\n",count);
}
