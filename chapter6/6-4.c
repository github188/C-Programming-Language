/*************************************************************************
	> File Name: 6-4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月16日 星期日 22时40分53秒
 ************************************************************************/

#include<stdio.h>
#include<ctype.h>

#define MAXWORD 100
#define NDISTINCT 1000

struct tnode {
    char * word;
    int count;
    struct tnode * left;
    struct tnode * right;
};

struct tnode * addtree(struct tnode *, char *);
int getword(char *, int);
void sortlist(void);
void treestore(struct tnode *);

struct tnode * list[NDISTINCT];
int ntn = 0;

int main()
{
    struct tnode * root;
    char word[MAXWORD];
    int i;

    root = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treestore(root);
    sortlist();
    for (i = 0; i < ntn; i++) {
        printf("%2d:%20s\n", list[i]->count, list[i]->word);
    }
    return 0;
}

void treestore(struct tnode * p)
{
    if (p != NULL) {
        treestore(p->left);
        if (ntn < NDISTINCT) {
            list[ntn++] = p;
        }
        treestore(p->right);
    }
}

void sortlist()
{
    int gap, i, j;
    struct tnode * temp;
    for (gap = ntn/2;gap > 0; gap /=2) {
        for (i = gap; i < ntn; i++) {
            for (j = i-gap; j>=0;j-=gap) {
                if ((list[j]->count) >= (list[j+gap]->count)) {
                    break;
                }
                temp = list[j];
                list[j] = list[j+gap];
                list[j+gap] = temp;
            }
        }
    }
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
