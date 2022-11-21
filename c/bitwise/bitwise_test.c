
#include"bitwise.h"


int main()
{
	unsigned int three_bits[10] = {0, 1, 7, 11, 8, 65, 33, 1029, 55, 12};
	printf("5 times 2^4\t%ld\n",Pow2((unsigned int)5,(unsigned int)4));

	printf("is 3 a power of 2?\t%d\n",IsPow2A((unsigned int) 3));	
	printf("is 8 a power of 2?\t%d\n",IsPow2A((unsigned int) 8));	
	printf("is 128 a power of 2?\t%d\n",IsPow2A((unsigned int) 128));
	printf("is 256 a power of 2?\t%d\n",IsPow2A((unsigned int) 256));
	printf("is 512 a power of 2?\t%d\n",IsPow2A((unsigned int) 512));
	printf("is 1024 a power of 2?\t%d\n",IsPow2A((unsigned int) 1024));
	
	
	printf("add 1 to 0\t%d\n",AddOne(0));
	printf("add 1 to 5\t%d\n",AddOne(5));
	printf("add 1 to -10\t%d\n",AddOne(-10));
		
	PrintThreeBits(three_bits, 10);

	return 0;
}
