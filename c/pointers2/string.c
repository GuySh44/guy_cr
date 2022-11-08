#include"string.h"
static int DIFF = 32;

size_t StrLen(const char* s)
{
	size_t i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return i;
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

int StrNcmp(const char *s1, const char *s2, size_t n)
{
	int j = 0;
	while (n > 0 && ((*(s1+j) != '\0' || (*(s2+j)) != '\0')))
	{
		if ((*(s1+j)) != (*(s2+j)))
			return (-1 + 2 * ((*(s1+j)) > (*(s2+j))));
		j++;
		n--;
	}
	return 0;
}

int StrCasecmp(const char *s1, const char *s2)
{
	int j = 0;
	while ((*(s1+j)) != '\0' || (*(s2+j)) != '\0')
	{
		char tmp_s1 = (*(s1+j));
		char tmp_s2 = (*(s2+j));
		if (tmp_s1 >= 'A' && tmp_s1 <= 'Z')
			tmp_s1 += DIFF;	
		if (tmp_s2 >= 'A' && tmp_s2 <= 'Z')
			tmp_s2 += DIFF;
		if (tmp_s1 != tmp_s2)
			return (-1 + 2 * (tmp_s1 > tmp_s2));
		j++;
	}
	return 0;
}

char *StrChr(const char *s, int c)
{
	int i = 0;
	while ((*(s+i)) != (char)c)
	{
		if ((*(s+i)) == '\0')
			return NULL;
		i++;
	}
	return ((char*)(s+i));
}



