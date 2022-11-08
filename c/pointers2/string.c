#include<string.h>
#include<stddef.h>

char *StrCpy(char *dest, const char *src)
{
	size_t i=0;
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
	
}
