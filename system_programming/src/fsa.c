/*****************************************************
* FSA                                               *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 27.06.2022                                  *
*****************************************************/



/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */

#include "fsa.h"
/********************************file Const************************************/
static const size_t meta_data_size = sizeof(fsa_ty *);
static const size_t begin_of_data = meta_data_size;
static const size_t word_size = sizeof(void *);

static const int last_block = 1;
static const size_t sizet_size = sizeof(size_t);
/********************************function declartions**************************/

static size_t AlignData(size_t data);

static void InitMetaData(char *runner, size_t pool_size,
                       size_t block_size, size_t offset);

static void PSwap(void **ret_ptr, fsa_ty *fsa);

static char *GetAsCharPointer(fsa_ty *fsa);

static size_t GetAsSizeT(void *data);

static fsa_ty *GetAsFsaTyPtr(size_t data);

static size_t GetNextFree(fsa_ty *fsa);

static void SwapFree(fsa_ty *fsa, void *ptr);

static size_t *GetAddBlock(char *runner);

/********************************struct definition*****************************/
struct fsa
{
    size_t next_free;
};

/********************************function declarations*************************/
fsa_ty *FsaInit(void *memory, size_t pool_size, size_t block_size)
{
	fsa_ty *ret = memory;
	size_t decrease_pool_size = meta_data_size;
	assert(NULL != memory);
		
	ret =GetAsFsaTyPtr(AlignData(GetAsSizeT(memory)));

	/* decreasing pool size in case there was a padding */ 
	decrease_pool_size += GetAsSizeT(ret) - GetAsSizeT(memory);
	
	pool_size -= decrease_pool_size;	
	ret->next_free = begin_of_data;

	InitMetaData(GetAsCharPointer(ret), pool_size,
	             AlignData(block_size), begin_of_data);
	return (ret);
}

void *FsaAlloc(fsa_ty *fsa)
{
	void *ret_ptr = NULL;
	assert(NULL != fsa);
	
	
	if (0xDEADBEEF == GetNextFree(fsa))
	{
		return NULL;
	}
	PSwap(&ret_ptr, fsa);
	return (ret_ptr);
}

void FsaFree(fsa_ty *fsa, void *ptr)
{
	assert(NULL != fsa);
	
	SwapFree(fsa, ptr);
}

size_t FsaCountFreeBlock(const fsa_ty *fsa)
{
	size_t counter = 0;
	size_t runner = 0;
	assert(NULL != fsa);
	runner = GetNextFree((fsa_ty *)fsa);
	
	for ( ; 0xDEADBEEF != runner ; ++counter )
	{
		runner = *(GetAddBlock((GetAsCharPointer((fsa_ty *)fsa) + runner)));
	}
	return counter;
}

size_t FsaSuggestSize(size_t num_blocks, size_t block_size)
{
	size_t pool_size = 0;
	assert(0 != num_blocks);
	assert(0 != block_size);
	
	block_size = AlignData(block_size);
	pool_size = ((num_blocks * block_size) + meta_data_size);
	
	return (pool_size);
}

/********************************static function*******************************/
static void InitMetaData(char *begin, size_t pool_size,
                       size_t block_size, size_t offset)
{
	size_t num_of_blocks = 0;
	
	assert(NULL != begin);
	assert(0 != pool_size);
	assert(0 != block_size);
	
	num_of_blocks = (pool_size) / block_size;
	
	for ( ; last_block != num_of_blocks; offset += block_size, --num_of_blocks)
	{
		*(GetAddBlock(begin + offset)) = offset + block_size;
	}
	*(GetAddBlock(begin + offset)) = 0xDEADBEEF;
}

static size_t AlignData(size_t data)
{

	return (((data)+ (word_size -1)) & (~(word_size -1)));
}

static void PSwap(void **ret_ptr, fsa_ty *fsa)
{
	*ret_ptr = (GetAsCharPointer(fsa) + GetNextFree(fsa));
	fsa->next_free = *(GetAddBlock(GetAsCharPointer(*ret_ptr)));	
}

static char *GetAsCharPointer(fsa_ty *fsa)
{
	assert(NULL != fsa);
	return ((char *)fsa);
}

static size_t GetAsSizeT(void *data)
{
	assert(NULL != data);
	
	return((size_t)data);
}

static fsa_ty *GetAsFsaTyPtr(size_t data)
{
	return((fsa_ty*)(data));
}

static size_t GetNextFree(fsa_ty *fsa)
{
	assert(NULL != fsa);
	
	return (fsa->next_free);
}

static void SwapFree(fsa_ty *fsa, void *ptr)
{
	
	*(GetAddBlock(ptr)) = GetNextFree(fsa);
	fsa->next_free = GetAsSizeT(ptr) - GetAsSizeT(fsa);
}

static size_t *GetAddBlock(char *runner)
{
	assert(NULL != runner);
	
	return((size_t *)runner);
}
