#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_mutex_lock pthread_mutex_t pthread_create pthread_join  pthread_attr_setdetachstate*/
#include <errno.h> /* perror */
#include <semaphore.h>/* sem_init sem_t sem_destroy sem_post sem_wait */

#include "queue.h"

#define NUM_PRODUCERS 20

#define NUM_CONSUMERS 20

#define QUEUE_SIZE 8

#define RUN_TIMES 100

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
	queue_t *queue;
	int *product;
	size_t i;
	sem_t sem_cur;
	sem_t sem_max;
} argument_t;


void *Consumer(argument_t *arg)
{
	/* wait on available data */
	if(-1 == sem_wait(&arg->sem_cur))
	{
		return arg;
	}
	
	/* lock before read and dequeue */
	pthread_mutex_lock(&lock);
		
	printf("Consumer got: %d\n",*((int*) QueuePeek(arg->queue)));
	
	QueuePop(arg->queue);	
	
	--arg->consumers;
	
	/* free producing action */
	if(-1 == sem_post(&arg->sem_max))
	{
		return arg;
	}
	
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

void *Producer(argument_t *arg)
{
	
	/* wait on empty space in queue */
	if(-1 == sem_wait(&arg->sem_max))
	{
		return arg;
	}
	
	/* lock for enqueue */
	pthread_mutex_lock(&lock);
	
	printf("Producer put: %d\n", arg->product[arg->i]);
	
	QueuePush(arg->queue, arg->product + arg->i);
	
	
	--arg->producers;
	
	++arg->i;

	/* free consuming action */
	if(-1 == sem_post(&arg->sem_cur))
	{
		return arg;
	}
	
	pthread_mutex_unlock(&lock);
	
	return NULL;
}


int main()
{
	int products[RUN_TIMES];
	
	size_t i = 0;
	
	pthread_t ids[NUM_CONSUMERS+NUM_PRODUCERS] = {0};
	
		
	/* container to data used by threads */
	argument_t arg;
	
	arg.producers = 0;
	arg.consumers = 0;
	arg.product = products;
	arg.i = 0;
	
	
	if(-1 == sem_init(&arg.sem_cur, 0, 0))
	{
		return 1;
	}
	
	if(-1 == sem_init(&arg.sem_max, 0, QUEUE_SIZE))
	{
		return 1;
	}
	
	if(NULL == (arg.queue = QueueCreate(QUEUE_SIZE)))
	{
		return 1;
	}
	
	for(; i < RUN_TIMES; ++i)
	{
		products[i] = i;
	}
	
	
	for(i = NUM_CONSUMERS; i < NUM_PRODUCERS + NUM_CONSUMERS; ++i)
	{
		if(0 != pthread_create(&ids[i], NULL, (void *(*)(void*))(Producer), &arg))
		{
			perror(NULL);
			continue;
		}
		
		++arg.producers;
	}
	
	for(i = 0; i < NUM_CONSUMERS; ++i)
	{
		if(0 != pthread_create(&ids[i], NULL, (void *(*)(void*))(Consumer), &arg))
		{
			perror(NULL);
			continue;
		}
		
		++arg.consumers;
	}
	
		
	for(i = 0; i < NUM_CONSUMERS + NUM_PRODUCERS; ++i)
	{
		pthread_join(ids[i], NULL);
	}

	QueueDestroy(arg.queue);
	if(-1 == sem_destroy(&arg.sem_cur))
	{
		return 1;
	}
	if(-1 == sem_destroy(&arg.sem_max))
	{
		return 1;
	}
	
	pthread_exit(0);
}

