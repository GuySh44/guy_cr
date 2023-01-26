#ifndef __AVL_NODE_H__
#define __AVL_NODE_H__

/* similar to binary node, but holds balance factor for each node as well */
typedef struct avl_node avl_node_t;

/*
allocate and create an avl tree node, with given child nodes and data to insert
return value:
pointer to the new node 
*/
avl_node_t *AvlNodeCreate(avl_node_t *left_child, avl_node_t *right_child,const void* data);

/*
get a node's balance factor
return value:
node balance factor
*/
short AvlNodeGetBalanceFactor(avl_node_t *node);

/*
get pointer to left child node of a parent
return value:
pointer to the left child
*/
avl_node_t *AvlNodeGetLeftChild(avl_node_t *parent);



/*
get pointer to right child node of a parent
return value:
pointer to the right child
*/
avl_node_t *AvlNodeGetRightChild(avl_node_t *parent);


/*
get the data of the current node
return value:
pointer to data of sent node
*/
void *AvlNodeGetData(avl_node_t *node);

/*
set the balance factor of a node to new_factor
*/
void AvlNodeSetBalanceFactor(avl_node_t *node, short new_factor);

/*
set the address to the left child node 
*/
void AvlNodeSetLeftChild(avl_node_t *parent, avl_node_t *left_child);

/*
set the address to the right child node 
*/
void AvlNodeSetRightChild(avl_node_t *parent, avl_node_t *right_child);

/*
set the pointer to the data of the node 
*/
void AvlNodeSetData(avl_node_t *node, void *data);

/*
free the node 
*/
void AvlNodeDestroy(avl_node_t *node);

#endif /* AVL_NODE_H */
