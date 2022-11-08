#include"string.h"

char *StrCpy(char *dest, const char *src)
{
	size_t i = 0;
	while ((*(src+i)) != '\0')
	{
		(*(dest+i)) = (*(src+i));
		i++;
	}
	(*(dest+i)) = (*(src+i));
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
