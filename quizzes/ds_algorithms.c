#include <stddef.h>
#include <stdio.h>
#include <assert.h>


/* euclides algorithm */

size_t GCD(size_t a, size_t b)
{
	if(b == 0) 
    {
		return a;
    }
    else 
    {
    	return GCD(b, a % b);
    }
}


int ArrayFind(char *arr, size_t size, char num)
{
	char LUT[256] = {0};
	size_t i = 0;
	for(; i < size; ++i)
	{
		LUT[(size_t)arr[i]] = (char)1;
	}
	return (int)LUT[(size_t)num];
}

void RotateCharArr(char *arr, size_t size, int n)
{
	size_t i = 0, j = 0, gcd = 0;
	char temp_curr, temp_next;
	
	if(n < 0)
	{
		n = size - (-n % size);
	}
	else
	{
		n = n % size;
	}
	
	gcd = GCD(size, n);
	
	for(; j < gcd; ++j)
	{
		temp_curr = arr[j];
		i = 0;
		for(; i < size / gcd; ++i)
		{
			temp_next = arr[(j+(i+1)*n) % size];
			arr[(j+(i+1)*n) % size] = temp_curr;
			temp_curr = temp_next;
			assert(printf("loop iteration\n"));
		}
	}
}

void PrintCharArr(char *arr, size_t size)
{
	size_t i = 0;
	for(; i < size; ++i)
	{
		printf("%c\t", arr[i]);
	}
	printf("\n");
}

int main()
{
	char arr1[6] = {'b', 'd', 'f', 'a', 'c', 'e'};
	
	printf("Find 'z' in arr1 = {'b', 'd', 'f', 'a', 'c', 'e'}:\t%d\n", ArrayFind(arr1, 6, 'z'));
		
	printf("Find 'a' in arr1 = {'b', 'd', 'f', 'a', 'c', 'e'}:\t%d\n", ArrayFind(arr1, 6, 'a'));
	
	RotateCharArr(arr1, 6, 3);
	
	PrintCharArr(arr1, 6);
	
	
	return 0;
}
