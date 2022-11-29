#include"structs.h"

int main()
{
	int a = 51, b = 48, c = 52;
	char check_type = 'c';
	
	
	
	extern char* strdup(const char*);
	char *str2 = NULL;
	char *str1 = "chapter";
	int i = 0, j = 0, k = 0, l = 0;
	ElementsArray arr[5];
	ElementsArray size;
	
	arr[0].data = (float*)malloc(sizeof(arr[0].data));
	*((float *)(arr[0].data)) = 4.2;
	arr[0].add = &addFloat;
	arr[0].clean = &cleanFloat;
	arr[0].print = &printFloat;
	
	arr[1].data = (float*)malloc(sizeof(arr[1].data));
	*((float *)(arr[1].data)) = 6.7;
	arr[1].add = &addFloat;
	arr[1].clean = &cleanFloat;
	arr[1].print = &printFloat;
	
	str2 = strdup(str1);
	arr[2].data = &str2;
	arr[2].add = &addString;
	arr[2].clean = &cleanString;
	arr[2].print = &printString;
	
	arr[3].data = (int*)malloc(sizeof(arr[3].data));
	*((int *)(arr[3].data)) = 12;
	arr[3].add = &addInt;
	arr[3].clean = &cleanInt;
	arr[3].print = &printInt;
	
	arr[4].data = (float*)malloc(sizeof(arr[4].data));
	*((float *)(arr[4].data)) = 56.32;
	arr[4].add = &addFloat;
	arr[4].clean = &cleanFloat;
	arr[4].print = &printFloat;
	printf("before:\n");
	for(; i < 5; ++i)
	{
		arr[i].print(arr[i].data);
	}
	printf("\n");
	for(; j < 5; ++j)
	{
		arr[j].add(arr[j].data, 10);	
	}
	printf("after:\n");
	for(; k < 5; ++k)
	{
		arr[k].print(arr[k].data);
	}
	for(; l < 5; ++l)
	{
		arr[l].clean(arr[l].data);
	}
	
	
	
	
	
	
	
	printf("max of a = 51 and b = 48\t%d\n", MAX2(a, b));
	printf("max of a = 51 and b = 48 and c = 52\t%d\n", MAX3(a, b, c));
	printf("SIZEOF_VAR int\t%ld\n",SIZEOF_VAR(a));
	printf("SIZEOF_VAR char\t%ld\n",SIZEOF_VAR(check_type));
	printf("SIZEOF_VAR ElementsArray\t%ld\n",SIZEOF_VAR(size));
	printf("SIZEOF_TYPE int\t%ld\n",SIZEOF_TYPE(int));
	printf("SIZEOF_TYPE char\t%ld\n",SIZEOF_TYPE(char));
	printf("SIZEOF_TYPE ElementsArray\t%ld\n",SIZEOF_TYPE(ElementsArray));
	return 0;
}