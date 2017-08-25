

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
typedef struct student
{
    char name[10];
    int num;
    int age;
    char addr[15];
}stu, *pt_stu;
void save() {
    FILE *fp;
    pt_stu p_stu = NULL;
    char name[10] = "tanwei";
    char addr[15] = "sichuan";

    fp = fopen("stu.dat", "wb");
    if (fp == NULL) {
        printf("file can not open!\n");
        return;
    }

    p_stu = (pt_stu)malloc(sizeof(stu));
    strcpy(p_stu->name, name);
    strcpy(p_stu->addr, addr);
    p_stu->age = 22;
    p_stu->num = 88;


    if (fwrite(p_stu, sizeof(struct student), 1, fp) != 1) {
        printf("file write error!\n");
    }
    fclose(fp);
}
void load()
{
    FILE *fp;
    pt_stu p_stu = NULL;

    fp = fopen("stu.dat","rb");
    if(fp==NULL)
    {
        printf("file can not open!\n");
        return;
    }
    p_stu = (pt_stu)malloc(sizeof(stu));



        if(fread(p_stu,sizeof(struct student),1,fp)!=1)
        {
            if(feof(fp))
            {
                fclose(fp);
                return;
            }
            printf("file read error!\n");
        }
        if (p_stu == NULL) {
            printf("file is empty.");
        }
        printf("%-10s %4d %4d %-15s\n", p_stu->name,p_stu->num,p_stu->age,p_stu->addr);
    fclose(fp);
}
int main()
{
    printf("Please enter data of students:\n");
    save();
    load();
    return 0;
}