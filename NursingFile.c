#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "NursingFile.h"
#include "NursingHome.h"

typedef unsigned char BYTE;
#define HOUR_FORMAT_LENGTH 5
#define STR_LEN 255

void readTextFile(char* fileName, NursingHome* pNursing)
{
    FILE* ptr;
    int numEmployees, numRooms, numTenants,numGroupActivity,countDish;
    ptr = fopen(fileName, "rb");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    fscanf(ptr, "%d", &numEmployees);
    for (int i = 0; i < numEmployees; i++)
    {
        Employee* tempEmployee = (Employee*)malloc(sizeof(Employee));
        int employeeType;
        fscanf(ptr, "%d", &tempEmployee->employeeNumber);
        fscanf(ptr, "%s", tempEmployee->employeeName);
        fscanf(ptr, "%d", &employeeType);
        tempEmployee->employeeType = (eEmployeeType)(employeeType);
        fscanf(ptr, "%d", &tempEmployee->tenantCount);
        addEmployeeFile(pNursing, tempEmployee);
    }
    fscanf(ptr, "%d", &numTenants);
    for (int i = 0; i < numTenants; i++)
    {
        Tenant* tempTenant = (Tenant*)malloc(sizeof(Tenant));
        fscanf(ptr, "%d", &tempTenant->tenantNameLen);
        tempTenant->tenantName = (char*)malloc(sizeof(tempTenant->tenantNameLen));
        fscanf(ptr, "%s", tempTenant->tenantName);
        fscanf(ptr, "%s", tempTenant->tenantID);
        fscanf(ptr, "%d", &tempTenant->tenantAge);
        fscanf(ptr, "%d", &tempTenant->entryDate.day);
        fscanf(ptr, "%d", &tempTenant->entryDate.month);
        fscanf(ptr, "%d", &tempTenant->entryDate.year);
        addTenantFile(pNursing, tempTenant);
    }
    fscanf(ptr, "%d", &numRooms);
    for (int i = 0; i < numRooms; i++)
    {
        Room* tempRoom = (Room*)malloc(sizeof(Room));
        char tempTenantId[ID_LENGTH + 1];
        fscanf(ptr, "%d", &tempRoom->roomNumber);
        fscanf(ptr, "%d", &tempRoom->floorNumber);
        fscanf(ptr, "%d", &tempRoom->numOfTenantInRoom);
        tempRoom->tenantInRoom = (Tenant*)malloc(sizeof(Tenant) * tempRoom->numOfTenantInRoom);
        for (int j = 0; j < tempRoom->numOfTenantInRoom; j++) 
        {
            fscanf(ptr, "%s", tempTenantId);
            for (int k = 0; k < pNursing->countTenant; k++)
            {
                if (strcmp(tempTenantId, pNursing->tenantArr[k]->tenantID) == 0)
                {
                    tempRoom->tenantInRoom[j] = *pNursing->tenantArr[k];
                }
            }
        }
        addRoomFile(pNursing, tempRoom);
    }
    fscanf(ptr, "%d", &numGroupActivity);
    for (int i = 0; i < numGroupActivity; i++)
    {
        GroupActivity* tempGroupActivity = (GroupActivity*)malloc(sizeof(GroupActivity));
        int instructorNumber,tempGroupActivityNameLen;
        fscanf(ptr, "%d", &tempGroupActivityNameLen);
        tempGroupActivity->groupActivityName = (char*)malloc(tempGroupActivityNameLen);
        tempGroupActivity->startingHour = (char*)malloc(HOUR_FORMAT_LENGTH+1);
        tempGroupActivity->endingHour = (char*)malloc(HOUR_FORMAT_LENGTH+1);
        fscanf(ptr, "%s", tempGroupActivity->groupActivityName);
        fscanf(ptr, "%s", tempGroupActivity->startingHour);
        fscanf(ptr, "%s", tempGroupActivity->endingHour);
        fscanf(ptr, "%d", &tempGroupActivity->studioNumber);
        fscanf(ptr, "%d", &tempGroupActivity->tenantCount);
        fscanf(ptr, "%d", &instructorNumber);
        tempGroupActivity->instructor = (Employee*)malloc(sizeof(Employee));
        for (int k = 0; k < pNursing->countEmployee; k++)
        {
            if (instructorNumber == pNursing->employeeArr[k].employeeNumber)
            {
               *tempGroupActivity->instructor = pNursing->employeeArr[k];
            }
        }
        addGroupActivityFile(pNursing, tempGroupActivity); 
    }

    int tempDishNameLen,diningEmployeeCount,diningTempEmployeeNumber,tempIngNameLen;
    char* tempDishName;
    fscanf(ptr, "%d", &countDish);
    for (int i = 0; i < countDish; i++)
    {
        Dish* tempDish = (Dish*)malloc(sizeof(Dish));
        tempDish->dishIngredientsArr = NULL;
        tempDish->IngredientsCount = 0; 
        fscanf(ptr, "%d", &tempDishNameLen);
        tempDish->dishName = (char*)malloc(tempDishNameLen + 1);
        fscanf(ptr, "%s", tempDish->dishName);
        fscanf(ptr, "%d", &tempDish->IngredientsCount);
        tempDish->dishIngredientsArr = (char**)malloc(sizeof(char*) * tempDish->IngredientsCount);
        for (size_t j = 0; j < tempDish->IngredientsCount; j++)
        {
            fscanf(ptr, "%d", &tempIngNameLen);
            tempDish->dishIngredientsArr[j] = (char*)malloc(tempIngNameLen + 1);
            fscanf(ptr, "%s", tempDish->dishIngredientsArr[j]);
        }
        insertNewDishToList(&pNursing->diningRoom->listOfDishes, tempDish);
        pNursing->diningRoom->countOfDishs++;
    }
    fscanf(ptr, "%d", &diningEmployeeCount);
    for (size_t i = 0; i < diningEmployeeCount; i++)
    {
        Employee* tempDiningEmployee = (Employee*)malloc(sizeof(Employee));
        fscanf(ptr, "%d", &diningTempEmployeeNumber);
        for (size_t j = 0; j < pNursing->countEmployee; j++)
        {
            if (pNursing->employeeArr[j].employeeNumber == diningTempEmployeeNumber) 
            {
                *tempDiningEmployee = pNursing->employeeArr[j];
                addEmployeeToDiningRoom(tempDiningEmployee, pNursing->diningRoom);
            }  
        }
     
    }

    fclose(ptr);
}
void writeTextFile(char* fileName, NursingHome* pNursing)
{
    FILE* ptr;
    ptr = fopen(fileName, "wb");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    fprintf(ptr, "%d\n", pNursing->countEmployee);
    for (int i = 0; i < pNursing->countEmployee; i++)
    {
        fprintf(ptr, "%d\n", pNursing->employeeArr[i].employeeNumber);
        fprintf(ptr, "%s\n", pNursing->employeeArr[i].employeeName);
        fprintf(ptr, "%d\n", pNursing->employeeArr[i].employeeType);
        fprintf(ptr, "%d\n", pNursing->employeeArr[i].tenantCount);
    }
    fprintf(ptr, "%d\n", pNursing->countTenant);
    for (int i = 0; i < pNursing->countTenant; i++)
    {
        fprintf(ptr, "%d\n", pNursing->tenantArr[i]->tenantNameLen);
        fprintf(ptr, "%s\n", pNursing->tenantArr[i]->tenantName);
        fprintf(ptr, "%s\n", pNursing->tenantArr[i]->tenantID);
        fprintf(ptr, "%d\n", pNursing->tenantArr[i]->tenantAge);
        fprintf(ptr, "%d\n", pNursing->tenantArr[i]->entryDate.day);
        fprintf(ptr, "%d\n", pNursing->tenantArr[i]->entryDate.month);
        fprintf(ptr, "%d\n", pNursing->tenantArr[i]->entryDate.year);
    }
    fprintf(ptr, "%d\n", pNursing->countRoom);
    for (int i = 0; i < pNursing->countRoom; i++)
    {
        fprintf(ptr, "%d\n", pNursing->roomArr[i]->roomNumber);
        fprintf(ptr, "%d\n", pNursing->roomArr[i]->floorNumber);
        fprintf(ptr, "%d\n", pNursing->roomArr[i]->numOfTenantInRoom);
        for (int j = 0; j < pNursing->roomArr[i]->numOfTenantInRoom; j++) 
        {
            fprintf(ptr, "%s\n", pNursing->roomArr[i]->tenantInRoom[0].tenantID);
        }
    }
    fprintf(ptr, "%d\n", pNursing->countGroupActivity);
    for (int i = 0; i < pNursing->countGroupActivity; i++)
    {
        fprintf(ptr, "%d\n", countLength(pNursing->groupActivityArr[i]->groupActivityName));
        fprintf(ptr, "%s\n", pNursing->groupActivityArr[i]->groupActivityName);
        fprintf(ptr, "%s\n", pNursing->groupActivityArr[i]->startingHour);
        fprintf(ptr, "%s\n", pNursing->groupActivityArr[i]->endingHour);
        fprintf(ptr, "%d\n", pNursing->groupActivityArr[i]->studioNumber);
        fprintf(ptr, "%d\n", pNursing->groupActivityArr[i]->tenantCount);
        fprintf(ptr, "%d\n", pNursing->groupActivityArr[i]->instructor->employeeNumber);
 
    }
    fprintf(ptr, "%d\n", pNursing->diningRoom->countOfDishs);
    NODE* tempNode = &pNursing->diningRoom->listOfDishes.head;
    for (int i = 0; i < pNursing->diningRoom->countOfDishs; i++)
    {
        tempNode = tempNode->next;
        Dish* tempDish = (Dish*)tempNode->key;
     
        fprintf(ptr, "%d\n", countLength(tempDish->dishName));
        fprintf(ptr, "%s\n", tempDish->dishName);
        fprintf(ptr, "%d\n", tempDish->IngredientsCount);
        for (size_t j = 0; j < tempDish->IngredientsCount; j++)
        {
            fprintf(ptr, "%d\n", countLength(tempDish->dishIngredientsArr[j]));
            fprintf(ptr, "%s\n", tempDish->dishIngredientsArr[j]);
        }

    }
    fprintf(ptr, "%d\n", pNursing->diningRoom->employeeCount);
    for (size_t i = 0; i < pNursing->diningRoom->employeeCount; i++)
    {
        fprintf(ptr, "%d\n", pNursing->diningRoom->employeeArr[i].employeeNumber);
    }

    fclose(ptr);
}

void readBinaryFile(char* fileName, NursingHome* pNursing)
{
    FILE* infile;
    int countEmployees, countRooms, countTenants,countGroupActivity,countDish;
    infile = fopen(fileName, "rb+");
    if (infile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    fread(&countEmployees, sizeof(int), 1, infile);
    for (size_t i = 0; i < countEmployees; i++)
    {
        Employee* tempEmployee = (Employee*)malloc(sizeof(Employee));
        BYTE data[11] = { 0 };
        fread(&data, sizeof(BYTE), 11, infile);
        for (int i = 0; i < EMPLOYEE_NAME_LEN-1; ++i) {
            tempEmployee->employeeName[i] = (char)data[i];
        }
        tempEmployee->employeeName[EMPLOYEE_NAME_LEN - 1] = '\0';
        tempEmployee->employeeNumber = data[9] >> 3;
        int employeeType = (data[9] & 6) >> 1;
        tempEmployee->employeeType = (eEmployeeType)employeeType;
        tempEmployee->tenantCount = ((data[9] & 1) << 3) | (data[10] >> 5);
        addEmployeeFile(pNursing, tempEmployee);
    }
    fread(&countTenants, sizeof(int), 1, infile);
    for (size_t i = 0; i < countTenants; i++)
    {
        Tenant* tempTenant = (Tenant*)malloc(sizeof(Tenant));
        fread(&tempTenant->tenantNameLen, sizeof(int), 1, infile);
        tempTenant->tenantName = (char*)malloc(tempTenant->tenantNameLen + 1);
        fread(tempTenant->tenantName, sizeof(char), tempTenant->tenantNameLen, infile);
        tempTenant->tenantName[tempTenant->tenantNameLen] = '\0';
        fread(&tempTenant->tenantID, sizeof(char), ID_LENGTH, infile);
        tempTenant->tenantID[ID_LENGTH] = '\0';
        fread(&tempTenant->tenantAge, sizeof(int), 1, infile);
        fread(&tempTenant->entryDate.day, sizeof(int), 1, infile);
        fread(&tempTenant->entryDate.month, sizeof(int), 1, infile);
        fread(&tempTenant->entryDate.year, sizeof(int), 1, infile);
        addTenantFile(pNursing, tempTenant);
    }
    fread(&countRooms, sizeof(int), 1, infile);
    for (size_t i = 0; i < countRooms; i++)
    {
        char* tempTenantId = (char*)malloc(ID_LENGTH + 1);
        Room* tempRoom = (Room*)malloc(sizeof(Room));
        fread(&tempRoom->roomNumber, sizeof(int), 1, infile);
        fread(&tempRoom->floorNumber, sizeof(int), 1, infile);
        fread(&tempRoom->numOfTenantInRoom, sizeof(int), 1, infile);
        tempRoom->tenantInRoom = (Tenant*)malloc(sizeof(Tenant) * tempRoom->numOfTenantInRoom);
        for (int j = 0; j < tempRoom->numOfTenantInRoom; j++) 
        {
            fread(tempTenantId, sizeof(char), ID_LENGTH, infile);
            tempTenantId[ID_LENGTH] = '\0';
            for (int k = 0; k < pNursing->countTenant; k++)
            {
                if (strcmp(tempTenantId, pNursing->tenantArr[k]->tenantID) == 0)
                {
                    tempRoom->tenantInRoom[j] = *pNursing->tenantArr[k];
                }
            }
        }
        addRoomFile(pNursing, tempRoom);
    }
    fread(&countGroupActivity, sizeof(int), 1, infile);
    for (int i = 0; i < countGroupActivity; i++)
    {
        GroupActivity* tempGroupActivity = (GroupActivity*)malloc(sizeof(GroupActivity));
        int instructorNumber, tempGroupActivityNameLen;
        fread(&tempGroupActivityNameLen, sizeof(int), 1, infile);
        tempGroupActivity->groupActivityName = (char*)malloc(tempGroupActivityNameLen+1);
        tempGroupActivity->startingHour = (char*)malloc(HOUR_FORMAT_LENGTH + 1);
        tempGroupActivity->endingHour = (char*)malloc(HOUR_FORMAT_LENGTH + 1);
        fread(tempGroupActivity->groupActivityName, sizeof(char), tempGroupActivityNameLen, infile);
        fread(tempGroupActivity->startingHour, sizeof(char), HOUR_FORMAT_LENGTH, infile);
        fread(tempGroupActivity->endingHour, sizeof(char), HOUR_FORMAT_LENGTH, infile);
        fread(&tempGroupActivity->studioNumber, sizeof(int), 1, infile);
        fread(&tempGroupActivity->tenantCount, sizeof(int), 1, infile);
        fread(&instructorNumber, sizeof(int), 1, infile);
        tempGroupActivity->groupActivityName[tempGroupActivityNameLen] = '\0';
        tempGroupActivity->startingHour[HOUR_FORMAT_LENGTH] = '\0';
        tempGroupActivity->endingHour[HOUR_FORMAT_LENGTH] = '\0';
        tempGroupActivity->instructor = (Employee*)malloc(sizeof(Employee));
        for (int k = 0; k < pNursing->countEmployee; k++)
        {
            if (instructorNumber == pNursing->employeeArr[k].employeeNumber) 
            {
                *tempGroupActivity->instructor = pNursing->employeeArr[k];
            }
        }
        addGroupActivityFile(pNursing, tempGroupActivity);
    }
    int tempDishNameLen, diningEmployeeCount, diningTempEmployeeNumber, tempIngNameLen;
    char* tempDishName;
    fread(&countDish, sizeof(int), 1, infile);
    for (int i = 0; i < countDish; i++)
    {
        Dish* tempDish = (Dish*)malloc(sizeof(Dish));
        tempDish->dishIngredientsArr = NULL;
        tempDish->IngredientsCount = 0;
        fread(&tempDishNameLen, sizeof(int), 1, infile);
        tempDish->dishName = (char*)malloc(tempDishNameLen + 1);
        fread(tempDish->dishName, sizeof(char), tempDishNameLen, infile);
        tempDish->dishName[tempDishNameLen] = '\0';
        fread(&tempDish->IngredientsCount, sizeof(int), 1, infile);
        tempDish->dishIngredientsArr = (char**)malloc(sizeof(char*) * tempDish->IngredientsCount);
        for (size_t j = 0; j < tempDish->IngredientsCount; j++)
        {
            fread(&tempIngNameLen, sizeof(int), 1, infile);
            tempDish->dishIngredientsArr[j] = (char*)malloc(tempIngNameLen + 1);
            fread(tempDish->dishIngredientsArr[j], sizeof(char), tempIngNameLen, infile);
            tempDish->dishIngredientsArr[j][tempIngNameLen] = '\0';
        }
        insertNewDishToList(&pNursing->diningRoom->listOfDishes, tempDish);
        pNursing->diningRoom->countOfDishs++;
    }
    fread(&diningEmployeeCount, sizeof(int), 1, infile);
    for (size_t i = 0; i < diningEmployeeCount; i++)
    {
        Employee* tempDiningEmployee = (Employee*)malloc(sizeof(Employee));
        fread(&diningTempEmployeeNumber, sizeof(int), 1, infile);
        for (size_t j = 0; j < pNursing->countEmployee; j++)
        {
            if (pNursing->employeeArr[j].employeeNumber == diningTempEmployeeNumber)
            {
                *tempDiningEmployee = pNursing->employeeArr[j];
                addEmployeeToDiningRoom(tempDiningEmployee, pNursing->diningRoom);
            }
        }
    }
    fclose(infile);
}
void writeBinaryFile(char* fileName, NursingHome* pNursing)
{
    FILE* outfile;
    outfile = fopen(fileName, "wb+");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    fwrite(&pNursing->countEmployee, sizeof(int), 1, outfile);
    for (size_t i = 0; i < pNursing->countEmployee; i++)
    {
        BYTE data[11] = { 0 };
        for (size_t j = 0; j < EMPLOYEE_NAME_LEN-1; j++)
        {
            data[j] = pNursing->employeeArr[i].employeeName[j];
        }
        data[9] = pNursing->employeeArr[i].employeeNumber << 3;
        data[9] = data[9] | pNursing->employeeArr[i].employeeType << 1 | (pNursing->employeeArr[i].tenantCount >> 3);
        data[10] = pNursing->employeeArr[i].tenantCount << 5;
        fwrite(&data, sizeof(BYTE), 11, outfile);
    }
    fwrite(&pNursing->countTenant, sizeof(int), 1, outfile);
    for (size_t i = 0; i < pNursing->countTenant; i++)
    {
        fwrite(&pNursing->tenantArr[i]->tenantNameLen, sizeof(int), 1, outfile);
        fwrite(pNursing->tenantArr[i]->tenantName, sizeof(char), pNursing->tenantArr[i]->tenantNameLen, outfile);
        fwrite(&pNursing->tenantArr[i]->tenantID, sizeof(char), ID_LENGTH, outfile);
        fwrite(&pNursing->tenantArr[i]->tenantAge, sizeof(int), 1, outfile);
        fwrite(&pNursing->tenantArr[i]->entryDate.day, sizeof(int), 1, outfile);
        fwrite(&pNursing->tenantArr[i]->entryDate.month, sizeof(int), 1, outfile);
        fwrite(&pNursing->tenantArr[i]->entryDate.year, sizeof(int), 1, outfile);
    }

    fwrite(&pNursing->countRoom, sizeof(int), 1, outfile);
    for (size_t i = 0; i < pNursing->countRoom; i++)
    {
        fwrite(&pNursing->roomArr[i]->roomNumber, sizeof(int), 1, outfile);
        fwrite(&pNursing->roomArr[i]->floorNumber, sizeof(int), 1, outfile);
        fwrite(&pNursing->roomArr[i]->numOfTenantInRoom, sizeof(int), 1, outfile);
        for (int j = 0; j < pNursing->roomArr[i]->numOfTenantInRoom; j++) 
        {
            fwrite(&pNursing->roomArr[i]->tenantInRoom[0].tenantID, sizeof(char), ID_LENGTH, outfile);
        }
    }
    fwrite(&pNursing->countGroupActivity, sizeof(int), 1, outfile);
    for (int i = 0; i < pNursing->countGroupActivity; i++)
    {   
        int len = countLength(pNursing->groupActivityArr[i]->groupActivityName);
        fwrite(&len, sizeof(int), 1, outfile);
        fwrite(pNursing->groupActivityArr[i]->groupActivityName, sizeof(char), len, outfile);
        fwrite(pNursing->groupActivityArr[i]->startingHour, sizeof(char), HOUR_FORMAT_LENGTH, outfile);
        fwrite(pNursing->groupActivityArr[i]->endingHour, sizeof(char), HOUR_FORMAT_LENGTH, outfile);
        fwrite(&pNursing->groupActivityArr[i]->studioNumber, sizeof(int), 1, outfile);
        fwrite(&pNursing->groupActivityArr[i]->tenantCount, sizeof(int), 1, outfile);
        fwrite(&pNursing->groupActivityArr[i]->instructor->employeeNumber, sizeof(int), 1, outfile);
    }
    fwrite(&pNursing->diningRoom->countOfDishs, sizeof(int), 1, outfile);
    NODE* tempNode = &pNursing->diningRoom->listOfDishes.head;
    for (int i = 0; i < pNursing->diningRoom->countOfDishs; i++)
    {
        tempNode = tempNode->next;
        Dish* tempDish = (Dish*)tempNode->key;
        int tempDishNameLen = countLength(tempDish->dishName);
        fwrite(&tempDishNameLen, sizeof(int), 1, outfile);
        fwrite(tempDish->dishName, sizeof(char), tempDishNameLen, outfile);
        fwrite(&tempDish->IngredientsCount, sizeof(int), 1, outfile);
        for (size_t j = 0; j < tempDish->IngredientsCount; j++)
        {
            int tempIngNameLen = countLength(tempDish->dishIngredientsArr[j]);
            fwrite(&tempIngNameLen, sizeof(int), 1, outfile);
            fwrite(tempDish->dishIngredientsArr[j], sizeof(char), tempIngNameLen, outfile);
        }
    }
    fwrite(&pNursing->diningRoom->employeeCount, sizeof(int), 1, outfile);
    for (size_t i = 0; i < pNursing->diningRoom->employeeCount; i++)
    {
        fwrite(&pNursing->diningRoom->employeeArr[i].employeeNumber, sizeof(int), 1, outfile);
    }

    fclose(outfile);
}

int	 readIntFromFile(int* pVal, FILE* fp)
{
    if (fread(pVal, sizeof(int), 1, fp) != 1)
    {
        return 0;
    }
    return 1;

}
