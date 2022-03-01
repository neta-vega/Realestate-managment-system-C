#define _CRT_SECURE_NO_WARNINGS

#include "files.h"
#include "structs1.h"
#include "libraries1.h"
#include "history.h"
#include "memory.h"
#include "list.h"

void read_commands_from_file(char* fname, int* IndexShortH, char** short_term_history, List* lst)
{
	int i, commandLen, j = 0, index_end_array, fileSize;
	char* str = (char*)calloc(MIN_STR, sizeof(char));
	FILE* fcommands = fopen(fname, "r");


	if (fcommands == NULL)
	{
		return;
	}
	fseek(fcommands, 0, SEEK_END);
	fileSize = ftell(fcommands);
	if (fileSize == 0)
	{
		fclose(fcommands);
		return;
	}
	else
	{
		fseek(fcommands, 0, SEEK_SET);
		fscanf(fcommands, "%d\n", IndexShortH);
		if (isShortHistoryFull(*IndexShortH)) index_end_array = 6;
		else (index_end_array = *IndexShortH - 1);

		for (i = 0; i < *IndexShortH; i++)
		{
			fscanf(fcommands, "\n");
			fscanf(fcommands, "%d ", &commandLen);
			increaseStrSize(&str, commandLen);
			fgets(str, commandLen + 1, fcommands);

			if (index_end_array >= 0)
			{

				short_term_history[index_end_array] = (char*)malloc((commandLen) * sizeof(char));
				memcpy(short_term_history[index_end_array], str, commandLen);
				(short_term_history[index_end_array])[commandLen] = '\0';
				index_end_array--;



			}
			else
			{
				insertDataToStartList(lst, str);
			}


		}
	}
	str = NULL;//Tamar 13.1
	free(str);//Tamar 13.1
	fclose(fcommands);
}


void write_commands_to_file(char* fname, int* IndexShortH, char** short_term_history, List* list)
{
	int i, index_end_array;
	FILE* fcommands = fopen(fname, "w");

	fprintf(fcommands, "%d\n", *IndexShortH); //number of commands 
	if (isShortHistoryFull(*IndexShortH))
	{
		index_end_array = 6;
	}
	else
	{
		index_end_array = *IndexShortH - 1;
	}

	for (i = 0; i < *IndexShortH; i++)
	{
		if (index_end_array >= 0)
		{
			fprintf(fcommands, "%d %s\n", strlen(short_term_history[index_end_array]), short_term_history[index_end_array]);
			short_term_history[index_end_array] = NULL; //Tamar 13.1
			free(short_term_history[index_end_array]); //Tamar 13.1
			index_end_array--;
			
		}
		else
		{
			fprintf(fcommands, "%d %s\n", strlen(list->tail->command), list->tail->command);
			if (list->head == list->tail)
			{
				list->head = list->tail = NULL;
				free(list->tail);//Tamar 13.1
				free(list->head); //Tamar 13.
			}
			else
			{
				removeTail(list);
			}
		}
	}
	fclose(fcommands);

}




AptDetails apt_details_by_bits(short int rooms, short int entry_day, short int entry_month, short int entry_year)
{
	AptDetails currApt = { 0,0,0 };
	currApt.b3 = 0xff;//b3 is the msb
	currApt.b2 = 0xff;
	currApt.b1 = 0xff;//b1 is the lsb

	//Assign "rooms" to 4 upper bits
	currApt.b3 &= 0x0f;
	currApt.b3 |= rooms << 4;

	//Assign "entry day" to 4 lower bits of b3, + 1 upper bit of b2
	currApt.b3 &= 0xf0;
	currApt.b2 &= 0x7f;
	currApt.b3 |= entry_day >> 1;
	currApt.b2 |= entry_day << 7;

	//assign "entry month" to the next 4 bits of b2
	currApt.b2 &= 0x87;
	currApt.b2 |= entry_month << 3;

	//assign "entry year" to the two lower bytes
	currApt.b2 &= 0xf8;
	currApt.b1 &= 0x00;//lower 4 bits should be 0 
	currApt.b2 |= entry_year >> 4;
	currApt.b1 |= entry_year << 4;

	return currApt;
}

void write_to_apt_binFile(char* fname, APARTMENT* aptArr, int aptArrSize)
{
	int i, adressLen;
	AptDetails currApt;
	FILE* binFile = fopen(fname, "wb");

	fwrite(&aptArrSize, sizeof(int), 1, binFile);
	for (i = 0; i < aptArrSize; i++)
	{
		adressLen = strlen(aptArr[i].adress);
		fwrite(&(aptArr[i].code), sizeof(short int), 1, binFile);
		fwrite(&adressLen, sizeof(int), 1, binFile);
		fwrite(aptArr[i].adress, sizeof(char), strlen(aptArr[i].adress), binFile);
		fwrite(&(aptArr[i].price), sizeof(int), 1, binFile);
		fwrite(&(aptArr[i].datatbase_entry_date), sizeof(time_t), 1, binFile);

		currApt = apt_details_by_bits(aptArr[i].NumOfRooms, aptArr[i].entryD, aptArr[i].entryM, aptArr[i].entryY);
		fwrite(&(currApt.b3), sizeof(char), 1, binFile);
		fwrite(&(currApt.b2), sizeof(char), 1, binFile);
		fwrite(&(currApt.b1), sizeof(char), 1, binFile);
	}

	fclose(binFile);
}


void read_from_apt_binFile(char* fname, APARTMENT** aptArr, int* aptArrSize)
{
	int i, adressLen, fileSize;
	FILE* binFile = fopen(fname, "rb");
	AptDetails currApt = { 0,0,0 };
	AptDetailsDecoded aptDecoded;
	APARTMENT* tempArr = NULL;

	if (binFile == NULL)
	{
		return;
	}
	fseek(binFile, 0, SEEK_END);
	fileSize = ftell(binFile);
	if (fileSize == 0)
	{
		fclose(binFile);
		return;
	}

	fseek(binFile, 0, SEEK_SET);
	fread(aptArrSize, sizeof(int), 1, binFile);
	*aptArr = NULL;

	for (i = 0; i < *aptArrSize; i++)
	{
		tempArr = (APARTMENT*)realloc(*aptArr, (i + 1) * sizeof(APARTMENT));
		fread(&(tempArr[i].code), sizeof(short int), 1, binFile);
		fread(&adressLen, sizeof(int), 1, binFile);
		tempArr[i].adress = (char*)malloc((adressLen + 1) * sizeof(char));
		fread(tempArr[i].adress, sizeof(char), adressLen, binFile);
		tempArr[i].adress[adressLen] = '\0';
		fread(&(tempArr[i].price), sizeof(int), 1, binFile);
		fread(&(tempArr[i].datatbase_entry_date), sizeof(time_t), 1, binFile);

		fread(&(currApt.b3), sizeof(char), 1, binFile);
		fread(&(currApt.b2), sizeof(char), 1, binFile);
		fread(&(currApt.b1), sizeof(char), 1, binFile);

		aptDecoded = decode_apt_details(currApt.b3, currApt.b2, currApt.b1);
		tempArr[i].NumOfRooms = aptDecoded.numRooms;
		tempArr[i].entryD = aptDecoded.entryD;
		tempArr[i].entryM = aptDecoded.entryM;
		tempArr[i].entryY = aptDecoded.entryY;

		*aptArr = (APARTMENT*)realloc(tempArr, (i + 1) * sizeof(APARTMENT));
	}
	tempArr = NULL; //Tamar 13.1
	free(tempArr); //Tamar 13.1
	fclose(binFile);
}

AptDetailsDecoded decode_apt_details(BYTE b3, BYTE b2, BYTE b1)
{
	AptDetailsDecoded aptDecoded = { 0,0,0,0 };

	aptDecoded.entryY = 0xff;
	aptDecoded.entryM = 0xff;
	aptDecoded.entryD = 0xff;
	aptDecoded.numRooms = 0xff;

	//assign entryY the correct bits from b1 and b2
	aptDecoded.entryY &= 0xf0;
	aptDecoded.entryY |= b1 >> 4;
	aptDecoded.entryY &= 0x0f;
	aptDecoded.entryY |= b2 << 4;
	aptDecoded.entryY &= 0x7f;

	//assign entryM the bits from b2
	aptDecoded.entryM &= 0x00;
	aptDecoded.entryM |= b2 >> 3;
	aptDecoded.entryM &= 0x0f;

	//assign entryD from b2 and b3
	aptDecoded.entryD &= 0x00;
	aptDecoded.entryD |= b2 >> 7;
	aptDecoded.entryD &= 0x01;
	aptDecoded.entryD |= b3 << 1;
	aptDecoded.entryD &= 0x1f;

	//assign num rooms from b3
	aptDecoded.numRooms &= 0x00;
	aptDecoded.numRooms |= b3 >> 4;

	return aptDecoded;
}