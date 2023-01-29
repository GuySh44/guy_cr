
#include <stdio.h>

#include "hash_table.h"
#include "my_utils.h"

size_t MODHundred(const void *num)
{
	return ((size_t)(num)) % 100;
}


int CompareInt(const void *num1, const void *num2)
{
	return (*(int*)num1) == (*(int*)num2);
}

int main()
{
	hash_table_t *first_table = HashCreate(MODHundred, 300, CompareInt);
	
	int twenty = 20, hundred_twenty = 120, ten = 10;

	
	printTest("Check if empty hash is empty",!HashIsEmpty(first_table));
	
	printTest("Check if empty hash size is 0",!(0 == HashSize(first_table)));
	
	printTest("Check if find on empty table returns NULL", !(NULL == HashFind(first_table, (const void*)&twenty)));
	
	printTest("Try to insert 20", HashInsert(first_table, &twenty, &twenty));
	
	printTest("Check if hash is empty",HashIsEmpty(first_table));
	
	printTest("Check if hash size is 1",!(1 == HashSize(first_table)));
	
	printTest("Try to insert 120", HashInsert(first_table, &hundred_twenty, &hundred_twenty));
	
	printTest("Check if hash size is 2",!(2 == HashSize(first_table)));
	
	printTest("Try to insert 10", HashInsert(first_table, &ten, &ten));
	
	
	HashDestroy(first_table);
	return 0;
}
