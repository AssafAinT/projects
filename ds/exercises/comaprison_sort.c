#include <stdio.h> /* printf */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */
#include <time.h> /* CLOCK_PER_SEC, clock_t */

void BubbleSort(int *arr, size_t arr_size);
void SelectionSort(int *arr, size_t arr_size);
void InsertionSort(int *arr, size_t arr_size);

#define ARR_SIZE 5000
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

void BubbleSort(int *arr, size_t arr_size)
{
	size_t i = 0; 
	size_t j = 0;
	int swap_holder = 0;
	
	for ( i=0; i < (arr_size - 1); ++i)
	{
		for (j=0 ; (j < arr_size - i - 1); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				swap_holder = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = swap_holder;
			}
		}
	}
}
void SelectionSort(int *arr, size_t arr_size)
{
	size_t i = 0; 
	size_t j = 0;
	int min_holder = 0;
		
	for (i=0; i < arr_size - 1; ++i)
	{
		for (j = i + 1; j < arr_size; ++j)
		{
			if (arr[j] < arr[i])
			{
				min_holder = arr[j];
				arr[j] = arr[i];
				arr[i] = min_holder;
			}
		}
	}
}

void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 0; 
	int j = 0;
	int min_holder = 0;
	
	for ( i = 1; i < arr_size; ++i)
	{
		min_holder = arr[i];
		for ((j = i - 1); min_holder < arr[j] && j >= 0; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = min_holder;
	}
}


void TestBubbleSort(void)
{
	int arr[ARR_SIZE] = {0};
	size_t i = 0;
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	for ( ; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin_time = clock();
	BubbleSort(arr, ARR_SIZE);
	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for bubble sort\n", exec_time);
	for (i=0; i < (ARR_SIZE-1); ++i)
	{
		assert(arr[i] < arr[i+1]);
	}
}

void TestSelecetionSort(void)
{
	
	int arr[ARR_SIZE] = {0};
	size_t i = 0;
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	for ( ; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin_time = clock();
	SelectionSort(arr, ARR_SIZE);
	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for selection sort\n", exec_time);
	
	for (i=0; i < (ARR_SIZE-1); ++i)
	{
		assert(arr[i] < arr[i+1]);
	}
}

void TestInsertionSort(void)
{
	int arr[ARR_SIZE] = {0};
	size_t i = 0;
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	for ( ; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin_time = clock();
	InsertionSort(arr, ARR_SIZE);
	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for insertion sort\n", exec_time);
	for (i=0; i < (ARR_SIZE-1); ++i)
	{
		assert(arr[i] < arr[i+1]);
	}

}

void QuickSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	double exec_time = 0.0; 
	clock_t begin_time = 0;
	begin_time = clock();
	qsort(arr, ARR_SIZE, sizeof(int),CompareData);

	exec_time = (double)(clock() - begin_time)/CLOCKS_PER_SEC;
	printf("%f seconds its the execution time for quick sort\n", exec_time);
}

int CompareData(const void *data1, const void *data2)
{
	
	return ((*(int *)(data1)) - (*(int *)data2));
}
