/*************************************************************************
	> File Name: uuid.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 16时37分04秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SHELL_STR_LEN 128
#define VOL_UUID_LEN 64




int  vol_get_uuid(char * vol_path, char * uuid)
{
    //static char uuid[VOL_UUID_LEN] = {0};
    int i = 0;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    FILE * file_temp = NULL;
    char parse_buf[128] = {0};
    char * str = NULL;
    char * strs[6] = {0};
    char * attribute;
    char * value;

    snprintf(cmd, MAX_SHELL_STR_LEN, "blkid %s", vol_path);
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;

    }

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            printf("%s",strs[i]);
            i++;
            str = NULL;

        }
        attribute = strtok(strs[1], "=");
        value   = strtok(NULL, "=");
        strncpy(uuid, value, VOL_UUID_LEN);
        return  0;
    }
    return 1;
}



int main()
{
    int  sys_ret = 0;
    char * vol_path = "/dev/vda1";
    char * uuid = NULL;
    uuid = (char *)malloc(sizeof(char)*VOL_UUID_LEN);
    sys_ret = vol_get_uuid(vol_path, uuid);
    printf("%s\n",uuid);
}
