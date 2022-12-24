#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct node sll_node;

struct node
{
	void* data;
	sll_node *next_node;
};

sll_node *getNext(sll_node *node)
{
	return node->next_node;
}

sll_node *getEnd(sll_node *node)
{
	while(NULL != node->next_node)
	{
		node = node->next_node;
	}
	return node;
}

int IsLoop(sll_node *head) 
{
    sll_node *slow = head;
    sll_node *fast = head;
    while(NULL != getNext(fast) && NULL != getNext(getNext(fast)))
    {
        slow = getNext(slow);
        fast = getNext(getNext(fast));
        if(fast == slow)
        {
        	return 1;
    	}
    }
    return 0;
}

void OpenLoop(sll_node *head) 
{
    sll_node *slow = head;
    sll_node *fast = head;
    sll_node *trailer = head;
    sll_node *loop_forward = head;
    size_t loop_size = 0;
    size_t i = 1;
    while(NULL != getNext(fast) && NULL != getNext(getNext(fast)))
    {
        slow = getNext(slow);
        fast = getNext(getNext(fast));
        if(fast == slow)
        {
        	slow = getNext(slow);
        	++loop_size;
        	break;
        }
    }
    while(slow != fast)
    {
    	slow = getNext(slow);
 	   	++loop_size;
    }
    for(; i < loop_size; ++i)
    {
    	loop_forward = getNext(loop_forward);
    }
    while(trailer != getNext(loop_forward))
    {
    	trailer = getNext(trailer);
    	loop_forward = getNext(loop_forward);
    }
    loop_forward->next_node = NULL;
}

int main()
{
	sll_node *node1 = malloc(sizeof(*node1));
	sll_node *node2 = malloc(sizeof(*node2));
	sll_node *node3 = malloc(sizeof(*node3));
	sll_node *node4 = malloc(sizeof(*node4));
	sll_node *node5 = malloc(sizeof(*node5));	
	sll_node *node6 = malloc(sizeof(*node6));
	sll_node *node7 = malloc(sizeof(*node7));
	
	node1->next_node = node2;
	node2->next_node = node3;
	node3->next_node = node4;
	node4->next_node = node5;
	node5->next_node = node6;
	node6->next_node = node7;
	node7->next_node = node3;
	
	printf("Did we find loop?\t%d\n", IsLoop(node1));
	OpenLoop(node1);
	printf("Did we free loop? node7 should point to NULL\n");
	printf("node7:\t%p\nlast node:\t%p\n", (void*)node7, (void*)getEnd(node1));
	printf("Did we find loop?\t%d\n", IsLoop(node1));
	
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	return 0;
}
