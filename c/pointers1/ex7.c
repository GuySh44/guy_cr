#include<stdio.h>
int main()
{
	unsigned int *ip = 0;
	float f = 3;
	float *fp = &f;
	ip = fp;
	printf("%u", *ip);
}
