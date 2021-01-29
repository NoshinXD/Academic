#include<stdio.h>
#include<windows.h>
#include<conio.h>

int n=0,ara[10000],x=0;

void entry_list();
void print_list();
void sort_list();
int search_number();
int append_number();
int insert_number();
void delete_number();
int menu();

int main()
{
    int option;

    do{
        system("cls");
        option=menu();
        system("cls");
        switch(option)
        {
            case1:
                entry_list();
                break;
            case2:
                print_list();
                break;
            case3:
                sort_list();
                break;
            case4:
                search_number();
                break;
            case5:
                append_number();
                break;
            case6:
                insert_number();
                break;
            case7:
                delete_number();
                break;
            case 8:
               return 0;
        }while(1);
    }while(1);

}

int menu()
{
    int option;

    printf("Choose a option:\n ");
    printf("1.entry a list\n");
    printf("2.print a list\n");
    printf("3.sort a list\n");
    printf("4.search a number\n");
    printf("5.append a number\n");
    printf("6.insert a number\n");
    printf("7.delete a number\n");
    printf("8.exit\n");

    printf("Enter your option: ");
    scanf("%d",&option);

    return option;
}

void entry_list()
{
    int i;

    printf("Enter the value of n:");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%d",&ara[i]);
}

void print_list()
{
    int i;

    printf("Enter the value of n:");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%d",&ara[i]);

    if(n>0){
        printf("The list is:");
        for(i=0;i<n;i++)
            printf("%d",ara[i]);

    }
}

void sort_list()
{
    int i,j,min,index,t;

    printf("Enter the value of n:");
    scanf("%d",&n);

    for(i=0;i<n;i++)scanf("%d",&ara[i]);

    if(n>0){
        for(j=0;j<n-1;j++)
        {
            min=ara[j];
            index=j;
            for(i=j+1;i<n;i++)
            {
                if(min>ara[i])
                    {
                        min=ara[i];
                        index=i;
                    }
                t=ara[j];
                ara[j]=ara[index];
                ara[index]=t;
            }
        }
    }
    x=1;
}

int search_number()
{
    int i,index=-1,target;
    int first=0,last=n-1,mid=(first+last)/2;

    printf("Enter the value of n:");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%d",&ara[i]);

    if(n==0)
        return -1;
    else
    {
        printf("Enter target number:");
        scanf("%d",&target);
        if(x==0)
        {
            for(i=0;i<n;i++)
            {
                if(ara[i]==target)
                {
                    index=i;
                    break;
                }
            }
        }
        else
        {
            while(last>=first)
            {
                if(ara[mid]==target)
                {
                    index=mid;
                    break;
                }
                else if(ara[mid]>target)
                    last=mid-1;
                else
                    first=mid+1;
            }
        }
            if(index==-1)
                printf("Not found");
            else
                printf("Found");
    }
}

int insert_number()
{
    int ara[10001],i,t,p,f;

    printf("Enter the value of n:");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%d",&ara[i]);

    if(n==0)
        return -1;
    else
    {
        printf("Enter target number & position:");
        scanf("%d%d",&t,&p);

        for(i=p-1;i<n-1;i++)
        {
            f=ara[i];
            if(i==p-1)ara[i]=t;
            else ara[i]=ara[i+1];
            ara[i+1]=f;
        }
    }
}

void delete_number()
{
    int t,index=-1,i,j;

    printf("Enter the value of n:");
    scanf("%d",&n);

    for(i=0;i<n;i++)scanf("%d",&ara[i]);

    printf("Enter target number:");
    scanf("%d",&t);

    for(i=0;i<n;i++){
        if(t==ara[i]){
            index=i;
            break;
        }
    }

    if(index==-1)printf("Not found");

    else {
            for(j=index;j<n-1;j++)ara[j]=ara[j+1];
    }

}

