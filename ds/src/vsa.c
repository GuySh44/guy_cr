#include <stddef.h> /* size_t */
#include <assert.h> /* assert */


#include "vsa.h"


#define MAGIC 0xDEADBEEF /* Debug mode alloced block signature */
#define WORD_SIZE sizeof(size_t)

/*
Reviewer: Yahav
*/

/* 

VSA - my vsa works with 2 word headers, type of size_t , when one word signyfies the alloced amount of bytes in the block,
and the other the amount of free bytes in the block.

there are 3 options when it comes to block "kind":
-alloced amount is 0 - so the block is freed and can be alloced
-alloced amount is more than 0:
	* if free amount is 0 - the block is alloced and there is no fragmantation
	* if free amount is more than 0 - the block is alloced and there is free amount of fragmantation
	
header_size - header size	
pool_size - The largest block available when the vsa is empty
data - the address of the pool start
*/
struct vsa
{
	size_t header_size;
	size_t pool_size;
	void *data;
};

/* defrag the pool, including "trapped" blocks between allocs */
static void VsaDefrag(vsa_t *vsa)
{
	size_t mem_ahead = vsa->pool_size;		/* allows us to "iterate" over the entire pool */
	size_t tmp_free_frag = 0;				/* temporal size for free bytes available when there is fragmantation */
	size_t *curr_free_ahead = ((size_t*)((char*)vsa->data + WORD_SIZE));		/* free bytes in current block space */
	size_t *curr_aloc_ahead = ((size_t*)((char*)vsa->data));					/* alloced bytes in current block space */
	size_t curr_block_size = *curr_free_ahead + *curr_aloc_ahead;				/* current block size */
	size_t *next_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size)); /* free bytes in next block space */
	size_t *next_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + curr_block_size + vsa->header_size)); /* alloced bytes in next block space */
	
	while (mem_ahead)
	{
		assert(mem_ahead > 0);
		mem_ahead = mem_ahead - curr_block_size - vsa->header_size;				/* how much memory till end */
		if(*curr_aloc_ahead == 0 && *next_aloc_ahead == 0 && *next_free_ahead != 0)		/* defrag 2 adjecent freed blocks */
		{
				*curr_free_ahead = *curr_free_ahead + *next_free_ahead + vsa->header_size;
				mem_ahead += curr_block_size + vsa->header_size;
				next_free_ahead = ((size_t*)((char*)curr_free_ahead + *curr_free_ahead + vsa->header_size));
				next_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + *curr_free_ahead + vsa->header_size));
				curr_block_size = *curr_free_ahead;
				continue;
				
		}
		else if(*curr_free_ahead > 0 && *next_aloc_ahead == 0 && *next_free_ahead != 0)		/* defrag adjecent block and fragmantation from previous block  */
		{
			mem_ahead += *curr_free_ahead;
			tmp_free_frag = *curr_free_ahead + *next_free_ahead;
			next_aloc_ahead = ((size_t*)((char*)next_aloc_ahead - *curr_free_ahead));
			*next_aloc_ahead = 0;
			next_free_ahead = ((size_t*)((char*)next_free_ahead - *curr_free_ahead));
			*next_free_ahead = tmp_free_frag;
			*curr_free_ahead = 0;
		}
		curr_free_ahead = next_free_ahead;													/* move to next set of blocks */
		curr_aloc_ahead = next_aloc_ahead;
		curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
		next_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size));
		next_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + curr_block_size + vsa->header_size));
	}
}


vsa_t *VsaInit(void *alloc_dest, size_t size)
{
	size_t address = (size_t)alloc_dest;
	short times_to_align = (WORD_SIZE - (address % WORD_SIZE)) % WORD_SIZE;
	
	vsa_t *vsa = (vsa_t*)alloc_dest;
	
	assert(alloc_dest);
	assert(size > times_to_align + sizeof(struct vsa));
	
	vsa->header_size = sizeof(size_t) + sizeof(size_t);
	
	#ifndef NDEBUG
    vsa->header_size += WORD_SIZE;
	#endif
	
	vsa->data = (void*)((char*)alloc_dest + times_to_align + sizeof(struct vsa));
	vsa->pool_size = size - times_to_align - sizeof(struct vsa) - vsa->header_size;
	
	*((size_t*)((char*)vsa->data + vsa->pool_size)) = 0; 				/* ending header/dummy */
	*((size_t*)((char*)vsa->data + vsa->pool_size+ WORD_SIZE)) = 0;		/* ending header/dummy */
	
	*((size_t*)(vsa->data)) = 0;										/* first header */
	*((size_t*)((char*)vsa->data + WORD_SIZE)) = vsa->pool_size - vsa->header_size;		/* first header */
	
	#ifndef NDEBUG
    *((size_t*)((char*)vsa->data + vsa->header_size - WORD_SIZE)) = MAGIC;		/* magic number signaure on first header */
    *((size_t*)((char*)vsa->data + vsa->pool_size + vsa->header_size - WORD_SIZE)) = MAGIC;		/* magic number signaure on last header/dummy */
	#endif
	
	return vsa;
}

void *VsaAlloc(vsa_t *vsa, size_t block_size)
{
	size_t *curr_free_ahead;
	size_t *curr_aloc_ahead;
	size_t curr_block_size;
	void *new_block = NULL;
	
	assert(vsa);
	
	VsaDefrag(vsa);
	
	block_size = (((block_size % WORD_SIZE) != 0) + (block_size / WORD_SIZE)) * WORD_SIZE;
	
	curr_free_ahead = ((size_t*)((char*)vsa->data + WORD_SIZE));
	curr_aloc_ahead = ((size_t*)((char*)vsa->data));
	curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
	
	while(0 != *curr_aloc_ahead || 0 != *curr_free_ahead)				/* while we didnt reach dummy */
	{
		if(0 == *curr_aloc_ahead && *curr_free_ahead >= block_size)		/* if the block ahead is free and big enough to hold the size */
		{
			if(*curr_free_ahead < block_size + vsa->header_size)		/* if there isnt enough space for another header at the end and we need to fragment */
			{
				*curr_free_ahead = *curr_free_ahead - block_size;
				*curr_aloc_ahead = block_size;
				new_block = (void*)((char*)curr_free_ahead + WORD_SIZE);
				
			 	#ifndef NDEBUG
			 	*((size_t*)new_block) = MAGIC;
			 	new_block = (void*)((char*)new_block + WORD_SIZE);
		 		#endif
		 		
				return new_block; 
			}
			else														/* regular space without fragmentation */
			{
				size_t tmp_free = *curr_free_ahead - block_size - vsa->header_size;
				*curr_aloc_ahead = block_size;
				*curr_free_ahead = 0;
				new_block = (void*)((char*)curr_free_ahead + WORD_SIZE);
				*((size_t*)((char*)curr_free_ahead + block_size + vsa->header_size)) = tmp_free;
				*((size_t*)((char*)curr_aloc_ahead + block_size + vsa->header_size)) = 0;
				
				#ifndef NDEBUG
			 	*((size_t*)new_block) = MAGIC;
			 	new_block = (void*)((char*)new_block + WORD_SIZE);
		 		#endif
		 		
		 		return new_block;
			}
		}
		curr_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size));		/* go to next block in search for big enough free */
		curr_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + curr_block_size + vsa->header_size));
		curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
	}
	return NULL;
}

void VsaFree(void *block)
{
	size_t *free_ahead;
	size_t *aloc_ahead;
	assert(block);
	
	#ifndef NDEBUG
	assert(*((size_t*)((char*)block - sizeof(size_t))) == (size_t)MAGIC);		/* assert we have signaure on alloced blocks */
	block = ((void*)((char*)block - sizeof(size_t)));
	#endif
	
	free_ahead = ((size_t*)((char*)block - sizeof(size_t)));			
	aloc_ahead = ((size_t*)((char*)block - 2 * sizeof(size_t)));
	
	*free_ahead += *aloc_ahead;													/* set free ahead of block to free + alloced */
	*aloc_ahead = 0;															/* set alloced to 0 */
}

size_t VsaLargestChunk(vsa_t *vsa)
{
	size_t largest = 0;
	size_t *curr_free_ahead;
	size_t *curr_aloc_ahead;
	size_t curr_block_size;	
	
	assert(vsa);
	
	VsaDefrag(vsa);
	
	curr_free_ahead = ((size_t*)((char*)vsa->data + WORD_SIZE));
	curr_aloc_ahead = ((size_t*)((char*)vsa->data));
	curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
	
	while(0 != *curr_aloc_ahead || 0 != *curr_free_ahead)						/* while we didnt reach last header/dummy */
	{
		if(0 == *curr_aloc_ahead && *curr_free_ahead > largest)					/* if we found a larger block we keep the size */
		{	
			largest = *curr_free_ahead;
		}
		curr_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size));		/* go to next block */
		curr_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + curr_block_size + vsa->header_size));
		curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
	}
	return largest;
}
