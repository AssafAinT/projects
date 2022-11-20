/*****************************************************
* FSA                                               *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 27.06.2022                                  *
*****************************************************/



/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fsa.h"




void SuggestedSizeTest(void);
void InitTest(void);
void AllocTest(void);
void CountFreeBlockTest(void);
void FreeTest(void);


int main(void)
{
	SuggestedSizeTest();
	InitTest();
	AllocTest();
	CountFreeBlockTest();
	FreeTest();
	return (0);
}

void SuggestedSizeTest(void)
{
	size_t num_blocks = 32;
	size_t size_of_blocks = 18;
	size_t pool_size = 0;
	
	size_t num_blocks2 = 1;
	
	pool_size = FsaSuggestSize(num_blocks, size_of_blocks);
	
	assert(776 == pool_size);
	
	assert(32 == FsaSuggestSize(num_blocks2, size_of_blocks));

}

void InitTest(void)
{
	fsa_ty *fixed_allocator = NULL;
	void *pool = NULL;
	size_t num_blocks = 5;
	size_t size_of_blocks = 12;
	size_t pool_size = 0;
	
	pool_size = FsaSuggestSize(num_blocks, size_of_blocks);
	
	pool = malloc(pool_size);
	
	fixed_allocator = FsaInit(pool, pool_size, size_of_blocks);
	
	assert((void *)fixed_allocator == pool );
	
	printf("-------------------------init test successed!!!-----------------\n");
	free(pool);
}


void AllocTest(void)
{
	fsa_ty *fixed_allocator = NULL;
	void *data_base = NULL;
	size_t num_blocks = 32;
	size_t size_of_blocks = 18;
	size_t pool_size = 0;
	void *runner = NULL;
	void *runner2 = NULL;
	void *copy = NULL;
	int data = 12;
	
	printf("\v-------------------------alloc test---------------------------\n");
	
	pool_size = FsaSuggestSize(num_blocks, size_of_blocks);
	
	data_base = malloc(pool_size);
	printf("%p malloc\n", (void *)data_base);
	copy = data_base;
	
	
	runner  = data_base;
	
	fixed_allocator = FsaInit((++*(char **)&copy), pool_size, size_of_blocks);
	assert(31 == FsaCountFreeBlock(fixed_allocator));
	printf("%p fixed allocator address\n", (void *)fixed_allocator);
	runner = FsaAlloc(fixed_allocator);
	printf("%p runner address\n", (void *)runner);
	runner = FsaAlloc(fixed_allocator);
	printf("%p runner address\n", (void *)runner);
	runner2 = FsaAlloc(fixed_allocator);
	printf("%p runner address\n", (void *)runner2); 
	assert(28 == FsaCountFreeBlock(fixed_allocator));
	
	*(int *)runner = data;
	printf("diffrence between addresses: %ld\n", (size_t)runner2 - (size_t)runner);
	printf("%d\n", *(int *)runner);
	
	free(data_base);
	
}



void CountFreeBlockTest(void)
{
	fsa_ty *fixed_allocator = NULL;
	void *data_base = NULL;
	size_t num_blocks = 32;
	size_t size_of_blocks = 18;
	size_t pool_size = 0;
	void *runner = NULL;
	void *runner2 = NULL;
	void *runner3 = NULL;
	int data = 12;
	
	pool_size = FsaSuggestSize(num_blocks, size_of_blocks);
	printf("-------------------------count free block test-----------------\n");
	
	data_base = malloc(pool_size);
	
	runner  = data_base;
	
	fixed_allocator = FsaInit(data_base, pool_size, size_of_blocks);
	assert(32 == FsaCountFreeBlock(fixed_allocator));
	runner = FsaAlloc(fixed_allocator);
	runner = FsaAlloc(fixed_allocator);
	runner2 = FsaAlloc(fixed_allocator);
	
	*(int *)runner = data;
	*(int *)runner2 = data;
	assert(29 == FsaCountFreeBlock(fixed_allocator));
	runner3 = FsaAlloc(fixed_allocator);
	*(int *)runner3 = data;
	assert(28 == FsaCountFreeBlock(fixed_allocator));
	free(data_base);
	
	printf("\v-----------------------count free block successed-------------\n");

}



void FreeTest(void)
{
	fsa_ty *fixed_allocator = NULL;
	size_t counter = 0;
	void *data_base = NULL;
	size_t num_blocks = 32;
	size_t size_of_blocks = 18;
	size_t pool_size = 0;
	void *runner = NULL;
	int data = 12;
	
	pool_size = FsaSuggestSize(num_blocks, size_of_blocks);
	printf("-------------------------free block test-----------------------\n");
	
	data_base = malloc(pool_size);
	
	runner  = data_base;
	
	fixed_allocator = FsaInit(data_base, pool_size, size_of_blocks);
	assert(32 == FsaCountFreeBlock(fixed_allocator));
	runner = FsaAlloc(fixed_allocator);
	assert(31 == FsaCountFreeBlock(fixed_allocator));
	*(int *)runner = data;
	printf("%d\n", *(int *)runner);
	
	FsaFree(fixed_allocator, runner);
	printf("first place to put data: %d\n", *(int *)runner);
	assert(32 == FsaCountFreeBlock(fixed_allocator));
	
	for ( ; counter < 32; ++counter)
	{
		runner = FsaAlloc(fixed_allocator);
	}
	assert(0 == FsaCountFreeBlock(fixed_allocator));
	
	FsaFree(fixed_allocator, runner);
	printf("after free: %lx\n", (*(size_t *)runner));
	printf("%ld free blocks\n", FsaCountFreeBlock(fixed_allocator));
	
	free(data_base);
	
}
