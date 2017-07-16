/*************************************************************************
	> File Name: 6-3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月16日 星期日 18时09分58秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXWORD 100

struct linklist {
    int lnum;
    struct linklist * ptr;
};

struct tnode {
    char * word;
    struct linklist * lines;
    struct tnode * left;
    struct tnode * right;
};

struct tnode * addtreex(struct tnode *, char *, int);
int getword(char *, int);
int noiseword(char *);
void treexprint(struct tnode *);

int main()
{
    struct tnode * root;
    char word[MAXWORD];
    int linenum = 1;

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && noiseword(word) == -1) {
            root = addtreex(root, word, linenum);
        } else if (word[0] == '\n') {
            linenum++;
        }
    }
    treexprint(root);
    return 0;
}

struct tnode * talloc(void);
struct linklist * lalloc(void);
void addln(struct tnode *, int);

struct tnode * addtreex(struct tnode *p, char *w, int linenum)
{
    int cond;
    
    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->lines = lalloc();
        p->lines->lnum = linenum;
        p->lines->ptr = NULL;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        addln(p, linenum);
    } else if (cond < 0) {
        p->left = addtreex(p->left, w, linenum);
    } else {
        p->right = addtreex(p->right, w, linenum);
    }
    return p;
}

void addln(struct tnode *p, int linenum)
{
    struct linklist * temp;

    temp = p->lines;
    while (temp->ptr != NULL && temp->lnum != linenum) {
        temp = temp->ptr;
    }

    if (temp->lnum != linenum) {
        temp->ptr = lalloc();
        temp->ptr->lnum = linenum;
        temp->ptr->ptr = NULL;
    }
}

void treexprint(struct tnode *p)
{
    struct linklist * temp;
    if (p != NULL) {
        treexprint(p->left);
        printf("%10s: ", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->ptr) {
            printf("%4d", temp->lnum);
        }
        printf("\n");
        treexprint(p->right);
    }
}

struct linklist * lalloc()
{
    return (struct linklist *)malloc(sizeof(struct linklist));
}

int noiseword(char * w)
{
    static char *nw[] = {
        "a",
        "an",
        "and",
        "are",
        "in",
        "is",
        "of",
        "or",
        "that",
        "the",
        "this",
        "to"
    };
    int cond, mid;
    int low = 0;
    int high = sizeof(nw) / sizeof(char *) - 1;

    while(low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(w, nw[mid]) < 0)) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}


int getword(char * word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
       *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];  
}


struct tnode * talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}
