#include <stdio.h>
#include "mystatic.h"

int x = 3;

extern void PrintGlobalVariableAddress()
{
	printf("x's address:\t%p\n",(void*)&x);
}
