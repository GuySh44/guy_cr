#include <stdio.h> /* printf */
#include <string.h> /* strcmp */


#include "avl.h"
#include "my_utils.h"

int StringCompare(const void *str1, const void *str2)
{
	return strcmp(*(char**)str1, *(char**)str2);
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
	avl_t *first_tree = AvlCreate(IntCompare);
	avl_t *second_tree = AvlCreate(StringCompare);
	avl_t *third_tree = AvlCreate(IntCompare);
	avl_t *fourth_tree = AvlCreate(IntCompare);
	int zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, eleven = 11, twelve = 12, thirteen = 13, fourteen = 14, fifteen = 15, sixteen = 16, twenty = 20, c_one = 1, c_two = 2, c_three = 3, c_four = 4, c_five = 5, c_six = 6, c_seven = 7, c_eight = 8, c_nine = 9, c_ten = 10, c_fifteen = 15, c_sixteen = 16;
	char *a = "a", *b = "b", *c = "c", *d = "d", *e = "e", *f = "f", *g = "g", *h = "h", *i = "i", *c_a = "a", *c_b = "b", *c_c = "c", *c_d = "d", *c_e = "e", *c_f = "f", *c_g = "g", *c_h = "h", *c_i = "i", *c_j = "j";
	
	if(NULL == first_tree)
	{
		return 1;
	}
	
	if(NULL == second_tree)
	{
		return 1;
	}
	
	printf("Destroy empty tree\n");
	AvlDestroy(fourth_tree);
	
	
	printTest("If first tree is empty", !(1 == AvlIsEmpty(first_tree)));
	printTest("first tree size should be 0", !(0 == AvlSize(first_tree)));
	
	AvlInsert(first_tree, &five);
	printTest("first tree height should be 1", !(1 == AvlHeight(first_tree)));
	printf("Remove first node for funziz\n");
	AvlRemove(first_tree, &c_five);
	printTest("first tree size should be 0", !(0 == AvlSize(first_tree)));
	
	AvlInsert(first_tree, &five);
	AvlInsert(first_tree, &four);
	AvlInsert(first_tree, &seven);
	printTest("first tree height should be 2", !(2 == AvlHeight(first_tree)));
	printTest("first tree size should be 3", !(3 == AvlSize(first_tree)));
	
	AvlInsert(first_tree, &two);
	AvlInsert(first_tree, &eight);
	printTest("first tree height should be 3", !(3 == AvlHeight(first_tree)));
	printTest("first tree size should be 5", !(5 == AvlSize(first_tree)));
	
	
	AvlInsert(first_tree, &three);
	AvlInsert(first_tree, &six);
	AvlInsert(first_tree, &one);
	printTest("first tree height should be 4", !(4 == AvlHeight(first_tree)));
	printTest("first tree size should be 8", !(8 == AvlSize(first_tree)));
	
	
	AvlInsert(first_tree, &nine);
	printTest("first tree height should be 4", !(4 == AvlHeight(first_tree)));
	printTest("first tree size should be 9", !(9 == AvlSize(first_tree)));

	
	printTest("If is empty should be 0", !(0 == AvlIsEmpty(first_tree)));
	
	printTest("does find 1 finds 1?", !(&one == AvlFind(first_tree, &c_one)));
		
	printTest("does find 2 finds 2?", !(&two == AvlFind(first_tree, &c_two)));
		
	printTest("does find 3 finds 3?", !(&three == AvlFind(first_tree, &c_three)));
		
	printTest("does find 4 finds 4?", !(&four == AvlFind(first_tree, &c_four)));
		
	printTest("does find 5 finds 5?", !(&five == AvlFind(first_tree, &c_five)));
		
	printTest("does find 6 finds 6?", !(&six == AvlFind(first_tree, &c_six)));
		
	printTest("does find 7 finds 7?", !(&seven == AvlFind(first_tree, &c_seven)));
		
	printTest("does find 8 finds 8?", !(&eight == AvlFind(first_tree, &c_eight)));
		
	printTest("does find 9 finds 9?", !(&nine == AvlFind(first_tree, &c_nine)));
	
	printTest("does find 10 return NULL?", !(NULL == AvlFind(first_tree, &c_ten)));
	
	printf("\n");
	
	printf("PreOrder:\n");
	
	AvlForEach(first_tree, PRE_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("InOrder\n");
		
	AvlForEach(first_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
			
	printf("PostOrder\n");
	
	AvlForEach(first_tree, POST_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("\n");
	
	printf("try remove non existent value :(\n");
	
	AvlRemove(first_tree, &zero);
	
	printf("we survived :)\n");
		
	AvlDestroy(first_tree);
	
	printf("\n");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		
	printf("Build monster tree:\n");	
	
	AvlInsert(third_tree, &ten);
	
	AvlInsert(third_tree, &eight);
	
	AvlInsert(third_tree, &nine);
	
	AvlInsert(third_tree, &seven);
	
	AvlInsert(third_tree, &two);
	
	AvlInsert(third_tree, &one);
	
	AvlInsert(third_tree, &zero);
	
	AvlInsert(third_tree, &five);
	
	AvlInsert(third_tree, &four);
	
	AvlInsert(third_tree, &six);
	
	AvlInsert(third_tree, &twelve);
	
	AvlInsert(third_tree, &eleven);
	
	AvlInsert(third_tree, &sixteen);
	
	AvlInsert(third_tree, &thirteen);
	
	AvlInsert(third_tree, &fifteen);
	
	AvlInsert(third_tree, &fourteen);
	
	AvlInsert(third_tree, &twenty);
	
	printf("InOrder\n");
		
	AvlForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("Remove 2\n");
	AvlRemove(third_tree, &c_two);
	
	printf("InOrder\n");
	
	AvlForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("Remove 7\n");
	AvlRemove(third_tree, &c_seven);
	
	printf("InOrder\n");
	
	AvlForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("Remove 16\n");
	AvlRemove(third_tree, &c_sixteen);
	
	printf("InOrder\n");
	
	AvlForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	printf("Remove 15 you smell me?\n");
	AvlRemove(third_tree, &c_fifteen);
	
	printf("InOrder\n");
	
	AvlForEach(third_tree, IN_ORDER, PrintInt, NULL);
	
	printf("\n");
	
	AvlDestroy(third_tree);
	
	printf("\n");
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	printTest("If is empty should be 1", !(1 == AvlIsEmpty(second_tree)));
	printTest("first tree size should be 0", !(0 == AvlSize(second_tree)));
	
	AvlInsert(second_tree, &e);
	printTest("first tree height should be 1", !(1 == AvlHeight(second_tree)));
	AvlInsert(second_tree, &d);
	AvlInsert(second_tree, &g);
	printTest("first tree height should be 2", !(2 == AvlHeight(second_tree)));
	printTest("first tree size should be 3", !(3 == AvlSize(second_tree)));
	
	AvlInsert(second_tree, &b);
	AvlInsert(second_tree, &h);
	printTest("first tree height should be 3", !(3 == AvlHeight(second_tree)));
	printTest("first tree size should be 5", !(5 == AvlSize(second_tree)));
	
	
	AvlInsert(second_tree, &c);
	AvlInsert(second_tree, &f);
	AvlInsert(second_tree, &a);
	printTest("first tree height should be 4", !(4 == AvlHeight(second_tree)));
	printTest("first tree size should be 8", !(8 == AvlSize(second_tree)));
	
	
	AvlInsert(second_tree, &i);
	printTest("first tree height should be 4", !(4 == AvlHeight(second_tree)));
	printTest("first tree size should be 9", !(9 == AvlSize(second_tree)));

	
	printTest("If is empty should be 0", !(0 == AvlIsEmpty(second_tree)));
	
	printTest("does find a finds a?", !(&a == AvlFind(second_tree, &c_a)));
		
	printTest("does find b finds b?", !(&b == AvlFind(second_tree, &c_b)));
		
	printTest("does find c finds c?", !(&c == AvlFind(second_tree, &c_c)));
		
	printTest("does find d finds d?", !(&d == AvlFind(second_tree, &c_d)));
		
	printTest("does find e finds e?", !(&e == AvlFind(second_tree, &c_e)));
		
	printTest("does find f finds f?", !(&f == AvlFind(second_tree, &c_f)));
		
	printTest("does find g finds g?", !(&g == AvlFind(second_tree, &c_g)));
		
	printTest("does find h finds h?", !(&h == AvlFind(second_tree, &c_h)));
		
	printTest("does find i finds i?", !(&i == AvlFind(second_tree, &c_i)));
	
	printTest("does find j return NULL?", !(NULL == AvlFind(second_tree, &c_j)));
	
	printf("\n");
	
	printf("PreOrder:\n");
	
	AvlForEach(second_tree, PRE_ORDER, PrintString, NULL);
	
	printf("\n");
	
	printf("InOrder\n");
		
	AvlForEach(second_tree, IN_ORDER, PrintString, NULL);
	
	printf("\n");
			
	printf("PostOrder\n");
	
	AvlForEach(second_tree, POST_ORDER, PrintString, NULL);
	
	printf("\n");
	
	
	
	AvlDestroy(second_tree);
	
	return 0;
}
