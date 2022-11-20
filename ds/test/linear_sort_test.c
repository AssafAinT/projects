/*****************************************************
 * Linear Sort                                       *
 * Assaf Ainhoren                                    *
 * Reviewer: Mark Galperin                           *
 * date: 10.07.2022                                  *
 *****************************************************/

#include <stdio.h> /*printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */

#include "linear_sort.h"

#define SIZE_OF_ARR_TO_SEND(arr) (sizeof(arr))/(sizeof(int))

#define MEGA_ARRAY_SIZE 5000
#define SUCCESS 0
#define FAIL 1
#define RANDOM_NUM_BETWEEN_ONE_TO_HUNDRED ((rand() % 100) + 1)
#define RANDOM_SEVEN_DIGIT_NUM ((rand() % 10000000) + 1000000)

static void TestCountingSort(void);
static void TestCountingSortNoSum(void);
static void TestRadixSort(void);

int main(void)
{
	TestCountingSort();
	TestCountingSortNoSum();
	TestRadixSort();
	
	return (SUCCESS);
}
static void PrintArray(int *arr, size_t arr_size)
{
	size_t i = 0;
	printf("[");
	for (i=0; i < arr_size ; ++i)
	{
		printf(" %d ", arr[i]);
	}
	printf("]\n");
	
}


static void TestCountingSort(void)
{
	int arr_to_sort[] = {1,4,6,8,3,9};
	int arr_to_sort1[] = {-3,5,8,0,-2,1};
	
	printf("------------------before sorting--------------------------\n");
	PrintArray(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort));
	assert(SUCCESS == CountingSort(arr_to_sort,
	                  SIZE_OF_ARR_TO_SEND(arr_to_sort)));
	printf("------------------after sorting--------------------------\n");
	PrintArray(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort));
	
	printf("------------------before sorting--------------------------\n");
	PrintArray(arr_to_sort1, SIZE_OF_ARR_TO_SEND(arr_to_sort1));
	assert(SUCCESS == CountingSort(arr_to_sort1,
	                  SIZE_OF_ARR_TO_SEND(arr_to_sort1)));
	printf("------------------after sorting--------------------------\n");
	PrintArray(arr_to_sort1, SIZE_OF_ARR_TO_SEND(arr_to_sort1));	
}

static void TestCountingSortNoSum(void)
{
	int arr_to_sort[] = {1,4,6,8,3,9};
	int arr_to_sort1[] = {-3,5,8,0,-2,1};
	int arr_to_sort2[] = {-3,-7,0,10,5,8,0,-2,1};
	int mega_array[MEGA_ARRAY_SIZE] = {0};
	int i = 0;

	for ( ;i<MEGA_ARRAY_SIZE ; ++i)
	{
		mega_array[i] = RANDOM_NUM_BETWEEN_ONE_TO_HUNDRED;
	}
	CountingSortNoSum(mega_array, MEGA_ARRAY_SIZE);
	for (i=0 ;i<MEGA_ARRAY_SIZE -1; ++i)
	{
		assert(mega_array[i] <= mega_array[i+1]);
	}
	printf("\n\n------------------before sorting no sum--------------------\n");
	PrintArray(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort));
	assert(SUCCESS == CountingSortNoSum(arr_to_sort,
	                  SIZE_OF_ARR_TO_SEND(arr_to_sort)));
	printf("------------------after sorting--------------------------\n");
	PrintArray(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort));
	
	printf("------------------before sorting no sum------------------------\n");
	PrintArray(arr_to_sort1, SIZE_OF_ARR_TO_SEND(arr_to_sort1));
	assert(SUCCESS == CountingSortNoSum(arr_to_sort1,
	                  SIZE_OF_ARR_TO_SEND(arr_to_sort1)));
	printf("------------------after sorting--------------------------\n");
	PrintArray(arr_to_sort1, SIZE_OF_ARR_TO_SEND(arr_to_sort1));	
	
	printf("----------------before sorting no sum--------------------------\n");
	PrintArray(arr_to_sort2, SIZE_OF_ARR_TO_SEND(arr_to_sort2));
	assert(SUCCESS == CountingSortNoSum(arr_to_sort2,
	                  SIZE_OF_ARR_TO_SEND(arr_to_sort2)));
	printf("------------------after sorting--------------------------\n");
	PrintArray(arr_to_sort2, SIZE_OF_ARR_TO_SEND(arr_to_sort2));	
}

static void TestRadixSort(void)
{
	int arr_to_sort[] = {3, 6, 1, 5, 9, 4, 7, 2, 8 , 10};
	int arr_to_sort1[] = {1, 6, 1, 15, 9, 0, 4, 7, 2, 8 , 10};
	int mega_array[MEGA_ARRAY_SIZE] = {0};
	int i = 0;
	
	for ( ;i<MEGA_ARRAY_SIZE ; ++i)
	{
		mega_array[i] = RANDOM_SEVEN_DIGIT_NUM;
	}
	assert(SUCCESS ==RadixSort(mega_array, MEGA_ARRAY_SIZE));
	for (i=0 ;i<MEGA_ARRAY_SIZE -1; ++i)
	{
		assert(mega_array[i] <= mega_array[i+1]);
	}
	printf("\n-------------radix sort mega test successed-----------------\n");
	
	printf("\n\n------------------before Radix sorting---------------------\n");
	PrintArray(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort));
	assert(SUCCESS == RadixSort(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort)));
	printf("------------------after Radix sorting--------------------------\n");
	PrintArray(arr_to_sort, SIZE_OF_ARR_TO_SEND(arr_to_sort));
	
	printf("\n\n------------------before Radix sorting---------------------\n");
	PrintArray(arr_to_sort1, SIZE_OF_ARR_TO_SEND(arr_to_sort1));
	assert(SUCCESS == RadixSort(arr_to_sort1,
	                  SIZE_OF_ARR_TO_SEND(arr_to_sort1)));
	printf("------------------after Radix sorting--------------------------\n");
	PrintArray(arr_to_sort1, SIZE_OF_ARR_TO_SEND(arr_to_sort1));
}
