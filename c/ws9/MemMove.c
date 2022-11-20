#include <stddef.h> /* size_t */
#include "memoryfuncs.h" /*header file with all self-implemented mem functions */

void *MemMove(void *dest, const void *src, size_t n)
{
	unsigned char *char_dest = dest;
	unsigned char *char_src = (unsigned char *) src;
	
	size_t address_diff = (size_t *)src - (size_t *)dest;
	
	if ((dest <= src) && (n < address_diff))
	{
		dest = MemCpy(dest, src, n);
		n = 0;
	}
	
	char_dest = char_dest + n -1 ;
	char_src = char_src + n -1;
	
	while (0 != n)
	{
		*char_dest = *char_src;
		--char_dest;
		--char_src;
		--n;
	}

	return (dest);
}


