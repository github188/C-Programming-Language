/*************************************************************************
	> File Name: sys_vol.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月27日 星期四 14时23分54秒
 ************************************************************************/

#include<stdio.h>


is_sys_vol(char * vol_name)
{
    char * buf[6] = {0};
    char cmd[30] = {0};
    FILE * file_temp = NULL;
    int ret;
    ret = is_logical_volume(vol_path);
    if (1 == ret) {
        strncpy(temp_path, vol_path, PATH_NAME_LEN);
        logical_convert_combination(temp_path);
        snprintf(cmd, MAX_SHELL_STR_LEN, "mount -l | grep %s", temp_path);        

    } else if (0 == ret) {
        snprintf(cmd, MAX_SHELL_STR_LEN, "mount -l | grep %s", vol_path);

    } else {
        log_write(LOG_ERR, "the vol_path %s is illegal.", vol_path);
        return -1;

    }
    log_write(LOG_INFO, "cmd:%s",cmd);  
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;

    }

    if(NULL != fgets(parse_buf, PHASE_LINE_LEN, file_temp)) {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            i++;
            str = NULL;

        }
    }
}



int main()
{
    
}
