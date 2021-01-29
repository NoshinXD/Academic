#include<stdio.h>
#include<stdlib.h>


int main()
{
    int A[6][4]={1,2,6,7,9,0,2,3,5,6,78,90,23,45,67,89,1,23,45,67,89,9,78,65};
    /*sizeof(A);
    sizeof(*A);
    sizeof(**A);
    sizeof(*A+1);
    sizeof(*(*A+3)+5);
    sizeof(*(*(A+2)+3));*/
    printf("the size of %d is %d\n",A,sizeof(A));
    printf("the size of %d is %d\n",*A,sizeof(*A));
    printf("the size of %d is %d\n",**A,sizeof(**A));
    printf("the size of %d is %d\n",*A+1,sizeof(*A+1));
    printf("the size of %d is %d\n",*(*A+3)+5,sizeof(*(*A+3)+5));
    printf("the size of %d is %d", *(*(A+2)+3),sizeof(*(*(A+2)+3)));

    return 0;
}
