#include"bitwise.h"

/* reviewer: raz */
long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}


/* reviewer: or */
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
	return ((n) && !(n & (n-1))); /* if n = 0 return 0, otherwise if n is power of 2, n and n-1 share no same bits only works when n >= 0 */
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
	assert(NULL != array);
	assert(arr_size != 0);
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

/* reviewer: raz */
void ByteMirrorLoop(unsigned char byte)
{
	unsigned char mirror = 0, byte_index = 1, mirror_index = 1 , count = 1;
	mirror_index <<= 7;							/* indexes are "1's" at different bits throughout a variable and i use them to "work" on seperate parts of the variable */
	count <<= 7;								/* 1 at MSB used as counter, logical rotation right decrements it */						
	while (count)
	{
		if (byte & byte_index)						/* if byte at byte_index is 1 change mirror to 1 at mirrored spot */
		{
			mirror ^= mirror_index;
		}
	byte_index <<= 1;							/* move everything to the right place for next iteration */
	mirror_index >>= 1;
	count >>= 1;
	}
	printf("mirror\t%d\n", mirror);
}

/* reviewer: raz */
void ByteMirrorNoLoop(unsigned char byte)
{
const unsigned char TableBitReverse[256] = 
					{
					  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
					  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
					  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
					  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
					  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
					  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
/*   LUT :)    */			  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
					  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
					  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
					  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
					  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
					  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
					  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
					  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
					  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
					  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
					};
	printf("mirror\t%d\n", TableBitReverse[byte]);
}

/* reviewer: raz */
int NoIfTwoAndSix(unsigned char byte)
{
	int flag1 = 0, flag2 = 0;
	flag1 = 1 & (byte >> 1);
	flag2 = 1 & (byte >> 5);
	return (flag1 & flag2);
}

int NoIfTwoOrSix(unsigned char byte)
{
	int flag1 = 0, flag2 = 0;
	flag1 = 1 & (byte >> 1);
	flag2 = 1 & (byte >> 5);
	return (flag1 | flag2);
}

unsigned char SwapThirdFifth(unsigned char byte)
{
	unsigned char bit_1 = (byte >> 2) & 1;			/* get 3rd bit */
	unsigned char bit_2 = (byte >> 4) & 1;			/* get 5th bit */
	unsigned char xor_of_bit = bit_1 ^ bit_2;		/* are they different */
	return (byte ^ (xor_of_bit << 2 | xor_of_bit << 4));	/* if different xor 1 with them, else do nothing */
}


/* reviewer: raz */
unsigned int CloseSixteen(unsigned int num)
{
	num >>= 4;
	return num<<4;
}

/* reviewer: raz */
/* when adding both vars we might overflow the memory containing one var and lose data */
void SwapBitwise(size_t* var1, size_t* var2)
{		
	assert (NULL != var1);
	assert (NULL != var2);
	*var1 ^= *var2;			/* add both vars into var1 */
	*var2 ^= *var1;			/* sub var1 from both vars */
	*var1 ^= *var2;			/* sub var2 from both vars */
}

/* reviewer: raz */
int SetBitsCountA(int num)
{
	unsigned int unsigned_num = (unsigned int) num;
	int count = 0;
	while(unsigned_num)
	{
		if(unsigned_num & 1)		/* while num != 0 check if LSB is 1 and if so increment count, "increment" num */
		{
			count++;
		}
		unsigned_num >>= 1;
	}
	return count;
}

/* reviewer: raz */
int SetBitsCountB(int num)
{
	unsigned int unsigned_num = (unsigned int) num;
	int table[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
			  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
			  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
/*   LUT :)    */	  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
			  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			  4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};
			  
			  
	int count = table[unsigned_num & 0xff];   					/* check num of set bits in first 8 bits 0xff = 11111111 */
	unsigned_num = unsigned_num >> 8;								/* move bits 9-16 to spots 1-8 */
	count += table[unsigned_num & 0xff];						/* add number of set bits there, and so on... */
	unsigned_num = unsigned_num >> 8;
	count += table[unsigned_num & 0xff];
	unsigned_num = unsigned_num >> 8;
	count += table[unsigned_num & 0xff];
	return count;
} 


/* reviewer: or */
void PrintFloatBinary(float num)
{
	int* read_as_int = (int *)&num;			/* read 32 bits as int for bitwise functionality */
	int int_num = *read_as_int;			/* run through the integer and print its bits */
	unsigned int index = 1;
	index <<= 31;
	printf("%f in binary is:\n", num);
	while (index)
	{
		printf("%d ", 1 && (int_num & index));
		index >>= 1;
	}
	printf("\n");
}


