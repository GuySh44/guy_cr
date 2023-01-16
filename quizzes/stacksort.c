#include <stddef.h>
#include <stdio.h>

#include "../ds/include/stack.h"
#define STACK_SIZE 128

void StackSort(stack_t *stack)
{
	stack_t *s_temp = StackCreate(STACK_SIZE, sizeof(int));
	size_t push_count = 0;
	int *temp = 0;
	
	StackPush(s_temp, StackPeek(stack));
	StackPop(stack);
	
	while(!IsStackEmpty(stack))
	{
		push_count = 0;
		temp = StackPeek(stack);
		StackPop(stack);
		while (*temp < *((int*)StackPeek(s_temp)) && !IsStackEmpty(s_temp))
		{
			StackPush(stack, StackPeek(s_temp));
			StackPop(s_temp);
			++push_count;
		}
		StackPush(s_temp, temp);
		while(push_count)
		{
			StackPush(s_temp,StackPeek(stack));
			StackPop(stack);
			--push_count;
		}
	}
	while(!IsStackEmpty(s_temp))
	{
		StackPush(stack, StackPeek(s_temp));
		StackPop(s_temp);
	}
	StackDestroy(s_temp);
}

int main()
{
	int intagers[5] = {30,-5,18,14,-3};
	
	stack_t *mystack = StackCreate(5,4);
	
	StackPush(mystack, intagers);
	StackPush(mystack, intagers+1);
	StackPush(mystack, intagers+2);
	StackPush(mystack, intagers+3);
	StackPush(mystack, intagers+4);
	
	printf("\n");
	printf("the stack before sort is:\n");
	printf("\ntop\n%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d bottom\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	
	StackPush(mystack, intagers);
	StackPush(mystack, intagers+1);
	StackPush(mystack, intagers+2);
	StackPush(mystack, intagers+3);
	StackPush(mystack, intagers+4);
	
	StackSort(mystack);
	
	printf("\n");
	printf("the stack after sort is:\n");
	printf("\ntop\n%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d bottom\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	
	StackDestroy(mystack);
	return 0;
}
