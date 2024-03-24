#include<stdio.h>
void IsSumFound(int *sorted_arr, int arr_size, int sum, int* result)
{
	result[0] = 0;
	result[1] = 0, result[2] = arr_size-1;
	
	while (result[1] != result[2])
	{
		int curr_sum = sorted_arr[result[1]] + sorted_arr[result[2]];
		if(curr_sum == sum)
		{
			result[0] = 1;
			return;
		}
		else if(curr_sum < sum)
		{
			result[1]++;
		}
		else
		{
			result[2]--;
		}
	}
	result[1] = -1;
	result[2] = -1;
}



int main()
{
	int sorted[] = {1, 4, 6 ,7, 8, 10};
	int result[3];
	IsSumFound(sorted,6,12,result);
	printf("Sum Found? %d\nIndexes: %d , %d\n",result[0], result[1], result[2]);
	return 0;
}
