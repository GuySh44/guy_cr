#include<stdio.h>
#include<string.h>
int main()
{
	printf("%lu\n%lu\n%lu\n",strlen("abc"), strlen(""), strlen("23432\0ll"));
	return 0;
}
