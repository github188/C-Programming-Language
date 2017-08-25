
#include<stdio.h>
#include<string.h>
#include<unistd.h>

//#include<blkid.c>

int get_disk(char * free_disk)
{
    char cmd[256] = {0};
//    char cmd1[256] = {0};
    FILE * file_temp = NULL;
    char parse_buf[256] = {0};
    char strs[15] = {0};
    char * strs1[15] = {0};
    char * str = NULL;
    char name[15][10] = {0};
    char disks[15][10] = {0};
    int i;
    int count = 0;
    int j;
    int k = 0;
    int p;

    snprintf(cmd, 256, "cat /proc/partitions | grep -v dm");
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;
    }

    while(!feof(file_temp)) {

        if(NULL != fgets(parse_buf, 128, file_temp)) {
            i = 0;
            if (k > 1) {
                for (p = 0;parse_buf[p] != '\n'; p++) {
                    if (parse_buf[p] >= 'a' && parse_buf[p] <= 'z') {
                        strs[i] = parse_buf[p];
                        i++;
                    }
                }
                strcpy(name[count], strs);
                count++;
            }
            k++;    
        }

    }
    
    for (i = 0; i < count; i++) {
        if (strcmp(name[i], name[i+1])) {
            strcpy(disks[j], name[i]);
            j++;
        } 
    }
    count = j;
    memset(cmd, 0x00, 256);
    memset(parse_buf, 0x00, 256);
    for (j = 0; j<count;j++) {

        i = 0;
        snprintf(cmd, 256, "blkid | grep /dev/%s", disks[j]);
        file_temp = popen(cmd, "r");
        if (NULL == file_temp) {
            perror("pipe open failed");
            return -1;
        }

        printf("%s\n", cmd);

        if(NULL != fgets(parse_buf, 128, file_temp)) {

            str = parse_buf;
            while(NULL != (strs1[i] = strtok(str," "))){
                i++;
                str = NULL;

            }
            printf("%s\n", strs1[1]);

        } else {
            printf("empty disk :%s\n", disks[j]);
        }

    }
}


int main()
{
    int i;
    char free_disk[10] = {0};
    int count = 0;
    get_disk(free_disk);
}
