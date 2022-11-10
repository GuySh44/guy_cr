#include"string.h"
static int DIFF = 32;
static size_t SIZE_RULE = 10;

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

char *StrDup(const char *s)
{
	size_t s_len = StrLen(s);
	char* new_s = malloc((s_len*sizeof(char))+1);
	if (new_s == NULL)
		return ((char*)NULL);
	StrCpy(new_s, s);
	new_s[s_len] = '\0';
	return new_s;
}

char *StrNcat(char *dest, const char *src, size_t n)
{
	char * dest_start = dest;
	while(*dest)
		dest++;
	assert(*dest == '\0');
	while (n > 0)
	{
		*dest = *src;
		if (*src == '\0')
			return dest_start;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return dest_start;
}

char *StrCat(char *dest, const char *src)
{
	char* dest_start = dest;
	while(*dest)
		dest++;
	assert(*dest == '\0');
	while (*src)
	{
		*dest =*src;
		src++;
		dest++;
	}
	*dest = '\0';
	return dest_start;
}

char *StrStr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return (char*)haystack;
	while(*haystack)
	{
		const char * tmp_hay = haystack;
		const char * tmp_needle = needle;
		while(tmp_hay[0] == tmp_needle[0])
		{
			if(*(++tmp_needle) == '\0')
				return (char*)haystack;
			tmp_hay++;
		}
		haystack++;
	}
	return (char*)NULL;
}

size_t StrSpn(const char *s, const char *accept)
{	
	int count = 0;
	int method_flag = 0;
	int dict[256] = {0};
	int found_flag = 1;
	if (StrLen(accept)>SIZE_RULE)
	{
		method_flag = 1;
	}	
	else
		method_flag = 2;
	switch (method_flag)
	{
		case 1:
			while(accept)
			{
				dict[(int)accept[0]] = 1;
				accept++;
			}		
			while(s)
			{
				if (!dict[(int)s[0]])
					return count;
				s++;
			}
			return count;
		break;
		
		case 2:
			while(s && found_flag)
			{
				found_flag = 0;
				while(accept)
				{
					if(s[0] == accept[0])
					{
						found_flag = 1;
						break;
					}
					accept++;
				}
				if(!found_flag)
					break;
				s++;
				count++;
			}
			return count;
		break;
	}
	return -1;
}

