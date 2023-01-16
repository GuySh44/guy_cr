#include <fcntl.h> /* open close */
#include <unistd.h> /* read lseek write */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <errno.h> /* perror */
#include <linux/types.h> /* __le __u */
#include <string.h> /* memmove strtok strdup strlen */
#include <assert.h>

/*
Reviewer Yarin
*/

#include "ext2.h"


#define SUPER_BLOCK_SIZE	(1024)
#define SUPER_BLOCK_OFFSET	(1024)
#define KILOBYTE	(1024)
#define GROUP_DESCRIPTOR_SIZE	(32)
#define EXT2_NAME_LEN (255)
#define	EXT2_NDIR_BLOCKS	(12)
#define RECORD_LEN_OFFSET (4)
#define	EXT2_IND_BLOCK	(EXT2_NDIR_BLOCKS)
#define	EXT2_DIND_BLOCK	(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK	(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS	(EXT2_TIND_BLOCK + 1)
#define EXT2_ROOT_INO (2)
#define BLOCK_OFFSET(block) ((block)*block_size_bytes)
#define I_MODE_SIZE (2)


struct ext2_dir_entry {
	__u32	inode;			/* Inode number */
	__u16	rec_len;		/* Directory entry length */
	__u16	name_len;		/* Name length */
	char	name[EXT2_NAME_LEN];	/* File name */
};

/*
   	 * The new version of the directory entry.  Since EXT2 structures are
   	 * stored in intel byte order, and the name_len field could never be
   	 * bigger than 255 chars, it's safe to reclaim the extra byte for the
   	 * file_type field.
   	 */
struct ext2_dir_entry_2 {
	__u32	inode;			/* Inode number */
	__u16	rec_len;		/* Directory entry length */
	__u8	name_len;		/* Name length */
	__u8	file_type;
	char	name[EXT2_NAME_LEN];	/* File name */
};	

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
	__u32	s_inodes_count;		/* Inodes count */
	__u32	s_blocks_count;		/* Blocks count */
	__u32	s_r_blocks_count;	/* Reserved blocks count */
	__u32	s_free_blocks_count;	/* Free blocks count */
	__u32	s_free_inodes_count;	/* Free inodes count */
	__u32	s_first_data_block;	/* First Data Block */
	__u32	s_log_block_size;	/* Block size */
	__s32	s_log_frag_size;	/* Fragment size */
	__u32	s_blocks_per_group;	/* # Blocks per group */
	__u32	s_frags_per_group;	/* # Fragments per group */
	__u32	s_inodes_per_group;	/* # Inodes per group */
	__u32	s_mtime;		/* Mount time */
	__u32	s_wtime;		/* Write time */
	__u16	s_mnt_count;		/* Mount count */
	__s16	s_max_mnt_count;	/* Maximal mount count */
	__u16	s_magic;		/* Magic signature */
	__u16	s_state;		/* File system state */
	__u16	s_errors;		/* Behaviour when detecting errors */
	__u16	s_minor_rev_level; 	/* minor revision level */
	__u32	s_lastcheck;		/* time of last check */
	__u32	s_checkinterval;	/* max. time between checks */
	__u32	s_creator_os;		/* OS */
	__u32	s_rev_level;		/* Revision level */
	__u16	s_def_resuid;		/* Default uid for reserved blocks */
	__u16	s_def_resgid;		/* Default gid for reserved blocks */
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
	__u32	s_first_ino; 		/* First non-reserved inode */
	__u16   s_inode_size; 		/* size of inode structure */
	__u16	s_block_group_nr; 	/* block group # of this superblock */
	__u32	s_feature_compat; 	/* compatible feature set */
	__u32	s_feature_incompat; 	/* incompatible feature set */
	__u32	s_feature_ro_compat; 	/* readonly-compatible feature set */
	__u8	s_uuid[16];		/* 128-bit uuid for volume */
	char	s_volume_name[16]; 	/* volume name */
	char	s_last_mounted[64]; 	/* directory where last mounted */
	__u32	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	__u8	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
	__u8	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
	__u16	s_padding1;
	__u32	s_reserved[204];	/* Padding to the end of the block */
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


/* Calculate Group Inode Table location */

size_t CalculateGroupTable(sb *super_block, gd *group_descriptor, size_t inode_num)
{
	
	size_t inode_block_index = 0;
	size_t block_size_bytes = 0;

	assert(super_block);
	assert(group_descriptor);
	
	block_size_bytes = (KILOBYTE << super_block->s_log_block_size);  /* from int (2 in my case) to the "real" block size */
	
	inode_block_index = (inode_num - 1) / super_block->s_inodes_per_group; /* inode tables start from inode 1 and not 0 hence the "- 1", calculate the block group */
	
	if(inode_block_index < 2 || inode_block_index % 3 == 0 || inode_block_index % 5 == 0 || inode_block_index % 7 == 0) /* GroupDescriptor exists */
	{
		return (inode_block_index * super_block->s_blocks_per_group * block_size_bytes + group_descriptor->bg_inode_table * block_size_bytes);
	}
	return (inode_block_index * super_block->s_blocks_per_group * block_size_bytes + 2 * block_size_bytes); /* GroupDescriptor doesnt exist */
}

/* Parse file names and iterate through the inodes using the EXT2 structure */

long GetFileInode(int device_fd, sb *super_block, gd *group_descriptor, char *pathname)
{
	char *token = NULL;
	gd *new_group_descriptor = NULL;
	size_t inode_num = 0;
	size_t last_inode_num = EXT2_ROOT_INO;
	
	assert(super_block);
	assert(group_descriptor);
	assert(pathname);
	
	token = strtok(pathname, "/"); /* parse first token which should be equal to first directory name */
	
	while(NULL != token)
	{	
		inode_num = UseFile(device_fd, super_block, group_descriptor, last_inode_num, SpiderDir, token);		/* get inode_num of token using from the directory entries */
		
		token = strtok(NULL, "/");		/* parse next directory */
		
		last_inode_num = inode_num;
	}
	
	free(new_group_descriptor);
	return inode_num;
}

/* copy from offset in ramdisk to buffer */

void CopyToBuffer(int fd, size_t offset, size_t block_size, void *buffer)
{
	assert(buffer);
	
	if(-1 == lseek(fd, offset, SEEK_SET))
	{
		perror(NULL);
	}
	if(-1 == read(fd, buffer, block_size))
	{
		perror(NULL);
	}
}

/* Do actions on temporary buffer holding data of EXT2 files */

long UseFile(int device_fd, sb *super_block, gd *group_descriptor, size_t inode_num, block_func action_func, void *arg)
{
	size_t block_size_bytes;
	void *block_buffer = NULL;
	inode *file_inode = NULL;
	size_t bytes_left;
	size_t bytes_read = 0;
	size_t i = 0;
	
	assert(super_block);
	assert(group_descriptor);
	
	file_inode = (inode*)malloc(super_block->s_inode_size);
	
	if(NULL == file_inode)
	{
		return 1;
	}
	
	LoadInode(device_fd, super_block, group_descriptor, file_inode, inode_num);
	
	assert(file_inode);
	
	block_size_bytes = KILOBYTE << super_block->s_log_block_size;
	bytes_left = file_inode->i_size;
	
	block_buffer = malloc(block_size_bytes);
	if(NULL == block_buffer)
	{
	
		return 1;
	}
	
	for(; i < 12 && bytes_left > 0 ; ++i, bytes_left -= bytes_read)		/* first 12 direct block indexes */
	{
		bytes_read = ((bytes_left / block_size_bytes) > 0) * block_size_bytes + ((bytes_left / block_size_bytes) == 0) * (bytes_left % block_size_bytes);		/* should we read entire blocks or only a part of */
		
		CopyToBuffer(device_fd, BLOCK_OFFSET(file_inode->i_block[i]), bytes_read, block_buffer);		/* copy inode file content, up to a block */
		
		if (PrintBlock == action_func)			/* print the file content block option */
		{
			action_func(block_buffer, bytes_read);
		}
		
		if (SpiderDir == action_func)			/* parse the file content holding dir entrys */
		{
			assert(arg);
			free(file_inode);
			return action_func(block_buffer, bytes_read, arg);
		}
	}
	free(file_inode);
	free(block_buffer);
	return 0;
}


void LoadInode(int device_fd, sb *super_block, gd* group_descriptor, inode *curr_inode, size_t inode_num)
{
	size_t inode_local_index = 0;
	
	assert(super_block);
	assert(group_descriptor);
	
	inode_local_index = (inode_num - 1) % super_block->s_inodes_per_group;
	
	CopyToBuffer(device_fd, CalculateGroupTable(super_block, group_descriptor, inode_num) + inode_local_index * super_block->s_inode_size , super_block->s_inode_size, curr_inode);
	
}

static void ChmodSetSignature(unsigned short *signature, char *args)
{
	size_t i = 0;
	size_t args_len = strlen(args);
	
	assert(signature);
	
	for(; i < args_len; ++i)
	{
		*signature += (int)args[i] - '0';
		*signature <<= 3;
	}
}

static int ChmodArgsCheck(char *args)
{
	size_t i = 0;
	size_t args_len;
	assert(args);
	
	args_len = strlen(args);
	
	if(args_len < 3 || args_len > 4)
	{
		return 2;
	}
	
	for(; i < args_len; ++i)
	{
		if(args[i] > '7' || args[i] < '0')
		{
			return 1;
		}
	}
	return 0;
}

/* our numeric chmod implementation */

long ChmodInode(int device_fd, sb *super_block, gd* group_descriptor, size_t inode_num, char *args)
{
	size_t inode_local_index = 0;
	int status = 0;
	unsigned short signature;
	unsigned short curr_imode;
	
	assert(super_block);
	assert(group_descriptor);
	assert(args);
	
	status = ChmodArgsCheck(args);
	if(1 == status)
	{
		printf("invalid mode: %s\n", args);
		return 1;
	}
	
	inode_local_index = (inode_num - 1) % super_block->s_inodes_per_group;

	CopyToBuffer(device_fd, CalculateGroupTable(super_block, group_descriptor, inode_num) + inode_local_index * super_block->s_inode_size, I_MODE_SIZE, &curr_imode);
	
	curr_imode &= 0xf000;
	
	ChmodSetSignature(&signature, args);
	
	signature += curr_imode;
	
	/*get the upper bits so signature can be safelly written on disk
	probably reading i_mode first and doin && on signature and current i_mode*/
	/* set indicator to relevant inode */
	if(-1 == lseek(device_fd, CalculateGroupTable(super_block, group_descriptor, inode_num) + inode_local_index * super_block->s_inode_size, SEEK_SET))
	{
		perror(NULL);
	}
	
	if(-1 == write(device_fd, &signature, I_MODE_SIZE))
	{
		perror(NULL);
	}
	
	return 0;
}

/* find name of inode inside of directory and return its number */

long SpiderDir(void *buffer, size_t size, char *name)
{
	size_t sum_record = 0;
	dir_entry2 *entry = NULL;
	unsigned int found_inode = 0;
	unsigned short curr_record = 0;
	
	assert(buffer);
	assert(name);
	
	while (sum_record != size)		/* as long as we didnt parse all the dir entries */
	{
		curr_record = *((unsigned short*)((char*)buffer + RECORD_LEN_OFFSET + sum_record));
		
		entry = (dir_entry2*)malloc(curr_record + 1);
		*((char*)entry + curr_record) = '\0';
		
		if(NULL == entry)
		{
			free(buffer);
			return -1;
		}
		
		memmove(entry, ((char*)buffer + sum_record), curr_record);
		
		if(0 == strcmp(entry->name, name))		/* if needed dir entry was found return the inode number */
		{
			found_inode = entry->inode;
			free(entry);
			free(buffer);
			return found_inode;
		}
		
		free(entry);
		
		sum_record += curr_record; 
	}
	free(buffer);
	return 0;
}


/* print buffer in hex */

long PrintBlock(void *buffer, size_t size)
{
	size_t i = 0;
	
	assert(buffer);
	
	for (; i < size; ++i)
	{
		printf("%02x ", *((unsigned char*)buffer + i));
    	if ((i + 1) % 16 == 0) 
    	{
    		printf("\n");
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{
	extern char* strdup(const char*); 
	
	char *device_name = argv[1];
	char *file_path = argv[2];
	char *path_dup = NULL;
	size_t gd_offset = 0;
	size_t block_size_bytes = 0;
	size_t inode_num = 0;
	int device_fd = 0;
	sb *super_block = NULL;
	gd *group_descriptor = NULL;
	inode *curr_inode = NULL;
	
	assert(device_name);
	assert(file_path);
	
	file_path = strstr(file_path, "ramdisk/");  /* set file path to start from '/' like root */
	file_path += strlen("ramdisk");
	/* open the "device" file ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	device_fd = open(device_name, O_RDONLY);
	
	if(device_fd == -1)
	{
		perror(NULL);
		return errno;
	}
	
	/* create super block struct and copy right content from HDD ~~~~~~*/
	super_block = (sb*)malloc(SUPER_BLOCK_SIZE);
	
	if(NULL == super_block)
	{
		return 1;
	}
	
	CopyToBuffer(device_fd, SUPER_BLOCK_OFFSET, SUPER_BLOCK_SIZE, super_block);

	PrintSuperBlock(super_block);
	
	/* create group descriptor struct and copy right content from FS ~*/
	
	group_descriptor = (gd*)malloc(GROUP_DESCRIPTOR_SIZE);
	
	if(NULL == group_descriptor)
	{
		return 1;
	}
	
	block_size_bytes = KILOBYTE << super_block->s_log_block_size;
	
	gd_offset = (KILOBYTE * (super_block->s_log_block_size == 0) ) + (block_size_bytes);
	
	CopyToBuffer(device_fd, gd_offset, GROUP_DESCRIPTOR_SIZE, group_descriptor);
	
	PrintGroupDescriptor(group_descriptor);
	
	curr_inode = (inode*)malloc(super_block->s_inode_size);
	
	if(NULL == curr_inode)
	{
		return 1;
	}
	
	/* parse the second inode which is the root directory inode in block 0 inode table */
	
	CopyToBuffer(device_fd, BLOCK_OFFSET(group_descriptor->bg_inode_table) + (EXT2_ROOT_INO - 1) * super_block->s_inode_size, super_block->s_inode_size, curr_inode);
		
	/* send path duplicate to path parsing function because strtok may change original string */
	
	path_dup = strdup(file_path);
	
	if(NULL == path_dup)
	{
		return 1;
	}
	
	/* Find the file in the path and print its content, can return the inode number*/
	
	inode_num = GetFileInode(device_fd, super_block, group_descriptor, path_dup);
	
	
	/*
	UseFile(device_fd, super_block, group_descriptor, inode_num,  PrintBlock, NULL);
	*/
	
	if(argc == 5 && !strcmp(argv[3], "chmod"))
	{
		ChmodInode(device_fd, super_block, group_descriptor, inode_num, argv[4]);
	}
	
	
	
	/* clean everything up  */
	if(-1 == close(device_fd))
	{
		perror(NULL);
		return errno;
	}
	
	free(group_descriptor);
	free(super_block);
	free(curr_inode);
	free(path_dup);
	
	return 0;
	
	(void)argc;
}

void PrintSuperBlock(const sb *super_block)
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


void PrintDirEntry(const dir_entry2 *entry)
{
	printf("Directory Entry:\n\
inode number:\t%u\n\
record length:\t%u\n\
name length:\t%u\n\
file type:\t%u\n\
name:\t%s\n\n",\
entry->inode,\
entry->rec_len,\
entry->name_len,\
entry->file_type,\
entry->name);
}

