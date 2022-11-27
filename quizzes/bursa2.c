#include<stdio.h>
#include<stddef.h>

void Bursa2(int* arr, size_t size, int* res_arr)
{
	int min_index = 0;
	int max_index = 1;
	size_t i = 1;
	res_arr[0] = 0;
	res_arr[1] = 1;
	res_arr[2] = arr[1] - arr[0];
	for(; i < size; ++i)
	{
		if(arr[i] < arr[min_index])
		{
			min_index = i;
			max_index = i;
		}
		else if (arr[max_index] - arr[min_index] > res_arr[2])
		{
			res_arr[0] = min_index;
			res_arr[1] = max_index;
			res_arr[2] = arr[max_index] - arr[min_index];
		}
		++max_index;
	}
}








int main()
{
	int res[3];
	int stocks[] = {6, 12, 3, 5, 1, 4, 9, 2};
	int blocks[] = {100, 2, 1000, 2000, 2050, 6, 10, 8};
	Bursa2(blocks, 8, res);
	printf("max:%d\tmin:%d\tsub:%d\n",res[0],res[1],res[2]);
	return 0;
}
