#include <stddef.h> /* size_t */

#include "memoryfuncs.h" /*header file with all self-implemented mem functions */




void *MemSet(void *source, int c, size_t n)
{
	unsigned char *copy_dest = source;
	size_t chunk = MakeBuffer((unsigned char)c);
	
	
	while((!IsAlign((size_t)copy_dest)) && (0 != n))
	{
		*copy_dest = (unsigned char)c;
		++copy_dest; 
		--n;
	}
	
	while(n >= sizeof(size_t))
	{
		(*(size_t *)copy_dest) = chunk;
		copy_dest += WORD;
		n -= WORD;
	}
	
	while(0 != n)
	{
		*copy_dest = (unsigned char)c;
		++copy_dest; 
		--n;
	}
	
	return source;
} 

size_t MakeBuffer(unsigned char value)
{
	size_t sizeof_t = 0;
	size_t i = 0;
	for ( ; i < WORD; ++i)
	{
    	sizeof_t <<= 8;
		sizeof_t = sizeof_t | value;
    }
	return (sizeof_t);
}

int IsAlign(size_t address)
{
	return !!(address % ALIGN_TO);
}

