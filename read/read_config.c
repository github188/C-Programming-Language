#include<stdio.h>
#include<string.h>
#include<errno.h>
#define CONFIG_PATH "/etc/capsheaf/vol.conf"
#define LOCAL_CONF_PATH(dest) strcat(dest, "conf/test")

char install_path[256] = {0};
int main(int argc, char *argv[])
{
    FILE *fp;
    char parse_buf[256];
    char * str = NULL;
    char * strs[128] = {0};
    int i = 0;
    
    fp = fopen(CONFIG_PATH, "r");
    if (fp == NULL)
    {
        printf("open fail and errno:%d, strerror():%s\n",errno, strerror(errno));
        return 1;
    }
    
    if (NULL != fgets(parse_buf, 256, fp))
    {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str,"\""))){
            i++;
            str = NULL;
        }
        strcpy(install_path, strs[1]);
    }
    printf("install_path:%s\n", install_path);
    printf("LOCAL_CONF_PATH:%s\n",strcat(install_path, "conf/test"));
    fclose(fp);
    fp = fopen(install_path, "r");
    if (fp == NULL)
    {
        printf("open fail and errno:%d, strerror():%s\n",errno, strerror(errno));
        return 1; 
    }

    if (NULL != fgets(parse_buf, 256, fp))
    {
        printf("parse_buf:%s\n",parse_buf);
    }

    return 0;
}
