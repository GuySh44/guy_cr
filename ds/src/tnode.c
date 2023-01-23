#include <stdlib.h> /* malloc free */
#include <assert.h>
#include "tnode.h"

struct bin_node
{
	void* data;
	bin_node_t *left_child;
	bin_node_t *right_child;
};

bin_node_t *TreeNodeCreate(bin_node_t *left_child, bin_node_t *right_child,const void* data)
{
	bin_node_t *new_node = (bin_node_t*)malloc(sizeof(bin_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = (void*)data;
	new_node->left_child = left_child;
	new_node->right_child = right_child;
	return new_node;
}

bin_node_t *TreeNodeGetLeftChild(bin_node_t *parent)
{
	assert(parent);
	return parent->left_child;
}

bin_node_t *TreeNodeGetRightChild(bin_node_t *parent)
{
	assert(parent);
	return parent->right_child;
}

void *TreeNodeGetData(bin_node_t *node)
{
	assert(node);
	return node->data;
}

void TreeNodeSetLeftChild(bin_node_t *parent, bin_node_t *left_child)
{
	assert(parent);
	parent->left_child = left_child;
}

void TreeNodeSetRightChild(bin_node_t *parent, bin_node_t *right_child)
{
	assert(parent);
	parent->right_child = right_child;
}

void TreeNodeSetData(bin_node_t *node, void *data)
{
	assert(node);
	node->data = data;
}

void TreeNodeDestroy(bin_node_t *node)
{
	assert(node);
	free(node);
}



