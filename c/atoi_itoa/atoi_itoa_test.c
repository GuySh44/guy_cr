#include"atoi_itoa.h"
#include<stdio.h>
#include<limits.h>

int main()
{
	char str1[11];
	char str2[12];
	intToString(INT_MAX,str1);
	intToString(INT_MIN,str2);
	printf("max int is:\t%s\n",str1);
	printf("min int is:\t%s\n",str2);
	return 0;
}
