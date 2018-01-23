#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd = open("./log", O_CREAT | O_RDWR, 0644);
    if(fd < 0)
    {
        perror("open");
        return 1;

    }

    int new_fd = dup2(fd, 1); //new_fd = 1
    if(new_fd < 0)
    {
        perror("dup2");
        return 2;

    }
    close(fd);

    char buf[1024];
    while(1)
    {
        memset(buf, '\0', sizeof(buf));
        ssize_t _s = read(0, buf, sizeof(buf) - 1);
        if(_s <  0)
        {
            perror("read");
            return 3;

        }
        else
        {
            buf[_s] = '\0';

        }
        if(strncmp("quit", buf, 4) == 0)
        {
            break;

        }
        printf("%s", buf); 
        fflush(stdout); 
        sleep(1);

    }
    close(new_fd);
    return 0;

}
