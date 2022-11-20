/*****************************************************
 * comparison_sorts                                  *
 * Assaf Ainhoren                                    *
 * Reviewer: Roi Herscho                             *
 * date: 10.07.2022                                  *
 *****************************************************/

#include <stddef.h> /* size_t */
#include <string.h> /*memmove */
#include "comparison_sorts.h"

typedef enum 
{
	FALSE,
	TRUE
} status_ty;
static void ValSwap(int *first_num, int *second_num);
static void SortedArrayInsert(int *arr, size_t size, int inserted_num);
void BubbleSort(int *arr, size_t arr_size)
{
	size_t i = 0; 
	size_t j = 0;
	int is_sorted = FALSE;
	

	for (; i < arr_size && (!is_sorted); ++i)
	{
		is_sorted = TRUE;
		for (j=0 ; (j < arr_size - i - 1); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				ValSwap(&arr[j], &arr[j+1]);
				is_sorted =FALSE;
			}
		}
	}	

}
void SelectionSort(int *arr, size_t arr_size)
{
	size_t i = 0; 
	size_t j = 0;
		
	for (i=0; i < arr_size - 1; ++i)
	{
		for (j = i + 1; j < arr_size; ++j)
		{
			if (arr[j] < arr[i])
			{
				ValSwap(&arr[j], &arr[i]);
			}
		}
	}
}

void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 1;
	for ( ; i < arr_size; ++i)
	{
		if (arr[i] < arr[i-1])
		{
			SortedArrayInsert(arr, i, arr[i]);
		}
	}
}

static void ValSwap(int *first_num, int *second_num)
{
	int temp = *first_num;
	*first_num = *second_num;
	*second_num = temp;
	
}

static void SortedArrayInsert(int *arr, size_t size, int inserted_num)
{
	size_t j =0;
	for ( ; arr[size] > arr[j] ; ++j)
		{
			/* empty bempty */
		}
		memmove(&arr[j + 1], &arr[j], (size-j)*(sizeof(int)));
		arr[j] = inserted_num;
}
