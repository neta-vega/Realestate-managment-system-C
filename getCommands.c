#define _CRT_SECURE_NO_WARNINGS

#include "getCommands.h"
#include "structs1.h"
#include "libraries1.h"
#include "memory.h"

int whichCommand(char* ch) //Receives the start of the command and returns a number accordingly
{

	if (strcmp(ch, "add-apt") == 0)
		return 1;
	if (strcmp(ch, "buy-apt") == 0)
		return 2;
	if (strcmp(ch, "delete-apt") == 0)
		return 3;
	if (strcmp(ch, "find-apt") == 0)
		return 4;
	if (strcmp(ch, "short_history") == 0)
		return 5;
	if (strcmp(ch, "history") == 0)
		return 6;
	if (ch[0] == '!')
		return 7;
	if (strcmp(ch, "exit") == 0)
		return 0;
	//free(ch); Tamar - 13.1 we allocate it in the main and calloc it before we get new command, free is no needed here 
}



void getAdress(char** adress, int* size)//Receives an address of strings in order to put the part of the apartment address in it and updates the size of the string
{
	int i = 1;
	char ch;

	ch = getchar();
	if (ch == '\n')
	{
		ch = getchar();
	}
	else if (ch == '"') //got '"', we will contiue to the next char 
	{
		ch = getchar(); //space afet '"'
		(*adress)[0] = ch;
		increaseStrSize(adress, sizeof(char));
		while (ch != '"') //puts the address which allocate between " " 
		{
			ch = getchar();
			increaseStrSize(adress, sizeof(char));
			(*adress)[i] = ch;
			i++;
		}
		//increaseStrSize(adress, sizeof(char)); Tamar 13.01
		(*adress)[i - 1] = '\0';
	}

	*size = strlen(*adress);


}

int getCommand(char** command)
{

	char ch;
	char* tmp = NULL;
	int i = 0;

	ch = getchar();
	if (ch == '\n')
	{
		ch = getchar();
	}

	while (ch != ' ' && ch != '\n')
	{
		char* tempCommand = (char*)malloc(sizeof(char) * (i + 1));;
		checkMemoryAllocationchar(tempCommand);
		memcpy(tempCommand, *command, i + 1);

		tempCommand[i] = ch;
		*command = tempCommand;
		i++;
		ch = getchar();
		if (ch == '\n')
		{
			(*command)[i] = '\0';
			return 2; //if ch is enter we want to know - return 2;
		}
		tempCommand = NULL; ////Tamar 13.1
		free(tempCommand); //Tamar 13.1
	}
	(*command)[i] = '\0';
	

	return 1;//there was no enter

}

void getSPCommand(char** command) //get command for find apt only 
{
	char ch;
	int i = 0;

	ch = getchar();
	if (ch == ' ')
	{
		ch = getchar();
	}

	while (ch != ' ')
	{
		increaseStrSize(command, sizeof(char));
		(*command)[i] = ch;
		i++;
		ch = getchar();
		if (i == 1 && ch == 's')
		{
			increaseStrSize(command, sizeof(char));
			(*command)[i] = 's';
			ch = getchar();
			if (ch == 'r')
			{
				i++;
				increaseStrSize(command, sizeof(char));
				(*command)[i] = 'r';
				i++;
			}
			else
			{
				i++;
				break;
			}
			break;
		}

	}
	increaseStrSize(command, sizeof(char));
	(*command)[i] = '\0';


}

void getAdressFromString(char* str, char** adress)
{
	char ch = 0;
	int i = 0;

	sscanf(str, "%c", &ch);
	while (ch != '\"')
	{
		(*adress)[i] = ch;
		increaseStrSize(adress, sizeof(char));
		str++;
		sscanf(str, "%c", &ch);

		i++;
	}
	(*adress)[i] = '\0';
}
void get_entire_command(char** command) //insert the entire command of ^ to command
{
	char ch;
	int i = strlen(*command) + 1; //where am i in command + space 
	char* tempCommand = (char*)calloc(i, sizeof(char));
	memcpy(tempCommand, *command, i - 1);
	increaseStrSize(command, sizeof(char));
	tempCommand[i - 1] = ' ';
	ch = getchar();


	while (ch != '\n')
	{
		increaseStrSize(&tempCommand, sizeof(char));
		checkMemoryAllocationchar(tempCommand);

		tempCommand[i] = ch;
		i++;
		ch = getchar();
	}
	*command = tempCommand;
	//*command = (char*)realloc(tempCommand, sizeof(char) * (i + 1));
	(*command)[i] = '\0';

}
