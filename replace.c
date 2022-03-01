#define _CRT_SECURE_NO_WARNINGS
#include "replace.h"
#include "structs1.h"
#include "libraries1.h"
#include "memory.h"
#include "history.h"
#include "convert.h"
#include "getCommands.h"
void roof_from_entire_command(char* command, int** IndexShortH, List** historyList, char** shortHistory, APARTMENT*** aptArr, int** arrSize, int** aptArrIndex, short int** code)
{
	int i = 1, j = 0;
	char* commandToDo = (char*)calloc(MIN_STR, sizeof(char));//holds <num> from !<num>^___^___ as string
	char* allCommand = (char*)calloc(MIN_STR, sizeof(char));//holds the relvant command from the history
	char* strSource = (char*)calloc(MIN_STR, sizeof(char));//holds the content the user wants to replace
	char* strDest = (char*)calloc(MIN_STR, sizeof(char));//holds the content the user wants to replace to
	char* str = (char*)calloc(11, sizeof(char));//'add-apt' or 'find-apt'
	int numCommandToDo; //holds num command as int 
	checkMemoryAllocationchar(commandToDo);
	checkMemoryAllocationchar(allCommand);
	checkMemoryAllocationchar(strSource);
	checkMemoryAllocationchar(strDest);
	checkMemoryAllocationchar(str);


	while (command[i] != '^')  //in commandToDo we have the command number we want to recover
	{
		commandToDo[j] = command[i];
		increaseStrSize(&commandToDo, sizeof(char));
		j++;
		i++;
	}
	commandToDo[j] = '\0';

	numCommandToDo = atoi(commandToDo);
	whichCommandFromHistory(numCommandToDo, **IndexShortH, *historyList, shortHistory, str);//after this line we have in str 'add-apt' or 'find-apt'

	if (strcmp(str, "add-apt") == 0)
	{

		if ((**IndexShortH - numCommandToDo) >= 7) //history list 
		{
			findCommandfromLongHistory(*historyList, numCommandToDo, &allCommand); //after this line we have in allCommand the entire command from history
			search_For_What_to_Replace(command, &strSource, &strDest);
			replaceSubstring(&allCommand, strSource, strDest);
			APARTMENT* temp = NULL;
			(**arrSize)++;
			temp = (APARTMENT*)realloc(**aptArr, sizeof(APARTMENT) * **arrSize);
			checkMemoryAllocationArr(temp);

			convert_Apt_String_to_struct(allCommand, ((temp)+**aptArrIndex));
			((temp)+**aptArrIndex)->code = (**code);
			((temp)+**aptArrIndex)->datatbase_entry_date = time(NULL);
			**aptArr = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * **arrSize);
			(**code)++;
			(**aptArrIndex)++;
			addToHistory(shortHistory, allCommand, **IndexShortH, *historyList);
			(**IndexShortH)++;
			free(allCommand);
		}
		else
		{
			if (isShortHistoryFull(**IndexShortH))
			{
				increaseStrSize(&allCommand, strlen(shortHistory[7 - (**IndexShortH - numCommandToDo) - 1]));
				strcpy(allCommand, shortHistory[7 - (**IndexShortH - numCommandToDo) - 1]);
			}
			else
			{
				increaseStrSize(&allCommand, strlen(shortHistory[numCommandToDo - 1]));
				strcpy(allCommand, shortHistory[numCommandToDo - 1]);
			}
			search_For_What_to_Replace(command, &strSource, &strDest);
			replaceSubstring(&allCommand, strSource, strDest);
			APARTMENT* temp = NULL;
			(**arrSize)++;
			temp = (APARTMENT*)realloc(**aptArr, sizeof(APARTMENT) * **arrSize);
			checkMemoryAllocationArr(temp);
			convert_Apt_String_to_struct(allCommand, ((temp)+**aptArrIndex));
			((temp)+**aptArrIndex)->code = **code;
			((temp)+**aptArrIndex)->datatbase_entry_date = time(NULL);
			**aptArr = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * **arrSize);
			(**code)++;
			(**aptArrIndex)++;
			addToHistory(shortHistory, allCommand, **IndexShortH, *historyList);
			(**IndexShortH)++;
			free(allCommand);

		}

	}
	else if (strcmp(str, "find-apt") == 0)
	{
		if (**IndexShortH > 6)
		{
			if (**IndexShortH - numCommandToDo >= 7)
			{
				findCommandfromLongHistory(*historyList, numCommandToDo, &allCommand);
				search_For_What_to_Replace(command, &strSource, &strDest);
				replaceSubstring(&allCommand, strSource, strDest);
				findAptfromHistory(**aptArr, **arrSize, allCommand);
				addToHistory(shortHistory, allCommand, **IndexShortH, *historyList);
				(**IndexShortH)++;
				free(allCommand);

			}
			else
			{
				char* saveStr = (char*)calloc(strlen(shortHistory[7 - (**IndexShortH - numCommandToDo) - 1]), sizeof(char));
				checkMemoryAllocationchar(saveStr);
				memcpy(saveStr, (shortHistory[7 - (**IndexShortH - numCommandToDo) - 1]), strlen(shortHistory[7 - (**IndexShortH - numCommandToDo) - 1]));
				saveStr[strlen(shortHistory[7 - (**IndexShortH - numCommandToDo) - 1])] = '\0';
				search_For_What_to_Replace(command, &strSource, &strDest);
				replaceSubstring(&saveStr, strSource, strDest);
				findAptfromHistory(**aptArr, **arrSize, saveStr);
				addToHistory(shortHistory, saveStr, **IndexShortH, *historyList);
				(**IndexShortH)++;
				free(saveStr);
			}

		}
		else
		{
			char* saveStr = (char*)calloc(strlen(shortHistory[numCommandToDo - 1]), sizeof(char));
			checkMemoryAllocationchar(saveStr);
			memcpy(saveStr, shortHistory[numCommandToDo - 1], strlen(shortHistory[numCommandToDo - 1]));
			saveStr[strlen(shortHistory[numCommandToDo - 1])] = '\0';
			search_For_What_to_Replace(command, &strSource, &strDest);
			replaceSubstring(&saveStr, strSource, strDest);
			findAptfromHistory(**aptArr, **arrSize, saveStr);
			addToHistory(shortHistory, saveStr, **IndexShortH, *historyList);
			(**IndexShortH)++;
			free(saveStr);
		}
	}
}
void search_For_What_to_Replace(char* command, char** source, char** dest)
{
	unsigned int i = 0, j = 0;

	while (i < strlen(command))
	{
		if (command[i] != '^')
			i++;
		else
		{
			i++;

			while (command[i] != '^')
			{
				increaseStrSize(source, sizeof(char));
				(*source)[j] = command[i];

				j++;
				i++;
			}
			increaseStrSize(source, sizeof(char));
			(*source)[j] = '\0';
			break;

		}

	}
	increaseStrSize(dest, strlen(command) - i - 1);
	memcpy(*dest, command + 1 + i, strlen(command) - i - 1);
	increaseStrSize(dest, sizeof(char));
	(*dest)[strlen(command) - i] = '\0';
}



void replace_command_from_history(char* command, int enter, int* IndexShortH,
	List* historyList, char** short_term_history, APARTMENT** aptArr, int* arrSize, int* aptArrIndex, short int* code)
{
	if (enter == 1)//no enter - command is not complete
	{
		get_entire_command(&command);
		roof_from_entire_command(command, &IndexShortH, &historyList, short_term_history, &aptArr, &arrSize, &aptArrIndex, &code);
	}
	if (enter == 2)
	{
		roof_from_entire_command(command, &IndexShortH, &historyList, short_term_history, &aptArr, &arrSize, &aptArrIndex, &code);
	}

}
void replaceSubstring(char* allCommand[], char source[], char dest[])
{
	int stringLen, subLen, newLen, allCommand_new_size;
	int i = 0, j, k, appear = 0;
	int flag = 0, start, end;
	char* tmp = NULL;
	stringLen = strlen(*allCommand);
	subLen = strlen(source);
	newLen = strlen(dest);

	tmp = (char*)realloc(*allCommand, 200 * sizeof(char));//max size


	for (i = 0; i < stringLen; i++)
	{
		flag = 0;
		start = i;
		for (j = 0; tmp[i] == source[j]; j++, i++)
			if (j == subLen - 1)
			{
				flag = 1;
				appear++;
			}

		end = i;
		if (flag == 0)
			i -= j;
		else
		{
			for (j = start; j < end; j++)
			{
				for (k = start; k < stringLen; k++)
					tmp[k] = tmp[k + 1];
				stringLen--;
				i--;
			}

			for (j = start; j < start + newLen; j++)
			{
				for (k = stringLen; k >= j; k--)
					tmp[k + 1] = tmp[k];
				tmp[j] = dest[j - start];
				stringLen++;
				i++;
			}
		}
	}

	allCommand_new_size = strlen(*allCommand) - appear * strlen(source) + appear * strlen(dest);

	*allCommand = (char*)realloc(tmp, (allCommand_new_size + 1) * sizeof(char));
	(*allCommand)[allCommand_new_size] = '\0';
}