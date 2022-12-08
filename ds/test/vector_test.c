#include"vector.h"
#include<stdio.h>

int main()
{
	size_t i = 0;
	int one = 1, two = 2, three = 3, four = 4, five = 5;
	vector_t* my_first_vector = VectorInit(10,sizeof(int));
	VectorPushBack(my_first_vector, &one);
	VectorPushBack(my_first_vector, &two);
	VectorPushBack(my_first_vector, &two);
	printf("The second index is:\t%d\n", *((int*)VectorAcess(my_first_vector,1)));
	*((int*)VectorAcess(my_first_vector,1)) = 6;
	printf("The changed second index is:\t%d\n", *((int*)VectorAcess(my_first_vector,1)));
	printf("Was third index passed by value:\t%d\n", *((int*)VectorAcess(my_first_vector,2)));
	VectorPopBack(my_first_vector);
	VectorPushBack(my_first_vector, &four);
	VectorShrink(my_first_vector);
	VectorPushBack(my_first_vector, &five);
	VectorResize(my_first_vector, 4);
	VectorPushBack(my_first_vector, &three);
	for(;i < VectorSize(my_first_vector); ++i)
	{
		printf("index %lu value: %d\n", i, *((int*)VectorAcess(my_first_vector,i)));
	}
	VectorResize(my_first_vector, 10);
	VectorDestroy(my_first_vector);
	return 0;
}
