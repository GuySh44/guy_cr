#include <stdio.h> /* printf */
#include <string.h> /* strcmp */


#include "bst.h"
#include "my_utils.h"

int StringCompare(const void *str1, const void *str2)
{
	return strcmp((char*)str1, (char*)str2);
}

int IntCompare(const void *num1, const void *num2)
{
	return *((int*)num1) - *((int*)num2);
}

int PrintInt(void *data, void *param)
{
	
	printf("%d ", *(int*)data);
	return 0;

	(void)param;
}

int PrintString(void *data, void *param)
{
	printf("\"%s\" ", *(char**)data);
	return 0;

	(void)param;

}

int main()
{
	bst_t *first_tree = BstCreate(IntCompare);
	bst_t *second_tree = BstCreate(StringCompare);
	int one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9;
	char *a = "a", *b = "b", *c = "c", *d = "d", *e = "e", *f = "f", *g = "g", *h = "h", *i = "i";
	
	if(NULL == first_tree)
	{
		return 1;
	}
	
	if(NULL == second_tree)
	{
		return 1;
	}
	
	printTest("If first tree is empty", !(1 == BstIsEmpty(first_tree)));
	printTest("first tree size should be 0", !(0 == BstSize(first_tree)));
	
	BstInsert(first_tree, &five);
	printTest("first tree height should be 1", !(1 == BstHeight(first_tree)));
	BstInsert(first_tree, &four);
	BstInsert(first_tree, &seven);
	printTest("first tree height should be 2", !(2 == BstHeight(first_tree)));
	printTest("first tree size should be 3", !(3 == BstSize(first_tree)));
	
	BstInsert(first_tree, &two);
	BstInsert(first_tree, &eight);
	printTest("first tree height should be 3", !(3 == BstHeight(first_tree)));
	printTest("first tree size should be 5", !(5 == BstSize(first_tree)));
	
	
	BstInsert(first_tree, &three);
	BstInsert(first_tree, &six);
	BstInsert(first_tree, &one);
	printTest("first tree height should be 4", !(4 == BstHeight(first_tree)));
	printTest("first tree size should be 8", !(8 == BstSize(first_tree)));
	
	
	BstInsert(first_tree, &nine);
	printTest("first tree height should be 4", !(4 == BstHeight(first_tree)));
	printTest("first tree size should be 9", !(9 == BstSize(first_tree)));

	
	printTest("If is empty should be 0", !(0 == BstIsEmpty(first_tree)));
	
	printf("\n");
	
	printf("PreOrder:\n");
	
	BstForEach(first_tree, PRE_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("InOrder\n");
		
	BstForEach(first_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
			
	printf("PostOrder\n");
	
	BstForEach(first_tree, POST_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	
	BstDestroy(first_tree);
	
	printf("\n");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	printTest("If is empty should be 1", !(1 == BstIsEmpty(second_tree)));
	printTest("first tree size should be 0", !(0 == BstSize(second_tree)));
	
	BstInsert(second_tree, &e);
	printTest("first tree height should be 1", !(1 == BstHeight(second_tree)));
	BstInsert(second_tree, &d);
	BstInsert(second_tree, &g);
	printTest("first tree height should be 2", !(2 == BstHeight(second_tree)));
	printTest("first tree size should be 3", !(3 == BstSize(second_tree)));
	
	BstInsert(second_tree, &b);
	BstInsert(second_tree, &h);
	printTest("first tree height should be 3", !(3 == BstHeight(second_tree)));
	printTest("first tree size should be 5", !(5 == BstSize(second_tree)));
	
	
	BstInsert(second_tree, &c);
	BstInsert(second_tree, &f);
	BstInsert(second_tree, &a);
	printTest("first tree height should be 4", !(4 == BstHeight(second_tree)));
	printTest("first tree size should be 8", !(8 == BstSize(second_tree)));
	
	
	BstInsert(second_tree, &i);
	printTest("first tree height should be 4", !(4 == BstHeight(second_tree)));
	printTest("first tree size should be 9", !(9 == BstSize(second_tree)));

	
	printTest("If is empty should be 0", !(0 == BstIsEmpty(second_tree)));
	
	printf("\n");
	
	printf("PreOrder:\n");
	
	BstForEach(second_tree, PRE_ORDER, PrintString, NULL);
	
	printf("\n");
	
	printf("InOrder\n");
		
	BstForEach(second_tree, IN_ORDER, PrintString, NULL);
	
	printf("\n");
			
	printf("PostOrder\n");
	
	BstForEach(second_tree, POST_ORDER, PrintString, NULL);
	
	printf("\n");
	
	
	
	BstDestroy(second_tree);
	
	return 0;
}
