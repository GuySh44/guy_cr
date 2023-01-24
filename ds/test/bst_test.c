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
	bst_t *third_tree = BstCreate(IntCompare);
	int zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, eleven = 11, twelve = 12, thirteen = 13, fourteen = 14, fifteen = 15, sixteen = 16, twenty = 20, c_one = 1, c_two = 2, c_three = 3, c_four = 4, c_five = 5, c_six = 6, c_seven = 7, c_eight = 8, c_nine = 9, c_ten = 10;
	char *a = "a", *b = "b", *c = "c", *d = "d", *e = "e", *f = "f", *g = "g", *h = "h", *i = "i", *c_a = "a", *c_b = "b", *c_c = "c", *c_d = "d", *c_e = "e", *c_f = "f", *c_g = "g", *c_h = "h", *c_i = "i", *c_j = "j";
	
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
	printf("Remove first node for funziz\n");
	BstRemove(first_tree, &c_five);
	printTest("first tree size should be 0", !(0 == BstSize(first_tree)));
	
	BstInsert(first_tree, &five);
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
	
	printTest("does find 1 finds 1?", !(&one == BstFind(first_tree, &c_one)));
		
	printTest("does find 2 finds 2?", !(&two == BstFind(first_tree, &c_two)));
		
	printTest("does find 3 finds 3?", !(&three == BstFind(first_tree, &c_three)));
		
	printTest("does find 4 finds 4?", !(&four == BstFind(first_tree, &c_four)));
		
	printTest("does find 5 finds 5?", !(&five == BstFind(first_tree, &c_five)));
		
	printTest("does find 6 finds 6?", !(&six == BstFind(first_tree, &c_six)));
		
	printTest("does find 7 finds 7?", !(&seven == BstFind(first_tree, &c_seven)));
		
	printTest("does find 8 finds 8?", !(&eight == BstFind(first_tree, &c_eight)));
		
	printTest("does find 9 finds 9?", !(&nine == BstFind(first_tree, &c_nine)));
	
	printTest("does find 10 return NULL?", !(NULL == BstFind(first_tree, &c_ten)));
	
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
		
	printf("Build monster tree:\n");	
	
	BstInsert(third_tree, &ten);
	
	BstInsert(third_tree, &eight);
	
	BstInsert(third_tree, &nine);
	
	BstInsert(third_tree, &seven);
	
	BstInsert(third_tree, &two);
	
	BstInsert(third_tree, &one);
	
	BstInsert(third_tree, &zero);
	
	BstInsert(third_tree, &five);
	
	BstInsert(third_tree, &four);
	
	BstInsert(third_tree, &six);
	
	BstInsert(third_tree, &twelve);
	
	BstInsert(third_tree, &eleven);
	
	BstInsert(third_tree, &sixteen);
	
	BstInsert(third_tree, &thirteen);
	
	BstInsert(third_tree, &fifteen);
	
	BstInsert(third_tree, &fourteen);
	
	BstInsert(third_tree, &twenty);
	
	printf("InOrder\n");
		
	BstForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("Remove 2\n");
	BstRemove(third_tree, &c_two);
	
	printf("InOrder\n");
	
	BstForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("Remove 7\n");
	BstRemove(third_tree, &c_seven);
	
	printf("InOrder\n");
	
	BstForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
		
	BstDestroy(third_tree);
	
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
	
	printTest("does find a finds a?", !(&a == BstFind(second_tree, &c_a)));
		
	printTest("does find b finds b?", !(&b == BstFind(second_tree, &c_b)));
		
	printTest("does find c finds c?", !(&c == BstFind(second_tree, &c_c)));
		
	printTest("does find d finds d?", !(&d == BstFind(second_tree, &c_d)));
		
	printTest("does find e finds e?", !(&e == BstFind(second_tree, &c_e)));
		
	printTest("does find f finds f?", !(&f == BstFind(second_tree, &c_f)));
		
	printTest("does find g finds g?", !(&g == BstFind(second_tree, &c_g)));
		
	printTest("does find h finds h?", !(&h == BstFind(second_tree, &c_h)));
		
	printTest("does find i finds i?", !(&i == BstFind(second_tree, &c_i)));
	
	printTest("does find j return NULL?", !(NULL == BstFind(second_tree, &c_j)));
	
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
