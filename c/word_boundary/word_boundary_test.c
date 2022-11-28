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
	void* mem4_original = malloc(7);
	void* mem4_my = malloc(7);
	void* mem5_original = malloc(32);
	void* mem5_my = malloc(32);
	void* mem6_original = malloc(10);
	void* mem6_my = malloc(10);
	void* mem7_original = malloc(10);
	void* mem7_my = malloc(10);
	void* mem8_original = malloc(10);
	void* mem8_my = malloc(10);
	void* mem9_original = malloc(10);
	void* mem9_my = malloc(10);
	int c = 65;
	int i = 0;
	mem2_original = (void*)(((char*)mem2_original_start) + 1);
	mem2_my = (void*)(((char*)mem2_my_start) + 1);
	printf("mem1_original pointer address:\t%p\n",mem1_original);
	printf("mem1_my pointer address:\t%p\n",mem1_my);
	memset(mem1_original,c,5);
	Memset(mem1_my,c,5);
	printf("mem2_original pointer address:\t%p\n",mem2_original);
	printf("mem2_my pointer address:\t%p\n",mem2_my);
	memset(mem2_original,c,32);
	Memset(mem2_my,c,32);
	printf("mem3_original pointer address:\t%p\n",mem3_original);
	printf("mem3_my pointer address:\t%p\n",mem3_my);
	memset(mem3_original,c,36);
	Memset(mem3_my,c,36);
	
	memcpy(mem4_original,"avdddd",7);
	printf("Mem4\n");
	Memcpy(mem4_my,"avdddd",7);
	
	memcpy(mem5_original,"abcdefghijklmnopqrstuvwxyz12345",32);
	printf("Mem5\n");
	Memcpy(mem5_my,"abcdefghijklmnopqrstuvwxyz12345",32);
	
	memcpy(mem6_original,"GuyGuyaye",10);
	printf("Mem6\n");
	Memcpy(mem6_my,"GuyGuyaye",10);
	
	for(;i < 10;i++)
	{
		((char*)mem7_original)[i] = i;
		((char*)mem8_original)[i] = i;
		((char*)mem9_original)[i] = i;
		((char*)mem7_my)[i] = i;
		((char*)mem8_my)[i] = i;
		((char*)mem9_my)[i] = i;
	}
	
	printf("src bigger than dest\n");
	memmove(mem7_original, (void*)((char*)mem7_original + 4), 6);
	Memmove(mem7_my, (void*)((char*)mem7_my + 4), 6);
	
	printf("dest bigger than src\n");
	memmove((void*)((char*)mem8_original + 4),mem8_original, 6);
	Memmove((void*)((char*)mem8_my + 4),mem8_my, 6);
	
	printf("src equal to dest\n");
	memmove(mem9_original, mem9_original, 10);
	Memmove(mem9_my, mem9_my, 10);
	
	free(mem1_original);
	free(mem2_original_start);
	free(mem3_original);
	free(mem1_my);
	free(mem2_my_start);
	free(mem3_my);
	free(mem4_original);
	free(mem5_original);
	free(mem6_original);
	free(mem4_my);
	free(mem5_my);
	free(mem6_my);
	free(mem7_original);
	free(mem8_original);
	free(mem9_original);
	free(mem7_my);
	free(mem8_my);
	free(mem9_my);
	
	return 0;
}
