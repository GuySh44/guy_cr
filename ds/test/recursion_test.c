#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "recursion.h"
#include "my_utils.h"

int main()
{
	Node *node1 = malloc(sizeof(*node1));
	Node *node2 = malloc(sizeof(*node2));
	Node *node3 = malloc(sizeof(*node3));
	Node *node4 = malloc(sizeof(*node4));
	Node *node5 = malloc(sizeof(*node5));	
	Node *node6 = malloc(sizeof(*node6));
	Node *node7 = malloc(sizeof(*node7));

	char dest1_org[5];
	char* src1_org = "abcd";
	char dest1_my[5];
	char* src1_my = "abcd";
	
	char dest2_org[7];
	char* src2_org = "abcd";
	char dest2_my[7];
	char* src2_my = "abcd";	
	
	char dest6_org[7] = {'a','b','c','d','\0'};
	char* src6_org = "ef";
	char dest6_my[7] = {'a','b','c','d','\0'};
	char* src6_my = "ef";
	
	char dest7_org[7] = {'a','b','c','d','\0'};
	char* src7_org = "";
	char dest7_my[7] = {'a','b','c','d','\0'};
	char* src7_my = "";
		
	const char* strstr_check1 = "ccbca";
	
	const char* strstr_check2 = "aaccbcca";
	
	const char* strstr_check3 = "";
	
	const char* strstr_check4 = "ac";
	
	int intagers[5] = {30,-5,18,14,-3};
	
	stack_t *mystack = StackCreate(5,4);
	
	
	printTest("Is regular fibonacci 0 = 0?", !(0 == FibonacciRegular(0)));
	printTest("Is regular fibonacci 1 = 1?", !(1 == FibonacciRegular(1)));
	printTest("Is regular fibonacci 2 = 1?", !(1 == FibonacciRegular(2)));
	printTest("Is regular fibonacci 3 = 2?", !(2 == FibonacciRegular(3)));
	printTest("Is regular fibonacci 4 = 3?", !(3 == FibonacciRegular(4)));
	printTest("Is regular fibonacci 5 = 5?", !(5 == FibonacciRegular(5)));
	printTest("Is regular fibonacci 6 = 8?", !(8 == FibonacciRegular(6)));
	printTest("Is regular fibonacci 7 = 13?", !(13 == FibonacciRegular(7)));
	printTest("Is recursive fibonacci 0 = 0?", !(0 == FibonacciRecursive(0)));
	printTest("Is recursive fibonacci 1 = 1?", !(1 == FibonacciRecursive(1)));
	printTest("Is recursive fibonacci 2 = 1?", !(1 == FibonacciRecursive(2)));
	printTest("Is recursive fibonacci 3 = 2?", !(2 == FibonacciRecursive(3)));
	printTest("Is recursive fibonacci 4 = 3?", !(3 == FibonacciRecursive(4)));
	printTest("Is recursive fibonacci 5 = 5?", !(5 == FibonacciRecursive(5)));
	printTest("Is recursive fibonacci 6 = 8?", !(8 == FibonacciRecursive(6)));
	printTest("Is recursive fibonacci 7 = 13?", !(13 == FibonacciRecursive(7)));
	
	node1->next_node = node2;
	node2->next_node = node3;
	node3->next_node = node4;
	node4->next_node = node5;
	node5->next_node = node6;
	node6->next_node = node7;
	node7->next_node = NULL;
	
	FlipListRecursive(node1);
	
	printTest("is node7->node6?", !(node7->next_node == node6));
	printTest("is node6->node5?", !(node6->next_node == node5));
	printTest("is node5->node4?", !(node5->next_node == node4));
	printTest("is node4->node3?", !(node4->next_node == node3));
	printTest("is node3->node2?", !(node3->next_node == node2));
	printTest("is node2->node1?", !(node2->next_node == node1));
	printTest("is node1->NULL?", !(node1->next_node == NULL));
	
	
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	
	
	printTest("regular strlen of empty string is 1", !(0 == strlen("")));
	printTest("recursive strlen of empty string is 1", !(0 == StrlenRecursive("")));
	printTest("regular strlen of a is 2", !(1 == strlen("a")));
	printTest("recursive strlen of a is 2", !(1 == StrlenRecursive("a")));
	printTest("regular strlen of aa is 3", !(2 == strlen("aa")));
	printTest("recursive strlen of aa is 3", !(2 == StrlenRecursive("aa")));
	
	printTest("regular strcmp of aa and aaa", !(strcmp("aa","aaa") < 0));
	printTest("recursive strcmp of aa and aaa", !(StrcmpRecursive("aa","aaa") < 0));
	printTest("regular strcmp of ab and aa", !(strcmp("ab","aa") > 0));
	printTest("recursive strcmp of ab and aa", !(StrcmpRecursive("ab","aa") > 0));
	printTest("regular strcmp of aa and aa", !(strcmp("aa","aa") == 0));
	printTest("recursive strcmp of aa and aa", !(StrcmpRecursive("aa","aa") == 0));
	
	strcpy(dest1_org,src1_org);
	StrcpyRecursive(dest1_my,src1_my);
	
	strcpy(dest2_org,src2_org);
	StrcpyRecursive(dest2_my,src2_my);
	
	printTest("regular strcpy of abcd exact size", strcmp(dest1_org,src1_org));
	printTest("recursive strcpy of abcd exact size", strcmp(dest1_my,src1_my));
	printTest("regular strcpy of abcd dest bigger size", strcmp(dest2_org,src2_org));
	printTest("recursive strcpy of abcd dest bigger size", strcmp(dest2_my,src2_my));
	
	
	strcat(dest6_org,src6_org);
	StrcatRecursive(dest6_my,src6_my);
	
	strcat(dest7_org,src7_org);
	StrcatRecursive(dest7_my,src7_my);
	
	printTest("are regular strcat and recursive strcat the same for exact size?",strcmp(dest6_org, dest6_my));
	printTest("are regular strcat and recursive strcat the same for empty src?",strcmp(dest7_org, dest7_my));
	
	
	printTest("is strstr regular and recursive return the same needle for ccbca find cbc",strcmp(strstr(strstr_check1,"cbc"), StrstrRecursive(strstr_check1,"cbc")));
	printTest("is strstr regular and recursive return the same needle for ccbca find empty string",strcmp(strstr(strstr_check1,""), StrstrRecursive(strstr_check1,"")));
	printTest("is strstr regular and recursive return the same needle for aaccbcca return first cc",strcmp(strstr(strstr_check2,"cc"), StrstrRecursive(strstr_check2,"cc")));
	printTest("is strstr regular and recursive return the same needle for empty string in empty string",strcmp(strstr(strstr_check3,""), StrstrRecursive(strstr_check3,"")));
	printTest("is strstr regular and recursive return the same needle for string not found return NULL",!(0 == StrstrRecursive(strstr_check4,"vvv")));
	
	StackPush(mystack, intagers);
	StackPush(mystack, intagers+1);
	StackPush(mystack, intagers+2);
	StackPush(mystack, intagers+3);
	StackPush(mystack, intagers+4);
	
	printf("\n");
	printf("the stack before sort is:\n");
	printf("\ntop\n%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d bottom\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	
	StackPush(mystack, intagers);
	StackPush(mystack, intagers+1);
	StackPush(mystack, intagers+2);
	StackPush(mystack, intagers+3);
	StackPush(mystack, intagers+4);
	
	SortStack(mystack);
	
	printf("\n");
	printf("the stack after sort is:\n");
	printf("\ntop\n%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d->\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	printf("%d bottom\n", *((int*)StackPeek(mystack)));
	StackPop(mystack);
	
	StackDestroy(mystack);

	return 0;
}
