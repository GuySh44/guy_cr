#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void *Memcpy(void *dest, void *src, size_t n)
{
	size_t addr  = (size_t)dest;
	void *start = dest;
	short word_size = sizeof(long);
	short align_times = (word_size - (addr % word_size)) % word_size;
	while(align_times)
	{
		*((char*)dest) = *((char*)src);
		dest = (void*)((char*)dest + 1);
		src = (void*)((char*)src + 1);
		--align_times;
		--n;
		printf("Copy byte by byte to alignment\n");
	}
	while(n >= (size_t)word_size)
	{
		*((long*)dest) = *((long*)src);
		dest = (void*)((long*)dest + 1) ;
		src = (void*)((long*)src + 1);
		n -= word_size;
		printf("Copy word by word\n");
	}
	while(n > 0)
	{
		*((char*)dest) = *((char*)src);
		dest = (void*)((char*)dest + 1);
		src = (void*)((char*)src + 1);
		--n;
		printf("Copy byte by byte to end\n");
	}
	return start;
}

int main()
{
	void* mem4_original = malloc(7);
	void* mem4_my = malloc(7);
	void* mem5_original = malloc(32);
	void* mem5_my = malloc(32);
	void* mem6_original = malloc(10);
	void* mem6_my = malloc(10);
	memcpy(mem4_original,"avdddd",7);
	printf("Mem4\n");
	Memcpy(mem4_my,"avdddd",7);
	
	memcpy(mem5_original,"abcdefghijklmnopqrstuvwxyz12345",32);
	printf("Mem5\n");
	Memcpy(mem5_my,"abcdefghijklmnopqrstuvwxyz12345",32);
	
	memcpy(mem6_original,"GuyGuyaye",10);
	printf("Mem6\n");
	Memcpy(mem6_my,"GuyGuyaye",10);
	return 0;
}
	
