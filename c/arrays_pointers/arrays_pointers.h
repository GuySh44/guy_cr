#ifndef __ARRAYS_POINTERS_H__
#define __ARRAYS_POINTERS_H__

#include<stdlib.h>
#include<stddef.h>
#include<stdio.h>
#include<string.h>

size_t josephus(size_t n, size_t start);

void printCTypes();
/*
void array1(int array[][4]);

void array2(int **array);

void array3(int *array[]);
*/

void rowCalc(int array[][4], int *res, int row_size, int col_size);

void envExercise(char *envp[]);

char **envCreate(char *envp[]);

size_t envLen(char *envp[]);

void envCopy(char **dest, char *src[]); 

void envFree(char **env);

#endif /* __ARRAYS_POINTERS_H__ */
