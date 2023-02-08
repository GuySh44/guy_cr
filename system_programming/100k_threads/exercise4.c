#include <pthread.h> /* pthread_create pthread_join */
#include <stdio.h> /* printf */
#include <errno.h>

/*
Reviewer: Yarin
*/

#define NUM_THREADS 20000

/*
time stats:
real	0m13.126s
user	1m38.287s
sys		0m1.166s
*/

static size_t chunk_size = 0;

static size_t number = 7777777777;


/* thread function */
void *SumDivisors(void *start)
{
	size_t sum_of_divisors = 0;
	size_t times = chunk_size;
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
	pthread_t ids_array[NUM_THREADS];
	size_t i = 0;
	size_t sum = 0;
	size_t remainder = 0;
	size_t *sum_ret = NULL;
	
	chunk_size = number / NUM_THREADS;
	
	remainder = number % NUM_THREADS;
	
	for(; i < NUM_THREADS - 1; ++i)
	{
		while(0 != pthread_create(ids_array + i, NULL, SumDivisors, (void*)(i*chunk_size)))
		{
			perror(NULL);
		}
		
	}
	
	chunk_size += remainder;
	pthread_create(ids_array + i, NULL, SumDivisors, (void*)((number/NUM_THREADS) * i));

	
	i = 0;
	
	for(; i < NUM_THREADS; ++i)
	{
		pthread_join(ids_array[i], (void**)&sum_ret);
		sum += (size_t)sum_ret;
	}
	
	printf("%lu\n", sum);
	
	return 0;
}
