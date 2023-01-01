#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "comparison_sort.h"
#define ARR_SIZE 5000

int (*compar)(const void *, const void *);

static int CompareInts(const void *num1, const void *num2)
{
	if(*(int*)num1 > *(int*)num2)
	{
		return 1;
	}
	else if(*(int*)num1 < *(int*)num2)
	{
		return -1;
	}
	return 0;
}

static int CheckSort(int *arr, int size)
{
	int i = 0;
	for(; i < size - 1; ++i)
	{
		if(arr[i] > arr[i + 1])
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	int arr[ARR_SIZE];
	int i = 0;
	double time_taken;
	clock_t start, end;
	srand(time(NULL));
	
	for(; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	start = clock();
	BubbleSort(arr, ARR_SIZE);
	end = clock();
	time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	printf("Did bubble succeed?\t%d\n", CheckSort(arr, ARR_SIZE));
	printf("Time taken:\t%f\n", time_taken);
	
	
	i = 0;
	for(; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	
	start = clock();
	SelectionSort(arr, ARR_SIZE);
	end = clock();
	time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	printf("Did selection succeed?\t%d\n", CheckSort(arr, ARR_SIZE));
	printf("Time taken:\t%f\n", time_taken);
	
	i = 0;
	for(; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	
	start = clock();		
	InsertionSort(arr, ARR_SIZE);
	end = clock();
	time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	printf("Did insertion succeed?\t%d\n", CheckSort(arr, ARR_SIZE));
	printf("Time taken:\t%f\n", time_taken);
	
	i = 0;
	for(; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	
	start = clock();		
	qsort(arr, ARR_SIZE, sizeof(int), CompareInts);
	end = clock();
	time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	printf("Did qsort succeed?\t%d\n", CheckSort(arr, ARR_SIZE));
	printf("Time taken:\t%f\n", time_taken);
	return 0;
}
