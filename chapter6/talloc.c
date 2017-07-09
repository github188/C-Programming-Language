#include<stdlib.h>

struct tnode * talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}
