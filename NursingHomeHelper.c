#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "NursingHomeHelper.h"
#include "General.h"

void sortTenant(NursingHome* pNursing)
{
	pNursing->tenantSortOpt = showSortMenu();
	int(*compare)(const void* ten1, const void* ten2) = NULL;

	switch (pNursing->tenantSortOpt)
	{
	case eName:
		compare = compareTenantByName;
		break;
	case eID:
		sortTenantById(pNursing); 
		break;
	case eAge:
		compare = compareTenantByAge;
		break;
	case eEntryDate:
		compare = compareTenantByEntryDate;
		break;
	}

	if (compare != NULL)
		qsort(pNursing->tenantArr, pNursing->countTenant, sizeof(Tenant*), compare);
	printTenants(pNursing);
}

void sortTenantById(NursingHome* pNursing)
{
	int(*compare)(const void* ten1, const void* ten2) = NULL;
	compare = compareTenantByName;
	if (compare != NULL)
		qsort(pNursing->tenantArr, pNursing->countTenant, sizeof(Tenant*), compare);
}

void sortGroupActivityName(NursingHome* pNursing)
{
	int(*compare)(const void* ten1, const void* ten2) = NULL;
	compare = compareGroupActivityByName;
	if (compare != NULL)
		qsort(pNursing->tenantArr, pNursing->countTenant, sizeof(Tenant*), compare);
}

eSortOption showSortMenu()
{
	int opt;
	printf("By which parameter do you want to sort?\n");
	do {
		for (int i = 0; i < eNofSortOpt; i++)
			printf("%d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

void findTenant(const NursingHome* pNursing)
{
	int(*compare)(const void* ten1, const void* ten2) = NULL;
	Tenant tStack = { 0 };
	Tenant* t = &tStack;

	switch (pNursing->tenantSortOpt)
	{
	case eName:
		printf("Search by Name:\n");
		t->tenantName = getStrExactName("Enter tenant name:");
		compare = compareTenantByName;
		break;

	case eID:
		printf("Search By ID:\n");
		tenantIdToFind(t->tenantID);
		compare = compareTenantByID;
		break;

	case eAge:
		printf("Search by Age:\n");
		t->tenantAge = getAge(); 
		compare = compareTenantByAge;
		break;

	case eEntryDate:
		printf("Search by Entry date:\n");
		getDate(&t->entryDate);
		compare = compareTenantByEntryDate;
		break;

	}

	if (compare != NULL)
	{
		Tenant** pTen = (Tenant**)bsearch(&t, pNursing->tenantArr, pNursing->countTenant, sizeof(Tenant*), compare);
		if (pTen == NULL)
			printf("Tenant was not found\n");
		else {
			printf("Tenant found, ");
			printTenant(*pTen);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}

}

int findTenantById(const NursingHome* pNursing)
{
	int(*compare)(const void* ten1, const void* ten2) = NULL;
	Tenant tStack = { 0 };
	Tenant* t = &tStack;

	printf("Search By ID:\n");
	tenantId(t->tenantID, pNursing->tenantArr, pNursing->countTenant);
	compare = compareTenantByID;

	if (compare != NULL)
	{
		Tenant** pTen = (Tenant**)bsearch(&t, pNursing->tenantArr, pNursing->countTenant, sizeof(Tenant*), compare);
		if (pTen == NULL)
		{
			printf("Tenant was not found\n");
			return 1; 
		}

		else {
			printf("Tenant found, ");
			printTenant(*pTen);
			return 0; 
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
		return 1; 
	}
}

int findGroupActivityByName(const NursingHome* pNursing)
{
	int(*compare)(const void* ten1, const void* ten2) = NULL;
	GroupActivity tStack = { 0 };
	GroupActivity* group = &tStack;

	printf("Search by Name:\n");
	group->groupActivityName = getStrExactName("Enter group activity name:");
	compare = compareTenantByName;

	if (compare != NULL)
	{
		GroupActivity** pGroup = (GroupActivity**)bsearch(&group, pNursing->groupActivityArr, pNursing->countGroupActivity, sizeof(GroupActivity*), compare);
		if (pGroup == NULL)
		{
			printf("Group Activity was not found\n");
			return 1; 
		}

		else {
			printf("Group Activity found, ");
			printGroupActivity(*pGroup);
			return 0;
		}
	}
	else {
		printf("The search cannot be performed, array not sorted.\n");
		return 1; 
	}
}


