#include <stddef.h>
#include <stdio.h>
#include <string.h>

void swap(char* x, char* y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
void permute(char* str, size_t start, size_t end)
{
    size_t i;
    if (start == end)				/* exit condition, when we "created" a new string */
    {
    	printf("%s\n", str);
    	return;
    }
    for (i = start; i <= end; ++i)
    {
		swap((str + start), (str + i));		/* create all possible combinations of current string */
		permute(str, start + 1, end);		/* send sub string recursively */
		swap((str + start), (str + i));		/* recreate original string so next swap is unique */
    }
}
 
int main()
{
    char str[] = "ABC";
    char str2[] = "ABCD";
    size_t n = strlen(str);
    permute(str, 0, n - 1);
    n = strlen(str2);
    permute(str2, 0, n - 1);
    return 0;
}
