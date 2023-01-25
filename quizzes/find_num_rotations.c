#include <stddef.h>
#include <stdio.h>

size_t FindNumRotation(int *arr, size_t size)
{
	size_t end = size - 1, start = 0, mid = (end + start)/2;
	
	while(arr[mid] > arr[(mid-1)%size])
	{
		if(arr[end] > arr[mid])
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
		mid = (start + end) / 2;
	}
	return mid;
}

int main()
{
	int arr1[7] = {4, 5, 7, 8, 11, 1, 2};
	int arr2[6] = {7, 8, 11, 1, 4, 5};
	int arr3[7] = {11, 1, 2, 4, 5, 7, 8};
	int arr4[7] = {1, 2, 4, 5, 7, 8, 11};
	printf("The array is rotated %lu times\n", FindNumRotation(arr1, 7));
	printf("The array is rotated %lu times\n", FindNumRotation(arr2, 6));
	printf("The array is rotated %lu times\n", FindNumRotation(arr3, 7));
	printf("The array is rotated %lu times\n", FindNumRotation(arr4, 7));
	return 0;
}
