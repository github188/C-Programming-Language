#include<stdio.h>
#define PHP_PATH "/usr/local/capsheaf/fsdb/php/bin/php"

int main(int argc, char * argv[])
{
    char cmd[128] = {0};
    FILE * file_temp = NULL;
    char parse_buf[128] = {0};

    snprintf(cmd, 128, "%s appMng.php -t %s -g", PHP_PATH, argv[1]);
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;
    }

    while (!feof(file_temp)) {
        if(NULL != fgets(parse_buf, 128, file_temp)) {
            if (parse_buf[0] == '&') {
                printf("%s",parse_buf);
            }
        }
    }
    pclose(file_temp);
    return 1;
}
