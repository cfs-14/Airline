/*
-Fill the existing inventory from a data file
-Allow users to enter transaction data from the keyboard
-Subtract transaction data from existing inventory
-Print an inventory report (original & updated)
-Print a transaction report
-Write an updated inventory file back to the disk
*/


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>

using namespace std;
using namespace System;

void printHeader(const char *);
inline void printTitles(void);
char * getMonthAbb(int mo);

int main(void)
{
	//>>Dec. Vars
	char *invName = "C:/Users/AdminMain.cece-PC/Desktop/Inventory.txt"; //"C:/Users/csadvanced/Desktop/Inventory.txt";
	FILE *invFile;
	char buffer = '\0', taction = '\0';
	char bufferStr[12] = "\0";//This was causing probs b/c string space was too small, so it would cause itemNo[0] == 8224 down the line. 
	int itemNo[9] = { 0 }, itemNoT[9] = { 0 };
	int stockAmt[9] = { 0 }, stockAmtT[9] = { 0 };
	int num = 0; 
	int limiter = 0;

	//>>Print Menu //view inventory or enter transaction data

	//>>Read inventory data from file of text
	invFile = fopen(invName, "r+");//open file for reading and writing, file must exist. 
	for (int newL = 0, i = 2, index = 0;!(feof(invFile));) // i has to at least equal to the number being modded by
	{
		//Will have to establish a signal in order to start reading in the nums as ints.\
						1. After reading in "stock"\
		2. After reading x amount of nums, (will req. const. num checking).\
		3. After 4 newlines
		while (newL < 4)
		{
			buffer = fgetc(invFile);
			if (buffer == '\n')
			{
				newL++;
			}

			putchar(buffer);
		}
		while (!(feof(invFile))) //Starts reading in Item no's and stock amts as ints. 
		{
			//scan & print whitespace string
			fscanf(invFile, "%[\t\n ]", bufferStr);
			printf("%s", bufferStr); //prints to stdout whitespace from string.

			//printf("*b/f,count: %d\tItemNo[0]: %4d*", count+1, itemNo[0]);//Happens here before countj gets to 10. 

			//scans num from file
			fscanf(invFile, "%d", &num);
			printf("%d", num); //prints to stdout the number read from file.
			//save into var
			printf("Num got: %d*", num);
			itemNo[index] = num;

			//scan & print whitespace string
			fscanf(invFile, "%[\t\n ]", bufferStr);
			printf("%s", bufferStr); //prints to stdout whitespace from string

			//scans num from file
			fscanf(invFile, "%d", &num);
			printf("%d", num); //prints to stdout the number read from file.
			//save into var
			stockAmt[index] = num;
			buffer = fgetc(invFile);
			putchar(buffer);
			index++;
			//count++;

			limiter = index; //future index limiter to print itemNo & stockAmt;
		}
	}

	//Ask for transaction data
	puts("\n\nWould you like to enter transaction data? Y/N: ");
	
	taction = (char)getch();
	putchar(taction);
	for (int index = 0; taction == 'Y' || taction == 'y'; index++)
	{ 
		puts("\nPlease enter the stock number: ");
		scanf("%4d", &itemNoT[index]);
		puts("\nPlease enter the amount of the transaction:");
		scanf("%d", &stockAmtT[index]);
		puts("\nWould You like to enter another transaction? Y/N: ");
		taction = (char)getch();
		putchar(taction);
	}
	///Print transaction
	//print header
	
	putchar('\n');
	putchar('\n');
	printHeader("Transaction");
	for (int j = 0; j < sizeof (itemNoT) / sizeof (itemNoT[0]); j++ )
	{
		printf("\t%4d\t\t\t%10d\n", itemNoT[j], stockAmtT[j]);

	}
	

	//test print if data is gotten
	/*
		for (int i = 0; i < limiter; i++)
		{
			printf("\nItem No: %4d\tStockAmt: %3d", itemNo[i], stockAmt[i]);
		}
	printf("\nItemNo[0]: %4d", itemNo[0]);
	*/

	//>>Enter transaction data

	puts("\nPress any key to exit");
	_getch();
	return 0;
}

void printHeader(const char  *title = " ")
{
	time_t currTime = time(NULL);
	struct tm *currTimeInf = localtime(&currTime);
	char * monthName = '\0';

	monthName = getMonthAbb(currTimeInf->tm_mon + 1);

	printf("\t\t\tWidget Corportation\
		\n\t\t%s Report as of ", title);
	printf("%s %02d, %4d\n", monthName, currTimeInf->tm_mday, currTimeInf->tm_year + 1900); //req's switch case for 1->1st, 2->2nd, etc. 
	puts("\n\tItem Number\t\t\tAmount in Stock\n");
}

char * getMonthAbb(int mo)
{
	switch (mo)
	{
	case 1:
		return "Jan";
	case 2:
		return "Feb";
	case 3:
		return "Mar";
	case 4:
		return "Apr";
	case 5:
		return "May";
	case 6:
		return "Jun";
	case 7:
		return "Jul";
	case 8:
		return "Aug";
	case 9:
		return "Sept";
	case 10:
		return "Oct";
	case 11:
		return "Nov";
	case 12:
		return "Dec";
	default:
		return "ERR";
	}

}

inline void printTitles(void)
{
	puts("\n\tItem Number\t\t\tAmount in Stock\n");
}