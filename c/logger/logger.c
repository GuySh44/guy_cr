#include"logger.h"

/* reviewer: or */
void printNum(int num)
{
	printf("%d\n",num);	
}
void firstExercise()
{
	int i = 0;
	struct print_me array[10];
	for(; i < 10; i++)
	{
		array[i].num = i;
		array[i].Print = &printNum;
		array[i].Print(array[i].num);
	}
}
