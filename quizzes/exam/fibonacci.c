#include <stdio.h>

unsigned long GetNFibonacciElement(unsigned int n)
{
	if(n <= 2)
	{
		return 1;
	}
	
	return GetNFibonacciElement(n - 1) + GetNFibonacciElement(n - 2);
}

int main()
{
	printf("fibonacci index 6 should be 8: %ld\n", GetNFibonacciElement(6));
	return 0;
}
