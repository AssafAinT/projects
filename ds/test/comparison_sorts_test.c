/*****************************************************
 * comparison_sorts                                  *
 * Assaf Ainhoren                                    *
 * Reviewer: Roi Herscho                             *
 * date: 10.07.2022                                  *
 *****************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */
#include <time.h> /* CLOCK_PER_SEC, clock_t */

#include "comparison_sorts.h"
#define HUGE_ARR_SIZE 5000
#define ARR_SIZE 12

int CompareData(const void *data1, const void *data2);
void TestBubbleSort(void);
void TestSelecetionSort(void);
void TestInsertionSort(void);
void QuickSortTest(void);

int main(void)
{
	
	TestBubbleSort();
	TestSelecetionSort();
	TestInsertionSort();
	QuickSortTest();
	return (0);
}

void TestBubbleSort(void)
{
	int arr[HUGE_ARR_SIZE] = {0};
	int arr2[ARR_SIZE] = {12,11,10,9,8,7,6,5,4,3,2,1};
	int arr3[ARR_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12};
	
	size_t i = 0;
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	for ( ; i < HUGE_ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin_time = clock();
	BubbleSort(arr, HUGE_ARR_SIZE);
	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for bubble sort\n", exec_time);
	BubbleSort(arr2, ARR_SIZE);
	BubbleSort(arr3, ARR_SIZE);
	for (i=0; i < (HUGE_ARR_SIZE-1); ++i)
	{
		assert(arr[i] < arr[i+1]);
	}
	printf("[");
	for (i=0; i < ARR_SIZE ; ++i)
	{
		printf(" %d ", arr2[i]);
	}
	printf("]\n");
	
	printf("[");
	for (i=0; i < ARR_SIZE ; ++i)
	{
		printf(" %d ", arr3[i]);
	}
	printf("]\n");
}

void TestSelecetionSort(void)
{
	
	int arr[HUGE_ARR_SIZE] = {0};
	int arr2[ARR_SIZE] = {12,11,10,9,8,7,6,5,4,3,2,1};
	int arr3[ARR_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12};
	
	size_t i = 0;
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	for ( ; i < HUGE_ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin_time = clock();
	SelectionSort(arr, HUGE_ARR_SIZE);
	BubbleSort(arr2, ARR_SIZE);
	BubbleSort(arr3, ARR_SIZE);
	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for selection sort\n", exec_time);
	
	for (i=0; i < (HUGE_ARR_SIZE-1); ++i)
	{
		assert(arr[i] < arr[i+1]);
	}
	
	printf("[");
	for (i=0; i < ARR_SIZE ; ++i)
	{
		printf(" %d ", arr2[i]);
	}
	printf("]\n");
	
	printf("[");
	for (i=0; i < ARR_SIZE ; ++i)
	{
		printf(" %d ", arr3[i]);
	}
	printf("]\n");
}

void TestInsertionSort(void)
{
	int arr[HUGE_ARR_SIZE] = {0};
	int arr2[ARR_SIZE] = {12,11,10,9,8,7,6,5,4,3,2,1};
	int arr3[ARR_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12};
	size_t i = 0;
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	for ( ; i < HUGE_ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin_time = clock();
	InsertionSort(arr, HUGE_ARR_SIZE);
	BubbleSort(arr2, ARR_SIZE);
	BubbleSort(arr3, ARR_SIZE);
	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for insertion sort\n", exec_time);
	for (i=0; i < (HUGE_ARR_SIZE-1); ++i)
	{
		assert(arr[i] < arr[i+1]);
	}
	
	printf("[");
	for (i=0; i < ARR_SIZE ; ++i)
	{
		printf(" %d ", arr2[i]);
	}
	printf("]\n");
	
	printf("[");
	for (i=0; i < ARR_SIZE ; ++i)
	{
		printf(" %d ", arr3[i]);
	}
	printf("]\n");

}

void QuickSortTest(void)
{
	int arr[HUGE_ARR_SIZE] = {0};
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	begin_time = clock();
	qsort(arr, HUGE_ARR_SIZE, sizeof(int),CompareData);

	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for quick sort\n", exec_time);
}

int CompareData(const void *data1, const void *data2)
{
	
	return ((*(int *)(data1)) - (*(int *)data2));
}
