#include"atoi_itoa.h"

void intToString(int num, char *str, int base)
{
	int i;
	int neg_flag = 0;
	long big_num = num;
	long tmp_num = num;
	int digit_count = 0;
	assert(NULL != str);
	assert(base > 1 && base < 36);
	if(num < 0)
	{
		neg_flag = 1;
		big_num *= -1;
	}
	do 
	{
		++digit_count;
		tmp_num /= base;
	}
	while (0 != tmp_num);
	
	i = digit_count + neg_flag - 1;
	
	for(; i > -1 + neg_flag; --i)
	{
	    int rem = big_num % base;
		str[i] = (char)((rem > 9)? (rem-10) + 'a' : rem + '0');
		big_num /= base;
	}
	if (neg_flag)
	{
		str[0] = '-';
	}
	str[digit_count+neg_flag] = '\0';
}

int stringToInt(char *str, int base)
{
	char *str_num_start;
	int base_pow = 1;
	int neg_flag = 0;
	int res = 0;
	int dig_extend = 0;
	assert(NULL != str);
	assert(base > 1 && base < 36);
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
	dig_extend = (base > 10) ? 9 : base;
	while (('0' <= (*(str_num_start + 1)) && ((*(str_num_start + 1)) < '0' + dig_extend)) ||
	 ('a' <= *(str_num_start + 1) && *(str_num_start + 1) < ('a' + base - 11)))
	{
		base_pow *= base;
		++str_num_start;
	}
	while (('0' <= (*(str)) && ((*(str)) < '0' + dig_extend)) || ('a' <= *str && *str <= ('a' + base - 11)))
	{
		assert(isalnum(*str));
		if(isdigit(*(str)))
		{
			res = res + ((*str) - '0') * base_pow;
		}
		else
		{
			res = res + ((*str) - 'a' + 10) * base_pow;
		}
		base_pow /= base;
		++str;
	}
	if (neg_flag)
	{
		res *= -1;
	}
	return res;
}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



void appearsTwo(char *arr1, int arr1_size, char *arr2, int arr2_size, char *arr3, int arr3_size)
{
	int LUT[256] = {0};
	int i = 0;
	printf("What chars appear in first and second but not third?\n");
	for(; i < arr1_size; ++i)
	{
		LUT[(int)arr1[i]] = 1;
	}
	i = 0;
	for(; i < arr3_size; ++i)
	{
		LUT[(int)arr3[i]] = 0;
	}
	i = 0;
	for(; i < arr2_size; ++i)
	{
		if(LUT[(int)arr2[i]])
		{
			printf("%c\t",arr2[i]);
		}
	}
	printf("\n");
}




































