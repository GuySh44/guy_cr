
#include <assert.h>
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc free */

/* I created a binary tree node API, tnode.h, a node from this library is of bin_node_t type */
#include "tnode.h"

#include "bst.h"


/* Reviewer: Yosef */

/* iterator is of binary tree node pointer type */
struct bst_iter
{
	bin_node_t *node;
};


/* Binary Search Tree holds a comparing function and the root */
struct bst
{
	compare_func_t cmp_func;
	bin_node_t *root;
};


/* Inorder traversal function performing and passing param to action_func on each node */
static int BstInorderDataAction(bin_node_t *root, action_function_t action_func, void *param)
{
	int ret_val = 0;
	
	assert(action_func);
	
	if(NULL == root)
	{
		return 0;
	}
	
	if(BstInorderDataAction(TreeNodeGetLeftChild(root), action_func, param))
	{
		return 1;
	}
	
	ret_val = action_func(TreeNodeGetData(root), param);
	
	if(ret_val)
	{
		return 1;
	}
	
	if(BstInorderDataAction(TreeNodeGetRightChild(root), action_func, param))
	{
		return 1;
	}
	
	return 0;
}



/* Preorder traversal function performing and passing param to action_func on each node */
static int BstPreorderDataAction(bin_node_t *root, action_function_t action_func, void *param)
{
	int ret_val = 0;
	
	assert(action_func);
	
	if(NULL == root)
	{
		return 0;
	}
	
	ret_val = action_func(TreeNodeGetData(root), param);
	
	if(ret_val)
	{
		return 1;
	}
	
	if(BstPreorderDataAction(TreeNodeGetLeftChild(root), action_func, param))
	{
		return 1;
	}
	
	if(BstPreorderDataAction(TreeNodeGetRightChild(root), action_func, param))
	{
		return 1;
	}
	
	return 0;
}


/* Postorder traversal function performing and passing param to action_func on each node */
static int BstPostorderDataAction(bin_node_t *root, action_function_t action_func, void *param)
{
	int ret_val = 0;
	
	assert(action_func);
	
	if(NULL == root)
	{
		return 0;
	}
	
	
	if(BstPostorderDataAction(TreeNodeGetLeftChild(root), action_func, param))
	{
		return 1;
	}
	
	if(BstPostorderDataAction(TreeNodeGetRightChild(root), action_func, param))
	{
		return 1;
	}
	
	ret_val = action_func(TreeNodeGetData(root), param);
	
	if(ret_val)
	{
		return 1;
	}
	
	return 0;
}


/* Creating binary search tree struct, and setting members to NULL */
bst_t *BstCreate(compare_func_t cmp_func)
{
	bst_t *new_tree = NULL;
	assert(cmp_func);
	
	new_tree = (bst_t*)malloc(sizeof(bst_t));
	if(NULL == new_tree)
	{
		return NULL;
	}
	
	new_tree->cmp_func = cmp_func;
	new_tree->root = NULL;
	
	return new_tree;
}

static void BstPostorderFree(bin_node_t *node)
{
	if(NULL == node)
	{
		return;
	}
	
	BstPostorderFree(TreeNodeGetLeftChild(node));
	
	BstPostorderFree(TreeNodeGetRightChild(node));
	
	free(node);
	
}

void BstDestroy(bst_t *bst)
{
	assert(bst);
	
	BstPostorderFree(bst->root);
	
	free(bst);
}


void BstRemove(bst_iter_t iter);


/* 
recursively go over the tree, binary searching the right spot for inserting.
when reaching a leaf's child it means we reached the spot of insertion, so we set the child from NULL to a new node holding the data
returns the root, setting the return value of the API function for the original return value 
 */
static bin_node_t *BstInsertRec(bin_node_t *node, const void *data, compare_func_t cmp_func, int *flag)
{
	bin_node_t *new_child = NULL;
	assert(data);
	assert(cmp_func);
	
	/* we reached a leaf's child */
	if(NULL == node)
	{
		return TreeNodeCreate(NULL, NULL, data);
	}
	
	/* the inserted data is less than the current node */
	if(cmp_func(TreeNodeGetData(node), data) > 0)
	{
		/* the left child of current node might change if node is a leaf */
		new_child = BstInsertRec(TreeNodeGetLeftChild(node), data, cmp_func, flag);
		if(NULL == new_child)
		{
			*flag = 1;
			return node;
		}
		TreeNodeSetLeftChild(node, new_child);
	}
	/* the inserted data is more than the current node */
	else if(cmp_func(TreeNodeGetData(node), data) < 0)
	{
		/* the right child of current node might change if node is a leaf */
		new_child = BstInsertRec(TreeNodeGetRightChild(node), data, cmp_func, flag);
		if(NULL == new_child)
		{
			*flag = 1;
			return node;
		}
		TreeNodeSetRightChild(node, new_child);
	}
	/* the inserted data is equal to the current node */
	else
	{
		*flag = 2;
		return NULL;
	}
	
	return node;
}

/*
wrapper to recursive insert function 
return value:
	0 - success
	1 - memory failure
	2 - data value already exists
*/
int BstInsert(bst_t *bst, const void *data)
{
	int flag = 0;
	assert(bst);
	assert(data);
	bst->root = BstInsertRec(bst->root, data, bst->cmp_func, &flag);
	return flag;
}


size_t BstHeight(const bst_t *bst);


size_t BstSize(const bst_t *bst);


int BstIsEmpty(const bst_t *bst);


bst_iter_t BstFind(bst_t *bst, const void *data);

/* choose traversal mode and action func */
int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param)
{
	assert(bst);
	assert(action_func);
	switch(mode)
	{
		case IN_ORDER:
			return BstInorderDataAction(bst->root, action_func, param);
			break;
			
		case PRE_ORDER:
			return BstPreorderDataAction(bst->root, action_func, param);
			break;
			
		case POST_ORDER:
			return BstPostorderDataAction(bst->root, action_func, param);
			break;
			
		default:
			break;
	}
	return 1;
}

