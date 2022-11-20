#include <sys/types.h> /*ssize_*/
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define _XOPEN_SOURCE 500
#include <unistd.h> /* pread*/
#include <string.h>
#include <assert.h>
#include "parsing.h"


#define MIN(a, b) ((a) < (b)? (a) : (b))
#define BASE_OFFSET 1024
static unsigned int block_size = 0;
#define RAM_DEVICE "/dev/ram0"               /* the floppy disk device */
#define BLOCK_OFFSET(block) ((block)*block_size)

static int fd;
static struct ext2_group_desc group;
struct ext2_super_block super;
struct ext2_inode inode; 

static __u32 read_blocks(__u32 *BlockArr, int nBlocks, char **Buffer_ptr, __u32 size);
static void ReadInode(int fd, int inode_no,
                      const struct ext2_group_desc *group, struct ext2_inode *inode);

/*int                           fd;       */ /* the floppy disk file descriptor */
/*int                           inode_no; */ /* the inode number to read  */
/*const struct ext2_group_desc *group;    */ /* the block group to which the inode belongs */
/*struct ext2_inode            *inode;    */ /* where to put the inode */
static void ReadSuperblock(int fd, struct ext2_super_block *super);

static void ReadGroupDesc(int fd, struct ext2_super_block *super,
                         struct ext2_group_desc *group);

static unsigned int ReadDir(int fd, const struct ext2_inode *inode, 
                     const struct ext2_group_desc *group);
static unsigned int ReadFileContent(int fd, struct ext2_inode *inode,
                     const struct ext2_group_desc *group,
					 const char *file_path);
unsigned int Open(const char *device_path, const char *file_path)
{
     
	unsigned int ret = 0;
	if ((fd = open(device_path, O_RDONLY)) < 0)
	{
		perror(device_path);
		exit(1);
	}

    ReadSuperblock(fd, &super);

    ReadGroupDesc(fd, &super, &group);
        
    ReadInode(fd, 2, &group, &inode);
	

    ReadDir(fd, &inode, &group);
	
	ret = ReadFileContent(fd, &inode,&group, file_path);

	return ret;
}
static unsigned int ReadDir(int fd, const struct ext2_inode *inode, 
                     const struct ext2_group_desc *group)
{
	void *block;
	struct ext2_dir_entry_2 *entry;

	if (S_ISDIR(inode->i_mode)) 
	{
		unsigned int size = 0;
		if ((block = malloc(block_size)) == NULL) { /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		read(fd, block, block_size);                /* read block from disk*/

		entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory */

		while((size < inode->i_size) && entry->inode) 
		{
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len);
			file_name[entry->name_len] = 0;     /* append null character to the file name */
			printf("%10u %s\n", entry->inode, file_name);
			entry = (struct ext2_dir_entry_2 *)((char *)entry + entry->rec_len);
			size += entry->rec_len;
		}

		free(block);
	}
	(void)group;
	return entry->inode;
}

static unsigned int ReadFileContent(int fd, struct ext2_inode *inode,
                     const struct ext2_group_desc *group,
					 const char *file_path)
{
	printf("reading file content from: %s\n\n", file_path);
	void *block;
	struct ext2_dir_entry_2 *entry;

	unsigned int size = 0;

	if ((block = malloc(block_size)) == NULL) { /* allocate memory for the data block */
		fprintf(stderr, "Memory error\n");
		close(fd);
		exit(1);
	}

	lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
	read(fd, block, block_size);                /* read block from disk*/

	entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory */
			/* Notice that the list may be terminated with a NULL
				entry (entry->inode == NULL)*/
	while((size < inode->i_size) && entry->inode) 
	{
		char file_name[EXT2_NAME_LEN+1];
		memcpy(file_name, entry->name, entry->name_len);
		file_name[entry->name_len] = 0;     /* append null character to the file name */
		printf("%10u %s\n", entry->inode, file_name);
		
		if (0 == strcmp(file_name, file_path))
		{
			break; /*only becuase foor looks ugly*/
		}
		
		entry = (struct ext2_dir_entry_2 *)((char *)entry + entry->rec_len);
		size += entry->rec_len;
	}
	/*ReadInode(fd, entry->inode, group, inode);*/
	
	free(block);
	return entry->inode;
}
static void ReadSuperblock(int fd, struct ext2_super_block *super)
{
    lseek(fd, BASE_OFFSET, SEEK_SET);
    printf("after lseek\n");
    read(fd, super, sizeof(struct ext2_super_block ));
    printf("after read\n");
    /*close(fd);*/
    printf("magic number %d\n", super->s_magic);
    if (super->s_magic != 0xEF53)
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}
    block_size = 1024 << super->s_log_block_size;

    printf("Reading super-block from device " "/dev/ram0" ":\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n"
	       ,
	       super->s_inodes_count,  
	       super->s_blocks_count,
	       super->s_r_blocks_count,     /* reserved blocks count */
	       super->s_free_blocks_count,
	       super->s_free_inodes_count,
	       super->s_first_data_block,
	       block_size,
	       super->s_blocks_per_group,
	       super->s_inodes_per_group,
	       super->s_creator_os,
	       super->s_first_ino,          /* first non-reserved inode */
	       super->s_inode_size);
}

static void ReadGroupDesc(int fd, struct ext2_super_block *super,
                         struct ext2_group_desc *group)
{
	/* read group descriptor */

	lseek(fd,block_size, SEEK_SET);
	if(32 != read(fd, group, sizeof(struct ext2_group_desc)))
    {
        perror("read");
    }
    else
    {
        printf("Reading first group-descriptor from device " RAM_DEVICE ":\n"
            "Blocks bitmap block: %u\n"
            "Inodes bitmap block: %u\n"
            "Inodes table block : %u\n"
            "Free blocks count  : %u\n"
            "Free inodes count  : %u\n"
            "Directories count  : %u\n\n"
            ,
            group->bg_block_bitmap,
            group->bg_inode_bitmap,
            group->bg_inode_table,
            group->bg_free_blocks_count,
            group->bg_free_inodes_count,
            group->bg_used_dirs_count);    /* directories count */

    }
	/*close(fd);*/
}


static void ReadInode(int fd, int inode_no,
                      const struct ext2_group_desc *group, struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no -1)*super.s_inode_size, SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
	if (S_ISDIR(inode->i_mode))
	{

	printf("Reading root inode\n"
	       "File mode: %hu\n"
	       "Owner UID: %hu\n"
	       "Size     : %u bytes\n"
	       "Blocks   : %u\n"
	       ,
	       inode->i_mode,
	       inode->i_uid,
	       inode->i_size,
	       inode->i_blocks);
    size_t i = 0;
    for(i=0; i<EXT2_N_BLOCKS; i++)
		if (i < EXT2_NDIR_BLOCKS)         
			printf("Block %2lu : %u\n", i, inode->i_block[i]);
		else if (i == EXT2_IND_BLOCK)     
			printf("Single   : %u\n", inode->i_block[i]);
		else if (i == EXT2_DIND_BLOCK)    
			printf("Double   : %u\n", inode->i_block[i]);
		else if (i == EXT2_TIND_BLOCK)    
			printf("Triple   : %u\n", inode->i_block[i]);
	}
	if (S_ISREG(inode->i_mode))
	{
		puts("files");
	}
    
}

int Read(int file_inode, char* buffer, size_t count)
{
    __u32 size;
    struct ext2_inode inode;

    /* read file inode */
    ReadInode(fd, file_inode, &group, &inode);
	
    size = read_blocks(inode.i_block, EXT2_NDIR_BLOCKS, &buffer, MIN(count, inode.i_size));

    if (size > 0) /* if all direct blocks have been read, and we have indirect as well */
    {
        __u32* block = (__u32*)malloc(block_size);

        pread(fd, block, block_size, BLOCK_OFFSET(inode.i_block[EXT2_IND_BLOCK]));

        size = read_blocks(block, block_size/sizeof(__u32), &buffer, size);
    }
    return count;
}

static __u32 read_blocks(__u32 *BlockArr, int nBlocks, char **Buffer_ptr, __u32 size)
{
	int i, len; 

	for (i = 0; i < nBlocks; ++i)
	{
		len = MIN(size, block_size);
		pread(fd, *Buffer_ptr, len, BLOCK_OFFSET(BlockArr[i]));

		*Buffer_ptr += len;

		if ((size -= len) <= 0)
		{
			break;
		}		
	}

	return size;
}
