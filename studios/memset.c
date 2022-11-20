#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE (sizeof(void *))

static const size_t align_to_word = WORD_SIZE;

static int IsAligned(size_t addr)
{
    return (addr % align_to_word);
}
void *CopyByChunk(void *src, int c, size_t nbytes);
void *CopyByBytes(void *src, int c, size_t nbytes);
size_t WordBuffer(int c);
void TestMemSet(void);
void *Memset(void *source, int c, size_t nbytes)
{
    size_t bytes_un_aligned = IsAligned((size_t)(source));
    void *head = source;

    source = CopyByBytes(source, c, bytes_un_aligned);
    nbytes -= bytes_un_aligned;
    source = CopyByChunk(source,  c, nbytes);

    nbytes %= WORD_SIZE;

    CopyByBytes(source, c, nbytes);
    return head;
}

int main()
{
//	void *p = malloc(10);
//	++*(char**)&p;
	
	TestMemSet();
//	TestCopy();
//	TestMemMov();

	return (0);
}

void TestMemSet(void)
{
	char str[] = "012345678910123456789201234567893012345678940";
	char *p = malloc(10);
	
	Memset(str, 'A', 8);
	printf("%s\n", str);
	
	++*(int *)p;
	
	Memset(p, 'd', 1);
	printf("%d\n", *p);
	
	--*(int *)p;
	printf("%d\n", *p);
	free(p);
}

size_t WordBuffer(int c)
{
    size_t word = 0;
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {
        word |= c;
        word <<= WORD_SIZE;
    }

    return word;
}
void *CopyByChunk(void *src, int c, size_t nbytes)
{
    size_t *as_size_t = (size_t *)src;
    size_t buffer = WordBuffer(c);

    while (nbytes >= WORD_SIZE)
    {
        *as_size_t = buffer;
        ++as_size_t;
        nbytes -= WORD_SIZE;
    }

    return (void *)as_size_t;
}

void *CopyByBytes(void *src, int c, size_t nbytes)
{
    char *as_char = (char *)src;

    while (!IsAligned((size_t)(src)) && nbytes != 0)
    {
        *as_char = c;
        ++as_char;
    }

    return (void *)as_char;
}