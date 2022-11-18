#ifndef __LOGGER_H__
#define __LOGGER_H__
#include<stdio.h> /* fclose fopen printf fgets fgetc remove rename */
#include<string.h> /* strcmp */
#include<stdlib.h> /* exit */
#include<errno.h> /* ENOENT */
#define BUFFER_SIZE 1024
#define NUM_OF_COMMANDS 5
#define COUNT_INDEX 1
#define EXIT_INDEX 2
#define START_APPEND_INDEX 3
#define APPEND_INDEX 4

void printNum(int num);

void firstExercise();

struct print_me
{
	int num;
	void (*Print)(int);
};



/*

EXERCISE 2

*/

typedef enum OperationStatus {Fail, Success} OperStatus;

typedef struct commands_t
{
	char *command;
	int (*Compare)(const char*, const char*);
	OperStatus (*Execute)(char*, char*);
} commands;


size_t parseInput(char *buffer, commands *ex2_commands);

OperStatus executeAppend(char *buffer, char *file_name);

OperStatus executeStartAppend(char *buffer, char *file_name);

OperStatus executeRemove(char *buffer, char *file_name);

OperStatus executeCount(char *buffer, char *file_name);

OperStatus executeExit(char *buffer, char *file_name);

FILE* openFile(char *file_name, size_t command_index);

void closeFile(FILE *file);

OperStatus executeEmpty(char *buffer, char *file_name);

int CmpStartAppend(const char *str1, const char *str2);

#endif
