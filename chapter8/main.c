//
// Created by 谭伟 on 2017/7/29.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct student
{
    char    chName[20];    //姓名
    int    nID;        //学号
    float    fScores[3];    //3门课的成绩
};
void main()
{
    int i = 0;
    int j = 0;
    char parse_buf[256] = {0};
    char id_str[32] = {0};
    char * str = NULL;                                                      //解析字符串的临时变量
    char * strs[5] = {0};                                                   //保存解析后的字符串
    FILE *pWrite,*pRead;
    struct student tStu,tStu2;
    char *pName = "letuknowit";
    char *attribute=NULL;
    char *value=NULL;
    pWrite=fopen("stu_scores.txt","w");
    if(NULL == pWrite)
    {
        return;
    }

    //初始化结构体信息，用于写入文件
    memcpy(tStu.chName,pName,20);
    tStu.nID = 1;
    tStu.fScores[0] = 89.0;
    tStu.fScores[1] = 87.0;
    tStu.fScores[2] = 88.0;

    //写入数据到文件中
    fprintf(pWrite,"id=%d,name=%s,chinese=%f,math=%f,english=%f\n",tStu.nID,tStu.chName,tStu.fScores[0],tStu.fScores[1],tStu.fScores[2]);
    fclose(pWrite);

    pRead=fopen("stu_scores.txt","r");
    if(NULL == pRead)
    {
        return;
    }

    while(NULL != fgets(parse_buf, 256, pRead)) {
        str = parse_buf;
        printf("%s\n", str);
        while (NULL != (strs[i] = strtok(str, ","))) {
            i++;
            str = NULL;
        }
    }
    for (j=0;j<i;j++) {

        //str = strtok(parse_buf, ",");
        attribute = strtok(strs[j], "=");
        value = strtok(NULL, "=");
        printf("%s\n",attribute);
        printf("%s\n",value);
        if(value != NULL) {
            if (strcmp(attribute,"id") == 0){
                tStu2.nID = atoi(value);
                printf("%d\n", tStu2.nID);
                continue;
            }
            
            if (strcmp(attribute,"name") == 0){
                strcpy(tStu2.chName,value);
                printf("%s\n", tStu2.chName);
                continue;
            }
            if (strcmp(attribute,"chinese") == 0){
                tStu2.fScores[0] = atof(value);
                printf("%.1f\n", tStu2.fScores[0]);
                continue;
            }
            if (strcmp(attribute,"math") == 0){
                tStu2.fScores[1] = atof(value);
                printf("%.1f\n",tStu2.fScores[1]);
                continue;
            }
            if (strcmp(attribute,"english") == 0){
                tStu2.fScores[2] = atof(value);
                printf("%.1f\n", tStu2.fScores[2]);
                continue;
            }
        }
        //str = strtok(NULL, ",");
    }
    //strncpy(id_str, strs[0], 32);
    //printf("%s\n", strs[0]);
    //从文件中读取数据(主要下面参数中的&)
    //fscanf(pRead,"id=%d,name=%s,chinese=%f,math=%f,english=%f\n",&tStu2.nID,tStu2.chName,&tStu2.fScores[0],&tStu2.fScores[1],&tStu2.fScores[2]);
    fclose(pRead);
   // printf("------------------------\n");
    //打印读取的数据到屏幕上
    printf("%d %s %.1f %.1f %.1f\n",tStu2.nID,tStu2.chName,tStu2.fScores[0],tStu2.fScores[1],tStu2.fScores[2]);
}
