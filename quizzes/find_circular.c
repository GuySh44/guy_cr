#include <stddef.h>
#include <stdio.h>

size_t FindCircular(int *arr, size_t size, int target)
{
	size_t top = size - 1;
	size_t bottom = 0;
	size_t mid = size / 2;
	size_t offset = 0;
	
	while(arr[mid] > (int)(arr[(mid - 1) % size]))
	{
		if (arr[top] > arr[mid])
		{
			top = mid - 1;
		}
		else
		{
			bottom = mid + 1;
		}
		mid = (top + bottom) / 2;
	}
	offset = mid;
	top = (offset + size - 1) % size;
	bottom = offset;
	mid = (bottom + ((top + size - offset) % size - (bottom + size - offset) % size) / 2) % size;
	
	while(arr[mid] != target)
	{
		if(arr[mid] > target)
		{
			top = (mid + size - 1) % size;
		}
		else
		{
			bottom = (mid + 1) % size;
		}
		mid = (bottom + ((top + size - offset) % size - (bottom + size - offset) % size) / 2) % size;
	}
	return mid;
}

int main()
{
	int arr[6] = {7, 8, 11, 1, 4, 5};
	int arr2[7] = {7, 1, 2, 3, 4, 5, 6};
	int arr3[7] = {2, 3, 4, 5, 6, 7, 1};
	int arr4[7] = {1, 4, 8, 12, 15, 16};
	printf("11 index in arr[6] = {7, 8, 11, 1, 4, 5} is:\t%lu\n",(FindCircular(arr, 6, 11)));
	printf("5 index in arr2[7] = {7, 1, 2, 3, 4, 5, 6} is:\t%lu\n",(FindCircular(arr2, 7, 5)));
	printf("3 index in arr3[7] = {2, 3, 4, 5, 6, 7, 1} is:\t%lu\n",(FindCircular(arr3, 7, 3)));
	printf("12 index in arr4[7] = {1, 4, 8, 12, 15, 16} is:\t%lu\n",(FindCircular(arr4, 7, 12)));
	return 0;
}
