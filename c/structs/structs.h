#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include<string.h> 
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#define DIGIT_ADD 48

typedef struct elements_array_t
{
void *data;
void (*add)(void*,int);
void (*clean)(void*);
void (*print)(void*);
} ElementsArray;

void cleanInt(void* num);

void cleanFloat(void* num);

void cleanString(void* str);

void addInt(void *data ,int num);

void addFloat(void *data, int num);

void addString(void *string, int num);

void printInt(void *data);

void printFloat(void *data);

void printString(void *data);

#endif
