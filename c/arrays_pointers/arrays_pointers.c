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

void printCTypes()
{
	printf("signed char %lu\n",sizeof(signed char));
	printf("unsigned char %lu\n",sizeof(unsigned char));
	printf("char %lu\n",sizeof(char));
	printf("short int %lu\n",sizeof(short int));
	printf("unsigned short int %lu\n",sizeof(unsigned short int));
	printf("int %lu\n",sizeof(int));
	printf("unsigned int %lu\n",sizeof(unsigned int));
	printf("long int %lu\n",sizeof(long int));
	printf("unsigned long int %lu\n",sizeof(unsigned long int));
	printf("float %lu\n",sizeof(float));
	printf("double %lu\n",sizeof(double));
	printf("long double %lu\n",sizeof(long double));
	printf("size_t %lu\n",sizeof(size_t));
	printf("pointer %lu\n",sizeof(size_t*));
}

