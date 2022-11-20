/*****************************************************
* VSA                                               *
* Assaf Ainhoren                                    *
* Reviewer: Mark Galperin                           *
* date: 27.06.2022                                  *
*****************************************************/



/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /*memcpy */

#include "vsa.h"


#define WORD_SIZE sizeof(void *)
#define VSA_SIZE sizeof(vsa_ty )
#define AS_SIZE_T(x) *(size_t *)(x)
#define NO_MORE_SPACE 0
#define NUM_OF_BEGIN_STRUCT 2
#define GET_BLOCK_STATUS(x) (((vsa_ty *)x)->block_status)
#define MAGIC_NUMBER 0xDEADBEEF
#define GET_ABS_VAL(val) ((val) > 0 ? (val) : (-1) * (val))
#define GET_MAGIC(BLOCK) ((vsa_ty *)BLOCK)->magic_number

static const size_t word_size = sizeof(void *);

struct vsa
{
    long block_status;
#ifndef NDEBUG
    size_t magic_number;
#endif
};


static size_t AlignData(size_t data);

static void DeFragmentSpaces(vsa_ty *pool);

static void InitMetaData(vsa_ty *pool, size_t pool_size);

static void *AdvanceRunnerByBlock(vsa_ty *runner);

static char *UpdateRunnerStatus(char *runner, size_t aligned_block_size);

static size_t AlignPoolSize(size_t pool_size, size_t bytes_to_align);

static size_t GetAsSizeT(void *data);

static long GetBlockStatus(vsa_ty *vsa);
/********************************function definition***************************/
vsa_ty *VsaInit(void *memory, size_t pool_size)
{
	vsa_ty *ret = memory;
	
	size_t decrease_pool_size = (NUM_OF_BEGIN_STRUCT * VSA_SIZE);
	assert(NULL != memory);
	
	ret = (vsa_ty *)AlignData(GetAsSizeT(memory));
	decrease_pool_size += GetAsSizeT(ret) - GetAsSizeT(memory);
	
	InitMetaData(ret, AlignPoolSize(pool_size, decrease_pool_size));
	return (ret);
}

void *VsaAlloc(vsa_ty *pool, size_t block_size)
{
	char *runner = (char *)pool;
	long aligned_block_size = 0;
	assert(NULL != pool);
	
	aligned_block_size = AlignData(block_size);
	
	while ((((vsa_ty*)runner)->block_status) < aligned_block_size &&
	       NO_MORE_SPACE != ((vsa_ty *)runner)->block_status)
	{
		if (((vsa_ty *)runner)->block_status > 0)
		{
			DeFragmentSpaces((vsa_ty *)runner);
			if(((vsa_ty *)runner)->block_status < aligned_block_size)
			{
				/* if also after defrag have found space advance runner */
				runner += VSA_SIZE + (((vsa_ty *)runner)->block_status);	
			}
		}
		else
		{
		  /* if the block status is negative advance the runner to next block*/
			runner += VSA_SIZE + GET_ABS_VAL(((vsa_ty *)runner)->block_status);
		}
	}
	
	return ((UpdateRunnerStatus(runner, aligned_block_size)));
}

void VsaFree(void *ptr)
{
	vsa_ty *vsa_ptr = ((vsa_ty *)ptr);

	assert(NULL != ptr);
	/* Get the pointer to hold meta-data */
	--vsa_ptr;
	
	assert(0xDEADBEEF == GET_MAGIC(vsa_ptr));
	assert(0 > GET_BLOCK_STATUS(vsa_ptr));

	GET_BLOCK_STATUS(vsa_ptr) = GET_ABS_VAL((GET_BLOCK_STATUS(vsa_ptr)));

}

size_t VsaBiggestChunkAvailable(vsa_ty *pool)
{
	vsa_ty *pool_runner = pool;
	long counter = 0;

	assert(NULL != pool);
	
	for ( ;NO_MORE_SPACE != pool_runner->block_status;
	      pool_runner = AdvanceRunnerByBlock(pool_runner))
	{
		DeFragmentSpaces(pool_runner);
		if (counter < pool_runner->block_status)
		{
			counter = pool_runner->block_status;
		}
	}
	

	return (counter);

}

/********************************static functions******************************/

static size_t AlignData(size_t data)
{

	return (((data)+ (word_size -1)) & (~(word_size -1)));
}

static void DeFragmentSpaces(vsa_ty *pool)
{

	char *runner_next = NULL;
	runner_next = (char *)pool + VSA_SIZE + (GET_ABS_VAL(GetBlockStatus(pool)));

	if (NO_MORE_SPACE != GET_BLOCK_STATUS(runner_next))
	{
		if (0 < GET_BLOCK_STATUS(runner_next) && 0 < GetBlockStatus(pool))
		{
			pool->block_status += GET_BLOCK_STATUS(runner_next) + VSA_SIZE;
		}
	}
}

static void InitMetaData(vsa_ty *pool, size_t pool_size)
{
	vsa_ty end_indicator = {0};
	
	pool->block_status = pool_size;
#ifndef NDEBUG
	pool->magic_number = MAGIC_NUMBER;
#endif

	end_indicator.block_status = NO_MORE_SPACE;
#ifndef NDEBUG
	end_indicator.magic_number = MAGIC_NUMBER;
#endif
	
	memcpy((((char *)pool) + (pool_size+VSA_SIZE)), &end_indicator, VSA_SIZE);
	
}

static void *AdvanceRunnerByBlock(vsa_ty *runner)
{
	assert(NULL != runner);
	runner = (vsa_ty *)((char *)(runner) +
	      VSA_SIZE + GET_ABS_VAL(GetBlockStatus(runner)));
	return (runner);
}

static char *UpdateRunnerStatus(char *runner, size_t aligned_block_size)
{
	char *ret = NULL;
	vsa_ty *new_meta_data = NULL;
	
	assert(NULL != runner);
	
	if (NO_MORE_SPACE == ((vsa_ty *)runner)->block_status)
	{
		return (NULL);
	}
	
	if ((long)(aligned_block_size + VSA_SIZE) < 
	   ((vsa_ty *)runner)->block_status)
	{
		ret = runner;
		runner += VSA_SIZE + aligned_block_size;
		new_meta_data = (vsa_ty *)runner;
		new_meta_data->block_status = ((vsa_ty *)ret)->block_status -
									aligned_block_size - VSA_SIZE;
		((vsa_ty *)ret)->block_status = -(aligned_block_size);
	#ifndef NDEBUG
		new_meta_data->magic_number = MAGIC_NUMBER;
		((vsa_ty *)runner)->magic_number = MAGIC_NUMBER;
	#endif	
	}
	else if ((long)(aligned_block_size + VSA_SIZE) ==
	        ((vsa_ty *)runner)->block_status)
	{
		ret = runner; 
		((vsa_ty *)ret)->block_status = -(aligned_block_size);
	#ifndef NDEBUG
		((vsa_ty *)runner)->magic_number = MAGIC_NUMBER;
	#endif	
	}
	
	
	return (ret + VSA_SIZE);
}


static size_t AlignPoolSize(size_t pool_size, size_t bytes_to_align)
{
	return (((pool_size - bytes_to_align) / WORD_SIZE) * WORD_SIZE);
}


static size_t GetAsSizeT(void *data)
{
	assert(NULL != data);
	
	return((size_t)data);
}


static long GetBlockStatus(vsa_ty *vsa)
{
	assert(NULL != vsa);
	
	return(vsa->block_status);
}
