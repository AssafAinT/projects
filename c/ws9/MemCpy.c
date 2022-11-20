#include <stddef.h> /* size_t */
#include "memoryfuncs.h" /*header file with all self-implemented mem functions */





void *MemCpy(void *dest, const void *src, size_t n)
{
	unsigned char *copy_dest = dest;
	const unsigned char *copy_src = src;
	
	
	while((!IsAlign((size_t)copy_dest)) && (0 != n))
	{
		
		*copy_dest = *copy_src;
		++copy_dest;
		++copy_src;
		--n;

	}
	
	
	while (n >= sizeof(size_t))
	{
		(*(size_t *)copy_dest) = (*(size_t *)src);
		copy_dest += WORD ;
		copy_src += WORD;
		n -= sizeof(size_t);
	}
	

	while (0 != n)
	{
		*copy_dest = *copy_src;
		++copy_dest; 
		++copy_src;
		--n;
	} 
	
	return (dest);
}



