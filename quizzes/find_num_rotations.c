#include <stddef.h>
#include <stdio.h>

size_t FindNumRotation(int *arr, size_t size)
{
	size_t e = size - 1, s = 0, m = (e + s)/2;
	
	while(arr[m] > arr[(m-1)%size] || arr[m] > arr[(m+1)%size])
	{
		if(arr[m] < arr[e] && arr[m] < arr[s])
		{
			e = m - 1;
			m = (s + e) / 2;
		}
		if(arr[m] > arr[e] && arr[m] > arr[s])
		{
			s = m + 1;
			m = (s + e) / 2;
		}
		else
		{
			return 0;
		}
	}
	return m;
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
