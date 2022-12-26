#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "fsa.h"

/*
REVIEWER: YAHAV
DATE: 26.12
QUOTE OF THE DAY: life doesnt smell 
*/
/* 
blocks_num - keeps the amount of blocks we calculated while init
block_size - keeps the size of each block, we calculated while init
data - pointer to the data + headers construct which is an array, in my implementation the headers are kept inside the data space :)
an additional dummy is kept at the end of data keeping the next available data block
*/
struct fsa
{
	size_t blocks_num;
	size_t block_size;
	void *data;
};

/* return 1 if the fsa is full */
static int FsaIsFull(fsa_t *fsa)
{
	size_t i = *((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num)));	/* check next available in dummy, if next available == dummy we full */
	assert(fsa);
	return i == (fsa->blocks_num);
}


size_t FsaSuggestedSize(size_t num_blocks, size_t block_size)
{
	short word_size = sizeof(size_t);
	short max_buffer = word_size - 1;	/* worst case unaligned memory start address */
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
	
	assert(alloc_dest);
	assert(size > times_to_align + sizeof(struct fsa));
	
	fsa->block_size = (((block_size % word_size) != 0) + (block_size / word_size)) * word_size;		/* complete block size to a multiplication on word size */
	fsa->blocks_num = (size - times_to_align - sizeof(struct fsa) - word_size) / (fsa->block_size); /* allocate as many blocks as possible with given size */
	fsa->data = (void*)((char*)alloc_dest + times_to_align + sizeof(struct fsa));	/* find the start of data */
	for(; i < fsa->blocks_num + 1; ++i)
	{
		*((size_t*)((char*)fsa->data + (fsa->block_size) * i)) = (size_t)((i + 1) % (fsa->blocks_num + 1)); /* set indexes in data/header space Josephus problem style */
	}
	return fsa;
}

void *FsaAlloc(fsa_t *fsa)
{
	size_t i = *((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num))); /* find next available block index in dummy */
	if (FsaIsFull(fsa)) /* check if full */
	{
		return NULL;
	}
	*((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num))) = *((size_t*)((char*)fsa->data + (fsa->block_size) * i)); /* set next available in dummy to the index pointed by the data/header space about to be allocated (josephus style) */
	return ((void*)((char*)fsa->data + fsa->block_size * i));	/* return data/header space to be allocated */
}


void FsaFree(fsa_t *fsa, void *block)
{
	size_t *last_header_ptr = ((size_t*)((char*)fsa->data + (fsa->block_size * (fsa->blocks_num))));	/* ptr to the dummy */
	size_t i = ((size_t)((char*)block - (char*)fsa->data)) / (fsa->block_size);		/* deduct the index of the block provided */
	assert(fsa);
	assert(block);
	*((size_t*)((char*)block)) = *last_header_ptr;	/* set next of block provided to next available in dummy */
	*last_header_ptr = i;	/* set next available in dummy to block provided */
}

size_t FsaCountFree(const fsa_t *fsa)
{
	size_t i = *((size_t*)((char*)fsa->data + (fsa->block_size) * (fsa->blocks_num)));	/* set i to next available pointed by dummy */
	size_t count = 0;
	while (i != (fsa->blocks_num))	/* while i isnt dummys index */
	{
		i = *((size_t*)((char*)fsa->data + (fsa->block_size) * i));	/* i = next available of the last i */
		++count;
	}
	return count;
}







