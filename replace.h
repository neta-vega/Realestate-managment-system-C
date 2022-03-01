#ifndef REPLACE_H
#define REPLACE_H
#include "structs1.h"
#include "libraries1.h"

//Replace convert_Apt_String_to_struct
void replaceSubstring(char* allCommand[], char source[], char dest[]);
void search_For_What_to_Replace(char* command, char** source, char** dest);
void replace_command_from_history(char* command, int enter, int* IndexShortH, List* historyList, 
	char** short_term_history, APARTMENT** aptArr, int* arrSize, int* aptArrIndex, short int* code);
void roof_from_entire_command(char* command, int** IndexShortH, List** historyList, 
	char** shortHistory, APARTMENT*** aptArr, int** arrSize, int** aptArrIndex, short int** code);
#endif // REPLACE_H
