#include<stdio.h>
double ten_pow(int n)
{
	int times;
	double result = 1, base;
	if (n < 0)
	{
		base = 0.1;
		times = -n;
	}
	else
	{
		base = 10;
		times = n;
	}	
	for(int i = 0; i < times; i++)
	{
		result *= base;
	}
	return result;
}

int int_length(int num)
{
	int count = 0;
	while (num / 10 != 0)
	{
	count++;
	num /= 10;
	}
	return count;
}

long int flipint(int num)
{
	int remainder = 0;
	long int new_num = 0;
	int tmp_num = num;
	while (tmp_num % 10 == 0)
		tmp_num /= 10;
	int count = int_length(tmp_num);
	while (tmp_num)
	{
		remainder = tmp_num % 10;
		new_num += remainder * ten_pow(count);
		count--;
		tmp_num /= 10;
	}
	return new_num;
}

int main(){
printf("%d\n", flipint(100500));
}

