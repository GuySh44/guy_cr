#include<stdio.h>

void swap(int* num1_p, int* num2_p)
{
	int tmp = *num1_p;
	*num1_p = *num2_p;
	*num2_p = tmp;
}

int main()
{
	int a = 2, b = 3;
	swap(&a,&b);
	printf("a val is: %d \nb val is: %d \n", a, b);
	return 0;
}
