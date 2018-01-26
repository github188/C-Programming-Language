#include<stdio.h>
//#include"utils.h"
#include<string.h>
#include<errno.h>

#define PHP_PATH "../../fsdb/php/bin/php"
#define APP_SCRIPT_PATH "./DBOperation/appMng.php"
#define MAX_TEXT_LEN 2048

int exec_cmd(const char *shell_cmd, int * o_ret, 
             void (*process_line)(const char *line, void *argv), void *argv)
{
    FILE *cmd_fd = NULL;
    char buf_line[MAX_TEXT_LEN] = {0};
    int ret;


    if (shell_cmd == NULL) {
        return -1;

    }

    cmd_fd = popen(shell_cmd, "r");
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



int main(int argc, char *argv[])
{
    char shell_cmd[1024] = {0};
    int cmd_ret;

    snprintf(shell_cmd, sizeof(shell_cmd), "%s %s -t %s -u -n %s", PHP_PATH, APP_SCRIPT_PATH, argv[1], argv[2]); /* TODO: 补充完整 */
    if (exec_cmd(shell_cmd, &cmd_ret, NULL, NULL) == -1) {
        printf("failed to exec shell cmd `%s`.", shell_cmd);
        return -1;        
    }
    if (cmd_ret==32){
        return 32;
    }
    else if (cmd_ret==31)
    {
        return 31;
    }
    return cmd_ret;
}
