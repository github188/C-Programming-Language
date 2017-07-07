#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
    char * token;
    char snapshot_name[32] = {0};
    char  buf1[30]="/dev/drcvg/test_snapshot";
    token = strtok( buf1, "/");
    while( token != NULL )
    {
        //printf( "%s ", token );
        token = strtok( NULL, "/");
    }
    strncpy(snapshot_name, token, 32);
    printf("%s\n",snapshot_name);
    return 0;
}
