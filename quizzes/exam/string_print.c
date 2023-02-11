#include <stdio.h>
#include <string.h>



struct S
{
    int *i;
    char c;
    short s;
    int *j;
};


struct S1
{
    unsigned int i : 2;
    unsigned char c : 1;
    unsigned short s : 3;
    int *j;
    unsigned char x : 2;
};

void foo1()
{
    size_t array [] = {0, 1, 2, 3, 4, 5};
    size_t val = 3;
    printf("%lu \n", val[array]);
}

void foo()
{
    char *s1 = "hello";
    char s2[] = "hello";
    char *s3 = s1;
    printf("%lu %lu %lu %lu \n", sizeof(s1),sizeof(s2),strlen(s1),strlen(s2));
    s3[0] = 'H';
    printf("%s \n", s3);
}

int main()
{
	union
	{
    	char array[7];
    	int i;
    	short s;
	} jack;
	
	printf("size of jack: %lu\n", sizeof(jack));
	return 0;
}
