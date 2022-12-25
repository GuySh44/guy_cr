#include"stack.h"

struct stack
{
	size_t capacity;
	size_t elem_size;
	void* base;
	void* top;
};

stack_t *StackCreate(const size_t capacity,const size_t elem_size)
{
	stack_t *new_stack =(stack_t*)malloc(sizeof(stack_t));
	if (NULL == new_stack)
	{
		return NULL;
	}
	assert(capacity);
	assert(elem_size);
	new_stack->base = malloc(capacity * elem_size);
	if (NULL == new_stack->base)
	{
		free(new_stack);
		return NULL;
	}
	new_stack->top = new_stack->base;
	new_stack->capacity = capacity;
	new_stack->elem_size = elem_size;
	return new_stack;
}

int StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack->base);
	free(stack);
	return 0;
}


void StackPush(stack_t *stack ,const void *elem)
{
	assert(NULL != stack);
	assert(NULL != elem);
	assert(StackSize(stack) <= StackCapacity(stack));
	memcpy((stack->top), elem, stack->elem_size);
	stack->top = (void*)(((char*)stack->top) + stack->elem_size);
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(!IsStackEmpty(stack));
	return (void*)(((char*)stack->top) - stack->elem_size);
}

void StackPop(stack_t *stack)
{
	assert(!IsStackEmpty(stack));
	stack->top = (void*)(((char*)stack->top) - stack->elem_size);
}

int IsStackEmpty(const stack_t *stack)
{
	assert((char*)stack->top >= (char*)stack->base);
	return !((char*)stack->top - (char*)stack->base);
}

size_t StackSize(const stack_t *stack)
{
	return (((char*)stack->top - (char*)stack->base) / stack->elem_size);
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}


