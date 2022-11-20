/*****************************************************
 * Linear Sort                                       *
 * Assaf Ainhoren                                    *
 * Reviewer: Mark Galperin                           *
 * date: 10.07.2022                                  *
 *****************************************************/
#ifndef __ILRD_OL127_128_LINEAR_SORT_H__
#define __ILRD_OL127_128_LINEAR_SORT_H__

#include <stddef.h> /*size_t */

/*****************************************************
* Description: sorting array by                      *
* counting sort algorithm and generalizing it to     *
* signed nums and also complex types                 *
* return value: Upon succes: 0                       *
				Upon failure: 1                      *
				                                     *
* Complexity:                                        *
* Time - O(n).                                       *
* Auxilary Space -O(k).                              *
*****************************************************/
int CountingSort(int *arr, size_t arr_size);
/*****************************************************
* Description: sorting array by                      *
* counting sort algorithm                            *
* return value: Upon succes: 0                       *
				Upon failure: 1                      *
				                                     *
* Complexity:                                        *
* Time - O(n).                                       *
* Auxilary Space -O(k).                              *
*****************************************************/
int CountingSortNoSum(int *arr, size_t arr_size);
/*****************************************************
* Description: sorting array by                      *
* Radix sort algorithm                               *
* return value: Upon succes: 0                       *
				Upon failure: 1                      *
				                                     *
* Complexity:                                        *
* Time - O(n).                                       *
* Auxilary Space -O(n).                              *
*****************************************************/

int RadixSort(int *arr, size_t arr_size);

#endif /* __ILRD_OL127_128_LINEAR_SORT_H__ */
