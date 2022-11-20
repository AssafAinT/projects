/*****************************************************
 * rec_sorts                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Haggai Newman                           *
 * date: 28.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memmove */

#include "rec_sorts.h"

static const size_t g_int_size = sizeof(int);
/***********************************Merge static functions*********************/
static status_ty AllocArrays(int **left_sub_array, int **right_sub_array,
                             size_t size);

static void RecMergeSort(int *arr, int *left_sub_array,int *right_sub_array,
                        size_t start, size_t end);

static void MergeAndSortSubArray(int *arr, int *left_sub_array,
                                int *right_sub_array,
								size_t start, size_t mid, size_t end);

static void FinalMerge(int *src_arr, int* left_sub_array, int *right_sub_array,
                 size_t start, size_t left_arr_size, size_t right_arr_size);

/*********************************quick sort static functions******************/

static void RecursiveQSort(void *arr_base, long start, long end,
                           size_t size_of_elem, cmp_func cmp);

static size_t MakePartition(void *arr_base, long start, long pivot,long end,
                           size_t size_of_elem, cmp_func cmp);

static int DataCmp(void *arr_base, long first_data, long second_data,
					   size_t size_of_element, cmp_func cmp);
static void Swap(void *data1, void *data2, size_t size);

static char *GetAddressOf(char *arr_base, size_t element_amount,
                          size_t size_element);


/*********************************quick sort section***************************/
void Qsort(void *base, size_t nmemb, size_t size, cmp_func cmp)
{
	assert(NULL != base);
	RecursiveQSort(base, 0, nmemb - 1, size, cmp);
}
static void RecursiveQSort(void *arr_base, long start, long end,
                           size_t size_of_elem, cmp_func cmp)
{
	
	if (start < end)
	{
		long pivot_index = MakePartition(arr_base, start, end,end-1,
		                                size_of_elem, cmp);
		RecursiveQSort(arr_base, start, pivot_index -1 , size_of_elem, cmp);
		RecursiveQSort(arr_base, pivot_index + 1, end, size_of_elem, cmp);
	}
}
static size_t MakePartition(void *arr_base, long start, long pivot,long end,
                           size_t size_of_elem, cmp_func cmp)
{
	
	while (start <= end)
	{
		if ( 0 < DataCmp(arr_base, start, pivot, size_of_elem, cmp))
		{
			if ( 0 > DataCmp(arr_base, end, pivot, size_of_elem, cmp))
			{
				Swap(GetAddressOf((char *)arr_base, start, size_of_elem),
					GetAddressOf((char *)arr_base, end, size_of_elem),size_of_elem);

			}
			--end;
		}
		else
		{
			++start;
		}
	}

	if ( 0 < DataCmp(arr_base, start, pivot, size_of_elem, cmp))
	{
		
		Swap(GetAddressOf((char *)arr_base, start, size_of_elem),
			 GetAddressOf((char *)arr_base, pivot, size_of_elem),size_of_elem);
	
		return(start);
	}
	
	return(pivot);

}

static int DataCmp(void *arr_base, long first_data, long second_data,
					   size_t size_of_element, cmp_func cmp)
{
	return (cmp(GetAddressOf((char *)arr_base, first_data, size_of_element),
	       GetAddressOf((char *)arr_base, second_data, size_of_element)));
}

static void Swap(void *data1, void *data2, size_t size)
{
	unsigned char *first = (unsigned char *)data1;
	unsigned char *second = (unsigned char *)data2;
	unsigned char temp = 0;
	
	while (0 < size)
	{
		temp = *first;
		*first++ = *second;
		*second++ = temp;
		--size;
	}
}
static char *GetAddressOf(char *arr_base, size_t element_amount,
                          size_t size_element)
{
	return (&arr_base[element_amount * size_element]);
}
/***********************************merge sort section*************************/
status_ty MergeSort(int *arr, size_t size)
{
	/* (start + end) / 2 */
	int start = 0;
	int end = size - 1;
	int *left_sub_array = NULL;
	int *right_sub_array = NULL;
	status_ty o_status = SUCCESS;
	o_status = AllocArrays(&left_sub_array, &right_sub_array, size);
	if (FAIL == o_status)
	{
		return (o_status);
	}
	
	RecMergeSort(arr, left_sub_array, right_sub_array,start, end);
	
	free(left_sub_array);
	left_sub_array = NULL;
	free(right_sub_array); 
	right_sub_array = NULL;
	
	return(o_status);
}

static void RecMergeSort(int *arr, int *left_sub_array,int *right_sub_array,
                        size_t start, size_t end)
{
	
	if (start < end )
	{
		size_t mid = (start + end) / 2;
		RecMergeSort(arr, left_sub_array, right_sub_array,start,mid);
		
		RecMergeSort(arr, left_sub_array, right_sub_array,mid +1 ,end);
		
		MergeAndSortSubArray(arr, left_sub_array, right_sub_array,
		                     start, mid, end);
	}
}

static void MergeAndSortSubArray(int *arr, int *left_sub_array,
                                int *right_sub_array,
								size_t start, size_t mid, size_t end)
{

	size_t left_arr_size = (mid - start) + 1;
	size_t right_arr_size = end - mid;
	
	size_t i = 0;

	for (i=0 ; i < left_arr_size; ++i)
	{
		size_t data_right_partition = start + i;

		left_sub_array[i] = arr[data_right_partition];
	}

	for ( i = 0; i < right_arr_size; ++i)
	{
		size_t data_left_partition = mid + i +1;

		right_sub_array[i] = arr[data_left_partition];
	}

	FinalMerge(arr, left_sub_array, right_sub_array,start , left_arr_size,
													right_arr_size);
}

static void FinalMerge(int *src_arr, int* left_sub_array, int *right_sub_array,
                     size_t start, size_t left_arr_size, size_t right_arr_size)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	for (i = 0, j=0, k = start; i < left_arr_size && j < right_arr_size; ++k)
	{
		if (left_sub_array[i] <= right_sub_array[j])
		{
			src_arr[k] = left_sub_array[i];
			++i;
		}
		else
		{
			src_arr[k] = right_sub_array[j];
			++j;
		}
	}

	if (i < left_arr_size)
	{
		size_t size_to_copy = (left_arr_size - i)*sizeof(int);

		memmove(&src_arr[k], &left_sub_array[i], size_to_copy);
		k = left_arr_size;
	}

	else
	{
		size_t right_size_to_copy = (right_arr_size - j) * g_int_size;

		memmove(&src_arr[k], &right_sub_array[j], right_size_to_copy);
		k = right_arr_size;
	}

}

static status_ty AllocArrays(int **left_sub_array, int **right_sub_array,
                             size_t size)
{
	size_t size_to_alloc = (size / 2) + 1;
	*left_sub_array = calloc(size_to_alloc, (size_to_alloc) * sizeof(int));
	if (NULL == left_sub_array)
	{
		return (FAIL);
	}

	*right_sub_array = calloc(size_to_alloc, (size_to_alloc) * sizeof(int));
	if (NULL == right_sub_array)
	{
		return (FAIL);
	}

	return (SUCCESS);
	
}

