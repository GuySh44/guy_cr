#ifndef __AVL_H__ILRD__CR3_
#define __AVL_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef enum {IN_ORDER, PRE_ORDER, POST_ORDER} traversal_t;

typedef struct avl avl_t;

/* returns an integer indicating the result of the action
return value:
    0 - success
    1 - failure
*/
typedef int (*action_function_t)(void *data, void *parameter);

/*returns an integer indicating the result of the comparison, as follows:

        0 - if the data1 and data2 are equal;
        negative value - if data1 is less than data2;
        positive value - if data1 is greater than data2.
*/
typedef int (*compare_func_t)(const void *data1, const void *data2);


/* Create a managment struct for the AVL tree, receives a compare function to compare between elements */
avl_t *AvlCreate(compare_func_t cmp_func);

/* Destroy the AVL tree */
void AvlDestroy(avl_t *avl);

/* remove node in the AVL tree */
void AvlRemove(avl_t *avl,void *data);


/* insert node in the AVL tree, 
return value:
    0 - success
    1 - failure
 */
int AvlInsert(avl_t *avl, const void *data);

/* check the Height(depth) of the AVL tree */
size_t AvlHeight(const avl_t *avl);

/* return the sum of nodes in the AVL tree */
size_t AvlSize(const avl_t *avl);

/* check if the tree contains any node 
return value:
    0 - NotEmpty
    1 - Empty
*/
int AvlIsEmpty(const avl_t *avl);

/* runs through the AVL tree to find the node that contain the received data and return an iterator to it, NULL if does not exist */
void *AvlFind(avl_t *avl, const void *data);

/* runs through the AVL tree using the given mode (pre / in / post order) and using action_func on each node, keeping certain data in parameter if needed, return :
0 - if action_func succeeded,
not 0 - if failed */
int AvlForEach(avl_t *avl, traversal_t mode, action_function_t action_func, void *param);


#endif /*__AVL_H__ILRD__CR3_*/
