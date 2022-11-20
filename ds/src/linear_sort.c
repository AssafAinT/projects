/*****************************************************
 * Linear Sort                                       *
 * Assaf Ainhoren                                    *
 * Reviewer: Mark Galperin                           *
 * date: 10.07.2022                                  *
 *****************************************************/

#include <stdlib.h> /* calloc, free ,rand*/
#include <assert.h> /* assert */
#include "linear_sort.h"

#define BASE_TEN 10
#define SUCCESS 0
#define FAIL 1
#define RADIX_COUNT_MAX_SIZE 11
static const unsigned int radix_max_range = 10;

static int GetMaxVal(int *arr, size_t arr_size);

static int GetMinVal(int *arr, size_t arr_size);

static int GetRange(int max ,int min);

static int RadixCountingSort(int *arr, int *sorted_arr, size_t arr_size , size_t radix_place);

static void CountNumApperance(int *count_arr, int *arr,
                             size_t arr_size, size_t min_val);

static void SortBackTheParamArray(int *user_arr, int *util_arr, size_t arr_size);

static void SumSubSetArrays(int *count_arr, size_t range);

int CountingSort(int *arr, size_t arr_size)
{
	int *sorted_arr = NULL;
	int *count_arr = NULL; 
	int range = 0;
	int min = 0;
	int i = 0;
	
	min = GetMinVal(arr, arr_size);
	range = GetRange(GetMaxVal(arr, arr_size), min);
	
	sorted_arr = (int *)calloc(arr_size, sizeof(int));
	if (NULL == sorted_arr)
	{
		return (FAIL);
	}
	count_arr = (int *)calloc((range + 1), sizeof(int));
	if (NULL == sorted_arr)
	{
		free(sorted_arr);
		return (FAIL);
	}
	
	/* count the appearance of every number */
	CountNumApperance(count_arr, arr, arr_size, GetMinVal(arr, arr_size));
	--(count_arr[0]);
	SumSubSetArrays(count_arr, GetRange(GetMaxVal(arr, arr_size), min));

	for (i=(arr_size - 1); i >= 0 ; --i)
	{
		sorted_arr[count_arr[arr[i] - min]] = arr[i];
		--(count_arr[arr[i] - min]);
	}
	
	SortBackTheParamArray(arr, sorted_arr, arr_size);

	free(sorted_arr);
	sorted_arr = NULL;
	free(count_arr);
	count_arr = NULL;
	
	return (SUCCESS);
}





int CountingSortNoSum(int *arr, size_t arr_size)
{
	int *count_arr = NULL; 
	int range = 0;
	int min = 0;
	int i = 0;
	int j = 0;
	
	min = GetMinVal(arr, arr_size);
	range = GetRange(GetMaxVal(arr, arr_size), min);
	
	count_arr = (int *)calloc((range + 1), sizeof(int));
	if (NULL == count_arr)
	{
		return (FAIL);
	}
	
	/* count the appearance of every number */
	CountNumApperance(count_arr, arr, arr_size,GetMinVal(arr,arr_size));

	for (i = 0; i <= range; ++i)
	{
		for ( ; count_arr[i] != 0; ++j, --(count_arr[i]))
		{
			arr[j] = i + min;
		}
	}
	
	free(count_arr);
	count_arr = NULL;
	
	return (SUCCESS);
}


int RadixSort(int *arr, size_t arr_size)
{
	int maximum = GetMaxVal(arr, arr_size);
	int radix_place = 0;
	int return_status = SUCCESS;
	int *sorted_arr = NULL;
	assert(NULL != arr);
	sorted_arr = (int *)calloc(arr_size , sizeof(int));
	
	if (NULL == sorted_arr)
	{
		return (FAIL);
	}
	for (radix_place = 1;(return_status == SUCCESS) &&
	                     (0 < (maximum / radix_place));
	                     radix_place *= BASE_TEN)
	{
		return_status = RadixCountingSort(arr, sorted_arr, arr_size, radix_place);
	}
	free(sorted_arr);
	sorted_arr = NULL;
	return return_status;

}

static int RadixCountingSort(int *arr, int *sorted_arr, size_t arr_size , size_t radix_place)
{

	int count_arr[RADIX_COUNT_MAX_SIZE] = {0}; 	
	int i = 0;


	/* count the appearance of every number */
	for (i = 0 ; i < (int)arr_size; ++i)
	{
		++(count_arr[(arr[i]/ radix_place) % BASE_TEN]);
	}
	
	SumSubSetArrays(count_arr, radix_max_range);
	
	
	for (i=(arr_size -1); i >= 0 ; --i)
	{
		size_t element_index = (arr[i]/radix_place) % BASE_TEN; 
		sorted_arr[count_arr[element_index]-1] = arr[i];
		--(count_arr[(arr[i]/radix_place) % BASE_TEN]);
	}
	
	SortBackTheParamArray(arr, sorted_arr, arr_size);
		
	return (SUCCESS);

}


static void CountNumApperance(int *count_arr, int *arr,
                             size_t arr_size, size_t min_val)
{
	size_t i = 0;
	
	for ( ; i < arr_size; ++i)
	{
		++(count_arr[arr[i]- min_val]);
	}
	
		
}


static void SortBackTheParamArray(int *user_arr, int *util_arr,size_t arr_size)
{
	size_t i=0;
	for ( ; i < arr_size; ++i)
	{
		user_arr[i] = util_arr[i];
	}
}

static void SumSubSetArrays(int *count_arr, size_t range)
{
	size_t i = 0;
	
	for (i = 1; i <= range; ++i)
	{
		count_arr[i] += count_arr[i-1];
	}
}


static int GetMaxVal(int *arr, size_t arr_size)
{
	size_t i = 0;
	int max_holder = arr[i];
	
	for ( ; i < arr_size; ++i)
	{
		if(arr[i] > max_holder)
		{
			max_holder = arr[i];
		}
	}
	return (max_holder);
}

static int GetMinVal(int *arr, size_t arr_size)
{
	size_t i = 0;
	int min_holder = arr[i];
	
	for ( ; i < arr_size; ++i)
	{
		if(arr[i] < min_holder)
		{
			min_holder = arr[i];
		}
	}
	return (min_holder);
}
static int GetRange(int max ,int min)
{
	return (max - min);
}


