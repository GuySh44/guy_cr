#include <stdio.h>

void SwapPtr(int **p1_ptr, int **p2_ptr)
{
	int *temp = *p1_ptr;
	
	*p1_ptr = *p2_ptr;
	*p2_ptr = temp;
}



int main()
{
    int a = 5;
    int b = 6;
    int *p1 = &a;
    int *p2 = &b;
    SwapPtr(&p1, &p2);  
    printf("%d,%d\n", a, b); /* prints 5,6 */
    printf("%d,%d\n", *p1, *p2); /* prints 6,5 */
    return 0;
}
