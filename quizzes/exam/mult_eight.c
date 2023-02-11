#include <stdio.h>

long MultEight(int num)
{
	long res = num;
	return res << 3;
}

int main()
{
	printf("1 mult by 8 should be 8: %ld\n", MultEight(1));
	printf("2 mult by 8 should be 16: %ld\n", MultEight(2));
	
	return 0;
}
