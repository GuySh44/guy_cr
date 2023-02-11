#include <stdio.h>

short CountBits(unsigned char byte)
{
	short count = 0;
	
	while(byte)
	{
		byte &= byte -1;
		++count;
	}
	
	return count;
}

int main()
{
	printf("On bits in 7 should be 3: %hu\n", CountBits((unsigned char)7));
	printf("On bits in 5 should be 2: %hu\n", CountBits((unsigned char)5));
	printf("On bits in 3 should be 2: %hu\n", CountBits((unsigned char)3));
	return 0;
}
