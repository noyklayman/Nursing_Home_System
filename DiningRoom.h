#ifndef _DINING_ROOM_
#define _DINING_ROOM_

#include "Employee.h"
#include "list.h"
#include "Dish.h"


typedef struct
{
	Employee*	employeeArr; 
	int			employeeCount;
	LIST		listOfDishes; 
	int			countOfDishs;

}DiningRoom;

int		insertNewDishToList(LIST* pDishList, Dish* pDish);
void	printDishes(const DiningRoom* diningRoom);
void	freeDiningRoom(DiningRoom* pDining);

#endif
