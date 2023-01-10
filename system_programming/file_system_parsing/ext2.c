#include <fcntl.h> /* open */
#include <unistd.h> /* read lseek */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <errno.h> /* perror */
#include <linux/types.h> /* __le __u */
#include <string.h> /* strcat */


#include "ext2.h"


#define SUPER_BLOCK_SIZE	(1024)
#define SUPER_BLOCK_OFFSET	(1024)
#define KILOBYTE	(1024)
#define GROUP_DESCRIPTOR_SIZE	(32)
#define	EXT2_NDIR_BLOCKS	(12)
#define	EXT2_IND_BLOCK	(EXT2_NDIR_BLOCKS)
#define	EXT2_DIND_BLOCK	(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK	(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS	(EXT2_TIND_BLOCK + 1)
#define BLOCK_OFFSET(block) ((block)*calc_block_size)

struct ext2_inode {
	__le16	i_mode;		/* File mode */
	__le16	i_uid;		/* Low 16 bits of Owner Uid */
	__le32	i_size;		/* Size in bytes */
	__le32	i_atime;	/* Access time */
	__le32	i_ctime;	/* Creation time */
	__le32	i_mtime;	/* Modification time */
	__le32	i_dtime;	/* Deletion Time */
	__le16	i_gid;		/* Low 16 bits of Group Id */
	__le16	i_links_count;	/* Links count */
	__le32	i_blocks;	/* Blocks count */
	__le32	i_flags;	/* File flags */
	union {
		struct {
			__le32  l_i_reserved1;
		} linux1;
		struct {
			__le32  h_i_translator;
		} hurd1;
		struct {
			__le32  m_i_reserved1;
		} masix1;
	} osd1;				/* OS dependent 1 */
	__le32	i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	__le32	i_generation;	/* File version (for NFS) */
	__le32	i_file_acl;	/* File ACL */
	__le32	i_dir_acl;	/* Directory ACL */
	__le32	i_faddr;	/* Fragment address */
	union {
		struct {
			__u8	l_i_frag;	/* Fragment number */
			__u8	l_i_fsize;	/* Fragment size */
			__u16	i_pad1;
			__le16	l_i_uid_high;	/* these 2 fields    */
			__le16	l_i_gid_high;	/* were reserved2[0] */
			__u32	l_i_reserved2;
		} linux2;
		struct {
			__u8	h_i_frag;	/* Fragment number */
			__u8	h_i_fsize;	/* Fragment size */
			__le16	h_i_mode_high;
			__le16	h_i_uid_high;
			__le16	h_i_gid_high;
			__le32	h_i_author;
		} hurd2;
		struct {
			__u8	m_i_frag;	/* Fragment number */
			__u8	m_i_fsize;	/* Fragment size */
			__u16	m_pad1;
			__u32	m_i_reserved2[2];
		} masix2;
	} osd2;				/* OS dependent 2 */
};

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
	__le16  s_inode_size; 		/* size of inode structure */
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
Inode struct size:\t\t%u\n\
Magic signature:\t\t%u\n\
File system state:\t\t%u\n\
OS:\t\t\t\t%u\n\
First non-reserved inode:\t%u\n\
block group # of this superblock:%u\n\
rev level:\t\t\t%u\n\
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
super_block->s_inode_size,\
super_block->s_magic,\
super_block->s_state,\
super_block->s_creator_os,\
super_block->s_first_ino,\
super_block->s_block_group_nr,\
super_block->s_rev_level);
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

void PrintInode(const inode *node)
{
	printf("Inode:\n\
{\n\
File mode:\t\t\t%x\n\
Low 16 bits of Owner Uid:\t%u\n\
Size in bytes:\t\t\t%u\n\
Creation time:\t\t\t0x%x\n\
Modification time:\t\t0x%x\n\
File flags:\t\t\t%u\n\
}\n\n",\
node->i_mode,\
node->i_uid,\
node->i_size,\
node->i_ctime,\
node->i_mtime,\
node->i_flags);
}

int main(int argc, char *argv[])
{
	char *device_name = argv[1];
	char *file_path = argv[2];
	size_t gd_offset = 0;
	size_t calc_block_size = 0;
	size_t inode_block_index = 0;
	size_t inode_local_index = 0;
	int device_fd = 0;
	sp *super_block = NULL;
	gd *group_descriptor = NULL;
	inode *curr_inode = NULL;
	
	/* open the "device" file */
	
	device_fd = open(device_name, O_RDONLY);
	
	if(device_fd == -1)
	{
		perror(NULL);
		return errno;
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
	
	calc_block_size = KILOBYTE << super_block->s_log_block_size;
	
	gd_offset = (KILOBYTE * (super_block->s_log_block_size == 0) ) + (calc_block_size);
	
	CopyBlock(device_fd, gd_offset, GROUP_DESCRIPTOR_SIZE, group_descriptor);
	
	PrintGroupDescriptor(group_descriptor);
	
	/* print root directory files contents */
	
	curr_inode = (inode*)malloc(super_block->s_inode_size);
	
	if(NULL == curr_inode)
	{
		return 1;
	}
	
	CopyBlock(device_fd, BLOCK_OFFSET(group_descriptor->bg_inode_table) + super_block->s_inode_size, super_block->s_inode_size, curr_inode);		/* parse the second inode which is the root directory inode in block 0 inode table */
	
	PrintInode(curr_inode);
	
	inode_block_index = ( - 1) / super_block->s_inodes_per_group;
	
	inode_local_index = ( - 1) % super_block->s_inodes_per_group;
	
	
	/* use what was implemented as static to implement a function that traverses one directory at a time */
	
	/* use the functions to print the file specified  */
	if(-1 == close(device_fd))
	{
		perror(NULL);
		return errno;
	}
	free(group_descriptor);
	free(super_block);
	free(curr_inode);
	return 0;
	
	(void)argc;
}
