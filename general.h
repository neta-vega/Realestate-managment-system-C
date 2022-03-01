#ifndef GENERAL_H
#define GENERAL_H
#include "structs1.h"
#include "libraries1.h"

//General functions
void mergeSort(APARTMENT* apt, int size, char* command, APARTMENT* res);
void merge(APARTMENT* a1, int s1, APARTMENT* a2, int s2, APARTMENT* res, char* command);
//Print functions
void printArrByCodes(int* finalArrCodes, APARTMENT* apt, int k, int size);
void printShortHistory(char** short_term_history, int IndexShortH);
void printArr(APARTMENT* apt, int size);
int check(char* s, char c);

#endif // GENERAL_H
