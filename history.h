#ifndef HISTORY_H
#define HISTORY_H
#include "structs1.h"
#include "libraries1.h"
#include <stdbool.h>
//History functions
bool isShortHistoryFull(int index); //
void addToHistory(char** short_term_history, char* allCommand, int shortHistoryIndex, List* historyList); //
void findAptfromHistory(APARTMENT* aptArr, int size, char* str); //
void FindDatefromHistory(APARTMENT* apt, int size, int** arr, int* index, char* str, int sizeOfString); //
void FindNumRoomsfromHistory(APARTMENT* apt, int size, int** arr, int* index, char* ch, char* str, int sizeOfString);//
void FindPricefromHistory(APARTMENT* apt, int size, int** arr, int* index, char* ch, char* str, int* sizeOfString); //
int getCodeFromAddressShortHistory(APARTMENT* aptArr, int* arrSize, char* shortTermh);//
void addAptfromHistory(APARTMENT* aptArr, int arrSize, short int newcode, int whichAptTocopy); //
int getCodeFromAddressHistory(APARTMENT* aptArr, int* arrSize, List* history, int commandNum);
void whichCommandFromHistory(int command, int shorHistoryindex, List* history, char** shorHistory, char* strCommand);
void findCommandfromLongHistory(List* historyList, int commandToDo, char** strCommand);//
#endif // HISTORY_H
