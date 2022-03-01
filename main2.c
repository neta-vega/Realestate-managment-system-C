#include "libraries1.h"
#include "history.h"
#include "commands.h"
#include "files.h"
#include "convert.h"
#include "general.h"
#include "getCommands.h"
#include "list.h"
#include "memory.h"
#include "replace.h"
#include "structs1.h"

//Best and long main EVER 
void main(int argc, char** argv)
{
	APARTMENT* aptArr;
	int arrSize = 0;
	short int code = 1;
	int aptArrIndex = 0;
	int enter;
	char* short_term_history[N];
	int IndexShortH = 0; //index for short history array
	char* command;
	APARTMENT* p;
	char* allCommand = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(allCommand);
	command = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(command);


	int which = 0;
	aptArr = NULL;
	List historyList = makeEmptyList();

	read_commands_from_file(argv[1], &IndexShortH, short_term_history, &historyList);
	read_from_apt_binFile(argv[2], &aptArr, &arrSize);
	if (arrSize > 0) aptArrIndex = arrSize;

	printf("Please enter one of the following commands :\n add - apt, find - apt, buy - apt, delete - apt or exit\n");

	enter = getCommand(&command);
	which = whichCommand(command);


	while (which != 0)
	{
		if (which == 1)
		{
			if (arrSize == 0) //if there are no apt in the array 
			{
				arrSize++;
				aptArr = (APARTMENT*)malloc(sizeof(APARTMENT) * arrSize);
				checkMemoryAllocationArr(aptArr);
				addApt(aptArr, code);
				p = aptArr + aptArrIndex * sizeof(APARTMENT);
				convert_APT_Struct_To_String(p, &allCommand);
				addToHistory(short_term_history, allCommand, IndexShortH, &historyList); //addind to short history the command 
				aptArrIndex++;
				code++;
				free(allCommand);
				IndexShortH++;

			}
			else // when there are at least one apt in the array 
			{
				APARTMENT* temp = NULL;
				arrSize++;
				allCommand = (char*)calloc(MIN_STR, sizeof(char));
				checkMemoryAllocationchar(allCommand);
				temp = (APARTMENT*)realloc(aptArr, sizeof(APARTMENT) * arrSize);
				checkMemoryAllocationArr(temp);
				addApt(temp + aptArrIndex, code);
				code++;
				aptArrIndex++;
				aptArr = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * arrSize);
				convert_APT_Struct_To_String(&aptArr[aptArrIndex - 1], &allCommand);
				addToHistory(short_term_history, allCommand, IndexShortH, &historyList); //addind to short history the command 
				IndexShortH++;
				free(allCommand); //Tamar 13.1
				temp = NULL;//Tamar 13.1
				free(temp);//Tamar 13.1
				
				
			}
		}

		else if (which == 2) //buy
		{
			allCommand = (char*)calloc(MIN_STR, sizeof(char));
			checkMemoryAllocationchar(allCommand);
			buyApt(&aptArr, &arrSize, &allCommand);
			addToHistory(short_term_history, allCommand, IndexShortH, &historyList); //addind to short history the command 
			free(allCommand);
			IndexShortH++;

		}
		else if (which == 3)//delete
		{
			allCommand = (char*)calloc(MIN_STR, sizeof(char));
			checkMemoryAllocationchar(allCommand);
			deleteApt(aptArr, &arrSize, allCommand);
			addToHistory(short_term_history, allCommand, IndexShortH, &historyList); //addind to short history the command 
			free(allCommand);
			IndexShortH++;

		}
		else if (which == 4)//find
		{
			allCommand = (char*)calloc(MIN_STR, sizeof(char));
			checkMemoryAllocationchar(allCommand);
			findApt(aptArr, arrSize, &allCommand);
			addToHistory(short_term_history, allCommand, IndexShortH, &historyList); //addind to short history the command 
			free(allCommand);
			IndexShortH++;
		}
		else if (which == 5) //short_history
		{
			if (isShortHistoryFull(IndexShortH)) //if the short_history is full 
			{
				printShortHistory(short_term_history, 7); //we will print all the 7 commands 
			}
			else printShortHistory(short_term_history, IndexShortH);//if the array is not full, we send the index-1 because we update it before this function
		}
		else if (which == 6) //all commands from short and long history
		{
			printList(&historyList);
			printShortHistory(short_term_history, IndexShortH);
		}
		else if (which == 7) //Restore commands
		{
			char* roof = strchr(command, '^'); //check if ^ is part of the command and return the frist occurrence 
			char* str = (char*)malloc(sizeof(char) * 11); //str holds the first part of the command 'add-apt' or 'find-apt'
			checkMemoryAllocationchar(str);
			if (strcmp(command, "!!") == 0) //!! 
			{
				whichCommandFromHistory(IndexShortH, IndexShortH, &historyList, short_term_history, str);//after this line we hold 'add-apt' or 'find-apt' in str    
				if (strcmp(str, "add-apt") == 0)
				{
					APARTMENT* temp = NULL;
					(arrSize)++;
					temp = (APARTMENT*)realloc(aptArr, sizeof(APARTMENT) * arrSize);
					checkMemoryAllocationArr(temp);
					aptArr = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * arrSize);
					addAptfromHistory(aptArr, arrSize, code, arrSize - 2); //adding apt to database from the short history 
					code++;
					aptArrIndex++;
				}
				else if (strcmp(str, "find-apt") == 0)
				{
					if (isShortHistoryFull(IndexShortH) == 1)
						findAptfromHistory(aptArr, arrSize, short_term_history[6]); //if Short history is full we'll preforem the last commands of find we have in the array
					else findAptfromHistory(aptArr, arrSize, short_term_history[IndexShortH - 1]); //else the array is not full, we'll preforem the commands place in IndexShortH - 1

				}
				if (isShortHistoryFull(IndexShortH)) addToHistory(short_term_history, short_term_history[6], IndexShortH, &historyList); //adding command to history list 
				else addToHistory(short_term_history, short_term_history[IndexShortH - 1], IndexShortH, &historyList); //adding command to short history
				IndexShortH++;
			}

			else if (roof != NULL) //which means we got !<num>^str1^str2...
			{
				replace_command_from_history(command, enter, &IndexShortH, &historyList, short_term_history, &aptArr, &arrSize, &aptArrIndex, &code);

			}
			else  // !<num> 
			{
				int commandToDo = atoi(command + 1);
				whichCommandFromHistory(commandToDo, IndexShortH, &historyList, short_term_history, str); 
				char* strCommand = (char*)calloc(MIN_STR, sizeof(char)); //strCommand holds the specific command from history list
				checkMemoryAllocationchar(strCommand);
				if (strcmp(str, "add-apt") == 0)
				{
					int whichAptTocopy; //apt index we want to duplicate 
					if ((IndexShortH - commandToDo) >= 7)//searching the command in history list 
					{
						APARTMENT* temp = NULL;
						(arrSize)++;
						temp = (APARTMENT*)realloc(aptArr, sizeof(APARTMENT) * arrSize);
						checkMemoryAllocationArr(temp);
						whichAptTocopy = getCodeFromAddressHistory(temp, &arrSize, &historyList, commandToDo); 
						aptArr = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * arrSize);
						addAptfromHistory(aptArr, arrSize, code, whichAptTocopy);
						code++;
						aptArrIndex++;
						temp = NULL;//Tamar 13.1
						free(temp); //Tamar 13.1
					}
					else //searching the command in short histort 
					{

						APARTMENT* temp = NULL;
						(arrSize)++;
						temp = (APARTMENT*)realloc(aptArr, sizeof(APARTMENT) * arrSize);
						checkMemoryAllocationArr(temp);
						
						if (isShortHistoryFull(IndexShortH))
							whichAptTocopy = getCodeFromAddressShortHistory(temp, &arrSize, short_term_history[6 - (IndexShortH - commandToDo)]);
						else
							whichAptTocopy = getCodeFromAddressShortHistory(temp, &arrSize, short_term_history[commandToDo - 1]);
						
						addAptfromHistory(temp, arrSize, code, whichAptTocopy);
						aptArr = (APARTMENT*)realloc(temp, sizeof(APARTMENT) * arrSize); //after this line aptArr inclode the duplicted apt
						code++;
						aptArrIndex++;
						temp = NULL;//Tamar 13.1
						free(temp); //Tamar 13.1
					}

				}
				else if (strcmp(str, "find-apt") == 0)
				{
					if (IndexShortH > 6) //which means short history is full
					{

						if (IndexShortH - commandToDo > 7) //preforming the command from history list 
						{
							findCommandfromLongHistory(&historyList, commandToDo, &strCommand);//retrive the command as strCommand 
							findAptfromHistory(aptArr, arrSize, strCommand);//preforeming the strCommand 
						}
						else //preforming the command from short history 
						{
							findAptfromHistory(aptArr, arrSize, short_term_history[7 - (IndexShortH - commandToDo) - 1]);
						}

					}
					else //short history is full 
					{
						findAptfromHistory(aptArr, arrSize, short_term_history[commandToDo - 1]);
					}



				}
				if (isShortHistoryFull(IndexShortH)) //adding command to history 
				{
					if (IndexShortH - commandToDo > 7)
					{
						findCommandfromLongHistory(&historyList, commandToDo, &strCommand);//we search the right command in history and put it inside strCommand
						addToHistory(short_term_history, strCommand, IndexShortH, &historyList);//we add the restored command to history
					}
					else
					{
						addToHistory(short_term_history, short_term_history[7 - (IndexShortH - commandToDo) - 1], IndexShortH, &historyList);
					}
				}
				else addToHistory(short_term_history, short_term_history[IndexShortH - 1], IndexShortH, &historyList);
				IndexShortH++;
				strCommand = NULL;//Tamar 13.1
				free(strCommand);//Tamar 13.1
			}
			str = NULL; //Tamar 13.1
			free(str);//Tamar 13.1
			
		}

		else
		{
			printf("error");
		}

		command = (char*)calloc(MIN_STR, sizeof(char)); //allocte new memory to the next command 
		checkMemoryAllocationchar(command);
		enter = getCommand(&command);
		which = whichCommand(command);
	



	}
	printArr(aptArr, arrSize);

	printf("good bye!");
	write_commands_to_file(argv[1], &IndexShortH, short_term_history, &historyList);
	write_to_apt_binFile(argv[2], aptArr, arrSize);



	exit(1);
}
