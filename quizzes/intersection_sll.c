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

size_t getLen(sll_node *node)
{
	size_t count = 1;
	while(NULL != node->next_node)
	{
		node = node->next_node;
		++count;
	}
	return count;
}

int IsIntersecting(sll_node *head1, sll_node *head2)
{
	return getEnd(head1) == getEnd(head2);
}

void ListSeperate(sll_node *head1, sll_node *head2)
{
	size_t list1_len = getLen(head1);
	size_t list2_len = getLen(head2);
	sll_node *last1; 
	while(list1_len > list2_len)
	{
		head1 = getNext(head1);
		--list1_len;
	}
	while(list2_len > list1_len)
	{
		head2 = getNext(head2);
		--list2_len;
	}
	while(head1 != head2)
	{
		last1 = head1;
		head1 = getNext(head1);
		head2 = getNext(head2);
	}
	last1->next_node = NULL;
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
	sll_node *node8 = malloc(sizeof(*node8));
	sll_node *node9 = malloc(sizeof(*node9));
	sll_node *node10 = malloc(sizeof(*node10));

	node1->next_node = node2;
	node2->next_node = node3;
	node3->next_node = node4;
	node4->next_node = node5;
	node5->next_node = node6;
	node6->next_node = NULL;
	
	node7->next_node = node8;
	node8->next_node = node9;
	node9->next_node = node10;
	node10->next_node = node3;
	
	printf("Are the lists intersecting?\t%d\n", IsIntersecting(node1, node7));
	ListSeperate(node1, node7);
	printf("Are the lists still intersecting?\t%d\n", IsIntersecting(node1, node7));
	return 0;
	
}
