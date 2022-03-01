#ifndef CONVERT_H
#define CONVERT_H
#include "structs1.h"
#include "libraries1.h"

//Convert functions
void convert_Apt_String_to_struct(char* str, APARTMENT* apt);
void convert_APT_Struct_To_String(APARTMENT* apt, char** allCommand);
//APARTMENT* convert_Code_Arr_To_Apt_Arr(int* finalArrCodes, APARTMENT* apt, int k, int size); Tamar 13.1
void convert_Code_Arr_To_Apt_Arr(int* finalArrCodes, APARTMENT* apt, int k, int size, APARTMENT* finalFind);
#endif // CONVERT_H
