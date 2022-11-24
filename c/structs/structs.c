#include"structs.h"

static char* intToString(int num)
{
	int tmp_num = num;
	char* new_string;
	int num_digits = 1;
	while(tmp_num > 9)
	{
		tmp_num /= 10;
		++num_digits;
	}
	new_string = (char*)malloc(num_digits + 1);
	if(NULL == new_string)
	{
		return NULL;
	}
	if(!num)
	{
		new_string[0] = '0';
		new_string[1] = '\0';
		return new_string;
	}
	new_string[num_digits] = '\0';
	while(num_digits)
	{
		new_string[num_digits - 1] = DIGIT_ADD + num % 10;
		--num_digits;
		num /= 10;
	}
	return new_string;
}

void cleanInt(void* data)
{
	free((int*)data);
}

void cleanFloat(void* data)
{
	free((float*)data);
}

void cleanString(void* str)
{
	free(*((char**)str));
}

void addInt(void *data ,int num)
{
	*((int*)data) += num;
}

void addFloat(void *data, int num)
{
	*((float*)data) += num;
}

void addString(void *data, int num)
{
	size_t new_string_size = 0;
	char* new_string = NULL;
	char *str_to_add = intToString(num);
	if(NULL == str_to_add)
	{
		return;
	}
	new_string_size = strlen(*((char**)data))+ strlen(str_to_add);
	new_string = (char*)calloc(new_string_size + 1, sizeof(char));
	if(NULL == new_string)
	{
		free(str_to_add);
		return;
	}
	new_string[new_string_size] = '\0';
	strcat(new_string, *((char**)data));
	strcat(new_string, str_to_add);
	free(*((char**)data));
	*((char**)data) = new_string;
	free(str_to_add);
}

void printInt(void *data)
{
	printf("Element is: %d\n", *((int*)data));
}

void printFloat(void *data)
{
	printf("Element is: %f\n", *((float*)data));
}

void printString(void *data)
{
	printf("Element is: %s\n", *((char**)data));
}


