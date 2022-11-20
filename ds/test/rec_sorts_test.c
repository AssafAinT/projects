/*****************************************************
 * rec_sorts_test                                    *
 * Assaf Ainhoren                                    *
 * Reviewer: Haggai Newman                           *
 * date: 28.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /*printf */
#include <assert.h> /* assert.h */
#include <stdlib.h>	/*rand*/
#include <time.h> /*clock_t*/

#include "rec_sorts.h"

#define MEGA_ARRAY_SIZE 5000
#define ARRAY_SIZE 10

void MergeSortTests(void);
void PrintArray(int *arr, size_t size);
int DataCompare(const void *data1, const void *data2);
void QuickSortTests(void);
void GenerateRandValues(int *arr);
void SortCheck(int *arr, size_t arr_size);
int main(void)
{	
	QuickSortTests();
	MergeSortTests();
	return (0);
}
void QuickSortTests(void)
{
	int array[ARRAY_SIZE] = {3, 6, 1, 5, 9, 4, 7, 2, -8 , 1};
	int array2[ARRAY_SIZE] = {1, 6, 1, 5, 9, 4, 7, 2, 8 , 1};
	int array3[ARRAY_SIZE] = {3, 7, 1, 5, 2, 4, 7, 2, 8 , 1};
	int array4[ARRAY_SIZE] = {5, 6, 1, 1, 9, 4, 7, 2, 8 , 1};
	int five_k_arr[MEGA_ARRAY_SIZE] = {0};
	double end_time = 0;
	double execute_time = 0;

	Qsort(array, ARRAY_SIZE, sizeof(int), DataCompare);
	SortCheck(array, ARRAY_SIZE);
	PrintArray(array, ARRAY_SIZE);
	Qsort(array2, ARRAY_SIZE, sizeof(int), DataCompare);
	SortCheck(array2, ARRAY_SIZE);
	PrintArray(array2, ARRAY_SIZE);
	Qsort(array3, ARRAY_SIZE, sizeof(int), DataCompare);
	SortCheck(array3, ARRAY_SIZE);
	PrintArray(array3, ARRAY_SIZE);
	Qsort(array4, ARRAY_SIZE, sizeof(int), DataCompare);
	SortCheck(array4, ARRAY_SIZE);
	PrintArray(array4, ARRAY_SIZE);

	GenerateRandValues(five_k_arr);
	execute_time = clock();
	Qsort(five_k_arr, MEGA_ARRAY_SIZE, sizeof(int), DataCompare);
	end_time = (double)(clock()- execute_time) / CLOCKS_PER_SEC;
	SortCheck(five_k_arr, MEGA_ARRAY_SIZE);

	printf("The home made Quick_sort is done in %f seconds\n", end_time);
	GenerateRandValues(five_k_arr);
	execute_time = clock();
	qsort(five_k_arr, MEGA_ARRAY_SIZE, sizeof(int), DataCompare);
	end_time = (double)(clock()- execute_time) / CLOCKS_PER_SEC;
	printf("The lib Quick_sort is done in %f seconds\n", end_time);

	printf("----------------------quick sort done------------------------\n\n");
}
void MergeSortTests(void)
{
	int array[ARRAY_SIZE] = {3, 6, 1, 5, 9, 4, 7, 2, -8 , 1};
	int array2[ARRAY_SIZE] = {1, 6, 1, 5, 9, 4, 7, 2, 8 , 1};
	int array3[ARRAY_SIZE] = {3, 7, 1, 5, 2, 4, 7, 2, 8 , 1};
	int array4[ARRAY_SIZE] = {5, 6, 1, 1, 9, 4, 7, 2, 8 , 1};
	int array5[ARRAY_SIZE] = {1, 2, 3, 4, 5, 4, 6, 7, -1235, 123};
	int five_k_arr[MEGA_ARRAY_SIZE] = {0};
	double end_time = 0;
	double execute_time = 0;

	assert(SUCCESS == MergeSort(array, ARRAY_SIZE));
	SortCheck(array, ARRAY_SIZE);
	PrintArray(array, ARRAY_SIZE);
	assert(SUCCESS == MergeSort(array2, ARRAY_SIZE));
	SortCheck(array2, ARRAY_SIZE);
	PrintArray(array2, ARRAY_SIZE);
	assert(SUCCESS == MergeSort(array3, ARRAY_SIZE));
	SortCheck(array3, ARRAY_SIZE);
	PrintArray(array3, ARRAY_SIZE);
	assert(SUCCESS == MergeSort(array4, ARRAY_SIZE));
	SortCheck(array4, ARRAY_SIZE);
	PrintArray(array4, ARRAY_SIZE);
	assert(SUCCESS == MergeSort(array5, ARRAY_SIZE));
	SortCheck(array5, ARRAY_SIZE);
	PrintArray(array5, ARRAY_SIZE);
	
	GenerateRandValues(five_k_arr);
	execute_time = clock();
	MergeSort(five_k_arr, MEGA_ARRAY_SIZE);
	end_time = (double)(clock()- execute_time) / CLOCKS_PER_SEC;
	SortCheck(five_k_arr, MEGA_ARRAY_SIZE);

	printf("The home made Merge_sort is done in %f seconds\n", end_time);
}

void PrintArray(int *array, size_t size)
{
	size_t index = 0;
	
	while (index < size)
	{
		printf("%d ",array[index]);
		++index;
	}
	printf("\n");
}
void GenerateRandValues(int *arr)
{
	size_t i = 0;
	for (i = 0; i < MEGA_ARRAY_SIZE; ++i)
	{
		arr[i] = (rand() % 100) + 1;
	}

}

void SortCheck(int *arr, size_t arr_size)
{
	size_t i = 0;
	for (i = 1; i < arr_size; ++i)
	{
		assert(arr[i] >= arr[i -1]);
	}

}
int DataCompare(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}