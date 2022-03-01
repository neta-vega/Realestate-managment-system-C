#ifndef MEMORY_H
#define MEMORY_H
#include "structs1.h"
#include "libraries1.h"

//Memory allocation functions
void checkMemoryAllocationchar(char* str);
void checkMemoryAllocationArr(APARTMENT* arr);
void increaseStrSize(char** str, int howMuch);
#endif // MEMORY_H
