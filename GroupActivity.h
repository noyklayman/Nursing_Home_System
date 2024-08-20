#ifndef _GROUP_ACTIVITY_
#define _GROUP_ACTIVITY_

#include "Employee.h"

#define MAX_TENANT_COUNT 16

typedef struct
{
	char*		groupActivityName;
	Employee*	instructor;
	char*		startingHour;
	char*		endingHour;
	int			studioNumber;
	int			tenantCount;

}GroupActivity;

void	initGroupActivity(GroupActivity* pGroup, Employee* instructor, GroupActivity** groupActivityArr, int countGroupActivity);
int		scanStudioNumber();
int		validateGroupActivityHours(const char* startingHour, const char* endingHour);
void	printGroupActivity(const GroupActivity* pGroupA);
int		compareGroupActivityByName(const void* groupActivity1, const void* groupActivity2);
int		check(GroupActivity** groupActivityArr, int countGroupActivity, int studioNumber, char* startingHour, char* endingHour);
int		overlapHours(const char* startingHour1, const char* endingHour1, const char* startingHour2, const char* endingHour2);
void	freeGroupActivity(void* pGroup);

#endif

