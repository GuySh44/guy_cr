#ifndef __QUEUE_H__ILRD__CR3_
#define __QUEUE_H__ILRD__CR3_

#include <stddef.h> /* size_t */

/* 
queue ADT, containing one element type
*/
typedef struct queue queue_t;


/* 
Create new queue

return value:
a pointer to a new queue
*/
queue_t *QueueCreate(const size_t capacity);


/* 
Destroy existing queue

return value:
0 if succeded
not 0 if failed
*/
int QueueDestroy(queue_t *queue);


/* 
push a new element into the queue 

return value:
none
*/
void QueuePush(queue_t *queue , void *elem);


/* 
check the element at the begining of the queue

return value:
void* the element
*/
void *QueuePeek(const queue_t *queue);


/* 
pop the element at the begining of the queue

return value:
none
*/
void QueuePop(queue_t *queue);


/* 
check if the queue is empty 

return value:
1 if empty
not 1 if not empty
*/
int IsQueueEmpty(const queue_t *queue);


/* 
return the size of current queue

return value:
size_t number of elements in current queue
*/
size_t QueueSize(const queue_t *queue);


/* 
return the capacity of the current queue 

return value:
size_t amount of memory the queue can hold
*/
size_t QueueCapacity(const queue_t *queue);

#endif  /* __QUEUE_H__ILRD__CR3_ */
