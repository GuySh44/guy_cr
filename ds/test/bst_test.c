#include<stdio.h> /* printf */


#include "bst.h"


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


int main()
{
	bst_t *first_tree = BstCreate(IntCompare);
	int one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9;
	
	if(NULL == first_tree)
	{
		return 1;
	}
	
	printf("If is empty should be 1\t%d\n", BstIsEmpty(first_tree));
	printf("first tree size should be 0\t%lu\n", BstSize(first_tree));
	
	BstInsert(first_tree, &five);
	BstInsert(first_tree, &four);
	BstInsert(first_tree, &seven);
	printf("first tree size should be 3\t%lu\n", BstSize(first_tree));
	
	BstInsert(first_tree, &two);
	BstInsert(first_tree, &eight);
	printf("first tree size should be 5\t%lu\n", BstSize(first_tree));
	
	
	BstInsert(first_tree, &three);
	BstInsert(first_tree, &six);
	BstInsert(first_tree, &one);
	printf("first tree size should be 8\t%lu\n", BstSize(first_tree));
	
	
	BstInsert(first_tree, &nine);
	printf("first tree size should be 9\t%lu\n", BstSize(first_tree));

	
	printf("If is empty should be 0\t%d\n", BstIsEmpty(first_tree));
	
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
	
	return 0;
}
