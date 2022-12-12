#ifndef __SNODE_H__
#define __SNODE_H__

typedef struct node s_list_node;

/*
allocate and create a singly linked node, with given next node and data to insert
return value:
pointer to the new node 
*/
s_list_node *SNodeCreate(s_list_node *next_node, void* data);

/*
get pointer to the next node pointed to by the current node
return value:
pointer to the next node
*/
s_list_node *SNodeGetNext(s_list_node *current);


/*
get the data of the current node
return value:
pointer to data of sent node
*/
void *SNodeGetData(s_list_node *node);

/*
set the address to the next node 
*/
void SNodeSetNext(s_list_node *node, s_list_node *next_node);

/*
set the pointer to the data of the node 
*/
void SNodeSetData(s_list_node *node, void *data);

/*
free the node 
*/
void SNodeDestroy(s_list_node *node);

#endif /* SNODE_H */
