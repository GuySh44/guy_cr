#include <pthread.h> /* pthread_create */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <errno.h>

#define NUM_THREADS 20000

/*
time stats:
real	0m12.415s
user	0m0.657s
sys		0m2.774s

*/

static size_t size;

static size_t number = 222222222222;



void *SumDivisors(void *start)
{
	size_t sum_of_divisors = 0;
	size_t times = size;
	size_t i = 1 + (size_t)start;
	
    for(; times > 0; ++i, --times)
    {
          if (0 == number % i)
          {
              sum_of_divisors += i;
          }
    }
	return (void*)sum_of_divisors;
}


int main()
{
	pthread_t ids[NUM_THREADS + 1];
	size_t i = 0;
	unsigned long *ptr = NULL;
	unsigned long sum = 0;
	size_t remainder = 0;
	
	size = number / NUM_THREADS;
	
	remainder = number % NUM_THREADS;
	
	for(; i < NUM_THREADS; ++i)
	{
		while(0 != pthread_create(ids + i, NULL, SumDivisors, (void*)(i*size)))
		{
			perror(NULL);
		}
		
	}
	
	size = remainder;
	pthread_create(ids + i, NULL, SumDivisors, (void*)((number / NUM_THREADS)*NUM_THREADS));

	
	i = 0;
	
	for(; i < NUM_THREADS + 1; ++i)
	{
		pthread_join(ids[i], (void**)&ptr);
		sum += (unsigned long)ptr;
	}
	
	printf("%lu\n", sum);
	
	return 0;
}
