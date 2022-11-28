#include"word_boundary.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	void* mem1_original = malloc(5);
	void* mem1_my = malloc(5);
	void* mem2_original;
	void* mem2_my;
	void* mem2_original_start = malloc(33);
	void* mem2_my_start = malloc(33);
	void* mem3_original = malloc(36);
	void* mem3_my = malloc(36);
	int c = 65;
	mem2_original = (void*)(((char*)mem2_original_start) + 1);
	mem2_my = (void*)(((char*)mem2_my_start) + 1);
	printf("mem1_original pointer address:\t%p\n",mem1_original);
	printf("mem1_my pointer address:\t%p\n",mem1_my);
	memset(mem1_original,c,5);
	MemSet(mem1_my,c,5);
	printf("mem2_original pointer address:\t%p\n",mem2_original);
	printf("mem2_my pointer address:\t%p\n",mem2_my);
	memset(mem2_original,c,32);
	MemSet(mem2_my,c,32);
	printf("mem3_original pointer address:\t%p\n",mem3_original);
	printf("mem3_my pointer address:\t%p\n",mem3_my);
	memset(mem3_original,c,36);
	MemSet(mem3_my,c,36);
	
	free(mem1_original);
	free(mem2_original_start);
	free(mem3_original);
	free(mem1_my);
	free(mem2_my_start);
	free(mem3_my);

	return 0;
}
