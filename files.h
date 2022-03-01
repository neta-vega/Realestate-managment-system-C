#ifndef FILES_H
#define FILES_H
#include "structs1.h"
#include "libraries1.h"

//Files functions 
void read_commands_from_file(char* fname, int* IndexShortH, char** short_term_history, List* lst);
void write_commands_to_file(char* fname, int* IndexShortH, char** short_term_history, List* list);
AptDetails apt_details_by_bits(short int rooms, short int entry_day, short int entry_month, short int entry_year);
AptDetailsDecoded decode_apt_details(BYTE b3, BYTE b2, BYTE b1);
void write_to_apt_binFile(char* fname, APARTMENT* aptArr, int aptArrSize);
void read_from_apt_binFile(char* fname, APARTMENT** aptArr, int* aptArrSize);
#endif // FILES_H
