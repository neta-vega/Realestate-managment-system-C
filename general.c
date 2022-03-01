#define _CRT_SECURE_NO_WARNINGS

#include "general.h"
#include "structs1.h"
#include "libraries1.h"
#include "memory.h"
#include <time.h>


void printArr(APARTMENT* apt, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("Apt details:\nCode: %d\nAddress: %s\nNumber Of Romms: %d\nPrice: %d\nEntry Date: %d%d%d\nDatabase entry date: %s\n", apt[i].code, apt[i].adress, apt[i].NumOfRooms, apt[i].price,  apt[i].entryD, apt[i].entryM, apt[i].entryY,  ctime(&apt[i].datatbase_entry_date));
	}

}
void printArrByCodes(int* finalArrCodes, APARTMENT* apt, int k, int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < k; j++)
		{
			if (apt[i].code == finalArrCodes[j])
			{
				printf("%s Price = %d Num Of Romms = %d, Entry Date - %d%d%d, Code = %d, %lld\n", apt[i].adress, apt[i].price, apt[i].NumOfRooms, apt[i].entryD, apt[i].entryM, apt[i].entryY, apt[i].code, apt[i].datatbase_entry_date);

			}
		}
	}

}



void mergeSort(APARTMENT* apt, int size, char* command, APARTMENT* res)
{
	int i;

	if (size == 1)
		return;
	mergeSort(apt, size / 2, command, res);
	mergeSort(apt + size / 2, size - size / 2, command, res);
	//res = (APARTMENT*)calloc(size,sizeof(APARTMENT));
	//checkMemoryAllocationArr(res);
	merge(apt, size / 2, apt + size / 2, size - size / 2, res, command);

	for (i = 0; i < size; i++)
	{
		apt[i] = res[i];
	}
	

}

void merge(APARTMENT* a1, int s1, APARTMENT* a2, int s2, APARTMENT* res, char* command)
{
	int i1 = 0, i2 = 0;
	int j = 0;

	if ((strcmp(command + 1, "s") == 0)) //low to high 
	{
		while (i1 < s1 && i2 < s2)
		{
			if (a1[i1].price < a2[i2].price)
			{
				res[j] = a1[i1];
				i1++;
				j++;
			}
			else
			{
				res[j] = a2[i2];
				i2++;
				j++;
			}
		}

		while (i1 < s1)
		{
			res[j] = a1[i1];
			i1++;
			j++;
		}
		while (i2 < s2)
		{
			res[j] = a2[i2];
			i2++;
			j++;
		}
	}
	else
	{
		while (i1 < s1 && i2 < s2)
		{
			if (a1[i1].price > a2[i2].price)
			{
				res[j] = a1[i1];
				i1++;
				j++;
			}
			else
			{
				res[j] = a2[i2];
				i2++;
				j++;
			}
		}

		while (i1 < s1)
		{
			res[j] = a1[i1];
			i1++;
			j++;
		}
		while (i2 < s2)
		{
			res[j] = a2[i2];
			i2++;
			j++;
		}

	}
}
void printShortHistory(char** short_term_history, int IndexShortH)
{

	int i = 0, temp, j;
	temp = IndexShortH;//temp saves the old value of the index before we change it

	if (IndexShortH >= 7)
	{
		i = IndexShortH - 7;
		IndexShortH = 7; //if the index is bigger than 7 we need to change it to print in the correct order
	}
	for (i, j = 0; i < temp; i++, j++)
	{
		//int commandToDo = (temp) > (7) ? (temp - 6) : (i + 1);
		printf(">> %d. %s\n", i + 1, short_term_history[j]);
	}
}
int check(char* s, char c)
{
	int i, count = 0;
	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
		{
			count++;
		}
	}
	return count;


}