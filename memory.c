#include "memory.h"
#include "structs1.h"
#include "libraries1.h"
void checkMemoryAllocationchar(char* str)
{
	if (str == NULL)
	{
		printf("Memory Allocation Failed for char!");
		exit(1);
	}

}


void checkMemoryAllocationArr(APARTMENT* arr)
{
	if (arr == NULL)
	{
		printf("Memory Allocation Failed for APTarr!");
		exit(1);
	}

}
void increaseStrSize(char** str, int howMuch)
{
	int size = strlen(*str);
	int newSize = size + howMuch + 4;
	char* tempCommand = (char*)calloc(newSize, sizeof(char));
	checkMemoryAllocationchar(tempCommand);
	memcpy(tempCommand, *str, size);

	memset(*str, 0, strlen(*str));
	*str = tempCommand;

}

//void freeList(ListNode* head) //Tamar 13.1
//{
//	ListNode* tmp;
//
//	while (head != NULL)
//	{
//		tmp = head;
//		tmp->command = NULL;
//		head = head->next;
//		free(tmp->command);
//		free(tmp);
//	}
//
//}
//void freeCommand(char** short_temrm_history, int IndexShortH)//Tamar 13.1
//{
//
//}