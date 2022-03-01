#ifndef STRUCTS_H
#define STRUCTS_H
#include "libraries1.h"
#include <time.h> 
typedef struct apt {
	int price;
	char* adress;
	short int code, NumOfRooms, entryD, entryM, entryY;
	time_t datatbase_entry_date;
}APARTMENT;

typedef struct listNode
{
	char* command;
	struct listNode* next;
}ListNode;
typedef struct lst
{
	ListNode* head;
	ListNode* tail;
}List;

typedef unsigned char BYTE;

typedef struct {
	BYTE b1, b2, b3;
} AptDetails;

typedef struct {
	short int numRooms;
	short int entryD;
	short int entryM;
	short int entryY;
}AptDetailsDecoded;
#endif // STRUCTS_H
