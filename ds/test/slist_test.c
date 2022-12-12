#include<stdio.h>
#include"my_utils.h"
#include<slist.h>
#include<assert.h>

int PrettyPrintList(s_list_t *list)
{
		s_list_iterator_t iter, end;
		assert(list);
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

int MatchInt(const void *data, void *parameter)
{
	return (*((const int*) data) == *((int*) parameter));
}

int SumInt(void *data, void *parameter)
{
	*((long*)parameter) += *((int*)data);
	return 0;
}

int main()
{
	s_list_t *list = SListCreate();
	long int_sum = 0;
	int one = 1, two = 2, three = 3, four = 4, m_one = -1, m_two = -2, m_three = -3, m_four = -4, m_one2 = -1, m_one3 = -1;
	s_list_iterator_t iter = SListEnd(list), iter_to, iter_from;
	printTest("Is size right? (0)", !(SListSize(list) == 0));
	
	printf("iterator to 1:%p\n\n", (void*)SListAdd(list, iter, &one));
	assert(printf("First add:\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (1)", !(SListSize(list) == 1));
	
	iter = SListEnd(list);
	printf("iterator to 2:%p\n\n", (void*)SListAdd(list, iter, &two));
	assert(printf("Second add:\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (2)", !(SListSize(list) == 2));
	
	iter = SListEnd(list);
	printf("iterator to 3:%p\n\n", (void*)SListAdd(list, iter, &three));
	assert(printf("Third add:\n\n"));
	assert(PrettyPrintList(list));
	printTest("Is size right? (3)", !(SListSize(list) == 3));
	
	iter = SListEnd(list);
	printf("iterator to 4:%p\n\n", (void*)SListAdd(list, iter, &four));
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
	
	iter_from = SListBegin(list);
	iter_to = SListEnd(list);
	SListForEach(list, iter_from, iter_to, SumInt, &int_sum);
	assert(printf("sum of all the elements:%ld\n", int_sum));
	int_sum = 0;
	
	assert(printf("Destroy List:\n\n"));
	SListDestroy(list);
	
	assert(printf("Create List in different ways:\n\n"));
	list = SListCreate();
	iter = SListBegin(list);
	SListAdd(list, iter, &two);
	
	iter = SListBegin(list);
	SListAdd(list, iter, &one);
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	iter = SListNext(iter);
	SListAdd(list, iter, &four);
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	iter = SListNext(iter);
	SListAdd(list, iter, &three);
	
	assert(PrettyPrintList(list));
	
	iter_from = SListBegin(list);
	iter_to = SListEnd(list);
	SListForEach(list, iter_from, iter_to, SumInt, &int_sum);
	assert(printf("sum of all the elements:%ld\n", int_sum));
	int_sum = 0;
	
	SListDestroy(list);

	assert(printf("Create List, and change the values:\n\n"));
	
	list = SListCreate();

	iter = SListBegin(list);
	SListAdd(list, iter, &one);
	
	iter = SListEnd(list);
	SListAdd(list, iter, &two);
	
	iter = SListEnd(list);
	SListAdd(list, iter, &three);
	
	iter = SListEnd(list);
	SListAdd(list, iter, &four);
	
	assert(printf("Before 'Set':\n\n"));
	assert(PrettyPrintList(list));
	
	iter = SListBegin(list);
	SListSet(list, iter, &m_one);
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	SListSet(list, iter, &m_two);
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	iter = SListNext(iter);
	SListSet(list, iter, &m_three);
	
	iter = SListBegin(list);
	iter = SListNext(iter);
	iter = SListNext(iter);
	iter = SListNext(iter);
	SListSet(list, iter, &m_four);
	
	assert(printf("After 'Set':\n\n"));
	assert(PrettyPrintList(list));
	
	SListSet(list, iter, &m_one2);
	
	iter_from = SListBegin(list);
	iter_to = SListEnd(list);
	assert(printf("Find 1 in entire list (it doesnt exist):%p\n", (void*)SListFind(iter_from, iter_to, MatchInt, &one)));
	assert(printf("Find -1 in entire list:%p\n", (void*)SListFind(iter_from, iter_to, MatchInt, &m_one3)));
	iter_from = SListNext(iter_from);
	assert(printf("Find -1 in second element to end of list:%p\n", (void*)SListFind(iter_from, iter_to, MatchInt, &m_one3)));
		
	iter_from = SListBegin(list);
	iter_to = SListEnd(list);
	SListForEach(list, iter_from, iter_to, SumInt, &int_sum);
	assert(printf("sum of all the elements:%ld\n", int_sum));
	int_sum = 0;
	iter_from = SListNext(iter_from);
	SListForEach(list, iter_from, iter_to, SumInt, &int_sum);
	assert(printf("sum of all the elements but the first:%ld\n", int_sum));
	assert(PrettyPrintList(list));
	int_sum = 0;
	SListDestroy(list);

	return 0;
}
