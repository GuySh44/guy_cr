
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

static bst_iter_t BstIterCreate(bin_node_t *node)
{
	bst_iter_t new_iter;
	
	new_iter.node = node;
	
	return new_iter;
}


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

/* free tree nodes recursively using postorder traversal */
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

/* call function to free all nodes, and then free the struct itself */
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

/* recursive height function, returns longest route from a leaf to root, by comparing sibling nodes height */
static size_t BstHeightRec(bin_node_t *node, size_t right_branch, size_t left_branch)
{
	if(node == NULL)
	{
		return 0;
	}
	
	right_branch = BstHeightRec(TreeNodeGetRightChild(node), 0, 0);
	left_branch = BstHeightRec(TreeNodeGetLeftChild(node), 0, 0); 
	
	if(right_branch > left_branch)
	{
		return right_branch + 1;
	}
	return left_branch + 1;
}

/* API wrapper to recursive function */
size_t BstHeight(const bst_t *bst)
{
	assert(bst);
	return(BstHeightRec(bst->root, 0, 0));
}

static int CountFunc(void *data, void *param)
{
	*((size_t*)param) = *((size_t*)param) + 1;
	return 0;
	
	(void)(data);
}

/* run foreach with a counter on all nodes, using a function that increments counts on each visit of a node */
size_t BstSize(const bst_t *bst)
{
	size_t count = 0;
	
	assert(bst);
	
	BstForEach((bst_t*)bst, IN_ORDER, CountFunc, &count);
	
	return count;
}


/* is bst->root NULL? */
int BstIsEmpty(const bst_t *bst)
{
	assert(bst);
	return (NULL == bst->root);
}


/*
recursive find function, that uses the fact we traverse a binary search tree.
returns iterator to the node holding data value, or NULL if no such node exists
*/
static bst_iter_t BstFindRec(bin_node_t *node, const void *data, compare_func_t cmp_func)
{
	assert(data);
	assert(cmp_func);
	
	if (0 == cmp_func(TreeNodeGetData(node), data))
	{
		return BstIterCreate(node);
	}
	else if(0 < cmp_func(TreeNodeGetData(node), data))
	{
		return BstFindRec(TreeNodeGetLeftChild(node), data, cmp_func);
	}
	else if(0 > cmp_func(TreeNodeGetData(node), data))
	{
		return BstFindRec(TreeNodeGetRightChild(node), data, cmp_func);
	}
	return BstIterCreate(NULL);
}


/* API function that wraps my recursive find func */
bst_iter_t BstFind(bst_t *bst, const void *data)
{
	assert(bst);
	assert(data);
	
	return BstFindRec(bst->root, data, bst->cmp_func);
}

/* 
choose traversal mode and action func
return value:
0 - success
1 - action func failed
2 - wrong mode
*/
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
	return 2;
}

