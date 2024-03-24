#include<stdio.h>
int setBits(unsigned char byte)
{
	int indexA = 1, indexB =2, i = 0, count = 0;
	for(;i < 7; ++i)
	{
		if(indexA & byte && indexB & byte)
		{
		++count;
		}
		indexA <<= 1;
		indexB <<= 1;
	}
	return count;
}

void swapA(int *num1, int *num2)
{
	int tmp = *num1;
	*num2 = *num1;
	*num2 = tmp;
}

void swapB(int *num1, int *num2)
{
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num2;
}

void swapC(int *num1, int *num2)
{
	*num1 = (*num1 & *num2) + (*num1 | *num2);
	*num2 = *num1 + (~*num2) + 1;	
	*num1 = *num1 + (~*num2) + 1;
}
int setBitsLoop(long num)
{
	int count = 0;
	printf("im about to looooop\n");
	while (num)
	{
		num = (num & (num - 1));
		++count;
		printf("I looped :)\n");
	}
	return count;
}

int main()
{
	printf("SetBits 01110110\t%d\n", setBits(118));
	printf("SetBits 01100110\t%d\n", setBits(102));

	printf("SetBitsLoop 1100000\t%d\n", setBitsLoop(96));	
	printf("SetBitsLoop 1100001\t%d\n", setBitsLoop(97));
	printf("11111110 >> 1\t%d\n", ((signed char)-2) >> 1);
	return 0;
}
