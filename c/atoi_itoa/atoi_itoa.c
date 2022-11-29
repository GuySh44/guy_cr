#include"atoi_itoa.h"

void intToString(int num, char *str)
{
	int neg_flag = 0;
	int i;
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
