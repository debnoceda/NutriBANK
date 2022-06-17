#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>


typedef struct {
	char userName[50];
	char firstName[20];
	char lastName[20];
	char address[50];
	char email[255];
	char birthMonth[10];
	char birthDay[10];
	char birthYear[10];
	char phoneNumber[15];
	char password[20];
	float balance;
}accountData;

//Declaration of all functions
void printChoices ();
void createAccount(accountData *user);
void printNewAccount();
void accountSuccessfullyCreated();
void loginSuccessfully();
void homeScreen(accountData user);
void balanceCheck(accountData user);
void systemProcessing ();
void logout();


void gotoxy (int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main (){
accountData user, receiver;
FILE *fp, *fptr;
char filename[20];
char username[50];
char password [20];
char decision = 'y';
int choice1, choice2;
int money;

	while (true){
		system("cls");
		printf("\n\n\n\n\t\t==== Welcome to NutriBANK ====");
		gotoxy (18, 5);
		printChoices();
		printf("\n\n\nPlease select a number:");
		scanf("%d", &choice1);
		if (choice1 == 1){
			createAccount (&user);
			user.balance = 0;
			printNewAccount(user);
			strcpy(filename, user.userName);
			fp=fopen(strcat(filename,".txt"),"w");
			fwrite(&user,sizeof(user),1,fp);

			if(fwrite != 0){
				accountSuccessfullyCreated();
			}
		}
		else if (choice1 == 2){
			system ("cls");
			gotoxy (34, 2);
			printf("\tAccount Login");
			gotoxy(7,5);
			printf("-----------------------------------------------""--------------------------------");
			gotoxy (35, 10);
			printf("======= LOG IN ======");

			gotoxy(30, 12);
			printf("Enter username:");
			scanf("%s", &username);
	
			gotoxy (30,14);
			printf("Enter password:");
			scanf("%s", &password);
			fp = fopen(strcat(username,".txt"),"r");
			if (fp == NULL){
				printf("\nERROR, username isn't registered in the system!");
				printf("Press any key to go back to Main Menu.\n");
				getch();
			}
			else {
				fread(&user,sizeof(user),1,fp);
				fclose(fp);
				if(strcmp(password,user.password)==0){
					loginSuccessfully();
					while(true){
						homeScreen(user);

						printf("\n\n\nPlease select the transaction you want:");
						scanf("%d", &choice2);

						if(choice2 == 1 ){
							balanceCheck(user);
						}
						else if(choice2==2){
							system("cls");

							gotoxy (30, 8);
							printf("Enter amount to be added in the account:");
							scanf("%d", &money);		
							user.balance += money;
							fp = fopen(username, "w");
							fwrite (&user, sizeof(user), 1, fp);
							if(fwrite!=0)
							systemProcessing(); 
							gotoxy(30, 8);
							printf("The amount P%d has been added to your account.", money);
							fclose(fp);
						}
						else if(choice2==3){
							system("cls");

							gotoxy(30,8);
							printf("Enter an amount to be withdrawn:");
							scanf("%d", &money);
							if (money % 100 !=0)
								printf("\n\n\n\n\nSorry, processed cannot be completed. Amount should be a multiple of 100");
							else{
								user.balance-=money;
								fp = fopen(username, "w");
								fwrite (&user, sizeof(user), 1, fp);
								if(fwrite!=0) 
								systemProcessing();
								gotoxy(30, 10);
								printf("An amount of P%d has been withdrawn from the account.", money);
								fclose(fp);
							}
						}
						else if(choice2==4){
							system("cls");
							gotoxy(30, 8);
							printf("Please enter the username of the receiver:");
							scanf("%s",username);
							gotoxy (30, 10);
							printf("Enter the amount to transfer:");
							scanf("%d",&money);
							systemProcessing();
							if(money > user.balance) 
								printf("\n\n\n\n\n\nSorry insufficent balance");
							else {
							fptr = fopen(strcat(username,".txt"),"r");
							if(fptr==NULL) 
								printf("\n\n\n\n\n\n\n\nERROR! Username is not registered in the system. Please try again.");
							else {
								fread(&receiver,sizeof(user),1,fptr);
								fclose(fptr);
							
								receiver.balance += money;
								
								fptr = fopen(username,"w");
								fwrite(&receiver,sizeof(user),1,fptr);
								if(fwrite != 0){
									//printf("\nUsername: %s", receiver.userName);
									//printf("\nName: %s %s", receiver.firstName, receiver.lastName);
									//printf("\nEmail: %s", receiver.email);
									//printf("\nBirthday: %s%s%s", receiver.birthMonth, receiver.birthDay, receiver.birthYear);
									//printf("\nPhone Number: %s", receiver.phoneNumber);
									//printf("\nPassword: %s", receiver.password);
									//printf("\nAccount Balance: %f", receiver.balance);
									gotoxy(30,10);
									printf("The transaction is completed. The amount P%d was transferred to %s", money, receiver.userName);
									fclose(fptr);
									user.balance -= money;
									strcpy(filename,user.userName);
									fp = fopen(strcat(filename,".txt"),"w");
									fwrite(&user,sizeof(user),1,fp);
									fclose(fp);
								}
							}
						}
						}
						else if(choice2==5){
							system("cls");

							gotoxy(30, 8);
							printf("Please enter your old password:");
							scanf("%s",password);
							if(!strcmp(password,user.password)){
								gotoxy(30,9);
								printf("Please enter your new password:");
								scanf("%s",password);
								strcpy(user.password,password);
								strcpy(filename,user.userName);
								fp = fopen(strcat(filename,".txt"),"w");
								fwrite(&user,sizeof(user),1,fp);
								fclose(fp);
								systemProcessing();
								gotoxy(30, 8);	
								printf("Password succesfullly changed!");
							}
							else 
								printf("\nSorry your password is wrong");
						}
						else if(choice2==6){
							logout();
							break;
						}
						else{
							printf("INVALID INPUT!");
							printf("Please press any key to try again");
							getch();
						}
						printf("\n\n\n\n\n\nDo you want to make another transaction? Press 'y' to continue.\n");
						scanf("%s", &decision);
						if (decision != 'y'){
							system ("cls");
							gotoxy(30,10);
							printf("Thank you for using NutriBANK");
							for (int i=0; i<200000000; i++){
								i++;
								i--;
							}
							logout();
							break;
						}
					}
				}
				else{
					gotoxy(7, 20);
					printf("ERROR, Invalid password!");
					gotoxy(7,22);
					printf("Please press any key to go back to the Main Menu\n");
					getch();
				}
			}
		}
		else if (choice1 == 3){
			printf("\nThank you for using NutriBANK");
			break;
		}
		else {
			printf("\nPlease enter a valid number!");
			for (int i=0; i<200000000; i++){
				i++;
				i--;
	}
		}
	}

	return 0;
}

void printChoices(){
	printf("\n\n----------------------------------------------------------");
	gotoxy (25, 7);
	printf("\n\t\t\tMAIN MENU");
	gotoxy (20, 10);
	printf("\n\t\t1.Create a new account");
	gotoxy (20, 12);
	printf("\n\t\t2.Login to your account");
	gotoxy (20, 14);
	printf("\n\t\t3.Exit");
	printf("\n----------------------------------------------------------");
}

void createAccount(accountData *user){
	system("cls");

		printf("\n\t\t\tCreate Account\n\n");
		printf("Enter username:");
		scanf("%s", &user->userName);
		fflush(stdin);
		printf("Enter first name and last name:");
		scanf("%s %s", &user->firstName, &user->lastName);
		fflush(stdin);
		printf("Enter address:");
		scanf("%s", &user->address);
		printf("Enter email:");
		scanf("%s", &user->email);
		fflush(stdin);
		printf("Enter birthday (mm/dd/yyyy format):");
		scanf("%s/%s/%s", &user->birthMonth, &user->birthDay, &user->birthYear);
		fflush(stdin);
		printf("Enter phone number:");
		scanf("%s", &user->phoneNumber);
		fflush(stdin);
		printf("Enter password:");
		scanf("%s", &user->password);
		fflush(stdin);
}

void printNewAccount(accountData user){
		printf("\nUsername: %s", user.userName);
		printf("\nName: %s %s", user.firstName, user.lastName);
		printf("\nEmail: %s", user.email);
		printf("\nBirthday: %s%s%s", user.birthMonth, user.birthDay, user.birthYear);
		printf("\nPhone Number: %s", user.phoneNumber);
		printf("\nPassword: %s", user.password);
		printf("\nAccount Balance: %.2f", user.balance);
		printf("\n\nPlease press any key to confirm");
		getch();
	
}

void accountSuccessfullyCreated(){
	int i;
	system("cls");
	printf("Please wait...\n\nYour data is processing..");
	for (i = 0; i < 10; i++) {
        for (int j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }

	gotoxy (30, 10);
	printf("Account has been successfully created!");
	gotoxy(0,20);
	printf("\nPlease press any key to go back to the Main Menu.");
	getch();

}

void loginSuccessfully (){
	int i;
	system ("cls");
	printf("Fetching account details..");
	for (i = 0; i < 10; i++) {
        for (int j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }

	gotoxy(30, 10);
	printf("Login Successfully!");
	gotoxy (0,20);
	printf("Press any key to continue");
	getch();
}

void homeScreen(accountData user){
	system("cls");

		gotoxy (30,1);
		printf("Welcome, %s %s", user.firstName, user.lastName);
		gotoxy(25,2);
		printf("------------------------------");
		gotoxy(55,6);
		printf("==== Your Account Information ====");
		gotoxy(55,8);
		printf("++++++++++++++++++++++++++++++++++");
		gotoxy(55,10);
		printf("Account ID: %u", user.userName);
		gotoxy(55,12);
		printf("Name: %s %s", user.firstName, user.lastName);
		gotoxy(55,14);
		printf("Address: %s", user.address);
		gotoxy(55,16);
		printf("Email: %s", user.email);
		gotoxy(55,18);
		printf("Birthday: %s%s%s", user.birthMonth, user.birthDay, user.birthYear);
		gotoxy(55,20);
		printf("Phone number: %s", user.phoneNumber);

		gotoxy(0,4);
		printf("\tHomescreen");
		gotoxy(0,6);
		printf("--------------------------");
		gotoxy(0,8);
		printf("1.Balance Check");
		gotoxy(0,10);
		printf("2.Cash Deposit");
		gotoxy(0,12);
		printf("3.Withdraw");
		gotoxy(0,14);
		printf("4.Send Money");
		gotoxy(0,16);
		printf("5.Change Password");
		gotoxy(0,18);
		printf("6.Logout");

}

void systemProcessing (){
	system("cls");
	printf("System is processing the transanction please wait..");
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }
}

void balanceCheck (accountData user){
	systemProcessing();
	gotoxy(43, 5);
	printf("ACCOUNT");
	gotoxy(30, 10);
	printf("Your current balance is P%.2f", user.balance);
}

void logout(){
	int i, j;
    system("cls");
    printf("Please wait, signing off..");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }
 
    gotoxy(30, 10);
    printf("Sign out successfully!\n");
 
    gotoxy(0, 20);
    printf("Please press any key to continue");
 
    getch();
}


