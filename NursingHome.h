#ifndef _NURSING_HOME_
#define	_NURSING_HOME_

#include "Room.h"
#include "Employee.h"
#include "GroupActivity.h"
#include "DiningRoom.h"

#define MAX_EMPLOYEE_IN_NURSING_HOME 32

typedef enum { eName, eID, eAge, eEntryDate, eNofSortOpt } eSortOption;

static const char* sortOptStr[eNofSortOpt] = { "Name", "ID", "Age", "EntryDate" };


typedef struct
{
	Tenant**		tenantArr; 
	int				countTenant;
	Room**			roomArr;
	int				countRoom;
	Employee*		employeeArr;
	int				countEmployee;
	GroupActivity** groupActivityArr;
	int				countGroupActivity;
	DiningRoom*		diningRoom; 
	eSortOption		tenantSortOpt;

}NursingHome;

void initNursingHome(NursingHome* pNursing);
int addTenant(NursingHome* pNursing);
int addTenantFile(NursingHome* pNursing, Tenant* tenant);
int increaseEmployeeCapacity(NursingHome* pNursing, int indexOfAvilableTherapists, int indexOfAvilableCooks);
int countLength(char* str);
int getAvailablePersonalOfType(NursingHome* pNursing, eEmployeeType type);
int addEmployee(NursingHome* pNursing);
int addEmployeeFile(NursingHome* pNursing, Employee* employee);
int checkKitchenWorker(Employee* emp, DiningRoom* diningRoom);
int addEmployeeToDiningRoom(Employee* emp, DiningRoom* diningRoom);
int initDinningRoom(NursingHome* pNursing);
int addRoom(NursingHome* pNursing, Tenant* pTenant);
int addRoomFile(NursingHome* pNursing, Room* room);
int addTenantToRoom(NursingHome* pNursing, const Tenant* pTenant);
int findRoomForTenant(const NursingHome* pNursing);
int actualAddTenantToRoom(Room* pRoom, const Tenant* pTenant);
Employee* findEmployeeByType(NursingHome* pNursing, eEmployeeType type);
void printTenants(const NursingHome* pNursing);
void printEmployees(NursingHome* pNursing);
void addGroupActivity(NursingHome* pNursing);
int addTenantToGroupActivity(NursingHome* pNursing);
int checkGroupActivityName(NursingHome* pNursing, char* groupActivityname);
int checkTenantId(NursingHome* pNursing, char* tenantID);
void printGroupActivites(NursingHome* pNursing);
void addDishToDinningRoom(NursingHome* pNursing);
void printDiningRoomInfo(NursingHome* pNursing);
void addGroupActivityFile(NursingHome* pNursing, GroupActivity* group);
void freeTenantArr(Tenant** arr, int size);
void freeRoomArr(Room** arr, int size);
void freeGroupActivityArr(GroupActivity** arr, int size);

void writeBinaryFile(char* fileName, NursingHome* pNursing);
void readBinaryFile(char* fileName, NursingHome* pNursing);
void readTextFile(char* fileName, NursingHome* pNursing);
void writeTextFile(char* fileName, NursingHome* pNursing);


#endif

