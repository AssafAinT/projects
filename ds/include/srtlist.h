#ifndef __ILRD_OL127_128_SORTED_LINKED_LIST_H__
#define __ILRD_OL127_128_SORTED_LINKED_LIST_H__
/*****************************************************
 * Sorted list                                       *
 * Assaf Ainhoren                                    *
 * Reviewer: Avia Avikasis                           *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include "dlist.h" /* dlist lib */

typedef int (*compare_data_func)(void *data1, void *data2 , void *params);
typedef struct srtlist srtlist_ty;
typedef struct srtlist_iterator srtlist_iterator_ty;

struct srtlist_iterator 
{
    dlist_iterator_ty dlist_iterator;
#ifndef NDEBUG
    dlist_ty *srtlist;
#endif
};
/****************************Function Declaration******************************/
/*****************************************************
* Description: Creating Sorted-List.                 *
*Params: sorting func, param                         *
* Return value: a pointer to the sorted-list.        *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(n).                                       *
*****************************************************/
srtlist_ty *SrtlistCreate(compare_data_func sort, void *param);

/*****************************************************
* Description: Destroying Sorted-List.               *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void SrtlistDestroy(srtlist_ty *srtlist); 
/*****************************************************
* Description: Inserting a data and sorting by       *
* the desired sorting method                         *
* Return value: A pointer to the inserted element.   *
*		upon failure : A pointer to the end of list. *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
srtlist_iterator_ty SrtlistInsert(srtlist_ty *srtlist, void *data);
/************************************************************
* Description: Removing a the data poined by the iterator   *
* Return value: A pointer to the Next iterator.             *
* Complexity:                                               *
* Time - O(n^2).                                              *
* Space -O(1).                                              *
************************************************************/
srtlist_iterator_ty SrtlistRemove(srtlist_iterator_ty iterator); 
/*************************************************************************
* Description:returns an iterator to the beginning of the list           *
	ERROR: passing an invalid pointer would result an undefined behavior.*
* Complexity:                                                            *
* time: O(1)                                                             *
* space: O(1).                                                           *
**************************************************************************/
srtlist_iterator_ty SrtlistBegin(const srtlist_ty *srtlist); 
/*************************************************************************
* Description:returns an iterator to the end of the list           *
	ERROR: passing an invalid pointer would result an undefined behavior.*
* Complexity:                                                            *
* time: O(1)                                                             *
* space: O(1).                                                           *
**************************************************************************/
srtlist_iterator_ty SrtlistEnd(const srtlist_ty *srtlist);
/*************************************************************************
 Description: returns the next iterator after the given iterator.        *
Return: The next iterator after the given iterator on success,           *
or an invalide iterator if the the given iterator is the end of the list,*
Complexity:                                                              *
time: O(1)                                                               *
space: O(1)                                                              *
**************************************************************************/
srtlist_iterator_ty SrtlistNext(srtlist_iterator_ty iterator);
/*************************************************************************
 Description: returns the previous iterator from given iterator.         *
Return: The next iterator after the given iterator on success,           *
 or an invalide iterator if the the given iterator is the beginning,     *
Complexity:                                                              *
time: O(1)                                                               *
space: O(1)                                                              *
**************************************************************************/
srtlist_iterator_ty SrtlistPrev(srtlist_iterator_ty iterator);
/*************************************************************************
 Description: retrives the data from a specified iterator.               *
                                                                         *
	ERROR:Passing an invalid pointer would result an undefined behavior. *
Complexity:                                                              *
time:  O(1).                                                             *
space O(1).                                                              *
**************************************************************************/
void *SrtlistGetData(srtlist_iterator_ty iterator);
/**************************************************************
 Description:Computing the size of the list(no. of elements). *
Complexity:                                                   *
Time - O(n).                                                  *
Space -O(1).                                                  *
***************************************************************/
size_t SrtlistSize(const srtlist_ty *srtlist);
/***************************************************************
 Description: evaluate if the sorted-list is empty.            *
Return: 1 if the given list is empty, or 0 otherwise.          *
                                                               *
Complexity:                                                    *
time:  O(1).                                                   *
space O(1).                                                    *
****************************************************************/
int SrtlistIsEmpty(const srtlist_ty *srtlist);
/************************************************************************
 Description: evalutes if two iterators are on the same addresses.      *
Return: 1 if the given iterators are the same, or 0 otherwise.          *
Complexity:                                                             *
time:  O(1).                                                            *
space O(1).                                                             *
************************************************************************/
int SrtlistIterIsEqual(srtlist_iterator_ty iterator1, 
                      srtlist_iterator_ty iterator2);

/**************************************************************************
 Description: execution of a recived function,                            *
for every data in the given iterators                                     *
Return: 0 for function Success, Otherwise a larger integer.               *
Sending iterators from different list will result in undefined behavior   *
Complexity:                                                               *
Time - O(n).                                                              *
Space -O(1).                                                              *
***************************************************************************/
int SrtlistForEach(srtlist_iterator_ty from,
                   srtlist_iterator_ty to, 
                   action_ty action_func,
                   void *param);
                   
/*******************************************************************************
Description: recives two iterators. and searcing for the param passed between  *
the iterators. not including the last iterator.                                *
Return: Upon Success the iterator which has the data,                          *
otherwise the to iterator                                                      * 
Sending iterators from different list will result in undefined behavior        *
is returned.                                                                   *
                                                                               *
Complexity:                                                                    *
Time - O(n).                                                                   *
Space -O(1).                                                                   *
*******************************************************************************/
srtlist_iterator_ty SrtlistFindIf(srtlist_iterator_ty from, 
                                  srtlist_iterator_ty to,
                                  is_match_ty match_func,
                                  void *param);

/**************************************************************************
* runs from 'from' iterator to 'to' iterator and finds                    *
* iterator with the given data, according to sort function                *
* PARAMS:                                                                 *
* srtlist_iterator_ty from  - start from this iterator                    *
* srtlist_iterator_ty to	 - up tp this iterator                        *
* const srtlist_ty *srtlist - to take sort func from                      *
* void *data_to_find        - data to find                                *
* RETURN:                                                                 *
* srtlist_iterator_ty found iterator on success, end iterator on fail     *
*                                                                         *
* COMPLEXITY:                                                             *
* time: O(n)                                                              *
* space: O(n)                                                             *
***************************************************************************/
srtlist_iterator_ty SrtlistFind(const srtlist_ty *srtlist, 
                               srtlist_iterator_ty from,
                               srtlist_iterator_ty to, 
                               void *data_to_find);
                               
/**************************************************************************
* merges src sorted list to dest list, and free src                       *
* PARAMS:                                                                 *
* srtlist_ty *dest_list - to merge                                        *
* srtlist_ty *src_list - to merge                                         *
* RETURN:                                                                 *
* srtlist_iterator_ty found iterator on success, end iterator on fail     *
* COMPLEXITY:                                                             *
* time: O(n)                                                              *
* space: O(n)                                                             *
***************************************************************************/
void SrtlistMerge(srtlist_ty *dest_list , srtlist_ty *src_list);

#endif /* __ILRD_OL127_128_SORTED_LINKED_LIST_H__ */ 
