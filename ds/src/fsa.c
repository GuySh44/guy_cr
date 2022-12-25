#include <stddef.h>
#include <string.h>

#include "fsa.h"

struct fsa
{
	size_t blocks_num;
	size_t block_size;
	void *data;
};


size_t FsaSuggestedSize(size_t num_blocks, size_t block_size)
{
	short word_size = sizeof(size_t);
	short max_buffer = word_size - 1;
	size_t complete_word = (((block_size % word_size) != 0) + (block_size / word_size)) * word_size;
	return max_buffer + sizeof(struct fsa) + ((complete_word + word_size) * num_blocks);
}

fsa_t *FsaInit(void *alloc_dest, size_t num_blocks, size_t block_size)
{
	size_t address = (size_t)alloc_dest;
	size_t i = 0;
	short word_size = sizeof(size_t);
	short times_to_align = (word_size - (address % word_size)) % word_size;
	fsa_t *fsa = (fsa_t*)alloc_dest;
	fsa->blocks_num = num_blocks;
	fsa->block_size = block_size;
	alloc_dest = (void*)((char*)alloc_dest + times_to_align + sizeof(fsa->blocks_num) + sizeof(fsa->block_size));
	fsa->data = alloc_dest;
	for(; i < num_blocks; ++i)
	{
		*((size_t*)((char*)(fsa->data) + (word_size + block_size) * i)) = (i + 1) % num_blocks;
	}
	return fsa;
}

/* Description: the function should return a pointer to the next available block, and update the managment struct */
void *FsaAlloc(fsa_t *fsa);

/* Description: the function "frees" the block specified, and updates the managment struct accordingly */
void FsaFree(fsa_t *fsa, void *block);

/* Description: the function returns the number of available blocks */
size_t FsaCountFree(const fsa_t *fsa);

