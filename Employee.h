#ifndef _EMPLOYEE_
#define	_EMPLOYEE_

#define SUCCESS 1
#define EMPLOYEE_NAME_LEN 10


typedef enum {
	eTherapist, eKitchen_worker, eTeacher, eNofEmployeeType
} eEmployeeType;

static const char* EmployeeTypeStr[eNofEmployeeType]
= { "Therapist", "Kitchen Worker", "Teacher" };

static const int EmployeeMaxCapacity[eNofEmployeeType]
= { 9, 9, 15 };

typedef struct
{
	char			employeeName[EMPLOYEE_NAME_LEN];
	int				employeeNumber;
	eEmployeeType	employeeType;
	int				tenantCount;

}Employee;


int				initEmployee(Employee* pEmp, Employee* employeeArr, int employeeCount);
eEmployeeType	getEmployeeType();
int				getEmployeeNumber(Employee* employeeArr, int employeeCount);
int				checkEmployeeNumber(Employee* employeeArr, int employeeCount, int randomnum);
void			printEmployee(Employee* pEmployee);
#endif
