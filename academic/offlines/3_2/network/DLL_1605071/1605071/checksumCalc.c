#include <stdio.h>
#include <string.h>
//#include "CRCV4.c"

void asciiToBin(char input, char binary[8])
{
    int n = (int)input;
    int a[8], copy[8], i;

    for(i=0; n>0; i++)    
    { 
        a[i] = n%2;  
        n = n/2;    
    }  

    int zeros = 0; 
    if(i < 8)
    {
        zeros = 8 - i;
    }

    int j;
    for(j=0; j<zeros; j++)
    {
        copy[j] = 0;
    }
    for(i=i-1; i>=0; i--)
    {
        copy[j] = a[i];
        j++;
    }

    for(int k=0; k<8; k++)
    {
        if(copy[k] == 0) binary[k] = '0';
        else binary[k] = '1';
    }
}

void concatenateChecksum(int type, int seqnum, int acknum, char* payload, char str[])
{
    char str1[5];
    
    if(seqnum == 0) 
    {
        str1[0] = '0';
        str1[1] = '0';
    }
    else if(seqnum == 1) 
    {
        str1[0] = '0';
        str1[1] = '1';
    }
    else
    {
        str1[0] = '1';
        str1[1] = '1';
    }

    if(acknum == 0) 
    {
        str1[2] = '0';
        str1[3] = '0';
    }
    else if(acknum == 1) 
    {
        str1[2] = '0';
        str1[3] = '1';
    }
    else
    {
        str1[2] = '1';
        str1[3] = '1';
    }
    
    str1[4] = 0;

    strcpy(str, str1);

    //printf("strlen(payload) : %d\n", (int)strlen(payload));
    for(int i=0; i<strlen(payload); i++)
    {
        //printf("i %d\n", i);
        char str2[9];
        asciiToBin(payload[i], str2);
//        if(i != strlen(payload) - 1) {/*str2[8] = ',';*/}
        str2[8] = 0;
        //printf("%s\n", str2); //uncomment it
        strcat(str, str2);
    }

    char str3[3];

    if(type == 0) 
    {
        str3[0] = '0';
        str3[1] = '0';
    }
    else if(type == 1) 
    {
        str3[0] = '0';
        str3[1] = '1';
    }
    else if(type == 2) 
    {
        str3[0] = '1';
        str3[1] = '0';
    }
    else
    {
        str3[0] = '1';
        str3[1] = '1';
    }
    
    str3[2] = 0;
    strcat(str, str3);
}

/*int main()
{
    char divisor[100];
    char binary[8];

    char payload[4];
    char str[26];
    printf("enter payload: ");
    scanf("%s", payload);
    concatenateChecksum(2, 1, 1, payload, str);
    printf("payload: %s\n", str);
    printf("strlen %d\n", strlen(str));

    printf("enter divisor: ");
    scanf("%s", divisor);

    char *rem;
    rem = CRC_zeros(str, divisor);
    //printf("here\n");
    printf("rem %s\n", rem);
    //printf("here2\n");
    CRC_rem(str, divisor, rem);

    return 0;
}*/
