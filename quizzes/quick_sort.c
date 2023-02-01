#include <stddef.h>
#include <stdio.h>

static void SwapInt(int* num1_p, int* num2_p)
{
	int tmp = *num1_p;
	*num1_p = *num2_p;
	*num2_p = tmp;
}

int Partition(int *arr, int start, int end)
{
	int pivot = arr[end];
	int i = (start - 1);	   
	int j = start;

	for (; j <= end - 1; ++j)
	{
		if (arr[j] < pivot)
		{
			++i;
			SwapInt(arr + i, arr + j);
		}
	}
	
	SwapInt(arr + i + 1, arr + end);
	return (i + 1);
}

void QuickSortRec(int *arr, int start, int end)
{
	int pi;

	if (start < end)
	{
		pi = Partition(arr, start, end);
		QuickSortRec(arr, start, pi - 1);
		QuickSortRec(arr, pi + 1, end);
	}
}

void QuickSort(int *arr, size_t size)
{
	QuickSortRec(arr, 0, size - 1);
}



int main()
{
	size_t i = 0;
	int arr2[] = {2, 4, 5, 1, 3, 6};
	int arr3[] = {-11, 3, 5, 1, 8, 6};
	
	QuickSort(arr2, 6);
	QuickSort(arr3, 6);
	
	for(; i < 6; ++i)
	{
		printf("%d ", arr2[i]);
	}
	printf("\n");
	
	i = 0;
	
	for(; i < 6; ++i)
	{
		printf("%d ", arr3[i]);
	}
	printf("\n");
	
	return 0;
}
