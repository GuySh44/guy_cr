#ifndef __EXT2_H__
#define __EXT2_H__

#include <stddef.h>

typedef struct ext2_super_block sp;

typedef struct ext2_group_desc gd;

void CopyBlock(int fd, size_t offset, size_t block_size, void *buffer);

void PrintSuperBlock(const sp *super_block);

void PrintGroupDescriptor(const gd *group_descriptor);

#endif /* __EXT2_H__ */

