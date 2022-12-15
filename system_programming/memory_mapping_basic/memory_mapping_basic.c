#include <stdio.h>
#include <stdlib.h>

static int StatFoo(int number)
{
	return number * 2;
}

long ExternFoo(long number)
{
	return number * 3;
}

int glob_var = 13;
static int glob_stat_var = 19;

int RecursiveFoo()
{
	char *malloced_three = malloc(3);
	short var = 9;
	static short static_var = 5;
	char *literal = "string literal";
	RecursiveFoo();
}

int main(int argc, char *argv[], char *envp[])
{
	RecursiveFoo();
	return 0;
}
