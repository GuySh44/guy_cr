#ifndef __VECTOR_H__ILRD__CR3_
#define __VECTOR_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

vector_t *VectorInit(size_t capacity, size_t elem_size);

void *VectorAcess(vector_t *vec, size_t index);

void VectorResize(vector_t *vec, size_t size);

void VectorDestroy(vector_t *vec);

void VectorPushBack(vector_t *vec, const void *data);

void VectorPopBack(vector_t *vec);

void VectorShrink(vector_t *vec); /*this function will leave a  additional 10% memory of the previous size  after shrink*/

size_t VectorSize(const vector_t *vec);


#endif  /* __VECTOR_H__ILRD__CR3_ */ 
