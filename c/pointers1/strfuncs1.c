#include<stdio.h>
#include<string.h>

size_t StrLen(const char* s)
{
	size_t i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return i;
}



int main()
{
	char* a = "adc";
	printf("%lu\n%lu\n%lu\n",strlen(a), strlen(""), strlen("23432\0ll"));
	printf("%lu\n%lu\n%lu\n",StrLen(a), StrLen(""), StrLen("23432\0ll"));
	return 0;
}
