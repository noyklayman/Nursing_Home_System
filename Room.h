#ifndef _ROOM_
#define	_ROOM_

#define MIN_FLOOR 1
#define MAX_FLOOR 4
#define MIN_ROOMS_IN_FLOOR 1
#define MAX_ROOMS_IN_FLOOR 8
#define MAX_TENANT_IN_ROOM 4

#include "Tenant.h"

typedef struct
{
	int		roomNumber;
	int		floorNumber;
	int		numOfTenantInRoom;
	Tenant* tenantInRoom; 
}Room;

int		initRoom(Room* pRoom, int roomCount);
void	freeRoom(void* pRoom);
#endif
