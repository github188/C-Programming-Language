#include <stdio.h>
#define N 3

int a[N];
void perm(int);
void print();
void swap(int, int);
int main()
{
    int i,n;
    int offset; 
    for(i = 0; i<N; i++)
    a[i] = i + 97;
    perm(0);

}

void perm(int offset)
{
    int i, temp;
    if(offset == N-1)
    {
        print();
        return;
    }
    for(i = offset; i < N; i++)
    {
        swap(i, offset);
        perm(offset + 1);
        swap(i, offset);
    }
}

void print()
{
    int i;
    for(i = 0; i < N; i++)
    printf(" %c ",a[i]);
    printf("\n");

}  

void swap(int i, int offset)
{
    int temp;
    temp = a[offset];
    a[offset] = a[i];
    a[i] = temp;

}
