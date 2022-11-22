#include"bitwise.h"


int main()
{
	size_t var1_swap = 3, var2_swap = 5, var3_swap = 0, var4_swap = 7, var5_swap = 4, var6_swap = 4, var7_swap = -5, var8_swap = 106;
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
	
	printf("Closest 16 multiplier to 5\t%d\n",CloseSixteen(5));
	printf("Closest 16 multiplier to 32\t%d\n",CloseSixteen(32));
	printf("Closest 16 multiplier to 33\t%d\n",CloseSixteen(33));
	printf("Closest 16 multiplier to 40\t%d\n",CloseSixteen(40));
	printf("Closest 16 multiplier to 49\t%d\n",CloseSixteen(49));
	printf("Closest 16 multiplier to 165\t%d\n",CloseSixteen(165));
	printf("Closest 16 multiplier to 180\t%d\n",CloseSixteen(180));

	
	printf("var1 before swap:\t%lu\nvar2 before swap:\t%lu\n",var1_swap,var2_swap);
	SwapBitwise(&var1_swap, &var2_swap);
	printf("var1 after swap:\t%lu\nvar2 after swap:\t%lu\n",var1_swap,var2_swap);
	printf("var3 before swap:\t%lu\nvar4 before swap:\t%lu\n",var3_swap,var4_swap);
	SwapBitwise(&var3_swap, &var4_swap);
	printf("var3 after swap:\t%lu\nvar4 after swap:\t%lu\n",var3_swap,var4_swap);
	printf("var5 before swap:\t%lu\nvar6 before swap:\t%lu\n",var5_swap,var6_swap);
	SwapBitwise(&var5_swap, &var6_swap);
	printf("var5 after swap:\t%lu\nvar6 after swap:\t%lu\n",var5_swap,var6_swap);
	printf("var7 before swap:\t%lu\nvar8 before swap:\t%lu\n",var7_swap,var8_swap);
	SwapBitwise(&var7_swap, &var8_swap);
	printf("var7 after swap:\t%lu\nvar8 after swap:\t%lu\n",var7_swap,var8_swap);
	
	printf("Loop set bits count 00000000\t%d\n",SetBitsCountA(0));
	printf("Loop set bits count 00000010\t%d\n",SetBitsCountA(2));
	printf("Loop set bits count 00000011\t%d\n",SetBitsCountA(3));
	printf("Loop set bits count 00100000\t%d\n",SetBitsCountA(32));
	printf("Loop set bits count 00100010\t%d\n",SetBitsCountA(34));
	printf("Loop set bits count 00100011\t%d\n",SetBitsCountA(35));
	printf("Loop set bits count 11111111\t%d\n",SetBitsCountA(255));
	
	printf("No Loop set bits count 00000000\t%d\n",SetBitsCountB(0));
	printf("No Loop set bits count 00000010\t%d\n",SetBitsCountB(2));
	printf("No Loop set bits count 00000011\t%d\n",SetBitsCountB(3));
	printf("No Loop set bits count 00100000\t%d\n",SetBitsCountB(32));
	printf("No Loop set bits count 00100010\t%d\n",SetBitsCountB(34));
	printf("No Loop set bits count 00100011\t%d\n",SetBitsCountB(35));
	printf("No Loop set bits count 11111111\t%d\n",SetBitsCountB(255));
	
	PrintFloatBinary(0);
	PrintFloatBinary(5);
	PrintFloatBinary(-4);
	PrintFloatBinary(1.23);
	PrintFloatBinary(-55.66);
	
	return 0;
}
