#include <assert.h>
#include <stdlib.h> /* malloc free */
#include <string.h> /* memcpy */

#include "queue.h"

struct queue
{
	size_t size;
	size_t capacity;
	int* base;
	int* top;
};

queue_t *QueueCreate(const size_t capacity)
{
	queue_t *new_queue = NULL;
	
	assert(capacity);
	
	new_queue = (queue_t*)malloc(sizeof(queue_t) + capacity * sizeof(int));
	if (NULL == new_queue)
	{
		return NULL;
	}
	
	new_queue->size = 0;
	new_queue->capacity = capacity;
	new_queue->base = (int*)((char*)new_queue + sizeof(struct queue));
	new_queue->top = new_queue->base;
	
	return new_queue;
}

int QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	free(queue);
	return 0;
}

void QueuePush(queue_t *queue , void *elem)
{
	void* base = NULL;
	
	assert(NULL != queue);
	assert(NULL != elem);
	
	base = (char*)queue+ sizeof(struct queue);

	assert(QueueSize(queue) <= QueueCapacity(queue));
	
	*queue->top = *(int*)elem;
	queue->top =(int*)((char*)base + (((char*)queue->top - (char*)base + sizeof(int)) % (queue->capacity * sizeof(int))));
	++queue->size;
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	return queue->base;
}

void QueuePop(queue_t *queue)
{
	void* base = NULL;
	assert(!IsQueueEmpty(queue));
	base = (char*)queue + sizeof(struct queue);
	queue->base = (int*)((char*)base + (((char*)queue->base - (char*)base + sizeof(int)) % (queue->capacity * sizeof(int))));
	--queue->size;
}

int IsQueueEmpty(const queue_t *queue)
{
	return (!queue->size);
}

size_t QueueSize(const queue_t *queue)
{
	return queue->size;
}

size_t QueueCapacity(const queue_t *queue)
{
	return queue->capacity;
}


