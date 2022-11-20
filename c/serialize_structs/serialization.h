#ifndef __ILRD_OL127_128_SERIALIZATION_H__
#define __ILRD_OL127_128_SERIALIZATION_H__

#include <stddef.h> 
int Serialization(const void *src, size_t bytes_to_copy, FILE *dest);
int DeSerialization(void *dest,size_t bytes_to_copy, FILE *src);
#endif
