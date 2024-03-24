#include <stdio.h>
#include <math.h>

double Sqrt(double number)
{
	double top = number;
	double bottom = 0;
	double mid = (top + bottom) / 2;
	while(mid * mid != number)
	{
		if(mid * mid > number)
		{
			top = mid;
		}
		else
		{
			bottom = mid;
		}
		mid = (bottom + top) / 2;
	}
	return mid;
}

int main()
{
	printf("my Sqrt of 25\t%f\n", Sqrt(25));
	printf("c Sqrt of 25\t%f\n", sqrt(25));
	printf("my Sqrt of 2.25\t%f\n", Sqrt(2.25));
	printf("c Sqrt of 2.25\t%f\n", sqrt(2.25));
	return 0;
}
