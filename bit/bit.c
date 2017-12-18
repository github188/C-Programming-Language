#include<stdio.h>
int main()
{
    //    int i = 0xcffffff3;
    //    printf("%x\n",0xcffffff3>>2);
    //    printf("%x\n",i>>2);
    //unsigned int a, b, mask = 0x0000ff00;
    //a = 0x12345678;
    //b = (a & mask) >> 8;
    //unsigned int a,b;
    //int i;
    //a=101;
    //for (i=0; i<7;i++) {
    //    a=a>>1;        
    //    printf("%u\n",a);
    //}
    int i=0;
    unsigned int sum=0;
    for (;i<16;i++)
    {
        sum = sum + 1U << i;
    }
    printf("sum:%d",sum);
    return 0;
}
