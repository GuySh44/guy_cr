#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>

typedef struct node Node;

struct node
{
	void *data;
	Node *next_node;
};

int FibonacciRegular(int element_index);

int FibonacciRecursive(int element_index);

Node* FlipListRecursive(Node* node);

size_t StrlenRecursive(const char *s);

int StrcmpRecursive(const char *s1, const char *s2);

char *StrcpyRecursive(char *dest, const char *src);

char *StrcatRecursive(char *dest, const char *src);

char *StrstrRecursive(const char *haystack, const char *needle);


#endif /* __RECURSION_H__ */
