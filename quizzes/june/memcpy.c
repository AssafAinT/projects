#include <stdio.h> /* size_t , printf */
#include <assert.h> /*assert */
#define WORD  sizeof(size_t)
#define ALIGN sizeof(size_t)

void *Memcpy(void *dest, const void *src, size_t bytes_to_cpy);
static int IsAlign(size_t add);
int main(void)
{
	char string_destination[100]="abcdlolololololololololololo";
	const char source_string[50]="bleep for bleep and life is amazing thank you all";

	Memcpy(string_destination, source_string, 2);
	puts(string_destination);
	Memcpy(string_destination, source_string, 19);
	Memcpy(string_destination, source_string, 25);
	puts(string_destination);
	puts(string_destination);
	return (0);
}

void *Memcpy(void *dest, const void *src, size_t bytes_to_cpy)
{
	unsigned char *dest_runner = NULL;
	const unsigned char *src_runner = NULL;
	assert(NULL != dest);
	assert(NULL != src);
	
	dest_runner = dest;
	src_runner = src;
	
	for (; (!IsAlign((size_t)dest_runner))&&
		   (0 != bytes_to_cpy);
		   ++dest_runner,
		   ++src_runner,
		   --bytes_to_cpy)
   {
   		*dest_runner = *src_runner;
   }
   
   for (; WORD <= bytes_to_cpy;
   		  ++dest_runner,
   		  ++src_runner,
   		  bytes_to_cpy -= WORD)
   {
   		(*(size_t *)dest_runner) = (*(size_t *)src_runner);
   }
   
   for (; 0 != bytes_to_cpy;
   		  ++dest_runner,
   		  ++src_runner,
   		  --bytes_to_cpy)
   {
   		*dest_runner = *src_runner;
   }
   return (dest);
}

static int IsAlign(size_t add)
{
	return (!!(add & ALIGN));
}
