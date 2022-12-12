#include<stdio.h>
#include"my_utils.h"
#include<slist.h>
#include<assert.h>

int PrettyPrintList(s_list_t *list)
{
		s_list_iterator_t iter, end;
		iter = SListBegin(list);
		end = SListEnd(list);
		printf("ALL RIGHTS RESERVED TO SHABABO INDUSTRIES™ UNAUTHORIZED COPYING IS FORBIDDEN BY LAW\n");
		while (0 == IterCmp(iter,end))
		{
			printf("%p:\n", (void*)iter);
			printf("------------------------------\n");
			printf("|    %d    ",*((int*)SListGet(list ,iter)));
			printf("|  %p  |\n",(void*)(iter = SListNext(iter)));
			printf("------------------------------\n");
			printf("\t\t│\n\t\t|\n\t\t|\n\t\t↓\n");	
		}
		printf("\t\tDUMMY\n\n\n");
		return 1;
}

int main()
{
	s_list_t *list = SListCreate();
	int one = 1, two = 2, three = 3, four = 4;
	s_list_iterator_t iter = SListEnd(list);
	printTest("Is size right? (0)", !(SListSize(list) == 0));
	
	SListAdd(list, iter, &one);
	assert(printf("First add:\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (1)", !(SListSize(list) == 1));
	
	iter = SListEnd(list);
	SListAdd(list, iter, &two);
	assert(printf("Second add:\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (2)", !(SListSize(list) == 2));
	
	iter = SListEnd(list);
	SListAdd(list, iter, &three);
	assert(printf("Third add:\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (3)", !(SListSize(list) == 3));
	
	iter = SListEnd(list);
	SListAdd(list, iter, &four);
	assert(printf("Fourth add:\n\n"));
	assert(PrettyPrintList(list));
	
	printTest("Is size right? (4)", !(SListSize(list) == 4));
	
	iter = SListBegin(list);
	SListRemove(list, iter);
	assert(printf("Remove from start (1):\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (3)", !(SListSize(list) == 3));
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	SListRemove(list, iter);
	assert(printf("Remove from middle (3):\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (2)", !(SListSize(list) == 2));
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	SListRemove(list, iter);
	assert(printf("Remove from end (4):\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (1)", !(SListSize(list) == 1));
	
	iter = SListBegin(list);
	SListRemove(list, iter);
	assert(printf("Remove last element (2):\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (0)", !(SListSize(list) == 0));
	
	iter = SListBegin(list);
	SListAdd(list, iter, &one);
	
	iter = SListEnd(list);
	SListAdd(list, iter, &two);
	
	iter = SListEnd(list);
	SListAdd(list, iter, &three);
	
	iter = SListEnd(list);
	SListAdd(list, iter, &four);
	
	assert(printf("Restored List:\n\n"));
	assert(PrettyPrintList(list));
	
	assert(printf("Destroy List:\n\n"));
	SListDestroy(list);
	
	
	
	return 0;
}
