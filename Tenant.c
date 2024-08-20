#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Tenant.h"
#include "General.h"

void initTenant(Tenant* pTenant, Tenant** tenantArr, int countTenant)
{
	pTenant->tenantName = getStrExactName("Enter Tenant Name:");
	pTenant->tenantNameLen= countStrLen(pTenant->tenantName);
	pTenant->tenantAge = getAge();
	tenantId(pTenant->tenantID, tenantArr, countTenant);
	getDate(&pTenant->entryDate);
}

int getAge() 
{
	int age = 0;
	do {
		printf("Enter Tenant Age between 60 to 120:\t");
		scanf("%d", &age);
	} while (age < 60 || age > 120);

	return age;
}

void tenantId(char* id, Tenant** tenantArr, int countTenant)
{
	char temp[STR_LEN];
	int check = 0;
	int ok = 1;
	do {
		ok = 1;
		printf("Enter Tenant ID (should be %d numbers):\t", ID_LENGTH);
		myGets(temp, STR_LEN);
		if (strlen(temp) != ID_LENGTH)
		{
			printf("Error! ID should be %d numbers.\n", ID_LENGTH);
			ok = 0;
		}
		else if((ContainsOnlyNumbersToID(temp)) == 0)
		{
				printf("Error! ID needs to be ONLY numbers.\n");
				ok = 0;
		}
		else
		{
			for (int i = 0;	i < countTenant; i++)
			{
				if (strcmp(temp, &tenantArr[i]->tenantID) == 0)
				{
					printf("Error! Tenant with this id already exists.\n");
					ok = 0;
				}
			}		
		}

	} while (!ok);

	strcpy(id, temp);
}

void tenantIdToFind(char* id)
{
	char temp[STR_LEN];
	int check = 0;
	int ok = 1;
	do {
		ok = 1;
		printf("Enter Tenant ID (should be %d numbers):\t", ID_LENGTH);
		myGets(temp, STR_LEN);
		if (strlen(temp) != ID_LENGTH)
		{
			printf("Error! ID should be %d numbers.\n", ID_LENGTH);
			ok = 0;
		}
		else  
		{
			if ((ContainsOnlyNumbersToID(temp)) == 0)
			{
				printf("Error! ID needs to be ONLY numbers.\n");
				ok = 0;
			}		
		}
	} while (!ok);

	strcpy(id, temp);
}

int	compareTenantByName(const void* tenant1, const void* tenant2)
{
	const Tenant* pTenant1 = *(const Tenant**)tenant1;
	const Tenant* pTenant2 = *(const Tenant**)tenant2;

	return strcmp(pTenant1->tenantName, pTenant2->tenantName);
}

int	compareTenantByID(const void* tenant1, const void* tenant2)
{
	const Tenant* pTenant1 = *(const Tenant**)tenant1;
	const Tenant* pTenant2 = *(const Tenant**)tenant2;

	return strcmp(pTenant1->tenantID, pTenant2->tenantID);
}

int	compareTenantByAge(const void* tenant1, const void* tenant2)
{
	const Tenant* pTenant1 = *(const Tenant**)tenant1;
	const Tenant* pTenant2 = *(const Tenant**)tenant2;

	return compareInt(&pTenant1->tenantAge, &pTenant2->tenantAge);
}

int	compareTenantByEntryDate(const void* tenant1, const void* tenant2)
{
	const Tenant* pTenant1 = *(const Tenant**)tenant1;
	const Tenant* pTenant2 = *(const Tenant**)tenant2;

	return compareEntryDate(&pTenant1->entryDate, &pTenant2->entryDate);
}

int	compareInt(const void* c1, const void* c2)
{
	const int cInt1 = *(int**)c1;
	const int cInt2 = *(int**)c2;

	if (cInt1 > cInt2)
	{
		return 1;
	}
	else if (cInt1 < cInt2) {
		return -1;
	}

	return 0;
}

void printTenant(const Tenant* pTenant)
{
	printf("Tenant Name: %s, Age: %d, ID: %s\n", pTenant->tenantName, pTenant->tenantAge, pTenant->tenantID);
	printDate(&pTenant->entryDate);
	printf("\n");
}

void freeTenant(void* pTenant)
{
	Tenant* temp = *(Tenant**)pTenant;
	free(temp);
}