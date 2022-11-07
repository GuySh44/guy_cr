#include<stdio.h>
#include<stdlib.h>

void CopyArray(int *array)
{
	int array_size = sizeof(array) / sizeof(array[0]);
	int* new_array = malloc(array_size * sizeof(int));
	for(int i=0; i<array_size;i++)
	{
		new_array[i] = array[i];
		printf("old: %d, copy: %d\n", array[i], new_array[i]);
	}
}


int main()
{
	int array[] = {0, 1, 2, 3, 4};
	CopyArray(array);
	return 0;	
}
