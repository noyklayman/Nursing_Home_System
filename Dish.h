#ifndef _DISH_
#define _DISH_


typedef struct
{
	char*	dishName;
	char**	dishIngredientsArr;
	int		IngredientsCount;

}Dish;

void	initDish(Dish* newDish);
void	printDish(const void* val);
void	freeDishArr(Dish** arr, int size);
void	freeDishs(void* val);
void	freeDish(Dish* pDish);

#endif