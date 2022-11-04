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

int main()
{
	ten_pow(-3);
}
