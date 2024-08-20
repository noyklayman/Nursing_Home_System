#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "DiningRoom.h"


int	insertNewDishToList(LIST* pDishList, Dish* pDish)
{
	NODE* pN = pDishList->head.next; 
	NODE* pPrevNode = &pDishList->head;
	Dish* pTempDish;
	int compRes;
	while (pN != NULL)
	{
		pTempDish = (Dish*)pN->key;
		compRes = strcmp(pTempDish->dishName, pDish->dishName);
		if (compRes == 0) 
		{
			printf("Error! - Not a new dish - \n");
			return 0;
		}

		pPrevNode = pN;
		pN = pN->next;
	}
	
	if (!L_insert(pPrevNode, pDish));
	return 0;
	return 1;
}

void printDishes(const DiningRoom* diningRoom)
{
	printf("The dishes are:");
	L_print(&diningRoom->listOfDishes, printDish);
}

void	freeDiningRoom(DiningRoom* pDining)
{
	L_free(&pDining->listOfDishes, freeDish);
}
