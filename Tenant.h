#ifndef _TENANT_
#define	_TENANT_

#define ID_LENGTH 9

#include "Date.h"
#include "Employee.h"

typedef struct
{
	char*		tenantName; 
	int			tenantNameLen;
	char		tenantID[ID_LENGTH + 1];
	int			tenantAge;
	Date		entryDate;
	char*		groupActivity;

}Tenant;

void	initTenant(Tenant* pTenant, Tenant** tenantArr, int countTenant);
int		getAge();
void	tenantId(char* id, Tenant** tenantArr, int countTenant);
void	tenantIdToFind(char* id);
int		compareTenantByName(const void* tenant1, const void* tenant2);
int		compareTenantByAge(const void* tenant1, const void* tenant2);
int		compareTenantByEntryDate(const void* tenant1, const void* tenant2);
int		compareTenantByID(const void* tenant1, const void* tenant2);
int		compareInt(const void* c1, const void* c2);
void	printTenant(const Tenant* pTenant);
void	freeTenant(void* pTenant);


#endif



