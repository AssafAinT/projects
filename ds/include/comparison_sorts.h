/*****************************************************
 * comparison_sorts                                  *
 * Assaf Ainhoren                                    *
 * Reviewer: Roi Herscho                             *
 * date: 10.07.2022                                  *
 *****************************************************/
#ifndef __ILRD_OL127_128_COMPARISON_SORTS_H__
#define __ILRD_OL127_128_COMPARISON_SORTS_H__


/*
Description: bubble sort the array
Return Value: void
Time: O(n^2)
Space: O(1)
*/
void BubbleSort(int *arr, size_t arr_size);
/*
Description: sort the array by selection-sort algorithm
Return Value: void
Time: O(n^2)
Space: O(1)
*/
void SelectionSort(int *arr, size_t arr_size);
/*
Description: sort the array by insertion-sort algorithm
Return Value: void
Complexity: 
Time: O(n^2)
Space: O(1)
*/
void InsertionSort(int *arr, size_t arr_size);


#endif /* __ILRD_OL127_128_COMPARISON_SORTS_H__ */
