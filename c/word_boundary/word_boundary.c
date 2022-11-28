#include "word_boundary.h"
#define BYTE_SIZE 8

/* memset reviewer: arthur */
void *Memset(void *s, int c, size_t n)
{
	void* start = s;								/* for returning */
	size_t i = 1;									/* for creating template */
	size_t word_size = sizeof(long);						/* word size kinda */		
	long template = (long)((char)c);						/* set start value of template */
	size_t address = (size_t)s;							/* get address as number */
	size_t times_to_align = (word_size - (address % word_size)) % word_size;	/* get number of bytes before next aligned address */
	size_t word_chunks;
	assert(n != 0);
	assert(c >= 0);
	assert(s);
	assert(printf("Memset:\n"));
	for (;times_to_align > 0 && n > 0; --times_to_align, --n)			/* align the memory address while copying byte to byte */
	{
		*((char*)s) = (char)c;
		s = (void*)(((char*)s) + 1);
		assert(printf("single byte operation\n"));
	}
	for(;i < word_size; ++i)							/* create the template used for copying c's */
	{
		template <<= BYTE_SIZE;
		template |= (long)((char)c);
	}
	word_chunks = n / word_size;							/* calculate number of whole words left to copy */
	for (;word_chunks > 0;--word_chunks)						/* copy whole words using template */
	{
		*((long*)s) = template;
		n -= word_size;
		s = (void*)(((char*)s) + word_size);
		assert(printf("whole word operation\n"));
	}
	for (; n > 0; n--)								/* copy trailing bytes that dont fit into words */ 
	{
		*((char*)s) = (char)c;
		s = (void*)(((char*)s) + 1);
		assert(printf("single byte operation\n"));
	}
	assert(printf("finished\n"));
	return start;
}

/* memset reviewer: arthur */
void *Memcpy(void *dest, const void *src, size_t n)
{
	void *start = dest;						/* for returning */
	size_t word_size = sizeof(long);				/* word size kinda */
	size_t word_chunks = n / word_size;				/* calculate number of whole words left to copy */
	size_t remainder = n % word_size;				/* copy trailing bytes that dont fit into words */ 
	assert(dest);
	assert(src);
	assert(printf("Memcpy:\n"));
	for(;word_chunks > 0;--word_chunks)				/* copy whole words */
	{
		*((long*)dest) = *((long*)src);
		dest = (void*)(((char*)dest) + word_size);
		src = (void*)(((char*)src) + word_size);
		assert(printf("whole word operation\n"));
	}
	for(;remainder > 0; --remainder)				/* copy trailing bytes that dont fit into words */
	{
		*((char*)dest) = *((char*)src);	
		dest = (void*)(((char*)dest) + 1);
		src = (void*)(((char*)src) + 1);
		assert(printf("single byte operation\n"));
	}
	assert(printf("finished\n"));
	return start;
}


/* memmove reviewer: arthur */
void *Memmove(void *dest, const void *src, size_t n)
{
	void *start = dest;						/* for returning */
	size_t src_address = (size_t)src;				/* for calculating relative spot */
	size_t dest_address = (size_t)dest;
	assert(dest);
	assert(src);
	if(dest_address > src_address)					/* only "special" case, we need to copy from end to start */
	{
		char *dest_end = ((char*)dest_address + (n-1));
		char *src_end = ((char*)src_address + (n-1));
		assert(printf("Memmove:\n"));
		for(;n > 0; --n)
		{
			*(dest_end) = *(src_end);
			--dest_end;
			--src_end;
			assert(printf("single byte operation\n"));
		}
		assert(printf("finished\n"));
	}
	else								/* Memcpy is just fine in other cases */
	{
		Memcpy(dest,src,n);
	}
	return start;
}



























