#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_mutex_lock pthread_mutex_t pthread_create pthread_join */
#include <errno.h> /* perror */
#include <semaphore.h>/*  */

#include "slist.h"

#define NUM_PRODUCERS 2

#define NUM_CONSUMERS 2

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*
Reviewer: Yahav
*/

/*
data sent to the threads instead of using global vars
*/
typedef struct argument
{
	int producers;
	int consumers;
	s_list_t *queue;
	size_t product;
} argument_t;

void *Consumer(argument_t *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		
		if(NULL != SListGet(arg->queue, SListBegin(arg->queue)))
		{
			printf("Consumer got: %ld\n",(size_t) SListGet(arg->queue, SListBegin(arg->queue)));
			
			SListRemove(arg->queue, SListBegin(arg->queue));
			
			break;
		}
	
		pthread_mutex_unlock(&lock);
		
	}
	
	--arg->consumers;
	
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

void *Producer(argument_t *arg)
{
	pthread_mutex_lock(&lock);
	
	printf("Producer put: %ld\n", arg->product);
	
	if(NULL == SListAdd(arg->queue, SListEnd(arg->queue), (void*)arg->product++))
	{
		return arg;
	}
	
	--arg->producers;
	
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

int main()
{
	pthread_t id = {0};
	
	pthread_attr_t attr = {0};
	
	/* container to data used by threads */
	argument_t arg;
	
	arg.producers = 0;
	arg.consumers = 0;
	arg.product = 1;
	
	if(pthread_attr_init(&attr))
	{
		return 1;
	}
	
	/* set threads to detached so we dont have to join them */
	if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
	{
		return 1;
	}
		
	if(NULL == (arg.queue = SListCreate()))
	{
		return 1;
	}
	
	while(1)
	{
		/* for every consumer we lost we create a new one */
		while(arg.consumers < NUM_CONSUMERS)
		{
			if(0 != pthread_create(&id, &attr, (void *(*)(void*))(Consumer), &arg))
			{
				perror(NULL);
				continue;
			}
			
			++arg.consumers;
		}
		
		/* for every producers we lost we create a new one */
		while(arg.producers < NUM_PRODUCERS)
		{
			if(0 != pthread_create(&id, &attr, (void *(*)(void*))(Producer), &arg))
			{
				perror(NULL);
				continue;
			}
			
			++arg.producers;
		}
		
	}
	
	SListDestroy(arg.queue);
	return 0;
}
