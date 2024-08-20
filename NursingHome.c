#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "NursingHome.h"
#include "General.h"
#include "GroupActivity.h"


void initNursingHome(NursingHome* pNursing)
{
	pNursing->employeeArr = NULL;
	pNursing->countEmployee = 0;
	pNursing->roomArr = NULL;
	pNursing->countRoom = 0;
	pNursing->tenantArr = NULL;
	pNursing->countTenant = 0;
	pNursing->groupActivityArr = NULL;
	pNursing->countGroupActivity = 0;
	pNursing->diningRoom = NULL;
}

int addTenant(NursingHome* pNursing)
{
	int indexOfAvilableTherapists = 0;
	int indexOfAvilableKitchenWorkers = 0;
	int result = 1;
	if (pNursing->countTenant == MAX_TENANT_COUNT)
	{
		printf("nursing home has maximum amount of tenants!\n");
		return 0;
	}
	else {
		if (pNursing->countEmployee == 0)
		{
			printf("Error adding a tenant!\nThere is no Employees in Nursing Home.");
			result = 0;
		}
		else {
			indexOfAvilableTherapists = getAvailablePersonalOfType(pNursing, eTherapist);
			indexOfAvilableKitchenWorkers = getAvailablePersonalOfType(pNursing, eKitchen_worker);

			if (indexOfAvilableKitchenWorkers > -1 && indexOfAvilableTherapists > -1)
			{
				Tenant* pTenant = (Tenant*)calloc(1, sizeof(Tenant));
				if (!pTenant)
				{
					return 0;
				}

				initTenant(pTenant, pNursing->tenantArr, pNursing->countTenant);

				pNursing->tenantArr = (Tenant**)realloc(pNursing->tenantArr, (pNursing->countTenant + 1) * sizeof(Tenant*));
				if (!pNursing->tenantArr)
				{
					freeTenant(pTenant);
					free(pTenant);
					return 0;
				}

				pNursing->tenantArr[pNursing->countTenant] = pTenant;
				pNursing->countTenant++;

				addTenantToRoom(pNursing, pTenant);

				increaseEmployeeCapacity(pNursing, indexOfAvilableTherapists, indexOfAvilableKitchenWorkers);
			}
			else {
				if (indexOfAvilableKitchenWorkers == -1)
				{
					printf("Not enough kitchen workers!\n");
					result = 0;
				}
				if (indexOfAvilableTherapists == -1)
				{
					printf("Not enough therapists workers!\n");
					result = 0;
				}
			}
		}
		return result;
	}
}

int addTenantFile(NursingHome* pNursing, Tenant* tenant)
{
	if (!tenant)
	{
		return 0;
	}
	if (pNursing->countEmployee == 0)
	{
		printf("Error adding a tenant!\nThere is no Employees in Nursing Home. first, add employees!\n");
		return 0;
	}
	else {
		pNursing->tenantArr = (Tenant**)realloc(pNursing->tenantArr, (pNursing->countTenant + 1) * sizeof(Tenant*));
		if (!pNursing->tenantArr)
		{
			free(tenant);
			return 0;
		}
		pNursing->tenantArr[pNursing->countTenant++] = tenant;
		return 1;
	}
}

int increaseEmployeeCapacity(NursingHome* pNursing, int indexOfAvilableTherapists, int indexOfAvilableKitchenWorker)
{
	pNursing->employeeArr[indexOfAvilableTherapists].tenantCount++;
	pNursing->employeeArr[indexOfAvilableKitchenWorker].tenantCount++;
}

int countLength(char* str)
{
	int count = 0;
	while (*str) {
		count++;
		str++;
	}
	return count;
}

int getAvailablePersonalOfType(NursingHome* pNursing, eEmployeeType type)
{
	for (int i = 0; i < pNursing->countEmployee; i++)
	{
		if (pNursing->employeeArr[i].employeeType == type
			&& pNursing->employeeArr[i].tenantCount < EmployeeMaxCapacity[type])
		{
			return i;
		}
	}
	return -1;
}

int addEmployee(NursingHome* pNursing)
{
	if (pNursing->countEmployee == MAX_EMPLOYEE_IN_NURSING_HOME)
	{
		printf("nursing home has maximum amount of employees!\n");
		return 0;
	}
	else {
		pNursing->employeeArr = (Employee*)realloc(pNursing->employeeArr, (pNursing->countEmployee + 1) * sizeof(Employee));
		if (!pNursing->employeeArr)
			return 0;
		initEmployee(&pNursing->employeeArr[pNursing->countEmployee], pNursing->employeeArr, pNursing->countEmployee);
		pNursing->countEmployee++;

		if (!checkKitchenWorker(&pNursing->employeeArr[pNursing->countEmployee - 1], pNursing->diningRoom)) {
			return 0;
		}

		printEmployees(pNursing);
		return 1;
	}
}

int addEmployeeFile(NursingHome* pNursing, Employee* employee)
{
	pNursing->employeeArr = (Employee*)realloc(pNursing->employeeArr, (pNursing->countEmployee + 1) * sizeof(Employee));
	if (!pNursing->employeeArr)
		return 0;
	pNursing->employeeArr[pNursing->countEmployee++] = *employee;
	return 1;
}

int checkKitchenWorker(Employee* emp, DiningRoom* diningRoom) {
	if (emp->employeeType == eKitchen_worker) {
		if (!addEmployeeToDiningRoom(emp, diningRoom)) {
			return 0;
		}
	}

	return 1;
}

int addEmployeeToDiningRoom(Employee* emp, DiningRoom* diningRoom) {

	if (diningRoom->employeeArr == NULL) 
	{
		diningRoom->employeeArr = (Employee*)malloc(sizeof(Employee));
		if (!diningRoom->employeeArr) {
			free(diningRoom);
			return 0;
		}
	}
	else {
		diningRoom->employeeArr = (Employee*)realloc(diningRoom->employeeArr, (diningRoom->employeeCount + 1) * sizeof(Employee));
		if (!diningRoom->employeeArr) {
			return 0;
		}
	}
	diningRoom->employeeArr[diningRoom->employeeCount] = *emp;
	diningRoom->employeeCount++;

	return 1;
}

int initDinningRoom(NursingHome* pNursing) {
	pNursing->diningRoom = (DiningRoom*)calloc(1, sizeof(DiningRoom));
	if (!pNursing->diningRoom) {
		return 0;
	}
	L_init(&pNursing->diningRoom->listOfDishes);
}

int addRoom(NursingHome* pNursing, Tenant* pTenant)
{
	Room* pRoom = (Room*)calloc(1, sizeof(Room));

	if (!pRoom)
	{
		return 0;
	}

	pNursing->roomArr = (Room**)realloc(pNursing->roomArr, (pNursing->countRoom + 1) * sizeof(Room*));
	if (!pNursing->roomArr)
	{
		free(pRoom);
		return 0;
	}

	pNursing->roomArr[pNursing->countRoom] = pRoom;
	initRoom(pRoom, pNursing->countRoom);
	pNursing->countRoom++;

	return 1;
}

int addRoomFile(NursingHome* pNursing, Room* room)
{
	if (!room)
	{
		return 0;
	}
	pNursing->roomArr = (Room**)realloc(pNursing->roomArr, (pNursing->countRoom + 1) * sizeof(Room*));
	if (!pNursing->roomArr) 
	{
		freeRoom(room);
		free(room);
		return 0;
	}
	pNursing->roomArr[pNursing->countRoom] = room;
	pNursing->countRoom++;
	return 1;
}

int addTenantToRoom(NursingHome* pNursing, const Tenant* pTenant)
{
	int roomNumber = findRoomForTenant(pNursing);
	Room* pRoom = NULL;
	if (roomNumber == -1)
	{
		addRoom(pNursing, pTenant); 
		pRoom = pNursing->roomArr[pNursing->countRoom - 1];
	}
	else {
		pRoom = pNursing->roomArr[roomNumber];
	}

	if (!actualAddTenantToRoom(pRoom, pTenant))
	{
		return 0;
	}

	printf("The room number is: %d in floor: %d\n", pRoom->roomNumber, pRoom->floorNumber);
	return 1;	
}

int findRoomForTenant(const NursingHome* pNursing)
{
	for (int i = 0; i < pNursing->countRoom; i++)
	{
		if (pNursing->roomArr[i]->numOfTenantInRoom < MAX_TENANT_IN_ROOM)
		{
			return i;
		}
	}
	return -1;
}

int actualAddTenantToRoom(Room* pRoom, const Tenant* pTenant)
{
	pRoom->tenantInRoom = (Tenant*)realloc(pRoom->tenantInRoom, (pRoom->numOfTenantInRoom + 1) * sizeof(Tenant));
	if (!pRoom->tenantInRoom)
	{
		return 0;
	}

	pRoom->tenantInRoom[pRoom->numOfTenantInRoom] = *pTenant;
	pRoom->numOfTenantInRoom++;

	return 1;
}

Employee* findEmployeeByType(NursingHome* pNursing, eEmployeeType type) {
	for (int i = 0; i < pNursing->countEmployee; i++)
	{
		if (pNursing->employeeArr[i].employeeType == type) {
			return &pNursing->employeeArr[i];
		}
	}
	return NULL;
}


void printTenants(const NursingHome* pNursing)
{
	if (pNursing->countTenant == 1)
	{
		printf("There is 1 Tenant in Nursing Home.\n");
		printTenant(pNursing->tenantArr[0]);
	}
	else
	{
		printf("There are %d Tenants\n", pNursing->countTenant);
		for (int i = 0; i < pNursing->countTenant; i++)
		{
			printTenant(pNursing->tenantArr[i]);
			printf("\n");
		}
	}

}

void printEmployees(NursingHome* pNursing)
{
	printf("There are %d Employees\n", pNursing->countEmployee);
	for (int i = 0; i < pNursing->countEmployee; i++)
	{
		printEmployee(&pNursing->employeeArr[i]);
		printf("\n");
	}
}
void addGroupActivityFile(NursingHome* pNursing, GroupActivity* group)
{
	pNursing->groupActivityArr = (GroupActivity**)realloc(pNursing->groupActivityArr, (pNursing->countGroupActivity + 1) * sizeof(GroupActivity*));
	if (!pNursing->groupActivityArr)
	{
		freeGroupActivity(group);
		free(group);
		return 0;
	}
	pNursing->groupActivityArr[pNursing->countGroupActivity] = group;
	pNursing->countGroupActivity++;
}
void addGroupActivity(NursingHome* pNursing)
{
	if (pNursing->countEmployee <= 0)
	{
		printf("Error! There are no employees in nursing home.\n");
		return;
	}
	Employee* teacher = findEmployeeByType(pNursing, eTeacher);
	if (teacher == NULL) {
		printf("There are no available teachers.\n");
		return;
	}

	GroupActivity* pGroup = (GroupActivity*)calloc(1, sizeof(GroupActivity));
	if (!pGroup)
	{
		return;
	}

	pNursing->groupActivityArr = (GroupActivity**)realloc(pNursing->groupActivityArr, (pNursing->countGroupActivity + 1) * sizeof(GroupActivity*));
	if (!pNursing->groupActivityArr)
	{
		freeGroupActivity(pGroup);
		free(pGroup);
		return 0;
	}
	initGroupActivity(pGroup, teacher, pNursing->groupActivityArr, pNursing->countGroupActivity);

	pNursing->groupActivityArr[pNursing->countGroupActivity] = pGroup;
	pNursing->countGroupActivity++;
}

int addTenantToGroupActivity(NursingHome* pNursing)
{
	int resultN = 0;
	int resultI = 0;
	char* groupActivityname = (char*)malloc(sizeof(char));
	char* tenantID = (char*)malloc(sizeof(char));

	if (pNursing->countGroupActivity <= 0)
	{
		return 0;
	}

	resultN = checkGroupActivityName(pNursing, groupActivityname);
	resultI = checkTenantId(pNursing, tenantID);

	if (resultN == 1 && resultI == 1)
	{
		for (int i = 0; i < pNursing->countTenant; i++)
		{
			if (pNursing->tenantArr[i]->tenantID == tenantID)
			{
				pNursing->tenantArr[i]->groupActivity = groupActivityname;
			}
		}	
		printf("The tenant added to the Group Activity\n");
	}
	else
	{
		printf("The tenant was not found\n");
	}

	return 1;
}

int checkGroupActivityName(NursingHome* pNursing, char* groupActivityname)
{
	int checkGroupActivityName = 1;
	do {
		printGroupActivites(pNursing);
		printf("Choose Group Activity Name:\n");
		scanf("%s", groupActivityname);

		for (int i = 0; i < pNursing->countGroupActivity; i++)
		{
			int result = strcmp(groupActivityname, pNursing->groupActivityArr[i]->groupActivityName);
			if (result == 0)
			{
				if (pNursing->groupActivityArr[i]->tenantCount == MAX_TENANT_COUNT)
				{
					printf("can not add to this group activity!");
					checkGroupActivityName = 0;
				}				
			}
		}
	}while (checkGroupActivityName == 0);

	if (checkGroupActivityName = 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int checkTenantId(NursingHome* pNursing, char* tenantID)
{
	int checkTenantId = 1;
	do {
		printTenants(pNursing);
		printf("Choose Tenant ID that you want to add:\n");
		scanf("%s", tenantID); 

		for (int i = 0; i < pNursing->countTenant; i++)
		{
			int result = strcmp(pNursing->tenantArr[i]->tenantID, tenantID);
			if (result != 0)
			{
				checkTenantId = 0;
			}
			else
			{
				checkTenantId = 1;
			}
		}
	} while (checkTenantId == 0);

	if (checkTenantId = 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void printGroupActivites(NursingHome* pNursing)
{
	if (pNursing->countGroupActivity == 1)
	{
		printf("There is 1 Group Activity\n");
		printGroupActivity(pNursing->groupActivityArr[0]);
		printf("\n");
	}

	else
	{
		printf("There are %d Group Activites\n", pNursing->countGroupActivity);
		for (int i = 0; i < pNursing->countGroupActivity; i++)
		{
			printGroupActivity(pNursing->groupActivityArr[i]);
			printf("\n");
		}
	}

}
void addDishToDinningRoom(NursingHome* pNursing)
{
	Dish* newDish = (Dish*)calloc(1, sizeof(Dish));
	if (newDish == NULL) 
	{
		printf("Memory allocation failed.\n");
		return;
	}

	initDish(newDish);

	printf("Please enter number of ingredients: ");
	int numOfIngredients;
	scanf("%d", &numOfIngredients);

	newDish->dishIngredientsArr = (char**)malloc((numOfIngredients) * sizeof(char*));
	if (newDish->dishIngredientsArr == NULL) 
	{
		free(newDish->dishName);
		free(newDish);
		return;
	}

	printf("Please add your ingredients:\n");
	for (int i = 0; i < numOfIngredients; i++)
	{
		newDish->dishIngredientsArr[i] = (char*)malloc(100 * sizeof(char)); 
		if (newDish->dishIngredientsArr[i] == NULL) {
			printf("Memory allocation failed.\n");
			
			for (int j = 0; j < i; j++)
				free(newDish->dishIngredientsArr[j]);
			free(newDish->dishIngredientsArr);
			free(newDish->dishName);
			free(newDish);
			return;
		}
		printf("Ingredient %d: ", i + 1);
		scanf("%s", newDish->dishIngredientsArr[i]);
	}

	newDish->IngredientsCount = numOfIngredients;

	insertNewDishToList(&pNursing->diningRoom->listOfDishes, newDish);
	pNursing->diningRoom->countOfDishs++;
}

void printDiningRoomInfo(NursingHome* pNursing)
{
	printDishes(pNursing->diningRoom);
}

void freeNursingHome(NursingHome* pNursing)
{
	freeTenantArr(pNursing->tenantArr, pNursing->countTenant);
	free(pNursing->tenantArr);
	freeRoomArr(pNursing->roomArr, pNursing->countRoom);
	free(pNursing->roomArr);
	freeGroupActivityArr(pNursing->groupActivityArr, pNursing->countGroupActivity);
	free(pNursing->groupActivityArr);
	free(pNursing->employeeArr);
	freeDiningRoom(pNursing->diningRoom);
}

void freeTenantArr(Tenant** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Tenant*), freeTenant);
}

void freeRoomArr(Room** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Room*), freeRoom);
}

void freeGroupActivityArr(GroupActivity** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(GroupActivity*), freeGroupActivity);
}

