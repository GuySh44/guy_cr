#include <stddef.h>
#include <assert.h>


#include "vsa.h"

#define MAGIC 0xDEADBEEF
#define WORD_SIZE sizeof(size_t)

struct vsa
{
	size_t header_size;
	size_t pool_size;
	void *data;
};

static void VsaDefrag(vsa_t *vsa)
{
	size_t mem_ahead = vsa->pool_size;
	size_t tmp_free_frag = 0;
	size_t *curr_free_ahead = ((size_t*)((char*)vsa->data + WORD_SIZE));
	size_t *curr_aloc_ahead = ((size_t*)((char*)vsa->data));
	size_t curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
	size_t *next_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size));
	size_t *next_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + curr_block_size + vsa->header_size));
	
	while (mem_ahead)
	{
		assert(mem_ahead > 0);
		mem_ahead = mem_ahead - curr_block_size - vsa->header_size;
		if(*curr_aloc_ahead == 0 && *next_aloc_ahead == 0 && *next_free_ahead != 0)
		{
				*curr_free_ahead = *curr_free_ahead + *next_free_ahead + vsa->header_size;
				mem_ahead += curr_block_size + vsa->header_size;
				next_free_ahead = ((size_t*)((char*)curr_free_ahead + *curr_free_ahead + vsa->header_size));
				next_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + *curr_free_ahead + vsa->header_size));
				curr_block_size = *curr_free_ahead;
				continue;
				
		}
		else if(*curr_free_ahead > 0 && *next_aloc_ahead == 0 && *next_free_ahead != 0)
		{
			mem_ahead += *curr_free_ahead;
			tmp_free_frag = *curr_free_ahead + *next_free_ahead;
			next_aloc_ahead = ((size_t*)((char*)next_aloc_ahead - *curr_free_ahead));
			*next_aloc_ahead = 0;
			next_free_ahead = ((size_t*)((char*)next_free_ahead - *curr_free_ahead));
			*next_free_ahead = tmp_free_frag;
			*curr_free_ahead = 0;
		}
		curr_free_ahead = next_free_ahead;
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
	*((size_t*)((char*)vsa->data + vsa->pool_size)) = 0;
	*((size_t*)((char*)vsa->data + vsa->pool_size+ WORD_SIZE)) = 0;
	
	*((size_t*)(vsa->data)) = 0;
	*((size_t*)((char*)vsa->data + WORD_SIZE)) = vsa->pool_size - vsa->header_size;
	
	#ifndef NDEBUG
    *((size_t*)((char*)vsa->data + vsa->header_size - WORD_SIZE)) = MAGIC;
    *((size_t*)((char*)vsa->data + vsa->pool_size + vsa->header_size - WORD_SIZE)) = MAGIC;
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
	
	while(0 != *curr_aloc_ahead || 0 != *curr_free_ahead)
	{
		if(0 == *curr_aloc_ahead && *curr_free_ahead >= block_size)
		{
			if( *curr_free_ahead < block_size + vsa->header_size)
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
			else
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
		curr_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size));
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
	assert(*((size_t*)((char*)block - sizeof(size_t))) == (size_t)MAGIC);
	block = ((void*)((char*)block - sizeof(size_t)));
	#endif
	
	free_ahead = ((size_t*)((char*)block - sizeof(size_t)));
	aloc_ahead = ((size_t*)((char*)block - 2 * sizeof(size_t)));
	
	*free_ahead += *aloc_ahead;
	*aloc_ahead = 0;
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
	
	while(0 != *curr_aloc_ahead || 0 != *curr_free_ahead)
	{
		if(0 == *curr_aloc_ahead)
		{
			if(*curr_free_ahead > largest)
			{
				largest = *curr_free_ahead;
			}
		}
		curr_free_ahead = ((size_t*)((char*)curr_free_ahead + curr_block_size + vsa->header_size));
		curr_aloc_ahead = ((size_t*)((char*)curr_aloc_ahead + curr_block_size + vsa->header_size));
		curr_block_size = *curr_free_ahead + *curr_aloc_ahead;
	}
	return largest;
}
