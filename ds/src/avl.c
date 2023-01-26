
#include <assert.h>
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc free */

/* I created an AVL node API, avl_node.h, a node from this library is of avl_node_t type */
#include "avl_node.h"

#include "avl.h"


/* Reviewer: Me */


/* AVL Tree holds a comparing function and the root */
struct avl
{
	compare_func_t cmp_func;
	avl_node_t *root;
};

/* Inorder traversal function performing and passing param to action_func on each node */
static int AvlInorderDataAction(avl_node_t *root, action_function_t action_func, void *param)
{
	int ret_val = 0;
	
	assert(action_func);
	
	if(NULL == root)
	{
		return 0;
	}
	
	if(AvlInorderDataAction(AvlNodeGetLeftChild(root), action_func, param))
	{
		return 1;
	}
	
	ret_val = action_func(AvlNodeGetData(root), param);
	
	if(ret_val)
	{
		return 1;
	}
	
	if(AvlInorderDataAction(AvlNodeGetRightChild(root), action_func, param))
	{
		return 1;
	}
	
	return 0;
}



/* Preorder traversal function performing and passing param to action_func on each node */
static int AvlPreorderDataAction(avl_node_t *root, action_function_t action_func, void *param)
{
	int ret_val = 0;
	
	assert(action_func);
	
	if(NULL == root)
	{
		return 0;
	}
	
	ret_val = action_func(AvlNodeGetData(root), param);
	
	if(ret_val)
	{
		return 1;
	}
	
	if(AvlPreorderDataAction(AvlNodeGetLeftChild(root), action_func, param))
	{
		return 1;
	}
	
	if(AvlPreorderDataAction(AvlNodeGetRightChild(root), action_func, param))
	{
		return 1;
	}
	
	return 0;
}


/* Postorder traversal function performing and passing param to action_func on each node */
static int AvlPostorderDataAction(avl_node_t *root, action_function_t action_func, void *param)
{
	int ret_val = 0;
	
	assert(action_func);
	
	if(NULL == root)
	{
		return 0;
	}
	
	
	if(AvlPostorderDataAction(AvlNodeGetLeftChild(root), action_func, param))
	{
		return 1;
	}
	
	if(AvlPostorderDataAction(AvlNodeGetRightChild(root), action_func, param))
	{
		return 1;
	}
	
	ret_val = action_func(AvlNodeGetData(root), param);
	
	if(ret_val)
	{
		return 1;
	}
	
	return 0;
}


/* Creating AVL tree struct, and setting members to NULL */
avl_t *AvlCreate(compare_func_t cmp_func)
{
	avl_t *new_tree = NULL;
	assert(cmp_func);
	
	new_tree = (avl_t*)malloc(sizeof(avl_t));
	if(NULL == new_tree)
	{
		return NULL;
	}
	
	new_tree->cmp_func = cmp_func;
	new_tree->root = NULL;
	
	return new_tree;
}

/* free tree nodes recursively using postorder traversal */
static void AvlPostorderFree(avl_node_t *node)
{
	if(NULL == node)
	{
		return;
	}
	
	AvlPostorderFree(AvlNodeGetLeftChild(node));
	
	AvlPostorderFree(AvlNodeGetRightChild(node));
	
	AvlNodeDestroy(node);
	
}

/* call function to free all nodes, and then free the struct itself */
void AvlDestroy(avl_t *avl)
{
	assert(avl);
	
	AvlPostorderFree(avl->root);
	
	free(avl);
}

/* find and return the maximal data value of a avl */
static void *AvlFindMaximal(avl_node_t *root)
{
	if(NULL == AvlNodeGetRightChild(root))
	{
		return AvlNodeGetData(root);
	}
	return AvlFindMaximal(AvlNodeGetRightChild(root));
}

/* recursive remove function, that 'rebuilds' the tree while managing find and delete node */
static avl_node_t *AvlRemoveRec(avl_node_t *root, void* data, compare_func_t cmp_func)
{
	void *successor_data = NULL;
	avl_node_t *temp_child = NULL;

	assert(data);
	/* we reached a leaf's child */
	if(root == NULL)
	{
		return NULL;
	}
	
	/* finding the node we need to delete, AVLing */
	if(0 < cmp_func(AvlNodeGetData(root), data))
	{
		AvlNodeSetLeftChild(root, AvlRemoveRec(AvlNodeGetLeftChild(root), data, cmp_func));
	}
	
	/* finding the node we need to delete, AVLing */
	else if(0 > cmp_func(AvlNodeGetData(root), data))
	{
		AvlNodeSetRightChild(root, AvlRemoveRec(AvlNodeGetRightChild(root), data, cmp_func));
	}
	/* we found the node */
	else
	{
		/* it has 2 children */
		if(NULL != AvlNodeGetRightChild(root) && NULL != AvlNodeGetLeftChild(root))
		{        
			/* find the maximal data value in the left sub-tree */   
			successor_data = AvlFindMaximal(AvlNodeGetLeftChild(root));
			/* we are about the swap the 'successor' and the current node, so we delete the current successor after saving its data */
			AvlNodeSetLeftChild(root, AvlRemoveRec(AvlNodeGetLeftChild(root), successor_data, cmp_func));
			/* we put 'successor's data into the current node */
			AvlNodeSetData(root, successor_data);
		}
		/* it has 1 or less childs */
		else
		{
			if(NULL == AvlNodeGetLeftChild(root))
			{
				temp_child = AvlNodeGetRightChild(root);
			}
			else
			{
				temp_child = AvlNodeGetLeftChild(root);
			}
			free(root);
			return temp_child;
		}
	}
	return root;
}

/* API remove function that calls the recursive remove function */
void AvlRemove(avl_t *avl,void *data)
{
	assert(avl);
	assert(data);
	
	avl->root = AvlRemoveRec(avl->root, data, avl->cmp_func);
}


/* 
recursively go over the tree, binary searching the right spot for inserting.
when reaching a leaf's child it means we reached the spot of insertion, so we set the child from NULL to a new node holding the data
returns the root, setting the return value of the API function for the original return value 
 */
static avl_node_t *AvlInsertRec(avl_node_t *node, const void *data, compare_func_t cmp_func, int *flag)
{
	avl_node_t *new_child = NULL;
	assert(data);
	assert(cmp_func);
	
	/* we reached a leaf's child */
	if(NULL == node)
	{
		return AvlNodeCreate(NULL, NULL, data);
	}
	
	/* the inserted data is less than the current node */
	if(cmp_func(AvlNodeGetData(node), data) > 0)
	{
		/* the left child of current node might change if node is a leaf */
		new_child = AvlInsertRec(AvlNodeGetLeftChild(node), data, cmp_func, flag);
		if(NULL == new_child)
		{
			*flag = 1;
			return node;
		}
		AvlNodeSetLeftChild(node, new_child);
	}
	/* the inserted data is more than the current node */
	else if(cmp_func(AvlNodeGetData(node), data) < 0)
	{
		/* the right child of current node might change if node is a leaf */
		new_child = AvlInsertRec(AvlNodeGetRightChild(node), data, cmp_func, flag);
		if(NULL == new_child)
		{
			*flag = 1;
			return node;
		}
		AvlNodeSetRightChild(node, new_child);
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
int AvlInsert(avl_t *avl, const void *data)
{
	int flag = 0;
	assert(avl);
	assert(data);
	avl->root = AvlInsertRec(avl->root, data, avl->cmp_func, &flag);
	return flag;
}

/* recursive height function, returns longest route from a leaf to root, by comparing sibling nodes height */
static size_t AvlHeightRec(avl_node_t *node, size_t right_branch, size_t left_branch)
{
	if(node == NULL)
	{
		return 0;
	}
	
	right_branch = AvlHeightRec(AvlNodeGetRightChild(node), 0, 0);
	left_branch = AvlHeightRec(AvlNodeGetLeftChild(node), 0, 0); 
	
	if(right_branch > left_branch)
	{
		return right_branch + 1;
	}
	return left_branch + 1;
}

/* API wrapper to recursive function */
size_t AvlHeight(const avl_t *avl)
{
	assert(avl);
	return(AvlHeightRec(avl->root, 0, 0));
}

static int CountFunc(void *data, void *param)
{
	*((size_t*)param) = *((size_t*)param) + 1;
	return 0;
	
	(void)(data);
}

/* run foreach with a counter on all nodes, using a function that increments counts on each visit of a node */
size_t AvlSize(const avl_t *avl)
{
	size_t count = 0;
	
	assert(avl);
	
	AvlForEach((avl_t*)avl, IN_ORDER, CountFunc, &count);
	
	return count;
}


/* is avl->root NULL? */
int AvlIsEmpty(const avl_t *avl)
{
	assert(avl);
	return (NULL == avl->root);
}


/*
recursive find function, that uses the fact we traverse an AVL tree.
returns pointer to data, or NULL if no such data exists
*/
static void *AvlFindRec(avl_node_t *node, const void *data, compare_func_t cmp_func)
{
	assert(data);
	assert(cmp_func);
	
	if (NULL == node)
	{
		return NULL;
	}
	if (0 == cmp_func(AvlNodeGetData(node), data))
	{
		return AvlNodeGetData(node);
	}
	else if(0 < cmp_func(AvlNodeGetData(node), data))
	{
		return AvlFindRec(AvlNodeGetLeftChild(node), data, cmp_func);
	}
	else if(0 > cmp_func(AvlNodeGetData(node), data))
	{
		return AvlFindRec(AvlNodeGetRightChild(node), data, cmp_func);
	}
	return NULL;
}


/* API function that wraps my recursive find func */
void *AvlFind(avl_t *avl, const void *data)
{
	assert(avl);
	assert(data);
	
	return AvlFindRec(avl->root, data, avl->cmp_func);
}

/* 
choose traversal mode and action func
return value:
0 - success
1 - action func failed
2 - wrong mode
*/
int AvlForEach(avl_t *avl, traversal_t mode, action_function_t action_func, void *param)
{
	assert(avl);
	assert(action_func);
	switch(mode)
	{
		case IN_ORDER:
			return AvlInorderDataAction(avl->root, action_func, param);
			break;
			
		case PRE_ORDER:
			return AvlPreorderDataAction(avl->root, action_func, param);
			break;
			
		case POST_ORDER:
			return AvlPostorderDataAction(avl->root, action_func, param);
			break;
			
		default:
			break;
	}
	return 2;
}

