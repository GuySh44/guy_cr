#include <stdio.h>
#include <stdlib.h>

int IntToString(int num, void *str_buf)
{
	short neg_flag = 0, digit_count = 1, i = 0;
	int temp_num = 0;
	char *temp_str = NULL;
	
	if(num < 0)
	{
		num *= -1;
		neg_flag = 1;
	}
	
	temp_num = num;
	while(temp_num > 9)
	{
		++digit_count;
		temp_num /= 10;
	}
	
	temp_str = (char*)malloc(digit_count + neg_flag + 1);
	
	if(NULL == temp_str)
	{
		return 1;
	}
	
	if(neg_flag)
	{
		*temp_str = '-';
	}
	
	temp_str[digit_count + neg_flag] = '\0';
	
	temp_num = num;
	
	for(; i < digit_count; ++i)
	{
		temp_str[digit_count + neg_flag - 1 - i] = '0' + (temp_num % 10);
		temp_num /= 10;
	}
	
	sprintf(str_buf, temp_str);
	
	free(temp_str);
	
	return 0;
}

int main()
{
	char str[8] = {0};
	IntToString(-123, str);
	printf("-123 to string: %s\n", str);
	return 0; 
}
