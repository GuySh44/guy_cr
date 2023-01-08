#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static void SwapInt(int* num1_p, int* num2_p)
{
	int tmp = *num1_p;
	*num1_p = *num2_p;
	*num2_p = tmp;
}

int FindKth(int *arr, size_t size, size_t k)
{
	size_t i = 0, j = 0;
	int min = 0;
	int *new_arr = (int*)malloc(sizeof(arr[0]) * size);
	int res = 0;
	for(; i < size; ++i)
	{
		new_arr[i] = arr[i];
	}
	i = 0;
	for(; i < k; ++i)
	{
		j = i;
		min = i;
		for(; j < size; ++j)
		{
			if (new_arr[j] < new_arr[min])
			{
				min = j;
			}
		}
		SwapInt(new_arr + i, new_arr + min);
	}
	res = new_arr[k - 1];
	free(new_arr);
	return res;
}


int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6};
	int arr2[] = {2, 4, 5, 1, 3, 6};
	int arr3[] = {-11, 3, 5, 1, 8, 6};
	printf("Find third smallest arr[] = {1, 2, 3, 4, 5, 6}:\t%d\n", FindKth(arr, 6, 3));
	printf("Find third smallest arr2[] = {2, 4, 5, 1, 3, 6}:\t%d\n", FindKth(arr2, 6, 3));
	printf("Find fifth smallest arr3[] = {-11, 3, 5, 1, 8, 6}:\t%d\n", FindKth(arr3, 6, 5));
	return 0;
}
