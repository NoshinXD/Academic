//saigo no CRC to omoimas

#include <stdio.h>
#include <string.h>

char* XOR(char* checksumStr, char* divisor)
{
    /*printf("in XOR: \n");
    printf("\nchecksumStr %s\n", checksumStr);
    printf("divisor %s\n", divisor);*/


    int genlen = strlen(divisor);
    //printf("genLen %d\n", genlen);
    char tempDivisor[genlen+1], rem_zero[genlen], tempRem[genlen+1];

    char tempInput[genlen+1];

    char *retRem;

    //printf("checksumStr %s\n", checksumStr); //e porjonto ok

    int checksumStrlen = strlen(checksumStr);

    for(int i=0; i<checksumStrlen; )
    {
        //printf("i %d\n", i);
        /*if(i==5)
        {
            printf("rem %s\n", rem);
        }*/
        if(i == 0)
        {
            for(int j=0; j<genlen; j++)
            {
                tempInput[j] = checksumStr[j];
            }
            tempInput[genlen] = 0;
        }
        else
        {
            int j;
            for(j=0; j<genlen-1; j++)
            {
                tempInput[j] = rem_zero[j];
            }
            tempInput[j] = checksumStr[i];
            tempInput[genlen] = 0;
        }

        /*if(i==0) 
        {
            printf("tempInput size: %d\n", strlen(tempInput));
        }*/

        if(tempInput[0] == '1')
        {
            for(int j=0; j<genlen; j++)
            {
                tempDivisor[j] = divisor[j];
            }
        }
        else
        {
            for(int j=0; j<genlen; j++)
            {
                tempDivisor[j] = '0';
            }
        }
        tempDivisor[genlen] = 0;

        //printf("tempInput %s, tempDivisor: %s\n", tempInput, tempDivisor);

        /*if(i == 5)
        {
            printf("tempInput %s, tempDivisor: %s\n", tempInput, tempDivisor);
        }*/

        for(int j=0; j<genlen; j++)
        {
            /*if(tempInput[j] == '1' && tempDivisor[j] == '1')
            {
                tempRem[j] = '0';
            }
            else if(tempInput[j] == '1' || tempDivisor[j] == '1')
            {
                tempRem[j] = '1';
            }
            else
            {
                tempRem[j] = '0';
            }*/

            if(tempInput[j] != tempDivisor[j]) tempRem[j] = '1';
            else tempRem[j] = '0';
        }
        tempRem[genlen] = 0;

        /*if(i == 0)
        {
            printf("tempRem: %s\n", tempRem);
        }*/
        
//        printf("tempRem: %s\n", tempRem);

        for(int j=0; j<genlen-1; j++)
        {
            rem_zero[j] = tempRem[j+1];
        }
        rem_zero[genlen-1] = 0;
//        printf("rem: %s\n", rem_zero);
        /*if(i == 0)
        {
            printf("rem: %s\n", rem);
        }*/
        
        if(i == 0)
        {
            i = i + genlen;
        }
        else
        {
            i++;
        }
        
    }

    //printf("remainder in XOR %s\n", rem_zero);

    retRem = (char*)malloc(genlen);
    for(int i=0; i<genlen-1; i++)
    {
        retRem[i] = rem_zero[i];
    }
    retRem[genlen-1] = 0;
    //printf("return remainder in XOR %s\n", retRem);
    return (char *)retRem;
}

char* CRC_zeros(char* input, char* divisor)
{
    char *rem;

    int inputlen = strlen(input);
    int genlen = strlen(divisor);

    char checksumStr[100];

    for(int i=0; i<inputlen; i++)
    {
        checksumStr[i] = input[i];
    }

    for(int i=inputlen; i<inputlen + genlen-1; i++)
    {
        checksumStr[i] = '0';
    }

    checksumStr[inputlen + genlen-1] = 0;
    //printf("case3: checksumStr after appending zeros: %s\n", checksumStr); //uncomment it
    rem = XOR(checksumStr, divisor);

    //printf("remainder in CRC_zero %s\n", rem); //uncomment it
    return (char *)rem;
}

char* CRC_rem(char *input, char* divisor, char* rem_rem)
{
    char *retRem;
    int inputlen = strlen(input);
    int genlen = strlen(divisor);

    char checksumStr[100];

    for(int i=0; i<inputlen; i++)
    {
        checksumStr[i] = input[i];
    }

    int k=0;
    for(int i=inputlen; i<inputlen + genlen-1; i++)
    {
        checksumStr[i] = rem_rem[k];
        k++;
    }

    checksumStr[inputlen + genlen-1] = 0;
    //printf("case3: checksumStr with rem: %s\n", checksumStr); //uncomment it

    retRem = XOR(checksumStr, divisor);
    //printf("\nremainder in CRC_rem %s\n", retRem); //uncomment it
    return (char *)retRem;
}

/*int main()
{
    char input[10000], divisor[100];

    printf("enter input: ");
    scanf("%s", input);

    printf("enter divisor: ");
    scanf("%s", divisor);

    char *rem = CRC_zeros(input, divisor);

    printf("enter input: ");
    scanf("%s", input);

    CRC_rem(input, divisor, rem);
}*/
