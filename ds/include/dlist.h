/*****************************************************
 * dlist WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayan Sheraizin                        *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#ifndef __ILRD_OL127_128_DLINKED_LIST_H__
#define __ILRD_OL127_128_DLINKED_LIST_H__

#include <stddef.h> /* size_t */

/********************************Struct declarations***************************/
typedef struct dlist dlist_ty;
typedef struct node *dlist_iterator_ty;

typedef int (*is_match_ty)(const void *data, void *params);
typedef int (*action_ty)(void *data, void *params);

/********************************function declarations*************************/

/*****************************************************
* Description: Creating Doubly-linked-List.          *
* Return value: a pointer to the new created list.   *
*			upon failure : NULL.                     *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
dlist_ty *DlistCreate(void);

/***************************************************** 
* Description: Destroy List.                         *
                                                     *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
******************************************************/ 
void DlistDestroy(dlist_ty *dlist); 

/***************************************************************************** 
* Description: inserts the given data before the given iterator.             *
* Return:                                                                    *
* 	A new iterator points to the given data.                                 *
* 	ERROR:Passing an invalide iterator whould result in undefined behavior.  *
* Params:                                                                    *
* 	position -       the iterator to insert hte data before.                 *
* 	data -           the data to insert.                                     *
                                                                             *
* Complexity:                                                                *
* time: O(1)                                                                 *
* space: O(n)                                                                *
******************************************************************************/
dlist_iterator_ty DlistInsertBefore(dlist_iterator_ty position, void *data);

/*************************************************************************
* Description: removes the given iterator and returns it's next iterator.*
* ERROR:Passing an invalide iterator whould result in undefined behavior.*
*Complexity:                                                             *
*                                                                        *
*time:  O(1).                                                            *
*space O(1).                                                             *
**************************************************************************/ 
dlist_iterator_ty DlistRemove(dlist_iterator_ty iterator); 

/*************************************************************************
* Description:returns an iterator to the beginning of the list           *
	ERROR: passing an invalid pointer would result an undefined behavior.*
* Complexity:                                                            *
* time: O(1)                                                             *
* space: O(1).                                                           *
**************************************************************************/
dlist_iterator_ty DlistBegin(const dlist_ty *dlist); 

/*************************************************************************
* Description:returns an iterator to the end of the list                 *
* 	ERROR: passing an invalid pointer would result an undefined behavior.*
* Complexity:                                                            *
* time: O(1)                                                             *
* space: O(1).                                                           *
**************************************************************************/
dlist_iterator_ty DlistEnd(const dlist_ty *dlist); 

/*************************************************************************
 Description: returns the next iterator after the given iterator.        *
Return: The next iterator after the given iterator on success,           *
or an invalide iterator if the the given iterator is the end of the list,*
Complexity:                                                              *
time: O(1)                                                               *
space: O(1)                                                              *
**************************************************************************/
dlist_iterator_ty DlistNext(dlist_iterator_ty iterator);

/*************************************************************************
 Description: returns the previous iterator from given iterator.         *
Return: The next iterator after the given iterator on success,           *
 or an invalide iterator if the the given iterator is the beginning,     *
Complexity:                                                              *
time: O(1)                                                               *
space: O(1)                                                              *
**************************************************************************/
dlist_iterator_ty DlistPrev(dlist_iterator_ty iterator);

/*************************************************************************
Description: sets the data inside the specified iterator.                *
                                                                         *
	ERROR:Passing an invalid pointer would result an undefined behavior. *
Complexity:                                                              *
time:  O(1).                                                             *
space O(1).                                                              *
**************************************************************************/
void DlistSetData(dlist_iterator_ty iterator, const void *data);

/*************************************************************************
 Description: retrives the data from a specified iterator.               *
                                                                         *
	ERROR:Passing an invalid pointer would result an undefined behavior. *
Complexity:                                                              *
time:  O(1).                                                             *
space O(1).                                                              *
**************************************************************************/
void *DlistGetData(dlist_iterator_ty iterator);

/**************************************************************
 Description:Computing the size of the list(no. of elements). *
Complexity:                                                   *
Time - O(n).                                                  *
Space -O(1).                                                  *
***************************************************************/
size_t DlistSize(const dlist_ty *dlist);

/***************************************************************
 Description: evaluate if the list is empty.                   *
Return: 1 if the given list is empty, or 0 otherwise.          *
                                                               *
Complexity:                                                    *
time:  O(1).                                                   *
space O(1).                                                    *
****************************************************************/
int DlistIsEmpty(const dlist_ty *dlist);

/*******************************************************************
 Description: evalutes if two iterators are on the same addresses. *
Return: 1 if the given iterators are the same, or 0 otherwise.     *
Complexity:                                                        *
time:  O(1).                                                       *
space O(1).                                                        *
********************************************************************/
int DlistIterIsEqual(dlist_iterator_ty iterator1, dlist_iterator_ty iterator2);

/**************************************************************************
 Description: execution of a recived function,                            *
for every data in the given iterators                                     *
Return: 0 for function Success, Otherwise a larger integer.               *
Complexity:                                                               *
Time - O(n).                                                              *
Space -O(1).                                                              *
***************************************************************************/
int DlistForEach(dlist_iterator_ty from, dlist_iterator_ty to, action_ty action_func, void *param);

/*******************************************************************************
Description: recives two iterators. and searcing for the param passed between  *
the iterators. not including the last iterator.                                *
Return: Upon Success the iterator which has the data,                          *
otherwise the to iterator                                                      * 
is returned.                                                                   *
                                                                               *
Complexity:                                                                    *
Time - O(n).                                                                   *
Space -O(1).                                                                   *
*******************************************************************************/
dlist_iterator_ty DlistFind(dlist_iterator_ty from,
                            dlist_iterator_ty to,
                            is_match_ty match_func,
                            void *param);
/*************************************************************************
* Description: Computing if a given data is found between the iterators  *
* and putting the desired data inside a new list(dest).                  *
* Return:                                                                *
* 	Upon success a newly list is created with the desired data inside.   *
* 	in case of a failure the dest list won't be changed.                 *
                                                                         *
* Params:                                                                *
	from iterator -       the iterator to start matching from            *
	to iterator -         the iterator which stops the matching          *
	dest list-            the list in which the elements will be stored. *
	match_func            the function that will compute for a match.    *
	data -           the data to insert.                                 *
                                                                         *
* Complexity:                                                            *
* Time - O(n).                                                           *
* Space -O(1).                                                           *
**************************************************************************/
int DlistMultiFind(dlist_iterator_ty from,
                  dlist_iterator_ty to,
                  dlist_ty *dest_list,
                  is_match_ty match_func,
                  void *param);

/**********************************************************************
* Description: adding elements before where iterator,                 *
* in the boundary of from till to.                                    *
                                                                      *
                                                                      *
Params:                                                               *
	from iterator -       the iterator to start  from                 *
	to iterator -         the iterator which stops the splice         *
	where iterator -------the iterator that retrives the elements.    *
	                                                                  *
Complexity:                                                           *
Time - O(1).                                                          *
Space -O(n).                                                          *
**********************************************************************/ 
void DlistSplice(dlist_iterator_ty where,
                dlist_iterator_ty from,
                dlist_iterator_ty to);

#endif /* __ILRD_OL127_128_DLINKED_LIST_H__ */
