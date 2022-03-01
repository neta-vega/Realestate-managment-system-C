#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "commands.h"
#include "structs1.h"
#include "libraries1.h"
#include "history.h"
#include "files.h"
#include "convert.h"
#include "general.h"
#include "getCommands.h"
#include "list.h"
#include "memory.h"
#include "replace.h"



void addApt(APARTMENT* apt, short int code) //Adds apartments to the APARTMENT array
{
	int size = 0;
	char* checkstr = NULL;
	checkstr = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(checkstr);
	//getAdress(checkstr, &size);
	getAdress(&checkstr, &size);
	apt->adress = (char*)malloc((size + 1) * sizeof(char));
	checkMemoryAllocationchar(apt->adress);
	strcpy(apt->adress, checkstr);
	scanf("%d", &(apt->price));
	scanf("%hd", &(apt->NumOfRooms));
	scanf("%hd%hd%hd", &(apt->entryD), &(apt->entryM), &(apt->entryY));
	apt->datatbase_entry_date = time(NULL);
	apt->code = code;
	free(checkstr);

}
void buyApt(APARTMENT** apt, int* size, char** allCommand)
{
	int i, j = 0;
	short int code_to_delete;
	char stam_code[100];
	char* stam = "buy-apt ";
	APARTMENT* temp = (APARTMENT*)realloc(*apt, *size * sizeof(APARTMENT));
	checkMemoryAllocationArr(temp);
	increaseStrSize(allCommand, strlen(stam) + 1);
	(*allCommand)[0] = '\0';
	scanf("%hi", &code_to_delete);
	strcat(*allCommand, stam);
	increaseStrSize(allCommand, strlen(_itoa(code_to_delete, stam_code, 10)));
	strcat(*allCommand, _itoa(code_to_delete, stam_code, 10));
	for (i = 0; i < *size; i++) //Searches for the code in the apartment database and puts in j the index of the apartment corresponding to the code
	{

		if (temp[i].code == code_to_delete)
		{
			j = i;
			break;
		}
	}
	for (j; j < (*size); j++)  //delete the apartment from the database and reduces it
	{
		memcpy(&temp[j], &temp[j + 1], sizeof(APARTMENT));
	}
	(*size)--;
	*apt = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * (*size)); //adjusting the size of the new database
	checkMemoryAllocationArr(*apt);
}

void deleteApt(APARTMENT* arr, int* arrSize, char* allCommand)
{
	int numDays = 0;
	char* enter = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(enter);
	char stam_num_days[100];
	char* stam = "delete-apt Enter ";
	allCommand[0] = '\0';
	float NumOfSeconds;

	getCommand(&enter);
	increaseStrSize(&enter, strlen(enter));
	scanf("%d", &numDays);

	NumOfSeconds = (float)numDays * SECONDS_PER_DAY;


	increaseStrSize(&allCommand, strlen(stam));
	strcat(allCommand, stam);

	increaseStrSize(&allCommand, strlen(_itoa(numDays, stam_num_days, 10)));
	strcat(allCommand, _itoa(numDays, stam_num_days, 10));
	for (int i = 0; i < *arrSize; i++)
	{
		if (arr[i].datatbase_entry_date >= time(NULL) - NumOfSeconds)//removing all the apt that feet to the request time range 
		{
			*arrSize -= i;
			break;
		}
	}
	arr = (APARTMENT*)realloc(arr, *arrSize * sizeof(APARTMENT));
	checkMemoryAllocationArr(arr);
}
void findApt(APARTMENT* apt, int size, char** allCommand)
{

	char* spCommand = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(spCommand);
	getSPCommand(&spCommand);
	int* arr;
	int index = 0, countCommand = 0, i, j, k = 0, countApear = 1; //its int* becuase its storage the codes num
	int* finalArrCodes; // after compered requriments, puts in finalArr the right apt. 
	APARTMENT* finalFind;
	APARTMENT* res;

	char* stam = "find-apt  ";
	(*allCommand)[0] = '\0';

	increaseStrSize(allCommand, strlen(stam));
	strcat(*allCommand, stam);

	increaseStrSize(allCommand, strlen(spCommand));
	strcat(*allCommand, spCommand);

	increaseStrSize(allCommand, sizeof(char));
	strcat(*allCommand, " ");


	arr = (int*)malloc(size * sizeof(int)); // all the apt that answer for the requriments 
	finalArrCodes = (int*)malloc(size * sizeof(int));


	while ((strcmp(spCommand + 1, "sr") != 0) && (strcmp(spCommand + 1, "s") != 0))
	{

		if (strcmp(spCommand + 4, "NumRooms") == 0)
		{
			FindNumRooms(apt, size, &arr, &index, spCommand, allCommand);

		}
		if (strcmp(spCommand + 4, "Price") == 0)
		{
			FindPrice(apt, size, &arr, &index, spCommand, allCommand);

		}
		if (strcmp(spCommand + 1, "Date") == 0) {
			FindDate(apt, size, &arr, &index, allCommand);
		}
		memset(spCommand, 0, strlen(spCommand));
		getSPCommand(&spCommand);

		increaseStrSize(allCommand, strlen(spCommand));
		strcat(*allCommand, spCommand);

		increaseStrSize(allCommand, sizeof(char));
		strcat(*allCommand, " ");
		countCommand++;
	}

	if (countCommand == 1) // when we got only one command 
	{
		if (index == 0)
			printf("Not Found!\n");
		else
		{
			finalFind = (APARTMENT*)malloc(sizeof(APARTMENT) * index); //Tamar 13.1
			checkMemoryAllocationArr(finalFind);//Tamar 13.1
			convert_Code_Arr_To_Apt_Arr(arr, apt, index, size,finalFind); //index+1 is the apt size 
			res = (APARTMENT*)calloc(size,sizeof(APARTMENT));//Tamar change from size* to index*
			mergeSort(finalFind, index, spCommand, res);
			printArr(finalFind, index);
		}
	}
	else //find which apt answer all the demands 
	{
		for (i = 0; i < index; i++)
		{
			countApear = 1;
			for (j = i + 1; j < index; j++)
			{
				if (arr[i] == arr[j])
					countApear++;
				if (countApear == countCommand)
				{
					finalArrCodes[k] = arr[i];
					k++;
					countApear = 1;

				}

			}
		}
		if (k == 0)
		{
			printf("Not Found!\n");
		}
		else
		{
			//finalFind = convert_Code_Arr_To_Apt_Arr(finalArrCodes, apt, k, size,finalFind);
			finalFind = (APARTMENT*)malloc(sizeof(APARTMENT) * index); //Tamar 13.1
			checkMemoryAllocationArr(finalFind);//Tamar 13.1
			convert_Code_Arr_To_Apt_Arr(arr, apt, index, size, finalFind);
			res = (APARTMENT*)malloc(size* sizeof(APARTMENT));//Tamar 13.01
			mergeSort(finalFind, k, spCommand, res);//Tamar 13.01 send res insted of finalFind
			printArr(finalFind, k);//Tamar 13.01 send res insted of finalFind
		}
	}
	res = NULL; //Tamar 13.01
	free(res); //Tamar 13.01
	spCommand = NULL;//Tamar 13.01
	free(spCommand);//Tamar 13.01

}

void FindNumRooms(APARTMENT* apt, int size, int** arr, int* index, char* ch, char** allCommand)
{
	int i;
	int numRooms;
	char stam_num_rooms[100];
	char* temp = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(temp);
	int* tmpArr = NULL;
	increaseStrSize(&temp, strlen(ch));
	memcpy(temp, ch, strlen(ch));
	scanf("%d", &numRooms);

	increaseStrSize(allCommand, strlen(_itoa(numRooms, stam_num_rooms, 10)));
	strcat(*allCommand, _itoa(numRooms, stam_num_rooms, 10));

	increaseStrSize(allCommand, sizeof(char));
	strcat(*allCommand, " ");

	if (strcmp(temp + 1, "MaxNumRooms") == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (apt[i].NumOfRooms <= numRooms)
			{
				(*arr)[*index] = apt[i].code;
				(*index)++;
				if (*index > size)
				{
					tmpArr = (int*)realloc(*arr, (*index + 1) * sizeof(int));
					*arr = (int*)realloc(tmpArr, (*index + 1) * sizeof(int));;

				}

			}
		}
	}
	if (strcmp(temp + 1, "MinNumRooms") == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (apt[i].NumOfRooms >= numRooms)
			{
				(*arr)[*index] = apt[i].code;
				(*index)++;
				if (*index > size)
				{
					tmpArr = (int*)realloc(*arr, (*index + 1) * sizeof(int));
					*arr = (int*)realloc(tmpArr, (*index + 1) * sizeof(int));;
				}
			}
		}
	}
	temp = NULL;// Tamar 13.1
	free(temp);// Tamar 13.1
	tmpArr = NULL;// Tamar 13.1
	free(tmpArr);//Tamar 13.1
}

void FindPrice(APARTMENT* apt, int size, int** arr, int* index, char* ch, char** allCommand)
{
	int i;
	int price;
	char stam_price[100];
	char* temp = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(temp);
	int* tmpArr = NULL;
	increaseStrSize(&temp, strlen(ch));
	temp = ch;
	scanf("%d", &price);

	increaseStrSize(allCommand, strlen(_itoa(price, stam_price, 10)));
	strcat(*allCommand, _itoa(price, stam_price, 10));

	increaseStrSize(allCommand, sizeof(char));
	strcat(*allCommand, " ");

	if (strcmp(temp + 1, "MaxPrice") == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (apt[i].price <= price)
			{
				(*arr)[*index] = apt[i].code;
				(*index)++;
				if (*index > size)
				{
					tmpArr = (int*)realloc(*arr, (*index + 1) * sizeof(int));
					*arr = (int*)realloc(tmpArr, (*index + 1) * sizeof(int));;
				}
			}
		}
	}
	if (strcmp(temp + 1, "MinPrice") == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (apt[i].price >= price)
			{
				(*arr)[*index] = apt[i].code;
				(*index)++;
				if (*index > size)
				{
					tmpArr = (int*)realloc(*arr, (*index + 1) * sizeof(int));
					*arr = (int*)realloc(tmpArr, (*index + 1) * sizeof(int));;
				}
			}
		}
	}
	tmpArr = NULL; //Tamar 13.1
	free(tmpArr);
}
void FindDate(APARTMENT* apt, int size, int** arr, int* index, char** allCommand)
{

	int i;
	int date;
	char stam_date[100];
	int* tmpArr = NULL;
	scanf("%d", &date);
	int day, month, year;

	increaseStrSize(allCommand, strlen(_itoa(date, stam_date, 10)));
	strcat(*allCommand, _itoa(date, stam_date, 10));

	increaseStrSize(allCommand, sizeof(char));
	strcat(*allCommand, " ");

	year = date % 10000;
	date /= 10000;
	month = date % 100;
	date /= 100;
	day = date;

	for (i = 0; i < size; i++)
	{
		if (apt[i].entryY + 2000 <= year)
		{
			if (apt[i].entryM <= month || apt[i].entryY + 2000 < year)
			{
				if (apt[i].entryD <= day || apt[i].entryM < month || apt[i].entryY + 2000 < year)
				{
					(*arr)[*index] = apt[i].code;
					(*index)++;
					if (*index > size)
					{
						tmpArr = (int*)realloc(*arr, (*index + 1) * sizeof(int));
						*arr = (int*)realloc(tmpArr, (*index + 1) * sizeof(int));;
					}
				}
			}
		}

	}
}