#include<stdio.h>
#define MAX2(a,b) (((a) > (b)) ? (a) : (b))
#define MAX3(a,b,c) MAX2(MAX2(a,b) , MAX2(b,c))
#define TO_LOWER(a) (((a) >= ('A') && (a) <= ('Z')) ? ((a) + ('a'-'A')) : (a))
#define OFFSET(s,f) ((size_t)&(((s*)0)->f))

int main()
{
	typedef struct strc
	{
		char field2;
		short field1;
		double field3;
	} test_struct;
	
	struct s
	{
		int num;
		char ch1;
		int* ptr;
		char ch2;
	} s3;
	
	
	typedef struct     
    	{       
       		int num;         
        	char ch1;     
    	} s1;  
    	 
    	struct     
	{       
		int num;         
		char ch1;     
	} s2;
	
	union u     
	{       
		int num;         
		char arr[5];     
	} u1; 
	
	test_struct test;
	printf("MAX3 of 4 , 7 , -2 is:%d\n", MAX3(4,7,-2));
	printf("A b C to lower is: %c, %c, %c\n", TO_LOWER('A'), TO_LOWER('b'), TO_LOWER('C'));
	printf("field1 offset:%lu\n", OFFSET(test_struct, field1));
	printf("field2 offset:%lu\n", OFFSET(test_struct, field2));
	printf("field3 offset:%lu\n", OFFSET(test_struct, field3));
	printf("s size:%lu\n", sizeof(s3));    
	printf("u1 size is:%lu\n", sizeof(u1));  
	return 0;
}
