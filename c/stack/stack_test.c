#include"stack.h"
#include<utils.h>
#include<stdio.h>

int main()
{
	typedef struct weird_t
	{
		int a;
		char b;
	}weird;
	struct stack
	{
		int c;
	} test1;
	weird weird_1, weird_2;
	stack_t *my_stack;
	stack_t *my_stack_destroy = StackCreate(5,4);
	int five = 5;
	int seven = 7;
	stack_t *my_stack_struct_destroy = StackCreate(5,sizeof(weird_1));
	stack_t *my_stack_struct;
	weird_1.a = 5;
	weird_1.b = 'a';
	weird_2.a = 7;
	weird_2.b = 'b';
	test1.c = 2;
	printf("test struct stack %d \n",test1.c);
	printf("TEST INT:\n");
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
	
	printf("TEST WEIRD STRUCT:\n");
	printTest("my_stack_struct_destroy capacity is 5",!(StackCapacity(my_stack_struct_destroy) == 5));
	printTest("Destroy normal stack:",StackDestroy(my_stack_struct_destroy));
	my_stack_struct = StackCreate(2,sizeof(weird_1));
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack_struct) == 2));
	StackPush(my_stack_struct,&weird_1);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack_struct) == 2));
	StackPush(my_stack_struct,&weird_2);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack_struct) == 2));
	printTest("It should'nt be empty",(IsStackEmpty(my_stack_struct) == 0));
	printTest("It even has a watermark...",!(StackSize(my_stack_struct) == 2));
	StackPop(my_stack_struct);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack_struct) == 2));
	printTest("It should'nt be empty",(IsStackEmpty(my_stack_struct) == 0));
	printTest("After I pop once",!(StackSize(my_stack_struct) == 1));
	StackPop(my_stack_struct);
	printTest("my_stack capacity is 2",!(StackCapacity(my_stack_struct) == 2));
	printTest("It should be empty",(IsStackEmpty(my_stack_struct) == 1));
	
	StackDestroy(my_stack_struct);
	return 0;
}
