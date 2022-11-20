/****************************************************
* find_elem_cir_srt_arr                             *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
int FindPivKey(int *arr, int start, int end);
int BsSrtArr(int *arr, int start, int end, int tar);
size_t FindElementCirSrtArr(int *arr, size_t size, int tar);

int main(void)
{
    int arr[6] = {7, 8, 11, 1, 4, 5};
    int tar = 5;
    int tar2 = 7;
    printf("target is in %d\n", FindElementCirSrtArr(arr, 6, tar));
    printf("target2 is in %d\n", FindElementCirSrtArr(arr, 6, tar2));
    return (0);
}

int FindPivKey(int *arr, int start, int end)
{
    int mid_i = 0;
    if (start > end)
    {
        return -1;
    }

    if (start == end)
    {
        return start;
    }

    mid_i = (start + end) / 2;

    if ( arr[mid_i] > arr[mid_i + 1] &&
        mid_i < end)
    {
        return mid_i;
    }

    if ( arr[mid_i] < arr[mid_i - 1] &&
    mid_i > start)
    {
        return mid_i - 1;
    }

    if ( arr[start] >= arr[mid_i])
    {
        return (FindPivKey(arr , start, mid_i - 1));
    }
    return (FindPivKey(arr , mid_i +1, end));
}
int BsSrtArr(int *arr, int start, int end, int tar)
{
    int mid_i = 0;
    if (start > end)
    {
        return -1;
    }

    mid_i = (start + end) / 2;

    if (tar == arr[mid_i])
    {
        return mid_i;
    }

    if (tar > arr[mid_i])
    {
        return (BsSrtArr(arr, mid_i + 1, end, tar));
    }
    return (BsSrtArr(arr, start, mid_i - 1, tar));
}
size_t FindElementCirSrtArr(int *arr, size_t size, int tar)
{
    int piv = 0;

    assert (NULL != arr);

    piv = FindPivKey(arr, 0, size -1);

    if (-1 == piv)
    {
        /* array is not rotated */
        return (BsSrtArr(arr, 0, size -1, tar)); 
    }

    if (arr[piv] == tar)
    {
        return piv;
    }
    
    if ( arr[0] <= tar)
    {
        return (BsSrtArr(arr, 0, piv-1, tar)); 
    }
    return (BsSrtArr(arr, piv+1, size-1, tar)); 

}