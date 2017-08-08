//
// Created by tw on 2017/8/8.
//

#include<stdio.h>
#define SIZE 10
struct student
{
    char name[10];
    int num;
    int age;
    char addr[15];
}stu[SIZE];
//保存数据(fwrite)
void save()
{
    FILE *fp;
    fp = fopen("stu.dat","wb");
    if(fp==NULL)
    {
        printf("file can not open!\n");
        return;
    }
    for(int i=0;i<SIZE;i++)
    {
        if(fwrite(&stu[i],sizeof(struct student),1,fp)!=1)
        {
            printf("file write error!\n");
        }
    }
    fclose(fp);
}
//读取数据(fread)
void load()
{
    FILE *fp;
    fp = fopen("stu.dat","rb");
    if(fp==NULL)
    {
        printf("file can not open!\n");
        return;
    }
    for(int i=0;i<SIZE;i++)
    {
        if(fread(&stu[i],sizeof(struct student),1,fp)!=1)
        {
            if(feof(fp))
            {
                fclose(fp);
                return;
            }
            printf("file read error!\n");
        }
        printf("%-10s %4d %4d %-15s\n",stu[i].name,stu[i].num,stu[i].age,stu[i].addr);
    }
    fclose(fp);
}
int main()
{
    printf("Please enter data of students:\n");
    for(int i=0;i<SIZE;i++)
    {
        scanf("%s%d%d%s",stu[i].name,&stu[i].num,&stu[i].age,stu[i].addr);
    }
    save();
    load();
    return 0;
}