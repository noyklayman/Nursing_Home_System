#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Dish.h"
#include "General.h"

void initDish(Dish* newDish)
{
	newDish->dishName = getStrExactName("Enter dish Name:");
	newDish->dishIngredientsArr = NULL;
	newDish->IngredientsCount = 0;
}

void printDish(const void* val)
{
	const Dish* pDish = (const Dish*)val;
	printf("\nDish name:%-20s\t", pDish->dishName);
	printf("Ingredients: ");
	for (int i = 0; i < pDish->IngredientsCount; i++)
	{
		printf("%s ", pDish->dishIngredientsArr[i]);
	}
}

void freeDishArr(Dish** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Dish*), freeDishs);
}

void freeDishs(void* val)
{
	freeDish((Dish*)val);
}

void freeDish(Dish* pDish)
{
	free(pDish->dishName);
	freeDishArr(pDish->dishIngredientsArr, pDish->IngredientsCount);
	free(pDish->dishIngredientsArr);
	free(pDish);
}
