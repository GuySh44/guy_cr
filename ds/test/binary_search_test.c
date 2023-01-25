
#include <stdio.h>

#include "binary_search.h"
#include "my_utils.h"

int main()
{
	int arr1[10] = {1, 2, 3, 5, 7, 10, 11, 13, 15, 20};
	int arr2[7] = {1, 2, 3, 5, 7, 10, 11};
	
	printTest("Did we find 3 in arr1 in index 2?(recursive)",!(2 == BinarySearchRec(arr1, 10, 3)));
	printTest("Did we find 11 in arr1 in index 6?(recursive)",!(6 == BinarySearchRec(arr1, 10, 11)));
	printTest("Did we find 1 in arr1 in index 0?(recursive)",!(0 == BinarySearchRec(arr1, 10, 1)));
	printTest("Did we find 20 in arr1 in index 9?(recursive)",!(9 == BinarySearchRec(arr1, 10, 20)));
	printTest("Did we find 7 in arr1 in index 4?(recursive)",!(4 == BinarySearchRec(arr1, 10, 7)));
	
	printf("\n");
	
	printTest("Did we find 3 in arr1 in index 2?(iterative)",!(2 == BinarySearchItera(arr1, 10, 3)));
	printTest("Did we find 11 in arr1 in index 6?(iterative)",!(6 == BinarySearchItera(arr1, 10, 11)));
	printTest("Did we find 1 in arr1 in index 0?(iterative)",!(0 == BinarySearchItera(arr1, 10, 1)));
	printTest("Did we find 20 in arr1 in index 9?(iterative)",!(9 == BinarySearchItera(arr1, 10, 20)));
	printTest("Did we find 7 in arr1 in index 4?(iterative)",!(4 == BinarySearchItera(arr1, 10, 7)));
	
	printf("\n\n");
	
	printTest("Did we find 3 in arr1 in index 2?(recursive)",!(2 == BinarySearchRec(arr2, 7, 3)));
	printTest("Did we find 10 in arr1 in index 5?(recursive)",!(5 == BinarySearchRec(arr2, 7, 10)));
	printTest("Did we find 1 in arr1 in index 0?(recursive)",!(0 == BinarySearchRec(arr2, 7, 1)));
	printTest("Did we find 11 in arr1 in index 6?(recursive)",!(6 == BinarySearchRec(arr2, 7, 11)));
	printTest("Did we find 5 in arr1 in index 3?(recursive)",!(3 == BinarySearchRec(arr2, 7, 5)));
	
	printf("\n");
	
	printTest("Did we find 3 in arr1 in index 2?(iterative)",!(2 == BinarySearchItera(arr2, 7, 3)));
	printTest("Did we find 11 in arr1 in index 6?(iterative)",!(5 == BinarySearchItera(arr2, 7, 10)));
	printTest("Did we find 1 in arr1 in index 0?(iterative)",!(0 == BinarySearchItera(arr2, 7, 1)));
	printTest("Did we find 20 in arr1 in index 9?(iterative)",!(6 == BinarySearchItera(arr2, 7, 11)));
	printTest("Did we find 7 in arr1 in index 4?(iterative)",!(3 == BinarySearchItera(arr2, 7, 5)));
	
	
	return 0;
}
