#include <stddef.h>
#include <stdio.h>


static void SwapInt(int* num1_p, int* num2_p)
{
	int tmp = *num1_p;
	*num1_p = *num2_p;
	*num2_p = tmp;
}

void SortZeroOne(int *arr, size_t size)
{
	size_t s = 0, e = size - 1;
	
	while(s < e)
	{
		if(arr[s] == 1 && arr[e] == 0)
		{
			SwapInt(arr+s, arr+e);
			++s;
			--e;
		}
		s += arr[s] ^ 1;
		e -= arr[e] ^ 0;
	}
}

void PrintArray(int *arr,size_t size)
{
	size_t i = 0;
	for(; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr1[12] = {0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0};
	int arr2[13] = {1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1};
	PrintArray(arr1, 12);
	PrintArray(arr2, 13);
	SortZeroOne(arr1, 12);
	SortZeroOne(arr2, 13);
	PrintArray(arr1, 12);
	PrintArray(arr2, 13);
	return 0;
}
