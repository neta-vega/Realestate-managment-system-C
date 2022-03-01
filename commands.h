#ifndef COMMANDS_H
#define COMMANDS_H
#include "structs1.h"
#include "libraries1.h"

//Commands perform functions
void addApt(APARTMENT* apt, short int code);
void buyApt(APARTMENT** apt, int* size, char** allCommand);
void deleteApt(APARTMENT* arr, int* arrSize, char* allCommand);
void findApt(APARTMENT* apt, int size, char** allCommand);
//Specific command to perform functions
void FindNumRooms(APARTMENT* apt, int size, int** arr, int* index, char* ch, char** allCommand);
void FindPrice(APARTMENT* apt, int size, int** arr, int* index, char* ch, char** allCommand);
void FindDate(APARTMENT* apt, int size, int** arr, int* index, char** allCommand);
#endif // COMMANDS_H

