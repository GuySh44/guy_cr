#include"string.h"

size_t StrLen(const char* s)
{
	size_t count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return count;
}

char *StrCpy(char *dest, const char *src)
{
	size_t i = 0;
	while ((*(src+i)) != '\0')
	{
		(*(dest+i)) = (*(src+i));
		i++;
	}
	(*(dest+i)) = '\0';
	return dest;
}

char *StrNcpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;
	int flag = 0;
	for (;i < n; i++)
	{
		if ((*(src+i)) == '\0')
		{
			flag = 1;
			break;		
		}
		(*(dest+i)) = (*(src+i));
	}
	if (flag == 1)
	{
		while (i < n)
		{
			(*(dest+i)) = '\0';
			i++;
		}
	}	
	return dest;
}

int StrCmp(const char* s1, const char* s2)
{
	int j = 0;
	while ((*(s1+j)) != '\0' || (*(s2+j)) != '\0')
	{
		if ((*(s1+j)) != (*(s2+j)))
			return (-1 + 2 * ((*(s1+j)) > (*(s2+j))));
		j++;
	}
	return 0;
}
