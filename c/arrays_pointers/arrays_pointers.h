#ifndef __ARRAYS_POINTERS_H__
#define __ARRAYS_POINTERS_H__

#include<stdlib.h> /* malloc */
#include<stddef.h> /* size_t */
#include<stdio.h> /* printf() */
#include<string.h> /* strlen() */
#include<ctype.h> /* tolower() */ 

size_t josephus(size_t n, size_t start);

void printCTypes();
/*
void array1(int array[][4]);

void array2(int **array);

void array3(int *array[]);
*/

void rowCalc(int array[][4], int *res, int row_size, int col_size);

void envExercise(char *envp[]);

#endif /* __ARRAYS_POINTERS_H__ */
