#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
        printf("entering main process---\n");
        int ret;
        char *argv[] = {"ls","-l",NULL};
        ret = execvp("ls",argv);
        if(ret == -1)
            perror("execl error");
        printf("exiting main process ----\n");
        return 0;

}
