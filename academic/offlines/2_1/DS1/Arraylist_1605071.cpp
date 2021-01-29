#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
    listMaxSize = LIST_INIT_SIZE;
    list = (int*)malloc(sizeof(int)*listMaxSize) ;
    length = 0 ;
}

int searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}


int insertItem(int newitem)
{
    int * tempList ;
    if(listMaxSize==0)
    {
        initializeList();
    }
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
    return SUCCESS_VALUE ;
}

int insertItemAt(int pos, int item)
{
    if(pos<=length)
    {
        int temp=list[pos];
        int h = insertItem(item);
        list[pos]=list[length-1];
        list[length-1]=temp;
    }
    else
        printf("Ooops!!! Required position is larger or equal to the length.");

    return SUCCESS_VALUE;
}

int shrink()
{
    int * tempList ;
    if (length <= .5 * listMaxSize && listMaxSize > LIST_INIT_SIZE)
    {
        //allocate new memory space for tempList
        listMaxSize = .5 * listMaxSize ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    }
    //printf("S");

    //list[length] = newitem ; //store new item
    //length++ ;
    return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
    if ( position >= length ) return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;

    int h;
    h = shrink();
    //printf("S");

    return SUCCESS_VALUE ;
}

int deleteAll()
{
    int i,h;
    for( i = length-1; i >= 0 ; i-- )
    {
        h=deleteItemAt(i);
    }

    if(listMaxSize>LIST_INIT_SIZE)
    {
        for(i=0; listMaxSize!=LIST_INIT_SIZE; i++)
        {
            shrink();
        }
    }

    return SUCCESS_VALUE ;
}

int clear()
{
    int i,h;

    for( i = length-1; i >= 0 ; i-- )
    {
        h=deleteItemAt(i);
    }

    free(list) ;
    //list=NULL;

    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return NULL_VALUE;
    deleteItemAt(position) ;
    return SUCCESS_VALUE ;
}

int deleteLast()
{
    int d = deleteItemAt(length-1);

    //int h = shrink();

    return SUCCESS_VALUE ;
}

int getLength()
{
    return length;
}

void printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

int exPostfix(char s[])
{
    int h;
    int a,b,f=0,result=0;
    int j;
    initializeList();

    for(j=0; s[j]!='\0'; j++)
    {
        if(s[j]>='0' && s[j]<='9')
        {
            insertItem(s[j]-48);
            //printf("S");
        }
        else
        {
            b=list[length-1];
            a=list[length-2];

            h = deleteLast();
            h = deleteLast();

            if(s[j]=='+')
                result=a+b;
            else if(s[j]=='-')
                result=a-b;
            else if(s[j]=='*')
                result=a*b;
            else if(s[j]=='/')
            {
                if(b==0)
                {
                    clear();
                    return NULL_VALUE;
                }
                result=a/b;
            }


            insertItem(result);
        }
    }

    if(length>1)
    {
        clear();
        return NULL_VALUE;
    }

    f=list[length-1];
    clear();
    return f;
}

int main()
{
    //initializeList();
    char *s;

    s = (char*) malloc (10000*sizeof(char)) ;
    int result;

    gets(s);

    result=exPostfix(s);

    if(result==NULL_VALUE)
    {
        printf("Ooops!!! Invalid expression.");
    }
    else
    {
        //result=exPostfix(s);
        printf("%d",result);
    }

    return 0;
}


/*int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Insert new item at. 5. Delete last. 6. Clear.\n");
        printf("7. Deleteall. 8. Print. 9. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            int pos,item;
            scanf("%d%d",&pos,&item);
            insertItemAt(pos,item);
        }

        else if (ch == 5)
        {
            deleteLast();
        }

        else if (ch == 6)
        {
            clear();
        }
        else if(ch==7)
        {
            deleteAll();
        }

        else if(ch == 8)
        {
            printList();
        }

        else if(ch==9)
        {
            break;
        }

    }
}*/
