#ifndef __LOGGER_H__
#define __LOGGER_H__
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h> /*exit*/

struct print_me
{
	int num;
	void (*Print)(int);
};

typedef enum commands {append} commands;

void manageLogger(char *file_name);

void printNum(int num);

void firstExercise();

commands parseInput(char *buffer);

void executeLogger(char *buffer, FILE *file, commands command);

void appendLine(char *buffer, FILE *file);

FILE* openFile(char *file_name, commands command);

void closeFile(FILE *file);

#endif
