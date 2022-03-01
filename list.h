#ifndef LIST_H
#define LIST_H
#include "structs1.h"
#include "libraries1.h"
//List functions 
void insertDataToEndList(List* lst, char* command);
List makeEmptyList();
int isEmptyList(List lst);
void printList(List* lst);
void createNode(char* command, ListNode* next, ListNode* tmp);
void insertDataToStartList(List* lst, char* data);
void insertNodeToStartList(List* lst, ListNode* head);
void removeTail(List* list);
#endif // LIST_H
