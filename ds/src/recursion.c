#include <stddef.h>
#include <string.h>

#include "recursion.h"
#include "stack.h"

/* Reviewer: Or */

int FibonacciRegular(int element_index)
{
	int i = 0;
	size_t curr = 0;
	size_t pre_curr = 0;
	size_t prepre_curr = 1; 
	for(; i < element_index; ++i)
	{
		curr = pre_curr + prepre_curr;
		prepre_curr = pre_curr;
		pre_curr = curr;
	}
	return curr;
}

/* Reviewer: Or */
/* 0,1 are "edge" cases and we need to check for them */
int FibonacciRecursive(int element_index)
{
	if(element_index == 1)
	{
		return 1;
	}
	if(element_index == 0)
	{
		return 0;
	}	
	return FibonacciRecursive(element_index - 1) + FibonacciRecursive(element_index - 2);
}

/* Reviewer: Daniel */
Node* FlipListRecursive(Node* node)
{
	Node *next = NULL;
    Node *new_head = NULL;
    if (node == NULL || node->next_node == NULL) {
        return node;						/* if the list is empty or we got to the last node we reached our stop condition */
    }
    next = node->next_node;					/* keep next node */
    new_head = FlipListRecursive(next);		/* get to last node */
    next->next_node = node;					/* set next node to current node, its just after the recursion so we start at the end of the list */
    node->next_node = NULL;					/* set current node next to NULL, solves end of list edge case */
    return new_head;
}

/*
All Str functions:
Reviewer: Yahav
 */

size_t StrlenRecursive(const char *s)
{
	if('\0' == *s)
	{
		return 0;
	}
	return 1 + StrlenRecursive(s+1);
}


int StrcmpRecursive(const char *s1, const char *s2)
{
	if(*s1 != *s2 || '\0' == *s1)
	{
		return ((*s1) - (*s2));
	}
	return StrcmpRecursive(s1+1,s2+1);
}

/*we find src end and copy from end to start*/
char *StrcpyRecursive(char *dest, const char *src)
{
	if('\0' == *src)
	{
		*dest = *src;
		return dest;
	}
	StrcpyRecursive(dest + 1, src + 1);
	*dest = *src;
	return dest;
}

char *StrcatRecursive(char *dest, const char *src)
{
	if('\0' == *dest)
	{
		return StrcpyRecursive(dest, src);
	}
	StrcatRecursive(dest + 1, src);
	return dest;
}

/*we find first occurance of needle by iterating over haystack, if we get to end of haystack we return NULL*/
char *StrstrRecursive(const char *haystack, const char *needle)
{
	if(0 == strncmp(haystack, needle, StrlenRecursive(needle)))
	{
		return (char*)haystack;
	}
	else if('\0' == *haystack)
	{
		return NULL;
	}
	return StrstrRecursive(haystack + 1, needle);
}

/*
Stack Sort
Reviewer: Yosef 
*/

/*we use Insert sort algorithm implemented for a stack. our starting point is a stack with 1 element inside it, and thats why we can deduct the stack is sorted in each step, then we insert the element in the right place just like insert sort*/
static void InsertSortStack(stack_t *stack, int elem)
{
	int stack_top = 0;
	if(IsStackEmpty(stack))
	{
		StackPush(stack, &elem);
		return;
	}
	stack_top = *((int*)StackPeek(stack));
	StackPop(stack);
	if(stack_top < elem)
	{
		StackPush(stack, &stack_top);
		StackPush(stack, &elem);
		return;
	}
	InsertSortStack(stack, elem);
	StackPush(stack, &stack_top);
} 

/*Base recursive function for the Sort, its main use is to empty the stack, and keep the last element we popped, then calling the insert function to insert the popped element in the right place*/
void SortStack(stack_t *stack)
{
	int stack_top = 0;
	if(1 == StackSize(stack))
	{
		return;
	}
	stack_top = *((int*)StackPeek(stack));
	StackPop(stack);
	SortStack(stack);
	InsertSortStack(stack, stack_top);
}


