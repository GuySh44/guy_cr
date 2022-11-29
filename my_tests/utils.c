#include"utils.h"


void printTest(char* test_name,int bool_int)
{
	printf("%s test result:\t", test_name);
	if(0 == bool_int)
	{
		printf("\033[1;32m");
		printf("[SUCCESS]");
		printf("\033[0m");
	}
	else
	{
		printf("\033[1;31m");
		printf("[FAIL]");
		printf("\033[0m");
	}
	printf("\n");
}
