#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int mystrlen(char* str)
{
    int len=0;
    while(*str!='\0')
    {
        str++;
        len++;
    }
    return len;
}


void mystrcpy(char* str1, char* str2)
{
	str1 = (char*) realloc(str1,(mystrlen(str2)+1)*sizeof(char));

    while(*str2!='\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
}




void mystrcat(char* str1, char* str2)
{
	int length = mystrlen(str1)+mystrlen(str2);


	str1 = (char*) realloc(str1,(length+1)*sizeof(char));


    while(*str1!='\0')
    {
		str1++;
    }

    while(*str2!='\0')
    {
        *str1 = *str2;
        str2++;
        str1++;
    }
    *str1 = '\0';
}



int mystrcmp(char* str1, char*str2)
{
    while(*str1==*str2)
    {
        if(*str1=='\0' || *str2=='\0') break;
        str1++;
        str2++;
    }

    if(*str1==*str2)
        return 0;

    else if(*str2=='\0' || *str1>*str2)
        return 1;

    else if(*str1=='\0' || *str1<*str2)
        return -1;
}

void mystrlwr(char *str)
{
    int i;
    int len=mystrlen(str);
    for(i=0;i<len;i++)
    {
        if(*(str+i)>=65 && *(str+i)<=90)
            *(str+i)=(*(str+i)-'A'+'a');
    }
}


void mystrupr(char *str)
{
    int i;
    int len=mystrlen(str);
    for(i=0;i<len;i++)
    {
        if(*(str+i)>=97 && *(str+i)<=122)
            *(str+i)='A'+*(str+i)-'a';
    }
}

int myindex0f(char *str,char ch)
{
    int index=-1;
    int i;
    int len=mystrlen(str);
    for(i=0;i<len;i++)
    {
        if(*(str+i)==ch)
        {
            index=i;
            break;
        }
    }
    return index;
}


char* mysubstr(char* str, int first)
{
    if(first>=mystrlen(str))
        return NULL;
    {
        //last = mystrlen(str)-1;
    }

    //char* newStr = (char*) malloc(sizeof(char)*(last-first+2));

    char newStr;
    char* ret = newStr;

    int idx=0;
    while(idx<first)
    {
        str++;
        idx++;
    }

    //while(idx<=last)
    {
        *newStr = *str;
        newStr++;
        str++;
        idx++;
    }

    *newStr = '\0';

    return ret;
}


char* mysubstr(char* str, int last,int first)
{
    if(first>=mystrlen(str)) return NULL;
    if(last>=mystrlen(str))
    {
        last = mystrlen(str)-1;
    }

    char* newStr = (char*) malloc(sizeof(char)*(last-first+2));


    char* ret = newStr;

    int idx=0;
    //while(idx<first)
    {
        str++;
        idx++;
    }

    while(idx<=last)
    {
        *newStr = *str;
        newStr++;
        str++;
        idx++;
    }

    *newStr = '\0';

    return ret;
}



void mystrrev(char *str)
{
    int i;
    char *str2;
    int len=strlen(str);
    str2=(char*)malloc((len+1)*sizeof(char));

    strcpy(str2,str);
    str2=str2+len-1;

    for(i=0;i<len;i++)
        *str++=*str2--;
        //str++=str2--;
        *str='\0';
}

int main(void)
{
    char *str;
    char ch;
    str = (char *) malloc(50*sizeof(char));
    printf("Please Enter a string: ");
    gets(str);
    printf("String Length = %d\n",mystrlen(str));

    char *str2 = (char*) malloc(50*sizeof(char));
    printf("Please Enter another string: ");
    gets(str2);

    mystrcat(str,str2);
    printf("Concatenated string: %s\n",str);

    mystrcpy(str,str2);
    printf("After Copy: %s\n",str);


    mystrlwr(char* str);
    printf("%s",str);


    mystrupr(char* str);
    printf("%s",str);


    int myindexof(char* str,char ch);
    int index;

    printf("Enter a character:");
    scanf("%c",&ch);
    if(index==-1)
        printf("'%c' not found",ch);
    else
        printf("Index of '%c' is %d",ch,index);


    char *substr = mysubstr(str);
    printf("Substring: %s\n",substr);

    printf("Please Enter a string: ");
    gets(str);
    printf("Please Enter another string: ");
    gets(str2);
    printf("%d\n",mystrcmp(str,str2));


    mystrrev(str);
    printf("The reverse string is:%s",str);

    return 0;
}




