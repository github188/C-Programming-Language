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
