#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include<string.h> /* strlen, strcat */
#include<assert.h> /* assert */
#include<stdio.h> /* printf */
#include<stdlib.h> /* malloc calloc */

/* reviewer: or */
#define DIGIT_ADD 48

#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

#define MAX3(a, b, c) (((MAX2(a,b) > MAX2(b,c)) ? MAX2(a,b) : MAX2(b,c)))

#define SIZEOF_VAR(type) (char *)(&type+1)-(char*)(&type)

#define SIZEOF_TYPE(type) ((char *)(((type *)0) + 1) - (char *)(((type *)0)))


/* struct holding a certain value of unknown type, and function pointers to address different implementations of functionality */
typedef struct elements_array_t
{
void *data;
void (*add)(void*,int);
void (*clean)(void*);
void (*print)(void*);
} ElementsArray;

/* create new element */

ElementsArray createInt(int num);

ElementsArray createFloat(float num);

ElementsArray createString(char *str);

/* "cleaning" functions to free each type */

void cleanInt(void* num);

void cleanFloat(void* num);

void cleanString(void* str);

/* adding functions to add int values in the required way */
void addInt(void *data ,int num);

void addFloat(void *data, int num);

void addString(void *string, int num);

/* printing functions to print each type */
void printInt(void *data);

void printFloat(void *data);

void printString(void *data);

#endif
