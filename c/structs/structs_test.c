#include"structs.h"

int main()
{
	int a = 51, b = 48, c = 52;
	char check_type = 'c';
	
	
	
	extern char* strdup(const char*);
	int i = 0, j = 0, k = 0, l = 0;
	ElementsArray arr[5];
	ElementsArray size;
	
	arr[0] = createFloat(4.2);
	
	arr[1] = createFloat(6.7);
	
	arr[2] = createString("chapter");
	
	arr[3] = createInt(12);
	
	arr[4] = createFloat(56.32);
	
	printf("before:\n");
	for(; i < 5; ++i)
	{
		arr[i].print(arr[i].data);
	}
	printf("\n");
	for(; j < 5; ++j)
	{
		arr[j].add(&arr[j].data, 10);	
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
