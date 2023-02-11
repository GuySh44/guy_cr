#include <stdio.h>

char ByteMirror(unsigned char byte)
{
	unsigned char flip_index = 1 << 7, index = 1, res = 0;
	int i = 0;
	
	for(; i < 8; ++i)
	{
		if(flip_index & byte)
		{
			res |= index;
		}
		
		flip_index >>= 1;
		index <<= 1;
	}
	
	return res;
}

int main()
{
	printf("15 flipped byte is: %i\n", (unsigned int)ByteMirror((char)15));
	return 0;
}
