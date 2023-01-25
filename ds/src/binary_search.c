
#include <assert.h>

#include "binary_search.h"

/* Reviewer: Or */

size_t BinarySearchItera(int *arr, size_t size, int num)
{
	size_t s = 0, e = size - 1 , m = (s + e) / 2;

	assert(arr);	
		
	while(arr[m] != num)
	{
		if(num > arr[m])
		{
			s = m + 1;
			m = (s + e) / 2;
		}
		else
		{
			e = m - 1;
			m = (s + e) / 2;
		}
	}
	return m;
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
}


size_t BinarySearchRec(int *arr, size_t size, int num)
{
	assert(arr);
	
	return BinarySearchRecWrap(arr, 0, size - 1, num);
}
