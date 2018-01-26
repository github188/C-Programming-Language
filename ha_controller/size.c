#include<stdio.h>
#include<unistd.h>
#include<linux/types.h>
#include"num_types.h"
#include"ddcp.h"

int main(int argc, char *argv[])
{
    __u16 fault_count;
    __u64 send_len;
    fault_count = atoi(argv[1]);
    send_len = sizeof(ddcp_hdr) + sizeof(ddcp_p1_heart_beat) + fault_count * sizeof(fault_info);
    printf("ddcp_hdr:%llu\n", sizeof(ddcp_hdr));
    printf("ddcp_p1_heart_beat:%llu\n", sizeof(ddcp_p1_heart_beat));
    printf("fault_info:%llu\n", sizeof(fault_info));
    printf("send_len:%llu\n",send_len);
    return 0;
}
