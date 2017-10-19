#include<stdio.h>
#include<stdlib.h>
#define PATH_NAME_LEN 128
#define TYPE_OF_LV    48


typedef struct  lv_info
{
    char lv_path[PATH_NAME_LEN];           /* 卷路径 */
    char lv_mount_path[PATH_NAME_LEN];     /* 卷挂载路径 */
    char lv_type[TYPE_OF_LV];              /* 卷类型 */
    unsigned long long lv_total_size;      /* 卷总空间 */
    unsigned long long lv_left_size;       /* 卷空余空间 */
}lv_info, *pt_lv_info;

typedef struct task_info
{
    pt_lv_info p_lv_info;
    int task_id;
}task_info, *p_task_info;


/*int son(pt_lv_info * p_lv)
{
    *p_lv = (pt_lv_info)malloc(sizeof(lv_info)*32);

    if (*p_lv == NULL) {
        return 0;
    }else {
        return 1;
    }
}*/

/*int main()
{
    int ret;
    pt_lv_info  p_lv_info = NULL;

    printf("%p\n", p_lv_info);
    ret = son(&p_lv_info);
    if(ret) {

        printf("%p\n", p_lv_info);

       free(p_lv_info);
       p_lv_info = NULL;
        printf("%p\n", p_lv_info);
    }
    return 0;
}*/

int main()
{
    int ret;
    //pt_lv_info  p_lv_info = NULL;
    p_task_info p_task = NULL;

    printf("%p\n", p_task);
    p_task = (p_task_info)malloc(sizeof(task_info));
    p_task->p_lv_info = (pt_lv_info) malloc(sizeof(lv_info));
    //ret = son(&p_lv_info);
    if(p_task) {

        printf("%p\n", p_task);
        free(p_task->p_lv_info);
        free(p_task);
        p_task = NULL;
        printf("%p\n", p_task);
    }
    return 0;
}

