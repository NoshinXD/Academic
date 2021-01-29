#include<stdio.h>
#include<stdlib.h>

int process(int *(*pf)(int*,int*))
{
    /*int c,option,i;
    int *p;
    int *q;*/
    int a,b;
    /*p=&a;
    q=&b;*/

    printf("Enter a:");
    scanf("%d",&a);
    printf("Enter b:");
    scanf("%d",&b);

    return (int*)pf(&a,&b);



}

int *sum(int*p,int*q)
{
    int i=0;
    i=*p+*q;
    return i;
}

int *sub(int*p,int*q)
{
    int i;
    i=*p-*q;
    return i;
}

int *max(int*p,int*q)
{
    int *p,*qi;
    if(*p>*q)
        i=*p;
    else
        i=*q;
    return i;
*/

int main()
{
    /*int m,b,x,c;
    m=*sum(int*,int*);
    b=*sub(int*,int*);
    x=*max(int*,int*);
    c=int process(i);
    printf("Result is %d",&c);*/

    int c=process(sum);
    printf("%d",c);
    return 0;
}
