#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc free */
#include <assert.h>
#include <stdio.h> /* printf */

#include "slist.h"

/* my own Singly listed node ADT */
#include "snode.h"

struct s_list
{
	s_list_node *head;
};

/* function for comparing Iterators, pretty redundant in our case*/
int IterCmp(s_list_iterator_t iter1, s_list_iterator_t iter2)
{
	return iter1 == iter2;
}

/* 
create the list, allocate memory for its structure and a dummy node 
return value:
the new list
*/
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

/* 
iterate on the list, and remove node by node starting from the first node onwards, release the dummy and free the struct after deleting all regular nodes 
*/
void SListDestroy(s_list_t *s_list)
{
	s_list_iterator_t iter = SListBegin(s_list);
	assert(s_list);
	while(NULL != SListNext(iter)) 
	{
		SListRemove(s_list, iter);
		iter = SListBegin(s_list);
	}
	SNodeDestroy(s_list->head);
	free(s_list);
}

/* 
iterate on the list and find position, insert the new node using the method seen in class 
return value:
iterator to the new node added node
*/
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

/* 
iterate on the list and find iter, delete the node using the method seen in class 
return value:
iterator to the next node after the removed
*/
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

/* 
iterate on the list and find iter, change the data pointer of the node 'pointed to' by iter 
*/
void SListSet(s_list_t *s_list, s_list_iterator_t iter, const void *data)
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
	SNodeSetData((s_list_node*)new_iter, (void*)data);
}

/* 
iterate on the list and find iter, return the data in the node pointed to by iter 
return value:
pointer to the data of the right node
return NULL if iter pointing to dummy
*/
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

/* 
iterate on the list and count elements, return the amount of elemnts not including dummy 
return value:
list size
*/
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


/* 
iterate on the list from iter_from to iter_to, using action_func on each node in the range 
return value:
0 if action func finished succeessfully, not 0 otherwise
*/
int SListForEach(s_list_t *s_list, s_list_iterator_t iter_from, s_list_iterator_t iter_to, action_function_t action_func, void *parameter)
{
	s_list_iterator_t list_from, list_to;
	assert(s_list);
	assert(iter_from);
	assert(iter_to);
	assert(action_func);
	list_from = SListBegin(s_list);
	while (0 == IterCmp(list_from, iter_from))
	{
		list_from = SListNext(list_from);
	}
	assert(list_from);
	list_to = SListBegin(s_list);
	while (0 == IterCmp(list_to, iter_to))
	{
		list_to = SListNext(list_to);
	}
	assert(list_to);
	if(NULL != SListNext(iter_to))
	{
		iter_to = SListNext(iter_to);
	}
	while(0 == IterCmp(list_from, list_to))
	{
		if(0 != action_func(SNodeGetData((s_list_node*)list_from), parameter))
		{
			return 1;
		}
		list_from = SListNext(list_from);
	}
	return 0;
}

/* 
iterate on the list from iter_from to iter_to, checking for a node with a certain value, matched by match_func to a parameter 
return value:
iterator to the matched node if found, NULL otherwise
*/
s_list_iterator_t SListFind(s_list_iterator_t iter_from, s_list_iterator_t iter_to, match_function_t match_func, void *parameter)
{
	assert(iter_from);
	assert(iter_to);
	assert(match_func);
	if(NULL != SListNext(iter_to))
	{
		iter_to = SListNext(iter_to);
	}
	while(0 == IterCmp(iter_from, iter_to))
	{
		if(match_func(SNodeGetData((s_list_node*)iter_from), parameter))
		{
			return iter_from;
		}
		iter_from = SListNext(iter_from);
	}
	return (s_list_iterator_t)(0);
}

/* 
return value:
iterator to the begining of the list
*/
s_list_iterator_t SListBegin(const s_list_t *s_list)
{
	assert(s_list);
	return (s_list_iterator_t)(s_list->head);
}

/* 
return value:
iterator to the next node after iter
*/
s_list_iterator_t SListNext(const s_list_iterator_t iter)
{
	assert(iter);
	return (s_list_iterator_t)(SNodeGetNext((s_list_node*)iter));
}

/* 
iterate on the list until getting to the dummy signfying the last node 
return value:
iterator to dummy (last node)
*/
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

