/*****************************************************
 * heap                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayam Sheraizin                        *
 * date: 31.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#ifndef __ILRD_OL127_128_HEAP_H__
#define __ILRD_OL127_128_HEAP_H__

#include <stddef.h> /* size_t */
#include "utils.h" /* eitan's util */

typedef struct heap heap_ty;

/*****************************************************
* Description: Creating the Heap                     *
* PARARMS:                                           *
* 		 cmp_func - function pointer to a compare    *
*        function to order the three by.             *
*        void params - user parsms                   *
* Return value: The Pointer to the Heap              *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
heap_ty *HeapCreate(cmp_func cmp, void *params);
/*****************************************************
* Description: Destroying the Heap                   *
* PARARMS:                                           *
* 		 bst - the bst to destroy                    *
*			sending invalid bst/pointer would cuase  *
*           UD behaviour                             *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void HeapDestroy(heap_ty *heap);
/*****************************************************
* Description: Push Data to the Heap                 *
* PARARMS:                                           *
* 		 heap - the bst to insert to                 *
*		 data - the data to insert                   *
* Return value: SUCCESS                              *
*			upon failure : FAIL                      *
* Complexity:                                        *
* Time - avg. O(logn) worst: O(n)                    *
* Space -O(1).                                       *
*****************************************************/
status_ty HeapPush(heap_ty *heap, void *data);
/*****************************************************
* Description: Pop Min/Max Element from the Heap     *
* PARARMS:                                           *
* 		 heap - the bst to insert to                 *
* Return value: void                                 *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space -O(1).                                       *
*****************************************************/
void HeapPop(heap_ty *heap);
/*****************************************************
* Description: Get top Data from the Heap            *
* PARARMS:                                           *
* 		 heap - the bst to peek from                 *
*		 data - the data to pop                      *
* Return value: void                                 *
* Complexity:                                        *
* Time - O(1).                                    *
* Space -O(1).                                       *
*****************************************************/
void *HeapPeek(const heap_ty *heap);
/*****************************************************
* Description: Removes Certain element from heap     *
* PARARMS:                                           *
* 		 heap - the bst to remove from               *
*		 data - the data to pop                      *
*		 is_match - user match function              *
* Return value: upon removal - SUCCESS               *
*              incase data not found - FAIL          *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void *HeapRemove(heap_ty *heap, const void *data,
                     is_match_func is_match);
/*****************************************************
* Description: count num of elements in heap         *
* PARARMS:                                           *
* 		 heap - the bst to count                     *
* Return value: the deleted data                     *
* 			FAILURE: NULL                            *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
size_t HeapSize(const heap_ty *heap);
/*****************************************************
* Description: check if heap is empty                *
* PARARMS:                                           *
* 		 heap - the bst to check                     *
* Return value: If Empty - TRUE                      *
*               otherwise - FALSE                    *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
bool_ty HeapIsEmpty(const heap_ty *heap);

/*advanced*/
heap_ty *HeapHeapify(void *src_array, size_t array_size, cmp_func compare,
                    const void *params);

void PrintHeap(heap_ty *heap);

#endif /* __ILRD_OL127_128_HEAP_H__ */
