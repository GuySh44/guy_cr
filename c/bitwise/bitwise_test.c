
#include"bitwise.h"


int main()
{
	unsigned int three_bits[10] = {0, 1, 7, 11, 8, 65, 33, 1029, 55, 12};
	printf("5 times 2^4\t%ld\n",Pow2((unsigned int)5,(unsigned int)4));

	printf("is 0 a power of 2? check B\t%d\n",IsPow2A((unsigned int) 0));	
	printf("is 3 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 3));	
	printf("is 8 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 8));	
	printf("is 9 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 9));	
	printf("is 128 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 128));
	printf("is 256 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 256));
	printf("is 512 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 512));
	printf("is 1024 a power of 2? check A\t%d\n",IsPow2A((unsigned int) 1024));
	
	printf("is 0 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 0));	
	printf("is 3 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 3));	
	printf("is 8 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 8));
	printf("is 9 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 9));		
	printf("is 128 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 128));
	printf("is 256 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 256));
	printf("is 512 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 512));
	printf("is 1024 a power of 2? check B\t%d\n",IsPow2B((unsigned int) 1024));
	
	
	printf("add 1 to 0\t%d\n",AddOne(0));
	printf("add 1 to 5\t%d\n",AddOne(5));
	printf("add 1 to -10\t%d\n",AddOne(-10));
		
	PrintThreeBits(three_bits, 10);
	
	printf("loop mirror 00000001\n");
	ByteMirrorLoop(1);
	printf("loop mirror 00000010\n");
	ByteMirrorLoop(2);
	printf("loop mirror 00010000\n");
	ByteMirrorLoop(16);
	printf("loop mirror 01101001\n");
	ByteMirrorLoop(105);
	
	
	printf("no loop mirror 00000001\n");
	ByteMirrorNoLoop(1);
	printf("no loop mirror 00000010\n");
	ByteMirrorNoLoop(2);
	printf("no loop mirror 00010000\n");
	ByteMirrorNoLoop(16);
	printf("no loop mirror 01101001\n");
	ByteMirrorNoLoop(105);


	printf("two and six 00000000\t%d\n",NoIfTwoAndSix(0));
	printf("two and six 00000010\t%d\n",NoIfTwoAndSix(2));
	printf("two and six 00000011\t%d\n",NoIfTwoAndSix(3));
	printf("two and six 00100000\t%d\n",NoIfTwoAndSix(32));
	printf("two and six 00100010\t%d\n",NoIfTwoAndSix(34));
	printf("two and six 00100011\t%d\n",NoIfTwoAndSix(35));
	printf("two and six 11111111\t%d\n",NoIfTwoAndSix(255));
	
	printf("two or six 00000000\t%d\n",NoIfTwoOrSix(0));
	printf("two or six 00000010\t%d\n",NoIfTwoOrSix(2));
	printf("two or six 00000011\t%d\n",NoIfTwoOrSix(3));
	printf("two or six 00100000\t%d\n",NoIfTwoOrSix(32));
	printf("two or six 00100010\t%d\n",NoIfTwoOrSix(34));
	printf("two or six 00100011\t%d\n",NoIfTwoOrSix(35));
	printf("two or six 11111111\t%d\n",NoIfTwoOrSix(255));
	
	printf("third to fifth 00000000\t%d\n",SwapThirdFifth(0));
	printf("third to fifth 00000101\t%d\n",SwapThirdFifth(5));
	printf("third to fifth 00010001\t%d\n",SwapThirdFifth(17));
	printf("third to fifth 00010101\t%d\n",SwapThirdFifth(21));
	printf("third to fifth 11111111\t%d\n",SwapThirdFifth(255));
	return 0;
}
