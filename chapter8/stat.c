/*************************************************************************
	> File Name: stat.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月17日 星期四 10时13分36秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>


int vol_get_major_minor(char * vol_path, int * tem_major, int * tem_minor)
{
        struct stat vol_stat = {0};

    if (stat(vol_path, &vol_stat)) {
                return -1;
            
    }

        *tem_minor = minor(vol_stat.st_rdev);
        *tem_major = major(vol_stat.st_rdev);

        return 0;

}

int main()
{
    int major;
    int minor;
    int ret;
    char vol_path[] = "/dev/vda1";

    ret = vol_get_major_minor(vol_path, &major, &minor);
    printf("ret:%d\n",ret);
    printf("major:%d\n", major);
    printf("minor:%d\n",minor);
}
