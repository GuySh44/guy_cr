#ifndef __LOGGER_H__
#define __LOGGER_H__
#include<stdio.h>
#include<errno.h>
#include<string.h> /* strcmp */
#include<stdlib.h> /*exit*/
#define BUFFER_SIZE 1024
#define NUM_OF_COMMANDS 5
#define APPEND_INDEX 4

void printNum(int num);

void firstExercise();

struct print_me
{
	int num;
	void (*Print)(int);
};
/*
typedef enum commands {append} commands;
*/

/*

EXERCISE 2

*/

typedef struct commands_t
{
	char *command;
	int (*Compare)(const char*, const char*);
	void (*Execute)(char*, char*);
} commands;

size_t parseInput(char *buffer, commands *ex2_commands);

void executeLogger(char *buffer, FILE *file, commands command);

void executeAppend(char *buffer, char *file_name);

void executeRemove(char *buffer, char *file_name);

FILE* openFile(char *file_name, size_t command_index);

void closeFile(FILE *file);

void executeEmpty(char *buffer, char *file_name);

#endif
