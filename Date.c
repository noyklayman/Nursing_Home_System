#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Date.h"
#include "General.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define BACK_SLASH '/'

void getDate(Date* pDate)
{
	char date[STR_LEN];
	int check = 1;

	do {
		printf("Enter entry date  dd%cmm%cyyyy  minimum year %d:\t", BACK_SLASH, BACK_SLASH, MIN_YEAR);
		myGets(date, STR_LEN, stdin);
		check = checkDate(date, pDate);
		if (!check)
			printf("Error try again\n");
	} while (!check);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ((date[2] != BACK_SLASH) || (date[5] != BACK_SLASH))
		return 0;
	sscanf(date, "%d%*c%d%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

int	compareEntryDate(const void* d1, const void* d2)
{
	const Date* pDate1 = (const Date*)d1;
	const Date* pDate2 = (const Date*)d2;

	if (pDate1->year > pDate2->year)
		return 1;
	if (pDate1->year < pDate2->year)
		return -1;

	if (pDate1->month > pDate2->month)
		return 1;

	if (pDate1->month < pDate2->month)
		return -1;

	if (pDate1->day > pDate2->day)
		return 1;

	if (pDate1->day < pDate2->day)
		return -1;

	return 0;
}

void printDate(const Date* pDate)
{
	printf("Entry Date: %d/%d/%d", pDate->day, pDate->month, pDate->year);
}