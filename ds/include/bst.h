#ifndef __BST_H__ILRD__CR3_
#define __BST_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef enum {IN_ORDER, PRE_ORDER, POST_ORDER} traversal_t;

typedef struct bst bst_t;
typedef struct bst_iter bst_iter_t;

typedef int (*action_function_t)(void *data, void *parameter);
typedef int (*compare_func_t)(const void *data1, const void *data2);


/* Create binary search tree by creatin a dummy node, receives a compare function to compare between elements */
bst_t *BstCreate(compare_func_t cmp_func);

/* Destroy the binary search tree */
void BstDestroy(bst_t *bst);

/* remove node in the binary search tree */
void BstRemove(bst_iter_t *iter);

/* insert node in the binary search tree */
int BstInsert(bst_t *bst, const void *data);

/* check the Height(depth) of the binary search tree */
size_t BstHeight(const bst_t *bst);

/* return the sum of nodes in the binary search tree */
size_t BstSize(const bst_t *bst);

/* check if the tree contains any node */
int BstIsEmpty(const bst_t *bst);

/* runs through the binary search tree to find the node that contain the received data and return an iterator to it */
bst_iter_t *BstFind(bst_t *bst, const void *data);

/* runs through the binary search tree using the given mode (pre / in / post order) and using action_func on each node, keeping certain data in parameter if needed, return 0 if action_func succeeded, not 0 if failed */
int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param);


#endif /*__BST_H__ILRD__CR3_*/
