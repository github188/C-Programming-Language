/*************************************************************************
	> File Name: sys_vol.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月27日 星期四 14时23分54秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

#define PATH_NAME_LEN 128
#define MAX_SHELL_STR_LEN 1024

int is_logical_volume(char * vol_path)
{
    int count = 0;

    while (*vol_path != '\0') {
        if (*vol_path == '/')
            count++;
        vol_path++;
    }
    if (count >= 3)
        return 1;
    else if (count == 2)
        return 0;
    else
        return -1;
}


int logical_convert_combination(char * logical_name)
{
    int ret = -1;
    char temp_name[PATH_NAME_LEN] ={0};
    char combination_name[PATH_NAME_LEN] ={0};

    char *value_vg = NULL;
    char *value_lv = NULL;

    strncpy(temp_name, logical_name, PATH_NAME_LEN);
    if(temp_name != NULL)
    {
        strtok(temp_name," /");
        value_vg  = strtok(NULL,    " /");
        value_lv  = strtok(NULL,    " /");
        sprintf(combination_name, "%s-%s", value_vg, value_lv);
        strncpy(logical_name, combination_name, PATH_NAME_LEN);
        ret = 0;
    }
    return ret;
}



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

    if(NULL != fgets(parse_buf, 128, file_temp)) {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            i++;
            str = NULL;
        }
        if (strcmp(strs[2],"/")==0) {
            printf("%s\n", strs[2]);
            pclose(file_temp);
            return 1;
        }
    }
    pclose(file_temp);
    return 0;
}




int main(int argc, char **argv)
{
    //char * mount_path = "/dev/cloudvg/test_lv";
    int ret = is_sys_vol(*(argv+1));
    printf("ret:%d\n",ret);
/*    if (strcmp(mount_path, "/")==0) {
        printf("1\n");
    } else {
        printf("0\n");
    }
*/
}

