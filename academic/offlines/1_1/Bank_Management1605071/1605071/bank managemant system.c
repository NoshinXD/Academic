#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

typedef struct
{
	int day;
	int month;
	int year;
}date;

typedef struct
{
	int TID;
	char TDescription;
	int Ttype;
	date Tdeposit_date;
	date Twithdraw_date;
	date Ttransfer_date;
	int t;
}Transaction;

typedef struct
{
	char name[100];
	int acc_no;
	date open_date;
	Transaction Thistory;
	int balance;
	int index;
	int indexw;
	int indext;
} bank;

 int deposit_amount[10][100];
 int (*dpa)[100]= deposit_amount;
 date  deposit_date[10][100];

 int withdraw_amount[10][100];
 int (*wpa)[100]= withdraw_amount;
 date withdraw_date[10][100];

 int transfer_amount[10][100];
 int (*tpa)[100]= transfer_amount;
 date transfer_date[10][100];

 int i=0 ,j1=0 ,indexj1 ;
 bank user[10];
 int acc=1000;
 int trans=2000;

 FILE *fptr;



 int menu();
 void Openacc();
 void Depositacc();
 int Searchacc(int holder);
 void Displayacc();
 void Withdrawacc();
 void Transferacc();
 void Transactionacc();

void gotoxy(int x, int y)
{
    COORD c={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int main()
{
	int option;
	do{

		option=menu();
		switch(option)
		{
			case 0: Openacc();
                    break;
			case 1: Depositacc();
                    break;
			case 2: Withdrawacc();
                    break;
			case 3: Transactionacc();
                    break;
			case 4: Displayacc();
                    break;
			case 5: Transferacc();
                    break;
		}

		if(option==6)
            break; break; break; break; break; break; break; break; break; break; break;

	 } while(option !=7);

	return 0;
}


int menu(void)
{
    int option;

	gotoxy(25,5);
	printf("0 For Opening Account.");

	gotoxy(25,6);
	printf("1 For Depositing Money.");

	gotoxy(25,7);
	printf("2 For Withdrawing Money.");

	gotoxy(25,8);
	printf("3 For Showing Transaction History.");

	gotoxy(25,9);
	printf("4 For Showing account Balance.");

	gotoxy(25,10);
	printf("5 For Transferring Money");

	gotoxy(25,11);
	printf("6.Exit");

	gotoxy(25,12);
	printf("Enter your option:");

	scanf("%d",&option);
	getch();

	system("cls");

	return option;

}
void Openacc()
{
    fptr= fopen("bank_management.txt", "a");
	printf("Enter your name:\n");
	scanf("%s",user[i].name);
	fprintf(fptr,"Name= %s\n",user[i].name);

	printf("Enter open date(DD/MM/YY):\n");
    scanf("%d%d%d",&user[i].open_date.day ,&user[i].open_date.month ,&user[i].open_date.year);
	fprintf(fptr,"OpenDate:%d/%d/%d\n",user[i].open_date.day ,user[i].open_date.month ,user[i].open_date.year);

	user[i].balance=0;

	printf("You have successfully opened a bank account.\n");

	acc++;
	user[i].acc_no=acc;
	printf("\n");

	printf("Name: %s\n",user[i].name);
	printf("Your account number:%d\n",user[i].acc_no);
	fprintf(fptr,"Acc. no: %d\n",user[i].acc_no);
	printf("Your account was opened on %d/%d/%d.\n\n\n",user[i].open_date.day ,user[i].open_date.month ,user[i].open_date.year);

	user[i].index=0;
	user[i].indexw=0;
	user[i].indext=0;
	i++;

	fclose(fptr);
	getch();
	system("cls");

	main();
}

void Depositacc(void)
{
    fptr= fopen("bank_management.txt", "a");

	int amount ,k ,holder;

	printf("Enter your account no:\n");
	scanf("%d",&holder);
	k=Searchacc(holder);

	if(k!=-1)
    {
		printf("Enter the amount you want to deposit:\n");
		scanf("%d",&deposit_amount[k][user[k].index]);
		fprintf(fptr, "Depositamount: %d\n",deposit_amount[k][user[k].index]);

		printf("Enter date(DD/MM/YY):\n");
		scanf("%d%d%d",&user[k].Thistory.Tdeposit_date.day ,&user[k].Thistory.Tdeposit_date.month ,&user[k].Thistory.Tdeposit_date.year);
		fprintf(fptr, "Deposit Date: %d/%d/%d\n",user[k].Thistory.Tdeposit_date.day ,user[k].Thistory.Tdeposit_date.month ,user[k].Thistory.Tdeposit_date.year );

		user[k].balance+=deposit_amount[k][user[k].index];

		deposit_date[k][user[k].index]=user[k].Thistory.Tdeposit_date;

		user[k].index++;
    }
	else
        printf("Your account is not found.\n\n\n");

	fclose(fptr);
	getch();
	system("cls");

	main();
}

int Searchacc(int holder)
{
    int j;
	for(j=0;j<i;j++)
    {
        if(user[j].acc_no==holder)
		{
		    break;
        }
	}
	if(j==i)
        return -1;
	if(j<i)
        return j;
}

void Displayacc()
{
    fptr= fopen("bank_management.txt", "a");
	int holder ,k ,indexi;

	printf("Enter your acc. no:\n");
	scanf("%d",&holder);
	k=Searchacc(holder);

	if(k!=-1)
    {
		printf("Your name: %s\n",user[k].name);
		printf("Your account number: %d\n",user[k].acc_no);
		printf("Your balance: %d Tk\n",user[k].balance);
    }
	else
        printf("Your account is not found.\n\n\n");

	fclose(fptr);
	getch();
	system("cls");

	main();
}

void Withdrawacc(void)
{
    fptr= fopen("bank_management.txt", "a");
	int k ,holder;

	printf("Enter  account number:\n");
	scanf("%d",&holder);
	k=Searchacc(holder);

	if(k!=-1)
    {
		printf("Enter amount of money:\n");
		scanf("%d",&withdraw_amount[k][user[k].indexw]);

		if(withdraw_amount[k][user[k].indexw]>user[k].balance)
            printf("You cannot withdraw money.\n\n\n");
		else
		{
            fprintf(fptr, "Withdrawamount: %d\n",withdraw_amount[k][user[k].indexw]);
            printf("Enter date(DD/MM/YY):\n");
            scanf("%d%d%d",&user[k].Thistory.Twithdraw_date.day ,&user[k].Thistory.Twithdraw_date.month ,&user[k].Thistory.Twithdraw_date.year);

            fprintf(fptr, "Withdraw Date: %d/%d/%d\n",user[k].Thistory.Twithdraw_date.day ,user[k].Thistory.Twithdraw_date.month ,user[k].Thistory.Twithdraw_date.year );

            user[k].balance-=withdraw_amount[k][user[k].indexw];

            withdraw_date[k][user[k].indexw]=user[k].Thistory.Twithdraw_date;

            user[k].indexw++;
		}
	}
	else
	   printf("Your account is not found.\n\n\n");

	   fclose(fptr);
	   getch();
	   system("cls");

	   main();
}

void Transferacc(void)
{
    fptr= fopen("bank_management.txt", "a");
	int  k, holder ,holder1 ,k1;

	printf("Your account  number:\n");
	scanf("%d",&holder);
	k=Searchacc(holder);

	if(k!=-1)
    {
		printf("To the account:\n");
		scanf("%d",&holder1);
		k1=Searchacc(holder1);
		if(k1!=-1)
		{
			printf("Enter the amount:\n");
			scanf("%d",&transfer_amount[k][user[k].indext]);

			transfer_amount[k1][user[k1].indext]=transfer_amount[k][user[k].indext];

			if(transfer_amount[k][user[k].indext]>user[k].balance)
                printf("You cannot transfer money.\n\n\n");
			else
			{
                fprintf(fptr, "Transferamount: %d\n",transfer_amount[k][user[k].indext]);
                printf("Enter date(DD/MM/YY):\n");
                scanf("%d%d%d",&user[k].Thistory.Ttransfer_date.day ,&user[k].Thistory.Ttransfer_date.month ,&user[k].Thistory.Ttransfer_date.year);

                fprintf(fptr, "Transfer Date: %d/%d/%d\n",user[k].Thistory.Ttransfer_date.day ,user[k].Thistory.Ttransfer_date.month ,user[k].Thistory.Ttransfer_date.year );

                user[k].balance-=transfer_amount[k][user[k].indext];
                user[k1].balance+=transfer_amount[k][user[k].indext];

                transfer_date[k][user[k].indext]=user[k].Thistory.Ttransfer_date;
                transfer_date[k1][user[k1].indext]=user[k].Thistory.Ttransfer_date;

                user[k].indext++;
			}

		}
		else
            printf("Target account is not found.\n\n\n");
	}
	else
        printf("Your account is not found.\n\n\n");

	fclose(fptr);
	getch();
	system("cls");

	main();
}

void Transictionacc()
{
    fptr= fopen("bank_management.txt", "a");
	int holder ,k ,indexi;

	printf("Enter your acc. no:");
	scanf("%d",&holder);
	k=Searchacc(holder);

	if(k!=-1)
    {
        for(indexj1=0 ;*(*(dpa+k)+indexj1) ;indexj1++)
        {
            printf("Transacted Money: %d Tk \n", deposit_amount[k][indexj1]);
			printf("Transaction Type: Deposit\n");
			printf("Transaction Date: %d/%d/%d\n",deposit_date[k][indexj1]);
			printf("TID: %d\n",deposit_amount[k][indexj1]+127865502 );
			printf("\n");
		}
		printf("\n\n");

		for(indexj1=0;*(*(wpa+k)+indexj1);indexj1++)
        {
            printf("Transacted Money: %d Tk \n", withdraw_amount[k][indexj1]);
			printf("Transaction Type: Withdraw.\n");
			printf("Transaction date: %d/%d/%d\n",withdraw_date[k][indexj1]);
			printf("TID: %d\n",withdraw_amount[k][indexj1]+125466201);
			printf("\n");
		}
		printf("\n\n");

		for(indexj1=0;*(*(tpa+k)+indexj1);indexj1++)
        {
            printf("Transacted Money: %d Tk \n", transfer_amount[k][indexj1] );
			printf("Transation Type: Transfer\n");
			printf("Transaction Date: %d/%d/%d\n",transfer_date[k][indexj1]);
			printf("TID: %d\n",transfer_amount[k][indexj1]+117428370);
			printf("\n");
		}
		printf("\n\n");
	}
	else
        printf("Your account is not found.\n\n\n");

	fclose(fptr);
	getch();
	system("cls");

	main();
}
