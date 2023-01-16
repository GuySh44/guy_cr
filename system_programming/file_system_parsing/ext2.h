#ifndef __EXT2_H__
#define __EXT2_H__

#include <stddef.h>

typedef struct ext2_dir_entry dir_entry1;

typedef struct ext2_dir_entry_2 dir_entry2;

typedef struct ext2_inode inode;

typedef struct ext2_super_block sb;

typedef struct ext2_group_desc gd;


typedef long (*block_func)();


void CopyToBuffer(int fd, size_t offset, size_t block_size, void *buffer);

long SpiderDir(void *buffer, size_t size, char *name);

long UseFile(int device_fd, sb *super_block, gd *group_descriptor, size_t inode_num, block_func action_func, void *arg);

void LoadInode(int device_fd, sb *super_block, gd* group_descriptor, inode *curr_inode, size_t inode_num);

long PrintBlock(void *buffer, size_t size);

long ChmodInode(int device_fd, sb *super_block, gd* group_descriptor, size_t inode_num, char *args);

void PrintDirEntry(const dir_entry2 *entry);

void PrintSuperBlock(const sb *super_block);

void PrintGroupDescriptor(const gd *group_descriptor);

void PrintInode(const inode *node);

size_t CalculateGroupTable(sb *super_block, gd *group_descriptor, size_t inode_num);

long GetFileInode(int device_fd, sb *super_block, gd *group_descriptor, char *pathname);


#endif /* __EXT2_H__ */

