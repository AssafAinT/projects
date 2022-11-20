#include <stdio.h>
#include <string.h> /*memcpy, memset */
#include <assert.h> /* assert */
#include "serialization.h"

#define FAIL_TO_READ_ALL -1 

int Serialization(const void *src,size_t bytes_to_copy, FILE *dest)
{
	size_t fwrite_status = 0;
	int ret_stat = 0;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	fwrite_status = fwrite(src, bytes_to_copy, 1, dest);
	
	if (bytes_to_copy > fwrite_status || 0 == fwrite_status)
	{
		ret_stat = FAIL_TO_READ_ALL;
	}
	
	
	return (ret_stat);
}

int DeSerialization(void *dest,size_t bytes_to_copy, FILE *src)
{
	size_t fread_status = 0;
	int ret_stat = 0;
	assert(NULL != src);
	assert(NULL != dest);
	
	fread_status = fread(dest, bytes_to_copy, 1, src);
	
	if (bytes_to_copy > fread_status || 0 == fread_status)
	{
		ret_stat = FAIL_TO_READ_ALL;
	}
	return (ret_stat);
}
