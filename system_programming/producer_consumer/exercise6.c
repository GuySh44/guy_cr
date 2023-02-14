#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_mutex_lock pthread_mutex_t pthread_create pthread_join  pthread_attr_setdetachstate*/
#include <errno.h> /* perror */
#include <semaphore.h>/* sem_init sem_t sem_destroy sem_post sem_wait */


#define NUM_PRODUCERS 1

#define NUM_CONSUMERS 50

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*
Reviewer: Iaab
*/
typedef struct argument
{
	size_t consumer_amount;
	size_t counter;
	pthread_cond_t cond_var;
	int resource;
	sem_t sem;
} argument_t;


void *Consumer(argument_t *arg)
{
	/* wait on semaphore until producer writes */	
	if(-1 == sem_wait(&arg->sem))
	{
		return arg;
	}
	
	/* make sure each consumer reads alone */
	pthread_mutex_lock(&lock);

	/* count number of threads that read */
	++arg->counter;

	printf("resource:%d\tcounter:%lu\n", arg->resource, arg->counter);
	
	/* if all consumers read, free cond variable */
	if(NUM_CONSUMERS == arg->counter)
	{
		pthread_cond_signal(&arg->cond_var);
	}
		
	pthread_mutex_unlock(&lock);

	return NULL;
}


void *Producer(argument_t *arg)
{
	int sval = 0;
	/* lock before writing */
	pthread_mutex_lock(&lock);

	arg->resource = 1;
	
	/* free all consumers to ask lock */
	do
	{
		if(-1 == sem_post(&arg->sem))
		{
			return arg;
		}
		if(-1 == sem_getvalue(&arg->sem, &sval))
		{
			return arg;
		}
	}
	while(sval != NUM_CONSUMERS);
	
	printf("Producer about to wait\n");

	/* wait on cond_var which is consumer count */
	if(NUM_CONSUMERS  != arg->counter)
	{
		pthread_cond_wait(&arg->cond_var, &lock);
	}
	
	printf("Producer finishing\n");
	
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

int main()
{
	pthread_t ids[NUM_CONSUMERS+NUM_PRODUCERS] = {0};
	
	size_t i = 0;
		
	/* container to data used by threads */
	argument_t arg;

	arg.resource = 0;
	
	arg.counter = 0;
	
	arg.consumer_amount = NUM_CONSUMERS;
	
	if(-1 == sem_init(&arg.sem, 0, 0))
	{
		return 1;
	}
	
	if(0 != pthread_cond_init(&arg.cond_var, NULL))
	{
		return 1;
	}
	
		
	for(i = 0; i < NUM_CONSUMERS; ++i)
	{
		if(0 != pthread_create(&ids[i], NULL, (void *(*)(void*))(Consumer), &arg))
		{
			perror(NULL);
			continue;
		}
		
	}
	
	for(i = NUM_CONSUMERS; i < NUM_PRODUCERS + NUM_CONSUMERS; ++i)
	{
		if(0 != pthread_create(&ids[i], NULL, (void *(*)(void*))(Producer), &arg))
		{
			perror(NULL);
			continue;
		}
		
	}

		
	for(i = 0; i < NUM_CONSUMERS + NUM_PRODUCERS; ++i)
	{
		pthread_join(ids[i], NULL);
	}


	if(-1 == sem_destroy(&arg.sem))
	{
		return 1;
	}
	
	if(0 != pthread_cond_destroy(&arg.cond_var))
	{
		return 1;
	}
	return 0;
}