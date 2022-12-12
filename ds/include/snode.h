#ifndef __SNODE_H__
#define __SNODE_H__

typedef struct node s_list_node;

s_list_node *SNodeCreate(s_list_node *next_node, void* data);

s_list_node *SNodeGetNext(s_list_node *current);

void *SNodeGetData(s_list_node *node);

void SNodeSetNext(s_list_node *node, s_list_node *next_node);

void SNodeSetData(s_list_node *node, void *data);

void SNodeDestroy(s_list_node *node);

#endif /* SNODE_H */
