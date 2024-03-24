#include <stddef.h>
#include <stdio.h>

size_t MillionChars(char ch)
{
	static size_t lut[256];
	if(ch == '0')
	{
		int i = 0;
		int max_i = (int)'0';
		size_t max = 0;
		for(; i < 256; ++i)
		{
			if(lut[i] > lut[max_i])
			{
				max = lut[i];
				max_i = i;
			}
		}
		i = 0;
		for(; i < 256; ++i)
		{
			lut[i] = 0;
		}
		return max;
	}
	++lut[(int)ch];
	return 0;
}

int SetBits(long num)
{
	int count = 0;
	while (num != 0)
	{
		num = (num) & (num - 1);
		++count;
	}
	return count;
}

int main()
{
	printf("MillionChars start:\n");
	MillionChars('a');
	MillionChars('b');
	MillionChars('c');
	MillionChars('d');
	MillionChars('a');
	MillionChars('q');
	MillionChars('e');
	MillionChars('a');
	MillionChars('a');
	printf("We should see 4 as result:\t%lu\n",MillionChars('0'));
	MillionChars('a');
	MillionChars('b');
	MillionChars('c');
	MillionChars('d');
	MillionChars('b');
	MillionChars('q');
	MillionChars('e');
	MillionChars('b');
	printf("We should see 3 as result:\t%lu\n",MillionChars('0'));
	printf("SetBits 1100000\t%d\n", SetBits(96));	
	printf("SetBits 1100001\t%d\n", SetBits(97));
	return 0;
}

