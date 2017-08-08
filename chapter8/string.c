/*************************************************************************
	> File Name: string.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月07日 星期一 15时01分02秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>


int change(char * tem) {
    //sprintf(tem, "hello,world");
    strcpy(tem,"hello,world.");
}



int main()
{
    char temp[1024] = {0};
    change(temp);
    printf("%s\n",temp);
}
