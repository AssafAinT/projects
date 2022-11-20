#ifndef __ILRD_RD127_128_PARSING_H__
#define __ILRD_RD127_128_PARSING_H__

#include <stddef.h> /*size_t*/
#include <ext2fs/ext2_fs.h> /*ext2 api*/

unsigned int Open(const char *device_path, const char *file_path);

int Read(int inode, char *buffer, size_t count);

#endif /* __ILRD_RD127_128_PARSING_H__ */