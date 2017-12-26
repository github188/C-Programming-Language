#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>

void print_hex(void* ptr,int len){
        unsigned char *buf=(unsigned char*)ptr;
        int i,j;
        char tmp[32];
        printf("\n==========packet size: %d===========\n",len);
    for(i=1;i<=len;i++){
                printf("%02x ",buf[i-1]);
                tmp[(i-1)%32]=buf[i-1];
        if(i%32==0){
                        printf("       ");
                        for(j=0;j<32;j++)
                            printf("%c",tmp[j]);
                        printf("\n");
                    
        }
            
    }
        printf("\n");
        //printf("=====================\n");
    //
}


unsigned long long read_local_info(int fd, void * buf, unsigned long long offset, unsigned long long size)
{
    off_t seek_ret=-1;
    long long read_size=-1;
    long long  total_size=0;

    seek_ret = lseek(fd,offset+total_size,SEEK_SET);
    if(seek_ret==-1){
        printf("lseek failed ,return %d, errno: %d, strerror:%s.", seek_ret, errno, strerror(errno));
        return -1;

    }
    while(total_size<size){
        read_size=read(fd,buf+total_size,size-total_size);
        if(read_size==-1){
            if (errno != EINTR){
                printf("[read]: write failed ,return, errno:%d, strerror:%s.", errno, strerror(errno));
                return -1;

            }

        }
        total_size+=read_size;


    }
    return total_size;

}


int main(int argc, char *argv[])
{
    int fd;
    void * buf = NULL;   
    unsigned long long total_size = 0;
    unsigned long long size = atol(argv[2]);
    fd = open(argv[1], O_RDWR);
    printf("fd:%d\n", fd);
    
    buf = malloc(size);

    total_size = read_local_info(fd, buf, 0, size);
    print_hex(buf, size);
}
