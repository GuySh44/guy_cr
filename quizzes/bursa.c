#include<stdio.h>
void Bursa(int *stocks, int size, int *res)
{
	int max_sub;
	int max = stocks[0], min = stocks[0];
	int i = 1, min_index = 0;
	res[0] = max;
	res[1] = min;
	res[2] = max-min;
	max_sub = 0;
	while (i < size)
	{
		if (stocks[i] > stocks[i-1] && i > min_index)
		{
			max = stocks[i];
		}
		else
		{
			min_index = i;
			min = stocks[i];
			max = stocks[i];
		}
		if (max-min > max_sub)
		{
			max_sub = max-min;
			res[0] = i;
			res[1] = min_index;
			res[2] = max_sub;
		}
		i++;
	}
}








int main()
{
	int res[3];
	int stocks[] = {6, 12, 3, 5, 1, 4, 9, 2};
	int blocks[] = {100, 2, 1000, 2000, 2050, 6, 10, 8};
	Bursa(blocks, 8, res);
	printf("max:%d\tmin:%d\tsub:%d\n",res[0],res[1],res[2]);
	return 0;
}
