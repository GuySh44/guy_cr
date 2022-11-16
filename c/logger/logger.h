#ifndef __LOGGER_H__
#define __LOGGER_H__
#include<stdio.h>
struct print_me
{
	int num;
	void (*Print)(int);
};

void printNum(int num);

void firstExercise();


#endif
