#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "GroupActivity.h"
#include "General.h"

#define TOTAL_MINUTES(a,b)(a * 60 + b)

void initGroupActivity(GroupActivity* pGroup, Employee* instructor, GroupActivity** groupActivityArr,int countGroupActivity)
{
	pGroup->instructor = instructor;
	pGroup->groupActivityName = getStrExactName("Enter Group Activity Name:");
	pGroup->startingHour = getHour("Please enter starting Hour:");
	char* endHour = getHour("Please enter ending Hour:");

	while (validateGroupActivityHours(pGroup->startingHour, endHour) == 0)
	{
		endHour = getHour("Group Activity should be two hours, enter ending Hour again:");
	}

	pGroup->endingHour = endHour; 

	int studioNumber = scanStudioNumber();
	
	if (check(groupActivityArr, countGroupActivity, studioNumber, pGroup->startingHour, pGroup->endingHour) == 0)
	{
		printf("Please choose another number of studio:\n");
		scanf("%d", &studioNumber);
	}
	
	pGroup->studioNumber = studioNumber;
	pGroup->tenantCount = 0;	
}

int  scanStudioNumber()
{
	int studioNumber = 0;
	do {
		printf("Please choose number of studio:\n");
		printf("600 - studio Lilach\n601 - studio Narkis\n602 - studio Vered\n603 - studio Savion\n");
		scanf("%d", &studioNumber);
	} while (studioNumber < 600 || studioNumber > 603);
	return studioNumber;
}

int validateGroupActivityHours(const char* startingHour, const char* endingHour)
{
	int hoursS = atoi(startingHour);
	int minutesS = atoi(startingHour + 3);

	int hoursE = atoi(endingHour);
	int minutesE = atoi(endingHour + 3);

	int totalMinutesS = TOTAL_MINUTES(hoursS,minutesS);
	int totalMinutesE = TOTAL_MINUTES(hoursE,minutesE);

	int total = totalMinutesE - totalMinutesS;

	if (total <= 120 && total >= 60)
		return 1;
	else
		return 0;
}

void printGroupActivity(const GroupActivity* pGroupA)
{
	printf("Group Activity Name: %s, Teacher Name:  %s, Studio Number: %d\n",
		pGroupA->groupActivityName, pGroupA->instructor->employeeName, pGroupA->studioNumber);
	printf("Start At %s End At %s\n", pGroupA->startingHour, pGroupA->endingHour);
}

int compareGroupActivityByName(const void* groupActivity1, const void* groupActivity2)
{
	const GroupActivity* pGroupActivity1 = *(const GroupActivity**)groupActivity1;
	const GroupActivity* pGroupActivity2 = *(const GroupActivity**)groupActivity2;

	return strcmp(pGroupActivity1->groupActivityName, pGroupActivity2->groupActivityName);
}

int	check(GroupActivity** groupActivityArr, int countGroupActivity, int studioNumber, char* startingHour, char* endingHour)
{
	int ch = 0;
	for (int i = 0; i < countGroupActivity; i++)
	{
		if (groupActivityArr[i]->studioNumber == studioNumber)
		{
			if (overlapHours(groupActivityArr[i]->startingHour, groupActivityArr[i]->endingHour, startingHour, endingHour) == 0)
			{
				return 0;
			}
		}
	}
	return 1;	
}

int overlapHours(const char* startingHour1, const char* endingHour1, const char* startingHour2, const char* endingHour2)
{

	int numS1 = atoi(startingHour1);
	int numE1 = atoi(endingHour1);
	int numS2 = atoi(startingHour2);
	int numE2 = atoi(endingHour2);

	if((numS2 < numS1 && numE2 <= numS1)  || (numS2 >= numE1 && numE2 > numE1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void freeGroupActivity(void* pGroup)
{
	GroupActivity* temp = *(GroupActivity**)pGroup;
	free(temp);
}
