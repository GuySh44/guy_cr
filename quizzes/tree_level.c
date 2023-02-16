#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "tnode.h"

typedef struct queue {
    void** items;
    int front;   
    int rear;     
    int size;   
} queue_t;

queue_t* create_queue(int size) {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
	if(NULL == q)
	{
		return NULL;
	}
	
    q->items = (void**)malloc(size * sizeof(void*));
	if(NULL== q->items)
	{
		free(q);
		return NULL;
	}
	
    q->front = -1;
    q->rear = -1;
    q->size = size;
    return q;
}

int is_empty(queue_t* q) {
    return q->front == -1;
}

int is_full(queue_t* q) {
    return (q->rear + 1) % q->size == q->front;
}

void enqueue(queue_t* q, void* item) {
    if (is_full(q)) {
        return; 
    }
    if (is_empty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->size;
    q->items[q->rear] = item;
}

void* dequeue(queue_t* q) {
    void* item = NULL;
	if (is_empty(q)) {
        return NULL; 
    }
    item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size;
    }
    return item;
}

void* peek(queue_t* q) {
    if (is_empty(q)) {
        return NULL;
    }
    return q->items[q->front];
}

void destroy_queue(queue_t* q) {
    free(q->items);
    free(q);
}




void LevelBLevelPrint(bin_node_t *root, queue_t *queue)
{
	bin_node_t *print_node = NULL, *left_child = NULL, *right_child = NULL;
	
	enqueue(queue, root);
	while(!is_empty(queue))
	{
		print_node = dequeue(queue);
		printf("%d\n", *((int*)TreeNodeGetData(print_node)));
		
		left_child = TreeNodeGetLeftChild(print_node);
		if(NULL != left_child)
		{
			enqueue(queue, left_child);
		}
		
		right_child = TreeNodeGetRightChild(print_node);
		if(NULL != right_child)
		{
			enqueue(queue, right_child);
		}
	}
}

int main()
{
	queue_t *queue = create_queue(10);
	int one = 1, two = 2, three = 3, four = 4, five = 5;
	
	bin_node_t *one_node, *two_node, *three_node, *four_node, *five_node;
	
	four_node = TreeNodeCreate(NULL, NULL, &four);
	five_node = TreeNodeCreate(NULL, NULL, &five);
	two_node = TreeNodeCreate(four_node, five_node, &two);
	three_node = TreeNodeCreate(NULL, NULL, &three);
	one_node = TreeNodeCreate(two_node, three_node, &one);
	
	LevelBLevelPrint(one_node, queue);
	
	TreeNodeDestroy(one_node);
	TreeNodeDestroy(two_node);
	TreeNodeDestroy(three_node);
	TreeNodeDestroy(four_node);
	TreeNodeDestroy(five_node);
	
	destroy_queue(queue);
	
	return 0;
}