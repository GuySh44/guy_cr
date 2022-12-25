#include <stdio.h>
#include "../ds/include/stack.h"
#define STACK_SIZE 128

void BalancedPar(const char *str)
{
	stack_t *stack = StackCreate(STACK_SIZE, sizeof(char));
	while(*str != '\0')
	{
		char chr = *str;
		if(chr == '(' || chr == '[' || chr == '{')
		{
			StackPush(stack, &chr);
			++str;
			continue;
		}
		switch (chr)
		{
			case ')':
				if(*((char*)StackPeek(stack)) != '(')
				{
					printf("Not Balanced\n");
					return;
				}
				StackPop(stack);
				break;
			case ']':
				if(*((char*)StackPeek(stack)) != '[')
				{
					printf("Not Balanced\n");
					return;
				}
				StackPop(stack);
				break;
			case '}':
				if(*((char*)StackPeek(stack)) != '{')
				{
					printf("Not Balanced\n");
					return;
				}
				StackPop(stack);
				break;
			default:
				break;				
		}
		++str;	
	}
	if(IsStackEmpty(stack))
	{
		printf("Balanced\n");
		return;
	}
	printf("Not Balanced\n");
}

int main()
{
	printf("string = “[()](){[()]()}”\n");
	BalancedPar("[()](){[()]()}");
	printf("string = “[{}(])”\n");
	BalancedPar("[{}(])");
	return 0;
}
