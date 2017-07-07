#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINES 5000     /* max #lines to be sorted */
#define MAXSTOR 5000
char *lineptr[MAXLINES];  /* pointers to text lines */
int readlines(char *lineptr[], char *linestor, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right,
		  int (*comp)(void *, void *));
int numcmp(char *, char *);
/* sort input lines */
int main(int argc, char *argv[])
{
   int nlines;        /* number of input lines read */
   char linestor[MAXSTOR];
   int numeric = 0;   /* 1 if numeric sort */
   if (argc > 1 && strcmp(argv[1], "-n") == 0)
	   numeric = 1;
   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
	   qsort((void**) lineptr, 0, nlines-1,
		 (int (*)(void*,void*))(numeric ? numcmp : strcmp));
	   writelines(lineptr, nlines);
	   return 0;
   } else {
	   printf("input too big to sort\n");
	   return 1;
   }
}

void qsort(void *v[], int left, int right,
		  int (*comp)(void *, void *))
{
   int i, last;
   void swap(void *v[], int, int);
   if (left >= right)    /* do  nothing if array contains */
	   return;           /* fewer than two elements */
   swap(v, left, (left + right)/2);
   last = left;
   for (i = left+1; i <= right;  i++)
	   if ((*comp)(v[i], v[left]) < 0)
		   swap(v, ++last, i);
   swap(v, left, last);
   qsort(v, left, last-1, comp);
   qsort(v, last+1, right, comp);
}

int numcmp(char *s1, char *s2)
{
   double v1, v2;
   v1 = atof(s1);
   v2 = atof(s2);
   if (v1 < v2)
	   return -1;
   else if (v1 > v2)
	   return 1;
   else
	   return 0;
}

void swap(void *v[],  int i, int j;)
{
   void *temp;
   temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}

void writelines(char *lineptr[], int nlines)
{
   while (nlines-- > 0)
	   printf("%s\n", *lineptr++);
}


int get_line(char s[],int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}


int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > linestop)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] - p;
            p += len;
        }
    return nlines;   
}
