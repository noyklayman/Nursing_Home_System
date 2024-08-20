#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Employee.h"
#include "General.h"


int initEmployee(Employee* pEmp, Employee* employeeArr, int employeeCount)
{
	strcpy_s(pEmp->employeeName, EMPLOYEE_NAME_LEN, getEmployeeName("Enter Employee Name:"));
	pEmp->employeeNumber = getEmployeeNumber(employeeArr, employeeCount);
	pEmp->employeeType = getEmployeeType();
	pEmp->tenantCount = 0;
	return SUCCESS;
}

eEmployeeType getEmployeeType()
{
	int chose;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofEmployeeType; i++)
		{
			printf("%d for %s\n", i, EmployeeTypeStr[i]);
		}
		scanf_s("%d", &chose);
	} while (chose < 0 || chose >= eNofEmployeeType);
	getchar();
	return (eEmployeeType)chose;
}

int getEmployeeNumber(Employee* employeeArr, int employeeCount)
{
	int randomnum;
	int check = 0;

	do {
		randomnum = randEmployeeNumber();
		check = checkEmployeeNumber(employeeArr, employeeCount, randomnum);
	} while (!check);
	printf("The employee number is: %d", randomnum);
	return randomnum;
}

int	checkEmployeeNumber(Employee* employeeArr, int employeeCount, int randomnum)
{
	for (int i = 0; i < employeeCount; i++)
	{
		if (employeeArr[i].employeeNumber == randomnum)
		{
			return 0;
		}
	}
	return 1;
}

void printEmployee(Employee* pEmployee)
{
	printf("Employee Name: %s,", pEmployee->employeeName);
	printf(" Number: %d, Type: %s\n", pEmployee->employeeNumber, EmployeeTypeStr[pEmployee->employeeType]);
}
