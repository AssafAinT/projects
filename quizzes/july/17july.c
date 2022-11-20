#include <stdio.h> /*printf, size_t */
#include <assert.h> /* assert */

#define NUM_OF_BITS_IN_CHAR_ARR (24)

void ShiftLeftArr(char *arr,size_t arr_size, size_t n_rot);
void ReverseArr(char *arr, size_t arr_size);
int CompareData(const char data1, const char data2);
int Find(char *c_arr, size_t arr_size, char n_to_find);
int main(void)
{
	char c_arr[] = {'a','b','c'};
	size_t i=0;
	size_t rot_amount = 2;
	ShiftLeftArr(c_arr,3, rot_amount);
	assert(1 == Find(c_arr, 3, 'c'));
	assert(0 == Find(c_arr, 3, 'd'));
	for(; i<3; ++i)
	{
		printf("%c\n", c_arr[i]);
	}
	return (0);
}

void ShiftLeftArr(char *arr,size_t arr_size, size_t n_rot)
{
	assert(NULL != arr);
	n_rot %= arr_size;
	ReverseArr(arr, n_rot);
	ReverseArr(arr+n_rot, arr_size-n_rot);
	ReverseArr(arr, arr_size);
}
void ReverseArr(char *arr, size_t arr_size)
{
	char tmp = 0;
	char *tail_arr = arr+(arr_size-1);
	for ( ;tail_arr > arr;--tail_arr, ++arr)
	{
		tmp = *arr;
		*arr = *tail_arr;
		*tail_arr = tmp;
	}
	
}
int Find(char *c_arr, size_t arr_size, char n_to_find)
{
	int is_match = 0;
	size_t i = 0;
	assert(NULL != c_arr);
	assert(0 < arr_size);
	
	for ( ; i < arr_size && 1 != is_match; ++i)
	{
		is_match = CompareData(c_arr[i], n_to_find);
	}
	
	return (is_match);
}

int CompareData(const char data1, const char data2)
{
	return (data1 == data2);
}
