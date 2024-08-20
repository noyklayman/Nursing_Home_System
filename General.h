#ifndef __GENERAL__
#define __GENERAL__


#define STR_LEN 255
#define HOUR_FORMAT_LENGTH 5

char*	getStrExactName(const char* msg);
char*	getDynStr(char* str);
char*	myGets(char* buffer, int size);
char*	getEmployeeName(const char* msg);
int		ContainsOnlyNumbersToID(const char* id);
int		randEmployeeNumber();
char*	getHour(const char* msg);
int		checkHour(const char* time);
void	generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));
int     countStrLen(char* str);



#endif
