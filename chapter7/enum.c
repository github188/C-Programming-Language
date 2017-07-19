/*************************************************************************
	> File Name: enum.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 15时04分36秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    typedef enum _app_type_e {
        APP_TYPE_ORACLE = 0,
        APP_TYPE_SQLSERVER = 1,
        APP_TYPE_MYSQL = 2,
        APP_TYPE_OTHER = 3,
        APP_TYPE_MAX
    }app_type_e;

    int i;
    for (i = 0; i<APP_TYPE_MAX;i++){
        printf("%d\n",i);
    }

}
