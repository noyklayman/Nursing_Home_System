#pragma once

#include "NursingHome.h"
#include "Employee.h"

#define NURSING_FILE_NAME "nursing_home.txt"
#define NURSING_BIN_FILE_NAME "nursing_home.bin"
#define EMPLOYEE_FILE_NAME "employee.bin"

typedef enum
{
	eReadBinary, eReadText, ePrintTenantAndEmployee, ePrintGroupActivites, ePrintDinningRoom, eAddEmployee, eAddTenant, eSortTenant, eFindTenant, eAddGroupActivity,
	eAddTenantToGroupActivity, eAddDishToDinningRoom,eNofOptions

} eMenuOptions;

const char* str[eNofOptions] = { "Read Binary", "Read Text", "Print Tenats And Employees", "Print group activites", "Print Dinning Room", "Add Employee", "Add Tenant", "Sort Tenant",
								"Find Tenant","Add group activity","Add tenant to group activity","Add dish to dinnig room", };

int menu();
