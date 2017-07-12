/*************************************************************************
	> File Name: 6-1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月12日 星期三 23时33分49秒
 ************************************************************************/

#include<stdio.h>
#include<ctype.h>

int getword(char * word, int lim)
{
    int c, d, comment(void), getch(void);
    void ungetch(int);
    char * w = word;

    while (isspace(c = getch))
        ;
    if (c != EOF)
        *w++ = c;
    if (isalnum(c) || c == '_' || c == '#') {
        for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        } else if (c == '\'' || c == '"') {
            for (;--lim>0; w++)
                if ((*w = getch()) == '\\')
                     *++w = getch();
            else if (*w == c) {
                w++;
                break;
            } else if (*w == EOF)
                break;
        } 
    } else if (c == '/')
        if ((d = getch()) == '*')
            c = comment();
        else 
            ungetch(d);
}

int comment(void)
{
    int c;
    while ((c = getch()) != EOF)
        if(c == '*')
            if((c = getch()) == '/')
                break;
            else
                ungetch(c);
    return c;
}
