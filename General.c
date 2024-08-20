#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "General.h"
#include "Tenant.h"

#define MAX_RAND 100
#define MIN_RAND 1
#define COLON ':'


char* getStrExactName(const char* msg)
{
	char* str;
	char temp[STR_LEN];
	printf("%s\t", msg);
	myGets(temp, STR_LEN);

	str = getDynStr(temp);
	return str;
}
int countStrLen(char* str)
{
	int count = 0;
	while (*str != '\0') {
		count++;
		str++;
	}
	return count;
}
char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
	{
		return NULL;
	}

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size)
{
	char* ok;
	int c;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, stdin);
			char* newline_pos = strchr(buffer, '\n'); 
			if(newline_pos==NULL) 
			while ((c = getchar()) != '\n' && c != EOF);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char* getEmployeeName(const char* msg)
{
	char* str = (char*)malloc((EMPLOYEE_NAME_LEN) * sizeof(char));
	char temp[EMPLOYEE_NAME_LEN];
	printf("%s\t", msg);
	myGets(temp, EMPLOYEE_NAME_LEN);
	strcpy(str, temp);
	
	return str;
}

int ContainsOnlyNumbersToID(const char* id)
{
	while (*id) {
		if (*id < '0' || *id > '9')
		{
			return 0;
		}
		id++;
	}
	return 1;
}

int randEmployeeNumber()
{
	srand(time(NULL));
	int random_number = rand() % 32;
	return random_number;
}

char* getHour(const char* msg)
{
	char* time = (char*)calloc(HOUR_FORMAT_LENGTH, sizeof(char));
	printf("%s\t", msg);
	scanf("%s", time);

	while (checkHour(time) == 0) {
		printf("Please enter a valid hour (Format 00:00)\n");
		scanf("%s", time);
	}

	return time;
}

int checkHour(const char* time)
{
	if (strlen(time) != 5)
	{
		return 0;
	}

	for (int i = 0; i < 2; i++)
	{
		if (!isdigit(time[i]))
		{
			return 0;
		}
	}
	if (time[2] != COLON)
	{
		return 0;
	}

	for (int i = 3; i < 5; i++)
	{
		if (!isdigit(time[i]))
		{
			return 0;
		}
	}

	int hours = (time[0] - '0') * 10 + (time[1] - '0');
	int minutes = (time[3] - '0') * 10 + (time[4] - '0');

	if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
	{
		return 0;
	}
	return 1;

}

void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+i * typeSize);
}


