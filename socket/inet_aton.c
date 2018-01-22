#define _BSD_SOURCE
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    struct in_addr addr;
    if (argc != 2)
    {
        fprintf(stderr, "%s <dotted-address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (inet_aton(argv[1], &addr) == 0) 
    {
        perror("inet_aton");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", inet_ntoa(addr));
    exit(EXIT_SUCCESS);
}
