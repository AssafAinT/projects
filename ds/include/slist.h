/*****************************************************
 * Slisr WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Haggai Newman                           *
 * date: 05.06.2022                                  *
 *****************************************************/
#ifndef __ILRD_OL127_128_SLINKED_LIST_H__ /* header - guard */
#define __ILRD_OL127_128_SLINKED_LIST_H__

#include <stddef.h> /* size_t */

/***************************************typdefs********************************/
typedef struct slist slist_ty;
typedef struct node *slist_iterator_ty;

typedef int (*is_match_ty)(const void *data, const void *params);
typedef int (*action_ty)(void *data, void *params);

/*******************************functions declarations*************************/

/* Description: Creating List. 
Return value: a pointer to the new created list.
			upon failure : NULL.
Complexity:
Time - O(1).
Space -O(n).*/
slist_ty *SlistCreate(void);

/* Description: Destroy List. 

Complexity:
Time - O(n).
Space -O(1).*/ 
void SlistDestroy(slist_ty *slist); 

/* Description: inserts the given data before the given iterator.

Return:
	The iterator that was inserted, or an invalide iterator if failed to insert.
	ERROR:Passing an invalide iterator whould result in undefined behavior.
Params:
	position -       the iterator to insert hte data before.
	data -           the data to insert.

Complexity:
time: O(1)
space: O(n) */
slist_iterator_ty SlistInsertBefore(slist_iterator_ty position, void *data); 

/* Description:returns an iterator to the beginning of the list
	ERROR: passing an invalid pointer would result an undefined behavior.
Complexity:
time: O(1)
space: O(1).*/
slist_iterator_ty SlistBegin(const slist_ty *slist);

/* Description:returns an iterator to the end of the list
	ERROR: passing an invalid pointer would result an undefined behavior.
Complexity:
time: O(1)
space: O(1).*/
slist_iterator_ty SlistEnd(const slist_ty *slist);


/* Description: returns the next iterator after the given iterator.
Return: The next iterator after the given iterator on success, 
 or an invalide iterator if the the given iterator is the end of the list,
Complexity:
time: O(1)
space: O(1)*/
slist_iterator_ty SlistNext(const slist_iterator_ty iterator);

/* Description: removes the given iterator and returns it's next iterator.
ERROR: Passing an invalide iterator whould result in undefined behavior.
Complexity:

time:  O(1).
space O(1). */
slist_iterator_ty SlistRemove(slist_iterator_ty iterator); 

/* Description: sets the data inside the specified iterator.

	ERROR:Passing an invalid pointer would result an undefined behavior.
Complexity:
time:  O(1).
space O(1). */
void SlistSetData(slist_iterator_ty iterator, void *data);

/* Description: retrives the data from the specified iterator.
return: The given iterator data.
	ERROR:Passing an invalid pointer would result an undefined behavior.
Complexity:
time:  O(1).
space O(1). */
void *SlistGetData(const slist_iterator_ty iterator);

/* Description:Computing the size of the list(no. of elements).
Complexity:
Time - O(n).
Space -O(1). */
size_t SlistSize(const slist_ty *slist);

/* Description: evaluate if the list is empty.
Return: 1 if the given list is empty, or 0 otherwise.

Complexity:
time:  O(1).
space O(1). */
int SlistIsEmpty(const slist_ty *slist);

/* Description: evalutes if two iterators are on the same addresses.
Return: 1 if the given iterators are the same, or 0 otherwise.
Complexity:
time:  O(1).
space O(1).*/
int SlistIterIsEqual(const slist_iterator_ty iterator1, const slist_iterator_ty iterator2);

/* Description: execution of a recived function,
for every data in the given iterators
Return: 0 for function Success, Otherwise a larger integer. 
Complexity:
Time - O(n).
Space -O(1). */
int SlistForEach(slist_iterator_ty from, slist_iterator_ty to, action_ty action_func, void *param);
 
/*Description: recives two iterators. and searcing for the param passed between
the iterators. not including the last iterator.
Return: Upon Success the iterator which has the data, otherwise the to iterator 
is returned. 

Complexity:
Time - O(n).
Space -O(1).  */
slist_iterator_ty SlistFind(slist_iterator_ty from, slist_iterator_ty to, is_match_ty match_func, void *param);

/*Description: executing a concatanation two lists together.
The function handles with releasing the src list!!

Complexity:
Time - O(1).
Space -O(n). .*/
void SlistAppend(slist_ty *dest, slist_ty *src);


/* Advanced */
/* slist_iterator_ty SlistSlice(slist_iterator_ty where, slist_iterator_ty from, slist_iterator_ty to); */


#endif /* __ILRD_OL127_128_SLINKED_LIST_H__ */
 
