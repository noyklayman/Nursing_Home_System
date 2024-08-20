#define _CRT_SECURE_NO_WARNINGS
#ifndef _DATE_
#define _DATE_

#define MIN_YEAR 2023

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void getDate(Date* pDate);
int	 checkDate(char* date, Date* pDate);
int	compareEntryDate(const void* d1, const void* d2);
void printDate(const Date* pDate);


#endif

