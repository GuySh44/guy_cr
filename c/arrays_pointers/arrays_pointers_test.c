#include "arrays_pointers.h"
int main()
{	
	int arr1[4][4] = {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
	int res[4];
	int *arr2[4];
	int **arr3;
	int k = 0;
	printf("index for 5 is: %lu\n",josephus(5,0));
	printf("index for 30 is: %lu\n",josephus(30,0));	
	printf("index for 40 is: %lu\n",josephus(40,0));	
	printf("index for 50 is: %lu\n",josephus(50,0));
	printf("index for 100 is: %lu\n",josephus(100,0));
	printCTypes();
	array1(arr1);
	array2(arr2);
	array3(arr3);
	
	rowCalc(arr1, res, 4, 4);
	for (; k < 4; k++)
	{
		printf("%d ",res[k]);
	}
	printf("\n");
	return 0;
}

