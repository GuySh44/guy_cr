#include <stdio.h>

int FlipBit(int val, unsigned int n)
{
	int index = 1;
	
	index <<= n;
	
	return val ^ index;
}

int main()
{
	int i = 1;
	printf("1 after flipping second bit should be 3: %d\n", FlipBit(i, 1));
	
	return 0;
}
