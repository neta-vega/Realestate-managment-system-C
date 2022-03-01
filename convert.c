#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "convert.h"
#include "structs1.h"
#include "libraries1.h"
#include "memory.h"
#include "getCommands.h"

void convert_APT_Struct_To_String(APARTMENT* apt, char** allCommand)
{
	(*allCommand)[0] = '\0';
	int aCSize = strlen(*allCommand);
	char stam_price[100];
	char stam_NumRooms[100];
	char stam_entryD[100];
	char stam_entryM[100];
	char stam_entryY[100];
	char* stam = "add-apt \"";
	int size = strlen(stam);
	increaseStrSize(allCommand, strlen(stam) + 1);


	strcat(*allCommand, stam);
	increaseStrSize(allCommand, strlen(apt->adress));

	strcat(*allCommand, apt->adress);
	increaseStrSize(allCommand, 3);

	strcat(*allCommand, "\" ");

	increaseStrSize(allCommand, strlen(_itoa((apt->price), stam_price, 10)));

	strcat(*allCommand, _itoa((apt->price), stam_price, 10)); //adding price to allCommand 
	increaseStrSize(allCommand, 1);

	strcat(*allCommand, " ");

	increaseStrSize(allCommand, strlen(_itoa((apt->NumOfRooms), stam_NumRooms, 10)));

	strcat(*allCommand, _itoa((apt->NumOfRooms), stam_NumRooms, 10));
	increaseStrSize(allCommand, 1);

	strcat(*allCommand, " ");

	increaseStrSize(allCommand, strlen(_itoa((apt->entryD), stam_entryD, 10)));
	strcat(*allCommand, _itoa((apt->entryD), stam_entryD, 10));
	increaseStrSize(allCommand, 1);

	strcat(*allCommand, " ");

	increaseStrSize(allCommand, strlen(_itoa((apt->entryM), stam_entryM, 10)));
	strcat(*allCommand, _itoa((apt->entryM), stam_entryM, 10));
	increaseStrSize(allCommand, 1);

	strcat(*allCommand, " ");

	increaseStrSize(allCommand, strlen(_itoa((apt->entryY), stam_entryY, 10)));
	strcat(*allCommand, _itoa((apt->entryY), stam_entryY, 10));
}

void convert_Apt_String_to_struct(char* str, APARTMENT* apt)
{
	int location = 0;

	apt->adress = (char*)calloc(MIN_STR, sizeof(char));
	checkMemoryAllocationchar(apt->adress);
	char stam_price[100];
	char stam_numRooms[100];
	char stam_Day[100];
	char stam_Month[100];
	char stam_Year[100];


	getAdressFromString(str + 9, &apt->adress);
	if (apt->adress != '\0')
	{
		location = 10 + strlen(apt->adress);
	}

	sscanf(str + location, "%s", stam_price);
	apt->price = atoi(stam_price);

	location += strlen(stam_price) + 1;
	sscanf(str + location, "%s", stam_numRooms); //+10 to contain white spaces
	apt->NumOfRooms = atoi(stam_numRooms);

	location += strlen(stam_numRooms) + 1;
	sscanf(str + location, "%s", stam_Day);
	apt->entryD = atoi(stam_Day);

	location += strlen(stam_Day) + 1;
	sscanf(str + location, "%s", stam_Month);
	apt->entryM = atoi(stam_Month);

	location += strlen(stam_Month) + 1;
	sscanf(str + location, "%s", stam_Year);
	apt->entryY = atoi(stam_Year);

}
void convert_Code_Arr_To_Apt_Arr(int* finalArrCodes, APARTMENT* apt, int k, int size, APARTMENT* finalFind) //converting the relevant apt to apt arr
{
	//APARTMENT* finalFind;
	//finalFind = (APARTMENT*)malloc(k * sizeof(APARTMENT));
	//checkMemoryAllocationArr(finalFind);
	int i, j, f = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < k; j++)
		{
			if (apt[i].code == finalArrCodes[j])
			{
				finalFind[f] = apt[i];
				f++;
			}
		}
	}
	//return finalFind;
}