#include <fcntl.h> /* open */
#include <unistd.h> /* read lseek */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <errno.h> /* perror */
#include <linux/types.h> /* __le __u */
#include <string.h> /* strcat */


#include "ext2.h"


#define SUPER_BLOCK_SIZE 1024
#define SUPER_BLOCK_OFFSET 1024
#define BLOCK_SIZE_BYTES 1024
#define GROUP_DESCRIPTOR_SIZE 32

struct ext2_super_block {
	__le32	s_inodes_count;		/* Inodes count */
	__le32	s_blocks_count;		/* Blocks count */
	__le32	s_r_blocks_count;	/* Reserved blocks count */
	__le32	s_free_blocks_count;	/* Free blocks count */
	__le32	s_free_inodes_count;	/* Free inodes count */
	__le32	s_first_data_block;	/* First Data Block */
	__le32	s_log_block_size;	/* Block size */
	__le32	s_log_frag_size;	/* Fragment size */
	__le32	s_blocks_per_group;	/* # Blocks per group */
	__le32	s_frags_per_group;	/* # Fragments per group */
	__le32	s_inodes_per_group;	/* # Inodes per group */
	__le32	s_mtime;		/* Mount time */
	__le32	s_wtime;		/* Write time */
	__le16	s_mnt_count;		/* Mount count */
	__le16	s_max_mnt_count;	/* Maximal mount count */
	__le16	s_magic;		/* Magic signature */
	__le16	s_state;		/* File system state */
	__le16	s_errors;		/* Behaviour when detecting errors */
	__le16	s_minor_rev_level; 	/* minor revision level */
	__le32	s_lastcheck;		/* time of last check */
	__le32	s_checkinterval;	/* max. time between checks */
	__le32	s_creator_os;		/* OS */
	__le32	s_rev_level;		/* Revision level */
	__le16	s_def_resuid;		/* Default uid for reserved blocks */
	__le16	s_def_resgid;		/* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 * 
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	__le32	s_first_ino; 		/* First non-reserved inode */
	__le16   s_inode_size; 		/* size of inode structure */
	__le16	s_block_group_nr; 	/* block group # of this superblock */
	__le32	s_feature_compat; 	/* compatible feature set */
	__le32	s_feature_incompat; 	/* incompatible feature set */
	__le32	s_feature_ro_compat; 	/* readonly-compatible feature set */
	__u8	s_uuid[16];		/* 128-bit uuid for volume */
	char	s_volume_name[16]; 	/* volume name */
	char	s_last_mounted[64]; 	/* directory where last mounted */
	__le32	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	__u8	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
	__u8	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
	__u16	s_padding1;
	/*
	 * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
	__u8	s_journal_uuid[16];	/* uuid of journal superblock */
	__u32	s_journal_inum;		/* inode number of journal file */
	__u32	s_journal_dev;		/* device number of journal file */
	__u32	s_last_orphan;		/* start of list of inodes to delete */
	__u32	s_hash_seed[4];		/* HTREE hash seed */
	__u8	s_def_hash_version;	/* Default hash version to use */
	__u8	s_reserved_char_pad;
	__u16	s_reserved_word_pad;
	__le32	s_default_mount_opts;
 	__le32	s_first_meta_bg; 	/* First metablock block group */
	__u32	s_reserved[190];	/* Padding to the end of the block */
};

struct ext2_group_desc
{
	__u32	bg_block_bitmap;	/* Blocks bitmap block */
	__u32	bg_inode_bitmap;	/* Inodes bitmap block */
	__u32	bg_inode_table;		/* Inodes table block */
	__u16	bg_free_blocks_count;	/* Free blocks count */
	__u16	bg_free_inodes_count;	/* Free inodes count */
	__u16	bg_used_dirs_count;	/* Directories count */
	__u16	bg_pad;
	__u32	bg_reserved[3];
};

void CopyBlock(int fd, size_t offset, size_t block_size, void *buffer)
{
	if(-1 == lseek(fd, offset, SEEK_SET))
	{
		perror(NULL);
	}
	if(-1 == read(fd, buffer, block_size))
	{
		perror(NULL);
	}
}

void PrintSuperBlock(const sp *super_block)
{
printf("SuperBlock:\n\
{\n\
Inodes count:\t\t\t%u\n\
Blocks count:\t\t\t%u\n\
Free blocks count:\t\t%u\n\
Free inodes count:\t\t%u\n\
First Data Block:\t\t%u\n\
Block size:\t\t\t%u\n\
Fragment size:\t\t\t%u\n\
Blocks per group:\t\t%u\n\
Fragments per group:\t\t%u\n\
Inodes per group:\t\t%u\n\
Magic signature:\t\t%u\n\
File system state:\t\t%u\n\
OS:\t\t\t\t%u\n\
First non-reserved inode:\t%u\n\
block group # of this superblock:%u\n\
}\n\n",\
super_block->s_inodes_count,\
super_block->s_blocks_count,\
super_block->s_free_blocks_count,\
super_block->s_free_inodes_count,\
super_block->s_first_data_block,\
super_block->s_log_block_size,\
super_block->s_log_frag_size,\
super_block->s_blocks_per_group,\
super_block->s_frags_per_group,\
super_block->s_inodes_per_group,\
super_block->s_magic,\
super_block->s_state,\
super_block->s_creator_os,\
super_block->s_first_ino,\
super_block->s_block_group_nr);
}

void PrintGroupDescriptor(const gd *group_descriptor)
{
	printf("GroupDescriptor:\n\
{\n\
Blocks bitmap block:\t\t%u\n\
Inodes bitmap block:\t\t%u\n\
Inodes table block:\t\t%u\n\
Free blocks count:\t\t%u\n\
Free inodes count:\t\t%u\n\
Directories count:\t\t%u\n\
}\n\n",\
group_descriptor->bg_block_bitmap,\
group_descriptor->bg_inode_bitmap,\
group_descriptor->bg_inode_table,\
group_descriptor->bg_free_blocks_count,\
group_descriptor->bg_free_inodes_count,\
group_descriptor->bg_used_dirs_count);
}

int main(int argc, char *argv[])
{
	char *device_name = argv[1];
	char *file_path = argv[2];
	size_t gd_offset = 0;
	int device_fd = 0;
	sp *super_block = NULL;
	gd *group_descriptor = NULL;
	
	/* open the "device" file */
	
	device_fd = open(device_name, O_RDONLY);
	
	if(device_fd == -1)
	{
		perror(NULL);
		return -1;
	}
	
	/* create super block struct and copy right content from HDD */
	super_block = (sp*)malloc(SUPER_BLOCK_SIZE);
	
	if(NULL == super_block)
	{
		return 1;
	}
	
	CopyBlock(device_fd, SUPER_BLOCK_OFFSET, SUPER_BLOCK_SIZE, super_block);

	PrintSuperBlock(super_block);
	
	/* create group descriptor struct and copy right content from HDD */
	
	group_descriptor = (gd*)malloc(GROUP_DESCRIPTOR_SIZE);
	
	if(NULL == group_descriptor)
	{
		return 1;
	}
	
	gd_offset = ((3 + (super_block->s_log_block_size > 0)) * BLOCK_SIZE_BYTES);
	
	CopyBlock(device_fd, gd_offset, GROUP_DESCRIPTOR_SIZE, group_descriptor);
	
	PrintGroupDescriptor(group_descriptor);
	
	/* send fd to function that prints files content for files in the root directory */
	
	/* use what was implemented as static to implement a function that traverses one directory at a time */
	
	/* use the functions to print the file specified  */
	return 0;
	
	(void)argc;
}
