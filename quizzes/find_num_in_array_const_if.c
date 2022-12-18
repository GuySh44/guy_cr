#include <stddef.h>
#include <stdio.h>

int FindNum(int *arr, size_t size, int num)
{
	size_t i = 0;
	size_t sum = 0;
	int arr_num;
	for(; i < size; ++i)
	{
		arr_num = arr[i];
		arr_num ^= num;
		arr_num = !arr_num;
		sum += arr_num;
	}
	if(sum > 0)
	{
		return 1;
	}
	return 0;
}

int main()
{
	int arr1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i = 0;
	for(; i < 20; ++i)
	{
		printf("Find %d in arr 1:\t%d\n", i, FindNum(arr1, 10, i));
	}
	return 0;
}
