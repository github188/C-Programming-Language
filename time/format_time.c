#define BUFLEN 255
#define LEN 1024
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{  
    FILE *fp;
    int num=1;
    time_t t;
    char tmpBuf[BUFLEN];
    char buffer[LEN];
    fp=fopen("test.txt","a+");
    if (fgets(buffer, LEN, fp)==NULL) {
        printf("333\n");
        while (1)
        {
            t = time(0);
            strftime(tmpBuf, BUFLEN, "%Y-%m-%d %H:%M:%S", localtime(&t)); //format date     and time. 
            snprintf(buffer, LEN, "%d %s\n", num, tmpBuf);
            //printf("buffer:%s\n",buffer);
            fputs(buffer, fp);
            fflush(NULL);
            sleep(1);
            num++;
        }
    } 
    else {
        //printf("444\n");
        while(!feof(fp)) {
            fgets(buffer, LEN, fp);
            if (feof(fp))
            {
                sscanf(buffer, "%d", &num);
                //printf("num:%d\n",num);
            }
        }
        while(1)
        {
            num++;
            t = time(0);
            strftime(tmpBuf, BUFLEN, "%Y-%m-%d %H:%M:%S", localtime(&t)); //format date     and time. 
            snprintf(buffer, LEN, "%d %s\n", num, tmpBuf);
            //printf("buffer:%s\n",buffer);
            fputs(buffer, fp);
            fflush(NULL);
            sleep(1);
        }
    
    }
    //printf("time is [%s]",tmpBuf);
    return 0;
}

