#include"atoi_itoa.h"

void intToString(int num, char *str)
{
	int i;
	int neg_flag = 0;
	long big_num = num;
	long tmp_num = num;
	int digit_count = 0;
	if(num < 0)
	{
		neg_flag = 1;
		big_num *= -1;
	}
	do 
	{
		++digit_count;
		tmp_num /= 10;
	}
	while (0 != tmp_num);
	
	i = digit_count + neg_flag - 1;
	
	for(; i > -1 + neg_flag; --i)
	{
		str[i] = (char)((big_num % 10) + '0');
		big_num /= 10;
	}
	if (neg_flag)
	{
		str[0] = '-';
	}
	str[digit_count+neg_flag] = '\0';
}

int stringToInt(char *str)
{
	char *str_num_start;
	int ten_pow = 1;
	int neg_flag = 0;
	int res = 0;
	while(isspace(*str))
	{
		++str;
	} 
	if(*str == '-')
	{
		neg_flag = 1;
		++str;
	}
	else if (*str == '+')
	{
		++str;
	}
	str_num_start = str;
	while (isdigit(*(str_num_start + 1)))
	{
		ten_pow *= 10;
		++str_num_start;
	}
	while (isdigit(*(str)))
	{
		res = res + ((*str) - '0') * ten_pow;
		ten_pow /= 10;
		++str;
	}
	if (neg_flag)
	{
		res *= -1;
	}
	return res;
}








