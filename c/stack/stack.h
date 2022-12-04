#ifndef __STACK_H__ILRD__CR3_
#define __STACK_H__ILRD__CR3_

#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdlib.h> /* malloc free */
#include <string.h> /* memcpy */

/* 
stack ADT, containing one element type
*/
typedef struct stack stack_t;


/* 
Create new stack

return value:
a pointer to a new stack
*/
stack_t *StackCreate(const size_t capacity,const size_t elem_size);


/* 
Destroy existing stack

return value:
0 if succeded
not 0 if failed
*/
int StackDestroy(stack_t *stack);


/* 
push a new element into the stack 

return value:
none
*/
void StackPush(stack_t *stack ,const void *elem);


/* 
check the element at the top of the stack

return value:
void* the element
*/
void *StackPeek(const stack_t *stack);


/* 
pop the element at the top of the stack 

return value:
none
*/
void StackPop(stack_t *stack);


/* 
check if the stack is empty 

return value:
1 if empty
not 1 if not empty
*/
int IsStackEmpty(const stack_t *stack);


/* 
return the size of current stack 

return value:
size_t number of elements in current stack
*/
size_t StackSize(const stack_t *stack);


/* 
return the capacity of the current stack 

return value:
size_t amount of memeory the stack can hold
*/
size_t StackCapacity(const stack_t *stack);

#endif  /* __STACK_H__ILRD__CR3_ */
