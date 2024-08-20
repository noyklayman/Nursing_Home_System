#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "NursingHomeHelper.h"
#include "NursingHome.h"
#define EXIT -1
int menu();

int main()
{
	NursingHome pNursing;

	initNursingHome(&pNursing);
	initDinningRoom(&pNursing);
	int option;
	int stop = 0;
	printf("\n");
	printf("-------- NURSING HOME OF JERUSALEM --------\n");
	printf("-------------------------------------------\n");
	do
	{
		option = menu();
		switch (option)
		{
		case eReadBinary:
			readBinaryFile(NURSING_BIN_FILE_NAME, &pNursing);
			break;
		case eReadText:
			readTextFile(NURSING_FILE_NAME, &pNursing);
			break;
		case ePrintTenantAndEmployee:
			printTenants(&pNursing);
			printEmployees(&pNursing);
			break;
		case ePrintGroupActivites:
			printGroupActivites(&pNursing);
			break;
		case ePrintDinningRoom:
			printDiningRoomInfo(&pNursing);
			break;
		case eAddEmployee:
			if (!addEmployee(&pNursing))
				printf("Error adding Employee.\n");
			break;
		case eAddTenant:
			if (!addTenant(&pNursing))
				printf("Error adding Tenant.\n");
			break;		
		case eSortTenant:
			sortTenant(&pNursing);
			break;
		case eFindTenant:
			findTenant(&pNursing);
			break;
		case eAddGroupActivity:
			addGroupActivity(&pNursing);
			break;
		case eAddTenantToGroupActivity:
			if (!addTenantToGroupActivity(&pNursing)) 
				printf("Error adding Tenant to group activity\n");
			break;
		case eAddDishToDinningRoom:
			addDishToDinningRoom(&pNursing);
			printDiningRoomInfo(&pNursing);
			break;
		case EXIT:
			writeTextFile(NURSING_FILE_NAME, &pNursing);
			writeBinaryFile(NURSING_BIN_FILE_NAME, &pNursing);
			printf("Bye bye\n");
			stop = 1;
			break;
		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	//freeNursingHome(pNursing);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	printf("\nYour option: ");
	scanf("%d", &option);
	char tav;
	scanf("%c", &tav);
	return option;
}