#ifndef GETCOMMANDS_H
#define GETCOMMANDS_H
#include "structs1.h"
#include "libraries1.h"

//Commands functions
int whichCommand(char* ch);
int getCommand(char** command);
void getSPCommand(char** command);
void get_entire_command(char** command);
void getAdressFromString(char* str, char** adress);
void getAdress(char** adress, int* size);
#endif // GETCOMMANDS_H
