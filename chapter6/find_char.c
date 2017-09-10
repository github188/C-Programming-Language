/*************************************************************************
	> File Name: find_char.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Sep 2017 06:05:11 AM UTC
 ************************************************************************/

#include<stdio.h>
#include<assert.h>
/*char * find_char(char const *source, char const *chars)
{
    while(*source != '\0') {
        while(*chars != '\0') {
            if (*source == *chars) {
                return source;
            }
            chars++;
        }
        source++;
    }
}*/


char * strpbrk( char *_Str, const char *_Control  )
{
    assert( ( NULL != _Str  ) && (NULL != _Control )  );
    char *_Str1;
    const char *_Str2;
    for ( _Str1 = _Str; *_Str1 != '\0'; ++_Str1  )
    {
        for ( _Str2 = _Control; *_Str2 != '\0'; ++_Str2  )
        {
            if ( *_Str1 == *_Str2  )
            {
                return _Str1;
            }
        }
    }
    return (char*)NULL;
}

int main(int argc, char ** argv) 
{
    char * result;
    //result = find_char(*(argv+1), *(argv+2));
    result =strpbrk(*(argv+1), *(argv+2));
    printf("%p\n", result);
}
