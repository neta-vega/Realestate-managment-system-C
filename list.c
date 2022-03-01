#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "list.h"
#include "structs1.h"
#include "libraries1.h"
#include "memory.h"
List makeEmptyList()
{
	List result;
	result.head = result.tail = NULL;
	return result;
}

int isEmptyList(List lst)
{
	return (lst.head == NULL);
}


void insertDataToEndList(List* lst, char* command)
{

	ListNode* tmp;
	ListNode* p = lst->head;
	tmp = (ListNode*)malloc(sizeof(ListNode));
	createNode(command, NULL, tmp);
	tmp->next = NULL;

	if (isEmptyList(*lst))
	{
		lst->head = tmp;
		lst->tail = tmp;
	}
	else
	{
		lst->tail->next = tmp;
		lst->tail = tmp;
	}
}


void createNode(char* command, ListNode* next, ListNode* tmp)
{

	tmp->command = (char*)malloc(sizeof(char) * strlen(command));
	checkMemoryAllocationchar(tmp->command);

	strcpy(tmp->command, command);

	tmp->next = next;

}

void insertDataToStartList(List* lst, char* data)
{
	ListNode* newHead;
	newHead = (ListNode*)malloc(sizeof(ListNode));
	createNode(data, NULL, newHead);
	insertNodeToStartList(lst, newHead);
}

void insertNodeToStartList(List* lst, ListNode* head)
{
	if (isEmptyList(*lst) == true)
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}



void printList(List* lst)
{
	int i = 1;
	ListNode* curr = lst->head;
	while (curr != NULL)
	{
		printf(">> %d. %s \n", i, curr->command);

		curr = curr->next;
		i++;
	}


}
void removeTail(List* list)
{
	ListNode* tmp = NULL;

	tmp = list->head;
	while (tmp->next->next != NULL)
	{
		tmp = tmp->next;
	}

	list->tail->command = NULL;
	free(list->tail->command);//Tamar 13.1
	list->tail = NULL;//Tamar 13.1
	free(list->tail);//Tamar 13.1
	tmp->next = NULL;
	list->tail = tmp;
}