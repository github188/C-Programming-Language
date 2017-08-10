/*************************************************************************
	> File Name: kernel.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 21时24分54秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define MAX_SHELL_STR_LEN 256


int main()
{
    char productos[32] = {0};
    int i = 0;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    FILE * file_temp = NULL;
    char parse_buf[128] = {0};
    char * str = NULL;
    char * strs[14] = {0};
    char * attribute;
    char * value;

    snprintf(cmd, MAX_SHELL_STR_LEN, "uname -a");
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;

    }

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            printf("%s\n",strs[i]);
            i++;
            str = NULL;
        }
        return  0;
    }
    return 1;
}
