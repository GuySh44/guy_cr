#ifndef __ATOI_ITOA_H__
#define __ATOI_ITOA_H__
#include<ctype.h> /*isalnum isdig isspace*/
#include<assert.h>
#include<stdio.h>/* printf */
#define IS_BIG_ENDIAN (*(unsigned short *)"\0\xff" < 0x0100)
/* reviewer yahav 30/11/22*/

void intToString(int num, char *str, int base);

int stringToInt(char *str, int base);

void intToStringBaseTen(int num, char *str);

int stringToIntBaseTen(char *str);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void appearsTwo(char *arr1, int arr1_size, char *arr2, int arr2_size, char *arr3, int arr3_size);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
void checkLittleEndian();


#endif
