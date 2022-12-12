#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc free */
#include <assert.h>
#include <stdio.h> /* printf */

#include "slist.h"
#include "snode.h"

struct s_list
{
	s_list_node *head;
};

static int PrettyPrintList(s_list_t *list)
{
		s_list_iterator_t iter, end;
		iter = SListBegin(list);
		end = SListEnd(list);
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


int IterCmp(s_list_iterator_t iter1, s_list_iterator_t iter2)
{
	return iter1 == iter2;
}

s_list_t *SListCreate()
{
	s_list_t *new_list =(s_list_t*)malloc(sizeof(s_list_t));
	s_list_node *dummy = NULL;
	if(NULL == new_list)
	{
		return NULL;
	}
	dummy = SNodeCreate(NULL, NULL);
	if(NULL == dummy)
	{
		free(new_list);
		return NULL;
	}
	new_list->head = dummy;
	return new_list;
}

void SListDestroy(s_list_t *s_list)
{
	s_list_iterator_t iter = SListBegin(s_list);
	assert(s_list);
	while(NULL != SListNext(iter)) 
	{
		SListRemove(s_list, iter);
		iter = SListBegin(s_list);
		assert(PrettyPrintList(s_list));
	}
	SNodeDestroy(s_list->head);
	free(s_list);
}

s_list_iterator_t SListAdd(s_list_t *s_list, s_list_iterator_t position, const void *data)
{
	s_list_node* new_node = SNodeCreate(NULL, NULL);
	s_list_iterator_t iter;
	assert(s_list);
	assert(position);
	if(NULL == new_node)
	{
		return NULL;
	}
	iter = SListBegin(s_list);
	while (0 == IterCmp(iter, position))
	{
		iter = SListNext(iter);
	}
	assert(iter);
	SNodeSetData(new_node,SNodeGetData((s_list_node*)iter));
	SNodeSetNext(new_node,SNodeGetNext((s_list_node*)iter));
	SNodeSetData((s_list_node*)iter,(void*)data);
	SNodeSetNext((s_list_node*)iter, new_node);
	return iter;
}

s_list_iterator_t SListRemove(s_list_t *s_list, s_list_iterator_t iter)
{
	s_list_iterator_t new_iter, after_iter;
	assert(s_list);
	assert(iter);
	new_iter = SListBegin(s_list);
	while (0 == IterCmp(new_iter, iter))
	{
		new_iter = SListNext(new_iter);
	}
	assert(new_iter);
	after_iter =  SListNext(new_iter);
	SNodeSetData((s_list_node*)new_iter,SNodeGetData((s_list_node*)after_iter));
	SNodeSetNext((s_list_node*)new_iter,SNodeGetNext((s_list_node*)after_iter));
	iter = SListNext(after_iter);
	SNodeDestroy((s_list_node*)after_iter);
	return iter;
}

void SListSet(s_list_t *s_list, s_list_iterator_t iter, const void *data);

void *SListGet(s_list_t *s_list, s_list_iterator_t iter)
{
	s_list_iterator_t new_iter;
	assert(s_list);
	assert(iter);
	new_iter = SListBegin(s_list);
	while (0 == IterCmp(new_iter, iter))
	{
		new_iter = SListNext(new_iter);
	}
	assert(new_iter);
	return SNodeGetData((s_list_node*)new_iter);
}

size_t SListSize(const s_list_t *s_list)
{
	s_list_iterator_t iter, last;
	size_t count = 0;
	assert(s_list);
	iter = SListBegin(s_list);
	last = SListEnd(s_list);
	assert(iter);
	assert(last);
	while (0 == IterCmp(iter, last))
	{
		iter = SListNext(iter);
		++count;
	}
	return count;
}

int SListForEach(s_list_t *s_list, s_list_iterator_t iter_from, s_list_iterator_t iter_to, action_function_t action_func, void *parameter);

s_list_iterator_t SListFind(s_list_iterator_t iter_from, s_list_iterator_t iter_to, match_function_t match_func, void *parameter);

s_list_iterator_t SListBegin(const s_list_t *s_list)
{
	assert(s_list);
	return (s_list_iterator_t)(s_list->head);
}

s_list_iterator_t SListNext(const s_list_iterator_t iter)
{
	assert(iter);
	return (s_list_iterator_t)(SNodeGetNext((s_list_node*)iter));
}

s_list_iterator_t SListEnd(const s_list_t *s_list)
{
	s_list_node* node_iter = s_list->head;
	assert(s_list);
	while(SNodeGetNext(node_iter) != NULL)
	{
		node_iter = SNodeGetNext(node_iter);
	}
	return (s_list_iterator_t)node_iter;
}

