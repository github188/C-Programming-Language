/*************************************************************************
	> File Name: array.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Sep 2017 12:18:34 PM UTC
 ************************************************************************/

#include<stdio.h>
#include<string.h>
char vol_name_backup[16][32] = {0};
int count = 0;

void push_to_array(char * vol_name)
{
    //char vol_name[10] = "vdb"
    strcpy(vol_name_backup[count], vol_name);
    printf("in push_to_array:%s\n", vol_name_backup[count]);
    count++;
}


int get_real_vol(char * vol_name, char * o_vol_name)
{
    int i;
    for(i = 0; i < count;) {
        if (strcmp(vol_name_backup[i], vol_name)==0) {
            strcpy(o_vol_name, vol_name_backup[i+1]);
            return 0;
        }
        i = i+2;
    }
    return 1;
}



int main()
{
    char tmp_vol_name[32] = {0};
    char vol_name[32] = "vdb";
    char temp_vol[32] = "test_lv";
    char o_vol[32] = {0};
    int i;
    strcpy(tmp_vol_name, vol_name);
    strcpy(vol_name, temp_vol);
    push_to_array(vol_name);
    push_to_array(tmp_vol_name);

    for(i = 0; i < count; i++) {
        printf("int main:%s\n", vol_name_backup[i]);
    }


    get_real_vol(vol_name, o_vol);
    printf("%s\n", o_vol);
}
