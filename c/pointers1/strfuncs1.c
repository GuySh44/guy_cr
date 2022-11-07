#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stddef.h>

size_t StrLen(const char* s)
{
	size_t i = 0;
	assert(s != NULL);
	while (s[i] != '\0')
	{
		i++;
	}
	return i;
}

int StrCmp(const char* s1, const char* s2)
{
	int j = 0;
	while (s1[j] != '\0' || s2[j] != '\0')
	{
		if (s1[j] != s2[j])
			return (-1 + 2 * (s1[j] > s2[j]));
		j++;
	}
	return 0;
}


int main()
{
	char* a = "adc";
	char b[4] = {'a', 'b', '\0', 'c'};
	char c[4] = {'a', 'b', 'b','\0'};
	printf("%lu\n%lu\n%lu\n",strlen(a), strlen(""), strlen("23432\0ll"));
	printf("%lu\n%lu\n%lu\n",StrLen(a), StrLen(""), StrLen("23432\0ll"));
	printf("%d\n%d\n%d\n",strcmp("abc","abd"), strcmp("abc","ab"),strcmp(b,c));
	printf("%d\n%d\n%d\n",StrCmp("abc","abd"), StrCmp("abc","ab"),StrCmp(b,c));
	return 0;
}
