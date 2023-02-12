#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* pthread_create */
#include <errno.h>

#define NUM_THREADS 3

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
const int con_glob_var = 23;
static const int con_glob_stat_var = 29;

void *Foo()
{
	char *malloced_three = malloc(3);
	short var = 9;
	const short con_var = 11;
	static short stat_var = 5;
	static const short con_stat_var = 17;
	char str[] = "dani el";
	char *literal = "string literal";
	const char *con_literal = "const string literal";
	printf("Dynamic explicit Library:\n");
	printf("heap var:\t%p\n", malloced_three);
	printf("local var:\t%p\n", &var);
	printf("const local var:\t%p\n", &con_var);
	printf("static local var:\t%p\n", &stat_var);
	printf("static const local var:\t%p\n", &con_stat_var);
	printf("string literal:\t%p\n", literal);
	printf("const string literal:\t%p\n", con_literal);
	printf("global var:\t%p\n", &glob_var);
	printf("global static var:\t%p\n", &glob_stat_var);
	printf("const global var:\t%p\n", &con_glob_var);
	printf("const static global var:\t%p\n", &con_glob_stat_var);
	printf("external function:\t%p\n", ExternFoo);
	printf("static function:\t%p\n", StatFoo);
	
	return NULL;
}

int main()
{
	pthread_t ids_array[NUM_THREADS];
	size_t i = 0;
	size_t *sum_ret = NULL;
	
	for(; i < NUM_THREADS; ++i)
	{
		while(0 != pthread_create(ids_array + i, NULL, Foo, NULL))
		{
			perror(NULL);
		}
		
	}
	
	for(i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(ids_array[i], (void**)&sum_ret);
	}
	
	return 0;
}
