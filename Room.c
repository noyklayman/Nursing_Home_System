#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Room.h"
#include "NursingHome.h"

#define FLOOR_NUMBER(a,b) (a / b) + 1;
#define ROOM_NUMBER(x,y,z)(x % y) + (100 *z);


int initRoom(Room* pRoom, int roomCount)
{
	pRoom->floorNumber = FLOOR_NUMBER(roomCount , MAX_ROOMS_IN_FLOOR);
	pRoom->roomNumber = ROOM_NUMBER(roomCount, MAX_ROOMS_IN_FLOOR, pRoom->floorNumber);
	pRoom->numOfTenantInRoom = 0;
}

void freeRoom(void* pRoom)
{
	Room* temp = *(Room**)pRoom;
	free(temp);
}