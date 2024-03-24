#include<stdio.h>


void maxsubarray(int *arr, int size, int *res)
{
	int i = 0;
	int s_ind = 0;
	int e_ind = 0;
	int sum = 0;
	res[2] = 0;
	for(;i < size; ++i)
	{
		sum += arr[i];
		if (sum > res[2] && sum > arr[i])
		{
			res[0] = s_ind;
			res[1] = e_ind;
			res[2] = sum;
		}
		if (sum < arr[i] && arr[i] >= 0)
		{
			sum = arr[i];
			s_ind = i;
			e_ind = i;
		}
		++e_ind;
	}
}



int main()
{
	int res[3];
	int arr[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int arr2[] = {-3, 1, -8, 12, 0, -3, 5, -9, 4};
	maxsubarray(arr2,9,res);
	printf("start:\t%d\nend:\t%d\nsum:\t%d\n",res[0], res[1], res[2]);
	return 0;
}
