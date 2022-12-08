#include"vector.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>

#define GROWTH_FACTOR 2
#define SHRINK_MARGAIN 0.1

struct vector
{
	size_t capacity;
	size_t element_size;
	size_t elements_count;
	void *data;
};

vector_t *VectorInit(size_t capacity, size_t elem_size)
{
	vector_t *new_vector = (vector_t*)malloc(sizeof(*new_vector)); 
	if (NULL == new_vector)
	{
		return NULL;
	}
	assert(capacity);
	assert(elem_size);
	new_vector->data = malloc(capacity * elem_size);
	if (NULL == new_vector->data)
	{
		free(new_vector);
		return NULL;
	}
	new_vector->capacity = capacity;
	new_vector->element_size = elem_size;
	new_vector->elements_count = 0;
	return new_vector;
}

void VectorDestroy(vector_t *vec)
{
	assert(vec);
	free(vec->data);
	free(vec);
}


void VectorPushBack(vector_t *vec, const void *data)
{
	assert(vec);
	if(vec->elements_count == vec->capacity)
	{
		VectorResize(vec, vec->capacity * GROWTH_FACTOR);
	}
	memcpy(((char*)(vec->data) + (vec->elements_count * vec->element_size)), data, vec->element_size);
	++(vec->elements_count); 
}

void VectorPopBack(vector_t *vec)
{
	assert(vec);
	--(vec->elements_count);
}

void *VectorAcess(vector_t *vec, size_t index)
{
	size_t calculated_index = index * vec->element_size;
	assert(vec);
	assert(index < vec->elements_count);
	return ((char*)vec->data + calculated_index);
}


void VectorResize(vector_t *vec, size_t size)
{
	void *resized_data = realloc(vec->data, size * vec->element_size);
	assert(vec);
	if (NULL == resized_data)
	{	
		assert(printf("Staying big and strong"));
		return;
	}
	vec->capacity = size;
	vec->data = resized_data;
	if(size < vec->elements_count)
	{
		vec->elements_count = size;
	}
}

void VectorShrink(vector_t *vec)
{
	size_t remainder = (vec->capacity) * SHRINK_MARGAIN;
	size_t new_capacity = (remainder + vec->elements_count);
	void* shrunk_data = realloc(vec->data, new_capacity * vec->element_size);
	assert(vec);
	if (NULL == shrunk_data)
	{	
		assert(printf("Yo I cant shrink rn"));
		return;
	}
	vec->data = shrunk_data;
	vec->capacity = new_capacity;
}

size_t VectorSize(const vector_t *vec)
{
	return vec->elements_count;
}


