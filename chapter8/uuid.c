/*************************************************************************
	> File Name: uuid.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 16时37分04秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
char * vol_get_uuid(char * vol_path)
{
    int i;
    char cmd[128] = {0};
    char * uuid[64];
    FILE * file_temp = NULL;
    char parse_buf[128] = {0};
    char * str = NULL;
    char * strs[3] = {0};
    char * attribute;
    char * value;

    snprintf(cmd, 128, "blkid %s", vol_path);
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return NULL;

    }

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            i++;
            str = NULL;

        }
        attribute = strtok(strs[1], "=");
        value     = strtok(NULL, "=");
        memcpy(uuid, value, 64);
        return  *uuid;
    }

}


int main()
{
    char * uuid = vol_get_uuid("/dev/vad1"); 
    //strncpy(uuid,vol_get_uuid("/dev/vda1"),64);

    printf("%s", uuid);      
}
