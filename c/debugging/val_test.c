#include<stdlib.h>
#include<stdio.h>
int main()
{
	int* lost = malloc(4);
	int* what_if = malloc(4);
	int rule_breaker[10];
	printf("%d",rule_breaker[10]);
	rule_breaker[10] = 1;
	free(lost);
	*lost = 1;
	if(*what_if){}
	return 0;
}
