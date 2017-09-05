
#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char * argv[])
{

    int i = 0;
    char cmd[256] = {0};
    FILE * file_temp = NULL;
    char parse_buf[256] = {0};
    char * str = NULL;
    char * strs[15] = {0};
    char * temp_version = NULL;
    char temp_linux[6] = {0};

    snprintf(cmd, 256, "blkid | grep %s", argv[1]);
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;


    }

    printf("%s\n", cmd);

    if(NULL != fgets(parse_buf, 128, file_temp)) {

        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            i++;
            str = NULL;

        }
        printf("%s\n", strs[1]);
        //temp_version = strtok(strs[2], "-");
        //strtolow(strs[0],temp_linux);
        //snprintf(version, 14, "%s %s",temp_linux, temp_version);
        return 1;

    } else {
        printf("empty disk :%s\n", argv[1]);
    }
    return 0;
