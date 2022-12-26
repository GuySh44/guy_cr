#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "fsa.h"

struct fsa
{
	size_t blocks_num;
	size_t block_size;
	void *data;
};

/*  return 1 if full */
static int FsaIsFull(fsa_t *fsa)
{
	size_t i = *((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num)));
	return i == (fsa->blocks_num);
}


size_t FsaSuggestedSize(size_t num_blocks, size_t block_size)
{
	short word_size = sizeof(size_t);
	short max_buffer = word_size - 1;
	size_t complete_word = (((block_size % word_size) != 0) + (block_size / word_size)) * word_size;	/* complete block size to a multiplication on word size */
	return max_buffer + sizeof(struct fsa) + (complete_word * num_blocks) + word_size;
}

fsa_t *FsaInit(void *alloc_dest, size_t block_size, size_t size)
{
	size_t address = (size_t)alloc_dest;
	size_t i = 0;
	short word_size = sizeof(size_t);
	short times_to_align = (word_size - (address % word_size)) % word_size;
	fsa_t *fsa = (fsa_t*)alloc_dest;
	
	assert(size > times_to_align + sizeof(struct fsa));
	
	fsa->block_size = (((block_size % word_size) != 0) + (block_size / word_size)) * word_size;
	fsa->blocks_num = (size - times_to_align - sizeof(struct fsa) - word_size) / (fsa->block_size);
	alloc_dest = (void*)((char*)alloc_dest + times_to_align + sizeof(struct fsa));
	fsa->data = alloc_dest;
	for(; i < fsa->blocks_num + 1; ++i)
	{
		*((size_t*)((char*)fsa->data + (fsa->block_size) * i)) = (size_t)((i + 1) % (fsa->blocks_num + 1));
	}
	return fsa;
}

void *FsaAlloc(fsa_t *fsa)
{
	size_t i = *((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num)));
	if (FsaIsFull(fsa))
	{
		return NULL;
	}
	*((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num))) = *((size_t*)((char*)fsa->data + (fsa->block_size) * i));
	return ((void*)((char*)fsa->data + fsa->block_size * i));
}


void FsaFree(fsa_t *fsa, void *block)
{
	size_t *last_header_ptr = ((size_t*)((char*)fsa->data + (fsa->block_size * (fsa->blocks_num))));
	size_t i = ((size_t)((char*)block - (char*)fsa->data)) / (fsa->block_size);
	*((size_t*)((char*)block)) = *last_header_ptr;
	*last_header_ptr = i;
}

size_t FsaCountFree(const fsa_t *fsa)
{
	size_t i = *((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num)));
	size_t count = 0;
	while (i != (fsa->blocks_num))
	{
		i = *((size_t*)((char*)fsa->data + (fsa->block_size) * i));
		++count;
	}
	return count;
}







