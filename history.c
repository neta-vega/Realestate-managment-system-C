#define _CRT_SECURE_NO_WARNINGS

#include "history.h"
#include "structs1.h"
#include "libraries1.h"
#include "memory.h"
#include "convert.h"
#include "general.h"
#include "list.h"
bool isShortHistoryFull(int index)
{
	if (index >= 7)
		return true;
	else return false;
}

void addToHistory(char** short_term_history, char* allCommand, int shortHistoryIndex, List* historyList)
{
	int i, saveStrLen = strlen(allCommand);
	char* saveAllCommand = (char*)malloc(sizeof(char) * strlen(allCommand));
	checkMemoryAllocationchar(saveAllCommand);
	strcpy(saveAllCommand, allCommand);
	//saveAllCommand[saveStrLen] = '\0';

	if (shortHistoryIndex >= 7)
	{
		insertDataToEndList(historyList, short_term_history[0]);
		for (i = 0; i < N - 1; i++)
		{
			memcpy(short_term_history[i], short_term_history[i + 1], strlen(short_term_history[i + 1]) + 1);
		}
		memcpy(short_term_history[6], saveAllCommand, strlen(allCommand) + 1);
	}
	else
	{
		short_term_history[shortHistoryIndex] = (char*)malloc(sizeof(char) * strlen(allCommand)); //allocate memory to the command string 
		checkMemoryAllocationchar(short_term_history[shortHistoryIndex]);
		strcpy(short_term_history[shortHistoryIndex], allCommand);
	}
	saveAllCommand = NULL;//Tamar 13.1
	free(saveAllCommand); //Tamar 13.1

}

void findAptfromHistory(APARTMENT* aptArr, int size, char* str)
{
	char* spCommand = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(spCommand);
	int* arr;
	int index = 0, countCommand = 0, i, j, k = 0, countApear = 1, sizeOfString = 8; //its int* becuase its storage the codes num
	// sizeOfString=9 cause find-apt is 9 chars
	int* finalArrCodes; // after compered requriments, puts in finalArr the right apt. 
	APARTMENT* finalFind;
	APARTMENT* res = NULL;
	arr = (int*)malloc(size * sizeof(int)); // all the apt that answer for the requriments 
	finalArrCodes = (int*)malloc(size * sizeof(int));
	increaseStrSize(&spCommand, strlen(str + sizeOfString));
	sscanf(str + sizeOfString, "%s", spCommand);
	sizeOfString += strlen(spCommand) + 1;


	while ((strcmp(spCommand + 1, "sr") != 0) && (strcmp(spCommand + 1, "s") != 0))
	{

		if (strcmp(spCommand + 4, "NumRooms") == 0)
		{
			FindNumRoomsfromHistory(aptArr, size, &arr, &index, spCommand, str, sizeOfString);
			sizeOfString += 3;
		}
		if (strcmp(spCommand + 4, "Price") == 0)
		{
			FindPricefromHistory(aptArr, size, &arr, &index, spCommand, str, &sizeOfString);

		}
		if (strcmp(spCommand + 1, "Date") == 0) {
			FindDatefromHistory(aptArr, size, &arr, &index, str, sizeOfString);
			sizeOfString += 10;
		}

		memset(spCommand, 0, strlen(spCommand));
		increaseStrSize(&spCommand, strlen(str + sizeOfString));
		sscanf(str + sizeOfString, "%s", spCommand);
		sizeOfString += strlen(spCommand) + 1;
		countCommand++;
	}

	if (countCommand == 1) // when we got only one command 
	{
		if (index == 0)
			printf("Not Found!\n");
		else
		{
			//finalFind = convert_Code_Arr_To_Apt_Arr(arr, aptArr, index, size); //index+1 is the apt size 
			finalFind = (APARTMENT*)malloc(sizeof(APARTMENT) * index); //Tamar 13.1
			checkMemoryAllocationArr(finalFind);//Tamar 13.1
			convert_Code_Arr_To_Apt_Arr(arr, aptArr, index, size, finalFind);//Tamar 13.1
			res = (APARTMENT*)calloc(size, sizeof(APARTMENT));
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
			//finalFind = convert_Code_Arr_To_Apt_Arr(finalArrCodes, aptArr, k, size);
			finalFind = (APARTMENT*)malloc(sizeof(APARTMENT) * index); //Tamar 13.1
			checkMemoryAllocationArr(finalFind);//Tamar 13.1
			convert_Code_Arr_To_Apt_Arr(arr, aptArr, index, size, finalFind);//Tamar 13.1
			res = (APARTMENT*)calloc(size, sizeof(APARTMENT));
			mergeSort(finalFind, k, spCommand, res);
			printArr(finalFind, k);
		}
	}
	spCommand = NULL;
	free(spCommand);
	res = NULL; //Tamar 13.1
	free(res);//Tamar 13.1

}
void FindNumRoomsfromHistory(APARTMENT* apt, int size, int** arr, int* index, char* ch, char* str, int sizeOfString)
{
	int i;
	int numRooms;
	int* tmpArr = NULL;
	char* temp = (char*)malloc(strlen(ch) * sizeof(char));
	checkMemoryAllocationchar(temp);
	temp = ch;
	sscanf(str + sizeOfString + 1, "%d", &numRooms);



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
	tmpArr = NULL;//Tamar 13.1
	free(tmpArr); //Tamar 13.1
	temp = NULL;//Tamar 13.1
	free(temp);//Tamar 13.1
}
void FindPricefromHistory(APARTMENT* apt, int size, int** arr, int* index, char* ch, char* str, int* sizeOfString)
{
	int i;
	int price;
	int* tmpArr = NULL;
	char stamprice[10];
	char* temp = (char*)malloc(strlen(ch) * sizeof(char));
	checkMemoryAllocationchar(temp);
	temp = ch;
	sscanf(str + *(sizeOfString), "%d", &price);
	_itoa(price, stamprice, 10);

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

	*sizeOfString += strlen(stamprice);


}
void FindDatefromHistory(APARTMENT* apt, int size, int** arr, int* index, char* str, int sizeOfString)
{

	int i;
	int date;
	int* tmpArr = NULL;
	sscanf(str + (sizeOfString), "%d", &date);
	int day, month, year;



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
void findCommandfromLongHistory(List* historyList, int commandToDo, char** strCommand)
{
	int k;
	ListNode* tmp = historyList->head;


	for (k = 1; k < commandToDo; k++)
	{
		tmp = tmp->next;
	}

	increaseStrSize(strCommand, strlen(tmp->command) + 1);
	strcpy(*strCommand, tmp->command);
	(*strCommand)[strlen(tmp->command)] = '\0';
}

void addAptfromHistory(APARTMENT* aptArr, int arrSize, short int newcode, int whichAptTocopy) //adding to aptArr an apt from history database
{
	aptArr[arrSize - 1] = aptArr[whichAptTocopy];
	aptArr[arrSize - 1].code = newcode;
	aptArr[arrSize - 1].datatbase_entry_date = time(NULL);
}

int getCodeFromAddressShortHistory(APARTMENT* aptArr, int* arrSize, char* shortTermh) //Short History - return index of the apt we want to duplicat 
{
	char* str = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(str);
	str[0] = '\0';
	char ch;
	int i = 0, j;
	sscanf(shortTermh + 9, "%c", &ch);
	while (ch != '\"')
	{
		increaseStrSize(&str, sizeof(char));
		strcat(str, &ch);
		i++;
		increaseStrSize(&str, sizeof(char));
		str[i] = '\0';
		sscanf(shortTermh + 9 + i, "%c", &ch);
	}
	for (j = 0; j < *arrSize; j++)
	{
		if (strcmp(aptArr[j].adress, str) == 0)
			return j;


	}

}

int getCodeFromAddressHistory(APARTMENT* aptArr, int* arrSize, List* history, int commandNum) //Long History - return index of the apt we want to duplicat 
{
	char* str = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(str);
	str[0] = '\0';
	char ch;
	int i = 0, j, k;
	ListNode* tmp = history->head;
	for (k = 8; k < commandNum; k++)
	{
		tmp = tmp->next;
	}

	sscanf(tmp->command + 9, "%c", &ch);
	while (ch != '\"')
	{
		increaseStrSize(&str, sizeof(char));
		strcat(str, &ch);
		i++;
		increaseStrSize(&str, sizeof(char));
		str[i] = '\0';
		sscanf(tmp->command + 9 + i, "%c", &ch);
	}
	for (j = 0; j < *arrSize; j++)
	{
		if (strcmp(aptArr[j].adress, str) == 0)
			return j;


	}
	str = NULL; //Tamar 13.1 
	free(str); //Tamar 13.1


}
void whichCommandFromHistory(int command, int shorHistoryindex, List* history, char** shorHistory, char* strCommand) //which command add/find to do on the history/Shistory
{
	if (shorHistoryindex - command > 6) //go to B  //Neta
	{
		int k;
		ListNode* tmp = history->head;
		for (k = 1; k < command; k++)
		{
			tmp = tmp->next;
		}

		sscanf(tmp->command, "%s", strCommand);

	}
	else // go to A 
	{
		if (isShortHistoryFull(shorHistoryindex)) sscanf(shorHistory[6 - (shorHistoryindex - command)], "%s", strCommand);
		else sscanf(shorHistory[command - 1], "%s", strCommand);

	}

}