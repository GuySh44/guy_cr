
#include <assert.h>

#include "binary_search.h"

/* Reviewer: Or */

size_t BinarySearchItera(int *arr, size_t size, int num)
{
	size_t start = 0, end = size - 1 , mid = (start + end) / 2;

	assert(arr);	
		
	while(arr[mid] != num)
	{
		if(num > arr[mid])
		{
			start = mid + 1;
			mid = (start + end) / 2;
		}
		else
		{
			end = mid - 1;
			mid = (start + end) / 2;
		}
	}
	return mid;
}

static size_t BinarySearchRecWrap(int *arr, size_t start, size_t end, int num)
{
	size_t mid = (start + end) / 2;
	
	
	if(num == arr[mid])
	{
		return mid;
	}
	if(num > arr[mid])
	{
		return BinarySearchRecWrap(arr, mid + 1, end, num);
	}
	else
	{
		return BinarySearchRecWrap(arr, start, mid - 1, num); 
	}
	return 999;
}


size_t BinarySearchRec(int *arr, size_t size, int num)
{
	assert(arr);
	
	return BinarySearchRecWrap(arr, 0, size - 1, num);
}
