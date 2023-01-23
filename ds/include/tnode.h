#ifndef __TNODE_H__
#define __TNODE_H__

typedef struct bin_node bin_node_t;

/*
allocate and create a binary tree node, with given child nodes and data to insert
return value:
pointer to the new node 
*/
bin_node_t *TreeNodeCreate(bin_node_t *left_child, bin_node_t *right_child,const void* data);

/*
get pointer to left child node of a parent
return value:
pointer to the left child
*/
bin_node_t *TreeNodeGetLeftChild(bin_node_t *parent);



/*
get pointer to right child node of a parent
return value:
pointer to the right child
*/
bin_node_t *TreeNodeGetRightChild(bin_node_t *parent);


/*
get the data of the current node
return value:
pointer to data of sent node
*/
void *TreeNodeGetData(bin_node_t *node);

/*
set the address to the left child node 
*/
void TreeNodeSetLeftChild(bin_node_t *parent, bin_node_t *left_child);

/*
set the address to the right child node 
*/
void TreeNodeSetRightChild(bin_node_t *parent, bin_node_t *right_child);

/*
set the pointer to the data of the node 
*/
void TreeNodeSetData(bin_node_t *node, void *data);

/*
free the node 
*/
void TreeNodeDestroy(bin_node_t *node);

#endif /* TNODE_H */
