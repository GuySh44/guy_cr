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

void setNext(sll_node *head, sll_node *next)
{
	head->next_node = next;
}

sll_node *getEnd(sll_node *node)
{
	while(NULL != node->next_node)
	{
		node = node->next_node;
	}
	return node;
}

void ReverseSLL(sll_node *head)
{
	sll_node *last = NULL;
	sll_node *next = getNext(head);
	sll_node *curr = head;
	while(NULL != next)
	{
		setNext(curr, last);
		last = curr;
		curr = next;
		next = getNext(next);
	}
	setNext(curr, last);
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
	node7->next_node = NULL;
	
	ReverseSLL(node1);
	
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	return 0;
}

