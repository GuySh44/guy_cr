
#include <assert.h>
#include <stddef.h> /* size_t */

#include "tnode.h"
#include "bst.h"

struct bst_iter
{
	bin_node_t *node;
};

struct bst
{
	compare_func_t cmp_func;
	bin_node_t *root;
};



bst_t *BstCreate(compare_func_t cmp_func);


void BstDestroy(bst_t *bst);


void BstRemove(bst_iter_t *iter);


int BstInsert(bst_t *bst, const void *data);


size_t BstHeight(const bst_t *bst);


size_t BstSize(const bst_t *bst);


int BstIsEmpty(const bst_t *bst);


bst_iter_t *BstFind(bst_t *bst, const void *data);


int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param);

