/*************************************************************************
	> File Name: kernel.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 21时24分54秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define MAX_SHELL_STR_LEN 256

void strtolow(char * str, char * o_str)
{
    for (; *str != '\0'; str++) {
        if (*str>64 && *str < 91) {
            *o_str=*str+32;
        }else if(*str > 96 && *str < 123) {
            *o_str = *str;
        }
        o_str++;
    }
}


int get_sys_version(char * version)
{

    int i = 0;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    FILE * file_temp = NULL;
    char parse_buf[256] = {0};
    char * str = NULL;
    char * strs[15] = {0};
    char * temp_version = NULL;
    char temp_linux[6] = {0};

    snprintf(cmd, MAX_SHELL_STR_LEN, "uname -a");
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;

    }

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        printf("%s\n",str);
        while(NULL != (strs[i] = strtok(str," "))){
            printf("%s\n",strs[i]);
            i++;
            str = NULL;
        }
        temp_version = strtok(strs[2], "-");
        strtolow(strs[0],temp_linux);
        snprintf(version, 14, "%s %s",temp_linux, temp_version);
        return 1;
    }
    return 0;
}



int get_sys_bit(char * bit)
{
    
    int i = 0;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    FILE * file_temp = NULL;
    char parse_buf[256] = {0};
    char * str = NULL;
    char * temp_bit; 
    snprintf(cmd, MAX_SHELL_STR_LEN, "getconf LONG_BIT");
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;

    }

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        temp_bit = strtok(str, " \n");
        strcpy(bit, temp_bit);
        printf("bit:%s\n",bit);
        return 1;
    }
    return 0;
}




int get_sys_release(char * release)
{
    
    int i = 0;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    FILE * file_temp = NULL;
    char parse_buf[256] = {0};
    char * str = NULL;
    char * strs[15] = {0};
    char * temp_version = NULL;
    char temp_release[10] = {0};
    
    snprintf(cmd, MAX_SHELL_STR_LEN, "cat /etc/issue");
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;

    }

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        printf("%s\n",str);
        while(NULL != (strs[i] = strtok(str," "))){
            printf("%s\n",strs[i]);
            i++;
            str = NULL;
        }
        strtolow(strs[0], release);
        return 1;
    }
    return 0;
}





int main()
{
    char productos[32] = {0};
    char bit[8] = {0};
    char version[14] = {0};
    char release[10] = {0};
    int sys_ret = 0;

    sys_ret = get_sys_version(version);
    sys_ret = get_sys_bit(bit);
    sys_ret = get_sys_release(release);
    snprintf(productos, 32, "%s x%s %s", version, bit, release);
    
    
    printf("%s\n",version);
    printf("%s\n",bit);
    printf("%s\n",release);
    printf("%s\n",productos);
}
