#include"arrays_pointers.h"
size_t josephus(size_t n, size_t start)
{
	size_t i=1;
	size_t current = start;
	size_t *array = malloc(sizeof(size_t)* n);
	size_t *tmp_array = array;
	for(;i < n; i++)
		*tmp_array++ = i;
	*tmp_array = 0;
	while(array[current] != current)
	{
		array[current] = array[array[current]];
		current = array[current];
	}
	free(array);
	return current;
}


