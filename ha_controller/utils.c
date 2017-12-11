/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: utils.c
 *  Author: zhouji
 *  Version: V1.0
 *  Date: 2017/07/11
 *  Description:    通用工具类函数接口
 * 
 *  Function List:
 *
 *  History:
 *      <author>   <time>  <version>  <desc>        
 *       zhouji   17/07/10    1.0     构建这个模块
\************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
//#include "log.h"
//#include "common.h"
#include "utils.h"
#define MAX_TEXT_LEN 2048



FILE *mypopen(const char *cmd,char type)
{
    int pipefd[2];           //管道描述符
    int pid_t;               //进程描述符

    if(type !='r' && type != 'w')
    {
        printf("myopen() flag error,%c\n",type);
        return NULL;
    }

    if(pipe(pipefd)<0)        //建立管道
    {
        printf("myopen() pipe create error\n");
        return NULL;
    }
    
    pid_t=fork();             //建立子进程

    if(pid_t < 0) 
        return NULL;

    if(0 == pid_t)            //子进程中......
    {
        if(type == 'r')
        {
            close(pipefd[0]);               //此函数返回文件指针是用于读，因此，在子进程中应该将结果写入管道，这样父进程返回的文件指针才能读，所以这里将读端关闭
            dup2(pipefd[1],STDOUT_FILENO);  //exec函数的执行结果将会通过标准输出写到控制台上，但这里我们不需要在控制台输出，而是需要将结果返回，因此将标准输出重定向到管道写端
            close(pipefd[1]);       

        }
        else{
            close(pipefd[1]);
            dup2(pipefd[0],STDIN_FILENO);
            close(pipefd[0]);
        }
        char *argv[] = {cmd,NULL};  
        if(execvp(cmd,argv)<0)          //用exec族函数执行命令
            return NULL;    
    }
    
    wait(0);                                //等待子进程返回

    if(type=='r'){
        close(pipefd[1]);
        return fdopen(pipefd[0],"r");   //由于程序需要返回的参数是文件指针，因此需要用fdopen函数将描述符打开，其返回值为相应的文件指针 
    }else{
        close(pipefd[0]);
        return fdopen(pipefd[1],"w");
    }
}



int exec_cmd(const char *shell_cmd, int * o_ret, 
        void (*process_line)(const char *line, void *argv), void *argv)
{
    FILE *cmd_fd = NULL;
    char buf_line[MAX_TEXT_LEN] = {0};
    int ret;
    

    if (shell_cmd == NULL) {
        return -1;
    }

    cmd_fd = mypopen(shell_cmd, 'r');
    if (cmd_fd == NULL) {
        printf("failed to popen shell cmd `%s`, errno:%d, strerror: %s.", shell_cmd, errno, strerror(errno));
        return -1;
    }

    if (process_line) {
        while(fgets(buf_line, sizeof(buf_line), cmd_fd)) {
            while (buf_line[strlen(buf_line) - 1] == '\n') {
                buf_line[strlen(buf_line) - 1] = '\0';
            }
            process_line(buf_line, argv);
            memset(buf_line, 0, sizeof(buf_line));
        }
    }

    ret = pclose(cmd_fd);
    if (o_ret) {
        /* TODO:根据实验结果，shell_cmd执行的返回结果与pclose的返回结果关系如下 */
        *o_ret = ret >> 8;
    }
    if (ret == -1) {
        return -1;
    }

    return 0;
}
