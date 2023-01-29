#include <string.h>
#include <stdio.h>

#include "hash_table.h"
#include "my_utils.h"

size_t MODHundred(const void *num)
{
	return ((size_t)(*(int*)num)) % 100;
}


int CompareInt(const void *num1, const void *num2)
{
	return !((*(int*)num1) == (*(int*)num2));
}

int SumInt(void *data, void *parameter)
{
	*((long*)parameter) += *(int*)data;
	return 0;
}

/* djb2 hash function*/
size_t HashString(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (0 != (c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	
	return hash;
}

int CompareString(const void *str1, const void *str2)
{
	return strcmp(str1, str2);
}

int main()
{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	hash_table_t *first_table = HashCreate(MODHundred, 300, CompareInt);
	
	hash_table_t *second_table = HashCreate(MODHundred, 100, CompareInt);
	
	
	int twenty = 20, hundred_twenty = 120, ten = 10, s_twenty = 20, s_hundred_twenty = 120;

	long int_sum = 0;
	
	HashDestroy(second_table);
	
	printTest("Check if empty hash is empty",!HashIsEmpty(first_table));
	
	printTest("Check if empty hash size is 0",!(0 == HashSize(first_table)));
	
	printTest("Check if find on empty table returns NULL", !(NULL == HashFind(first_table, (const void*)&twenty)));
	
	printTest("Try to insert 20", HashInsert(first_table, &twenty, &twenty));
	
	printTest("Check if hash is empty",HashIsEmpty(first_table));
	
	printTest("Check if hash size is 1",!(1 == HashSize(first_table)));
	
	printTest("Try to insert 120", HashInsert(first_table, &hundred_twenty, &hundred_twenty));
	
	printTest("Check if hash size is 2",!(2 == HashSize(first_table)));
	
	printTest("Try to insert 10", HashInsert(first_table, &ten, &ten));
	
	printTest("try to find hundred twenty", !(HashFind(first_table, &s_hundred_twenty) == &hundred_twenty));
	
	printTest("try to find twenty", !(HashFind(first_table, &s_twenty) == &twenty));
	
	printTest("try to remove twenty", HashRemove(first_table, &s_twenty));
	
	printTest("Check if hash size is 2",!(2 == HashSize(first_table)));
	
	printTest("try to find twenty after remove", !(HashFind(first_table, &s_twenty) == NULL));
	
	printTest("try to remove hundred twenty", HashRemove(first_table, &s_hundred_twenty));
	
	printTest("try to find hundred twenty after remove", !(HashFind(first_table, &s_hundred_twenty) == NULL));
	
	printTest("Check if empty hash size is 1",!(1 == HashSize(first_table)));
	
	printTest("Try to insert 20", HashInsert(first_table, &twenty, &twenty));
	
	printTest("Check if hash size is 2",!(2 == HashSize(first_table)));
	
	printTest("Try to insert 120", HashInsert(first_table, &hundred_twenty, &hundred_twenty));
	
	printTest("Check if hash size is 3",!(3 == HashSize(first_table)));
	
	printTest("Check the sum of all values, did it succedd?", HashForEach(first_table, SumInt, &int_sum));
	
	printTest("Is the sum 150?", !(150 == int_sum));
	
	HashDestroy(first_table);
	
	
	
	return 0;
}
