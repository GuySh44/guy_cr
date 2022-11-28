#include "word_boundary.h"
#define BYTE_SIZE 8

void *MemSet(void *s, int c, size_t n)
{
	void* start = s;
	size_t i = 1;
	size_t word_size = sizeof(long);
	long template = (long)((char)c);
	size_t address = (size_t)s;
	size_t times_to_align = (word_size - (address % word_size)) % word_size;
	size_t word_chunks;
	assert(n != 0);
	assert(c >= 0);
	assert(s);
	
	for (;times_to_align > 0 && n > 0; --times_to_align, --n)
	{
		*((char*)s) = (char)c;
		s = (void*)(((char*)s) + 1);
		assert(printf("single byte operation\n"));
	}
	for(;i < word_size; ++i)
	{
		template <<= BYTE_SIZE;
		template |= (long)((char)c);
		
	}
	word_chunks = n / word_size;
	for (;word_chunks > 0;--word_chunks)
	{
		*((long*)s) = template;
		n -= word_size;
		s = (void*)(((char*)s) + word_size);
		assert(printf("whole word operation\n"));
	}
	for (; n > 0; n--)
	{
		*((char*)s) = (char)c;
		s = (void*)(((char*)s) + 1);
		assert(printf("single byte operation\n"));
	}
	assert(printf("finished\n"));
	return start;
}
