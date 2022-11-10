#include<stddef.h> /* size_t */
#include<stdio.h> /* printf */

size_t StrLen(const char* s)
{
	const char *start = s;
	while(*s++);
	return s-start-1;
}

int palindromeCheck(const char* s)
{
	size_t s_len = StrLen(s);
	const char* end = s + s_len - 1;
	while(end-s > 1)
	{
		if(*s++ != *end--)
			return 0;
	}
	return 1;
}

int main()
{
	printf("%d\n",palindromeCheck("abccba"));
	printf("%d\n",palindromeCheck("abc"));
	printf("%d\n",palindromeCheck("abxtltxba"));
	return 0;
}
