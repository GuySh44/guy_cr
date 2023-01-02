#ifndef __VSA_H__ILRD__CR3_
#define __VSA_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

vsa_t *VsaInit(const void *alloc_dest, const size_t size);

void *VsaAlloc(vsa_t *vsa, const size_t block_size);

void VsaFree(void *block);

size_t VsaLargestChunk(vsa_t *vsa);

#endif /* __VSA_H__ILRD__CR3_ */

