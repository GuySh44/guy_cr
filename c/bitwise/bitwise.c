#include"bitwise.h"

/* reviewer: raz */
long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}



int IsPow2A(unsigned int n)
{
	unsigned int count = 2;
	while (n)			/* n is not 0 */
	{
		if (n & 1)              /* n LSB is 1 */
		{
			count >>= 1;    /* divide count by 2 */
		}
		n >>= 1;		/* continue running on n */
	}
	return (count & 1);		/* is count != 1? */
}

int IsPow2B(unsigned int n)
{
	
}


/* reviewer: raz */
int AddOne(int n)
{
	int check_one = 1;		/*binary one for checking each bit in n */
	while (n & check_one)		/* check if next bit is 1 */
	{
		n ^= check_one;		/* turn next bit 0 */
		check_one <<= 1;	/* move checker one bit left */
	}
	n = n ^ check_one;		/* turn the first zero we see in n into one */
	return n;
}

/* reviewer: raz */
void PrintThreeBits(unsigned int * array, size_t arr_size)
{
	unsigned int * finish = array + arr_size;		/* end of array */
	printf("Three bits on:\n");
	for (;array != finish; array++)				/* running on array */
	{
		unsigned int n = *array;			
		unsigned int count = 8;				/* for counting 3 times */
		while (n)					/* n is not 0 */
		{
			if (n & 1)				/* if n LSB is 1 */
			{
				count >>= 1;			/* divide count by 2 */
			}
			n >>= 1;				/* divide n by 2 */
		}
		if (count & 1)					/* if count = 1 */
		{
			printf("%u  ",*array);	
		}
	}
	printf("\n");
	
}





