#include <stdio.h>


int FlipDigitInNum(int num)
{
	short neg_flag = 0, digit_count = 0, i = 0;
	int temp_num = 0, res = 0;
	long mult = 1;
	
	if(num < 0)
	{
		num *= -1;
		neg_flag = 1;
	}
	
	temp_num = num;
	
	while(0 != temp_num)
	{
		++digit_count;
		mult *= 10;
		temp_num /= 10;
	}
	
	temp_num = num;
	
	for(; i < digit_count; ++i)
	{
		mult /= 10;
		res += (temp_num % 10) * mult;
		temp_num /= 10;
	}
	
	if(neg_flag)
	{
		res *= -1;
	}
	
	return res;
}

int main()
{
	printf("58: %d\n", FlipDigitInNum(58));
	printf("-520: %d\n", FlipDigitInNum(-520));
	
	return 0;
}
