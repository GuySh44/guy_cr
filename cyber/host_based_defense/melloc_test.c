#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
	char *str1 = NULL;
	char *str2 = NULL;
	char *str3 = NULL;
	const char *check1 = "passwor lmao";
	const char *check2 = "password lmaomao";
	const char *check3 = "password lmaomaozadong";

	str1 = malloc(sizeof(check1));
	str2 = malloc(sizeof(check2));
	str3 = malloc(sizeof(check3));

	strcpy(str1, check1);
	strcpy(str2, check2);
	strcpy(str3, check3);

	malloc(sizeof("copy"));
	
	free(str1);
	free(str2);
	free(str3);
	
	return 0;
}
