/*************************************************************************
	> File Name: char.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 13时27分49秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//#include"/root/tw/drc_ha/src/common/num_types.h"
//#include"/root/tw/drc_ha/src/common/ddcp.h"

typedef struct _ddcp_hdr {
    unsigned char      packet_type:4,    /* 包类型 */
                       sender_role:4;    /* 发送者角色 */
    unsigned char      control_cmd;      /* 控制码 */
    unsigned int       task_id;          /* 任务ID */
    unsigned int       packet_len;       /* 协议数据长度 */
    char               packet[0];        /* 指向协议数据 */
}ddcp_hdr, *pt_ddcp_hdr;


int main()
{
    struct timespec  timestamp_value;
    pt_ddcp_hdr p_hdr = NULL;
    printf("44444444");
    p_hdr = (pt_ddcp_hdr)malloc(sizeof(ddcp_hdr)+sizeof(unsigned long long));
    printf("55555555");
    unsigned long long timestamp_status;
    unsigned long long * time;

    clock_gettime(CLOCK_REALTIME,&timestamp_value);
    timestamp_status = timestamp_value.tv_sec*1000000000 + timestamp_value.tv_nsec;
    p_hdr-> packet_type = 1;
    p_hdr->sender_role = 0;
    p_hdr->control_cmd = 1;
    p_hdr->task_id = 1;
    p_hdr->packet_len = sizeof(unsigned long long);
    printf("11111");
    *((unsigned long long *)(p_hdr->packet)) = timestamp_status;
    printf("22222");
    *time = timestamp_status;
    printf("33333");

    printf("%lld\n", *time);
    printf("%lld\n", p_hdr->packet);
}

