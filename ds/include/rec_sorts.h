/*****************************************************
 * rec_sort                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Haggai Newman                           *
 * date: 28.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#ifndef __ILRD_OL127_128__REC_SORTS__H__
#define __ILRD_OL127_128__REC_SORTS__H__

#include <stddef.h> /*size_t*/

typedef int(*cmp_func)(const void *data1, const void *data2);

typedef enum
{
    SUCCESS = 0,
    FAIL = 1
}status_ty;

/*****************************************************
* Description: sorting array by                      *
* Merge Sort Algorithm -Divide and conquer           *
* signed nums and also complex types                 *
* return value: Upon succes: 0 and the sorted array  *
				Upon failure: 1                      *
				                                     *
* Complexity:                                        *
* Time - O(nlogn).                                   *
* Space -O(n).                                       *
*****************************************************/
status_ty MergeSort(int *arr, size_t size);
/*****************************************************
* Description: sorting array by                      *
* quick_sort algorithm                               *
* return value: void                                 *
*				                                     *
* Complexity:                                        *
* Time - O(nlogn).                                   *
* Auxilary Space -O(1).                              *
*****************************************************/
void Qsort(void *base, size_t nmemb, size_t size, cmp_func cmp);

#endif /* __ILRD_OL127_128__REC_SORTS__H__ */
