#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void ReverseSentence(char *str)
{
	size_t size = strlen(str);
	char *new_str = malloc(size+1);
	size_t i = 0;
	while(i < size)
	{
		size_t start = i;
		while(str[i] != ' ' && i < size)
		{
			++i;
		}
		memcpy(new_str+size-i, str+start, i-start);
		if(i < size)
		{
			new_str[size-1-i] = ' ';
		}
		++i;
	}
	memcpy(str, new_str, size);
	free(new_str);
}


int main()
{
	char string[13] = "i am student";
	char raz[17] = "raz is my friend";
	printf("first string:\n%s\n",string);
	ReverseSentence(string);
	printf("after change::\n%s\n",string);
	printf("raz string:\n%s\n",raz);
	ReverseSentence(raz);
	printf("after change::\n%s\n",raz);
	return 0;
}
