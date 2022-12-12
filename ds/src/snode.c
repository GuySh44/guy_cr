#include <stdlib.h> /* malloc free */
#include <assert.h>
#include "snode.h"

struct node
{
	void* data;
	s_list_node *next_node;
};

s_list_node *SNodeCreate(s_list_node *next_node, void* data)
{
	s_list_node *new_node = (s_list_node*)malloc(sizeof(s_list_node));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->next_node = next_node;
	return new_node;
}

s_list_node *SNodeGetNext(s_list_node *current)
{
	assert(current);
	return current->next_node;
}

void *SNodeGetData(s_list_node *node)
{
	assert(node);
	return node->data;
}

void SNodeSetNext(s_list_node *node, s_list_node *next_node)
{
	assert(node);
	node->next_node = next_node;
}

void SNodeSetData(s_list_node *node, void *data)
{
	assert(node);
	node->data = data;
}

void SNodeDestroy(s_list_node *node)
{
	assert(node);
	free(node);
}




