#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create pthread_join */
#include <errno.h> /* perror */

#define NUM_THREADS 2

/*
Reviewer: Yahav
*/

/*
data sent to the threads instead of using global vars
*/
typedef struct argument
{
	int produce;
	int element;
} argument_t;

/*
busy waiting on produce value
*/
void *Consumer(argument_t *arg)
{
	
	while(1)
	{
		while(arg->produce){};
	
		printf("element value:%d\n", arg->element);
		
		arg->produce = 1;
		
	}
	return NULL;
}

/*
busy waiting on produce value
*/
void *Producer(argument_t *arg)
{
	while(1)
	{
		while(!arg->produce){};
		
		++arg->element;
		
		arg->produce = 0;
	}
	return NULL;
}

int main()
{
	int i = 0;
	pthread_t ids_array[NUM_THREADS];
	
	/* container to data used by threads */
	argument_t arg;
	
	arg.produce = 1;
	arg.element = 0;
	
	if(0 != pthread_create(&ids_array[0], NULL, (void *(*)(void*))Consumer, &arg))
	{
		perror(NULL);
	}
	
	if(0 != pthread_create(&ids_array[1], NULL, (void *(*)(void*))Producer, &arg))
	{
		perror(NULL);
	}
	
	
	for(i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(ids_array[i], NULL);
	}
	
	return 0;
}

