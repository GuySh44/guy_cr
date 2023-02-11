#include <stdio.h>

char RotateLeft(char byte, unsigned int nbits)
{
	short carry = 0, index = 1 << 7;
	unsigned int i = 0;
	
	nbits = nbits % 8;
	
	for(; i < nbits; ++i)
	{
		carry = ((index & byte) != 0);
		byte <<= 1;
		byte |= carry;
	}
	
	return byte;
}

int main()
{
	printf("10000001 rotated once left should be 3: %d\n", (int)RotateLeft(-127, 1));
	return 0;
}
