/*************************************************************************
	> File Name: return_str.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 16时57分08秒
 ************************************************************************/

//#include<stdio.h>
#include <stdio.h>
#include <string.h>
char *strlong(char *str1, char *str2){
    if(strlen(str1) >= strlen(str2)){
            return str1;
          
    }else{
            return str2;
          
    }

}
int main(){
      char str1[30], str2[30], *str;
      gets(str1);
      gets(str2);
      str = strlong(str1, str2);
      printf("Longer string: %s\n", str);
      return 0;

}
