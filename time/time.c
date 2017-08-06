/*************************************************************************
	> File Name: time.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月06日 星期日 21时21分07秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>

int main()
{
    time_t now;
    time_t now1;

    now = time(0);
    sleep(3);
    now1 = time(0);

    printf("%lld\n",now);
    printf("%lld\n",now1);
}
