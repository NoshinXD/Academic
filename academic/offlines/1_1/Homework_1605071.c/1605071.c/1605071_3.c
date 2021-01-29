#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void searching_replacing(char *sentence, char *str, char *replc);

int main()
{
    char *sentence,*str,*replc;
    sentence=(char*)malloc(100*sizeof(char));
    str=(char*)malloc(100*sizeof(char));
    replc=(char*)malloc(100*sizeof(char));


    printf("Enter 1st string: ");
    gets(sentence);
    printf("Enter sub-string: ");
    gets(str);
    printf("Enter 2nd string: ");
    gets(replc);

    searching_replacing(sentence,str,replc);

    printf(sentence);

    return 0;
}

void searching_replacing(char *sentence, char *str, char *replc)
{
    char *tmp;
    int i,j=0,k,l;

    tmp=(char*)malloc(100*sizeof(char));
    strcpy(tmp,sentence);

    for(i=0;tmp[i]!='\0';i++){
        if(tmp[i]!=str[0])sentence[j++]=tmp[i];
        else{
            for(k=i,l=0;str[l]!='\0';l++,k++){
                if(tmp[k]!=str[l])break;
            }
            if(str[l]=='\0'){
                    i=k-1,l=0;
                    for(;replc[l]!='\0';)sentence[j++]=replc[l++];
            }
            else sentence[j++]=tmp[i];
        }
    }
    sentence[j]='\0';

}

