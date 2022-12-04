#include"stack.h"
#include<utils.h>

int main()
{
	stack_t *my_stack;
	stack_t *my_stack_destroy = StackCreate(5,4);
	int five = 5;
	int seven = 7;
	printTest("my_stack_destroy capacity is 5",!(StackCapacity(my_stack_destroy) == 5));
	printTest("Destroy normal stack:",StackDestroy(my_stack_destroy));
	my_stack = StackCreate(2,4);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack) == 2));
	StackPush(my_stack,&five);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack) == 2));
	printTest("Did my five survive?",!(*((int*)StackPeek(my_stack)) == 5));
	StackPush(my_stack,&seven);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack) == 2));
	printTest("It should'nt be empty",(IsStackEmpty(my_stack) == 0));
	printTest("Lets see paul sevens card... OMG...",!(*((int*)StackPeek(my_stack)) == 7));
	printTest("It even has a watermark...",!(StackSize(my_stack) == 2));
	StackPop(my_stack);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack) == 2));
	printTest("It should'nt be empty",(IsStackEmpty(my_stack) == 0));
	printTest("Did my five survive again?",!(*((int*)StackPeek(my_stack)) == 5));
	printTest("After I pop once",!(StackSize(my_stack) == 1));
	StackPop(my_stack);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack) == 2));
	printTest("It should be empty",(IsStackEmpty(my_stack) == 1));
	
	StackDestroy(my_stack);
	return 0;
}
