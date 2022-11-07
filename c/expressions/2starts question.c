#include <stdio.h>
	int a = 3;
	int foo(){}
int main()
{
	int (*b)() = foo;
	int (*c)() = &foo;
	foo = b;
	&foo = c; 
	printf("%p \n",foo);
	printf("%p \n",&foo);
}
