/****************************************************
* is_sum_found                                      *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef enum 
{   
    is_found,
    first_num,
    second_num,
    o_arr_size
}o_param_ty;
int IsSumFound(int *arr, size_t arr_size, int *o_arr, int sum);
void IsSumFoundRecursive(int *arr, size_t arr_size, size_t *o_i,
                       int *o_arr, int sum);
int main(void)
{
    int arr[5] = {2, 4, 7, 12 ,14};
	size_t arr_size = 5; 
	size_t i = 0;
	int sum = 9;
	int result[o_arr_size] = {0};   
    assert(1 ==IsSumFound(arr, arr_size -1, result, sum));
    
    while (i < o_arr_size)
    {
        printf("o_arr has %d inside \n", result[i]);
        ++i;
    }
    i=0;
    while (i < o_arr_size)
    {
        result[i] = 0;
        ++i;
    }
    assert(0 ==IsSumFound (arr, arr_size -1, result, 33));
    i = 0;
    while (i < o_arr_size)
    {
        printf("o_arr has %d inside \n", result[i]);
        ++i;
    }


    return (0);
}

int IsSumFound(int *arr, size_t arr_size, int *o_arr, int sum)
{   
    size_t i = 0;

    IsSumFoundRecursive(arr, arr_size, &i, o_arr, sum);
    if (0 == o_arr[is_found])
    {
        o_arr[first_num] = 0;
        o_arr[second_num] = 0;
        return o_arr[is_found];
    }
    return (o_arr[is_found]);
}

void IsSumFoundRecursive(int *arr, size_t arr_size, size_t *o_i,
                       int *o_arr, int sum)
{
    
    if (arr_size <= *o_i )
    {
        return;
    }
    if (arr[*o_i] + arr[arr_size] == sum)
    {
        o_arr[is_found] = 1;
        o_arr[first_num] = *o_i;
        o_arr[second_num] = arr_size;
        return;
    }
    else if (arr[*o_i] + arr[arr_size] < sum)
    {
        ++*(o_i);
        IsSumFoundRecursive(arr, arr_size, o_i, o_arr, sum);
    }
    else if(arr[*o_i] + arr[arr_size] > sum)
    {
        IsSumFoundRecursive(arr, --arr_size, o_i, o_arr, sum);
    }
}