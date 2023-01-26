#include <stdlib.h> /* malloc free */
#include <assert.h>
#include "avl_node.h"

struct avl_node
{
	short balance_factor;
	void* data;
	avl_node_t *left_child;
	avl_node_t *right_child;
};

avl_node_t *AvlNodeCreate(avl_node_t *left_child, avl_node_t *right_child,const void* data)
{
	avl_node_t *new_node = (avl_node_t*)malloc(sizeof(avl_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->balance_factor = 0;
	new_node->data = (void*)data;
	new_node->left_child = left_child;
	new_node->right_child = right_child;
	return new_node;
}

short AvlNodeGetBalanceFactor(avl_node_t *node)
{
	assert(node);
	return node->balance_factor;
}

avl_node_t *AvlNodeGetLeftChild(avl_node_t *parent)
{
	assert(parent);
	return parent->left_child;
}

avl_node_t *AvlNodeGetRightChild(avl_node_t *parent)
{
	assert(parent);
	return parent->right_child;
}

void *AvlNodeGetData(avl_node_t *node)
{
	assert(node);
	return node->data;
}

void AvlNodeSetBalanceFactor(avl_node_t *node, short new_factor)
{
	assert(node);
	node->balance_factor = new_factor; 
}

void AvlNodeSetLeftChild(avl_node_t *parent, avl_node_t *left_child)
{
	assert(parent);
	parent->left_child = left_child;
}

void AvlNodeSetRightChild(avl_node_t *parent, avl_node_t *right_child)
{
	assert(parent);
	parent->right_child = right_child;
}

void AvlNodeSetData(avl_node_t *node, void *data)
{
	assert(node);
	node->data = data;
}

void AvlNodeDestroy(avl_node_t *node)
{
	assert(node);
	free(node);
}



