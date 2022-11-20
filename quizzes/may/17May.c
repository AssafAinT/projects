#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int *IsSumFound(int *arr, size_t arr_size, int sum);
int main()
{
	int arr[5] = {2, 4, 7, 12 ,14};
	size_t arr_size = 5; 
	size_t i = 0;
	int sum = 21;
	int *result =  IsSumFound(arr, (arr_size-1), sum);
		
	for ( i = 0; i<3; ++i)
	{
		printf("%d\n", result[i]);
	}
	
	free(result);
	result = NULL;
	return (0);
}

int *IsSumFound(int *arr, size_t arr_size, int sum)
{
	size_t i = 0;
	int *result = (int *)calloc(3, sizeof(int));
	
	while (arr_size > i)
	{
		if( arr[i] + arr[arr_size] == sum)
		{
			result[0] = 1;
			result[1] = i;
			result[2] = arr_size;
			return (result);
		}
		else if(arr[i] + arr[arr_size] < sum)
		{
			++i;
		}
		else if( arr[i] + arr[arr_size] > sum)
		{
			--arr_size;
		}
	}
	return (result);
}
	

