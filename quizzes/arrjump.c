#include <stddef.h>
#include <stdio.h>

int ArrJump2(int *arr, size_t size, size_t sum)
{
	int how_far = arr[0];
	
	if(arr[0] < 0)
	{
		return 0;
	}
	arr[0] = -arr[0];
	
	if((size_t)how_far == size - 1)
	{
		arr[0] = -arr[0];
		return 1;
	}
	
	if((size_t)how_far < size - 1 && how_far > 0)
	{
		if(ArrJump2(arr + how_far, size - how_far, sum + how_far))
		{
			arr[0] = -arr[0];
			return 1;
		}
	}
	
	if((size_t)how_far < sum && how_far > 0)
	{
		if(ArrJump2(arr - how_far, size + how_far, sum - how_far))
		{
			arr[0] = -arr[0];
			return 1;
		}
	}
	arr[0] = -arr[0];	
	return 0;
}

int ArrJump(int *arr, size_t size)
{
	return ArrJump2(arr, size, 0);
}


int main()
{
	int arr1[9] = {2, 4, 1, 6, 4, 2, 4, 3, 5};
	int arr2[9] = {2, 4, 1, 6, 3, 2, 4, 3, 5};
	int arr3[9] = {2, 4, 0, 6, 3, 2, 4, 3, 5};
	int arr4[1] = {0};
	int arr5[9] = {2, 4, 1, 6, 2, 2, 2, 3, 5};
	
	printf("Can we get from start to end in arr1[9] = {2, 4, 1, 6, 4, 2, 4, 3, 5}:\t%d\n", ArrJump(arr1, 9));
	printf("Can we get from start to end in arr2[9] = {2, 4, 1, 6, 3, 2, 4, 3, 5}:\t%d\n", ArrJump(arr2, 9));
	printf("Can we get from start to end in arr3[9] = {2, 4, 0, 6, 3, 2, 4, 3, 5}:\t%d\n", ArrJump(arr3, 9));
	printf("Can we get from start to end in arr4[1] = {0}:\t%d\n", ArrJump(arr4, 1));
	printf("Can we get from start to end in arr5[9] = {2, 4, 1, 6, 2, 2, 2, 3, 5}:\t%d\n", ArrJump(arr5, 9));
	return 0;
}
