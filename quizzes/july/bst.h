/*****************************************************
 * Binary_Search_Tree                                *
 * Assaf Ainhoren                                    *
 * Reviewer: Ahron Cohen                             *
 * date: 19.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#ifndef __ILRD_OL127_128_BST_H__
#define __ILRD_OL127_128_BST_H__

#include <stddef.h> /* size_t */



typedef struct bst bst_ty;
typedef struct node *bst_iterator_ty;

typedef int(*cmp_func)(const void *bst_data,
                       const void *user_data,
                       void *params);
                       
typedef int(*action_func)(void *data, void *params);

/*****************************************************
* Description: Creating the BST                      *
* PARARMS:                                           *
* 		 cmp_func - function pointer to a compare    *
*        function to order the three by.             *
*        void params - user parsms                   *
* Return value: The Pointer to the BST               *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
bst_ty *BstCreate(cmp_func cmp, void *params);
/*****************************************************
* Description: Destroying the BST                    *
* PARARMS:                                           *
* 		 bst - the bst to destroy                    *
*			sending invalid bst/pointer would cuase  *
*           UD behaviour                             *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void BstDestroy(bst_ty *bst);
/*****************************************************
* Description: Insert data to the BST                *
* PARARMS:                                           *
* 		 bst - the bst to insert to                  *
*		 data - the data to insert                   *
* Return value: Iterator to the inserted data        *
*			upon failure : NULL                      *
*		Sending Duplicates would result ud behavior  *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space -O(1).                                       *
*****************************************************/
bst_iterator_ty BstInsert(bst_ty *bst, void *data);
/*****************************************************
* Description: Remove the data From the BST          *
* PARARMS:                                           *
* 		 position - iterator to the data to remove   *
* Return value: the data that was removed            *
*			upon failure : NULL                      *
*		Sending invalid ptr would result ud behavior *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space -O(1).                                       *
*****************************************************/
void *BstRemove(bst_iterator_ty position);
/*****************************************************
* Description: finds the data in the BST             *
* PARARMS:                                           *
* 		 bst - bst to search in                      *
*        data - data to find                         *
* Return value: iterator to the data that was found  *
*			upon failure : NULL                      *
*		Sending invalid ptr would result ud behavior *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space -O(1).                                       *
*****************************************************/
bst_iterator_ty BstFind(const bst_ty *bst, void *data);
/*****************************************************
* Description: finds the smallest data in the BST    *
* PARARMS:                                           *
* 		 bst - bst to search in                      *
* Return value: iterator to the smallest data        *
*			upon failure : NULL                      *
*		Sending invalid ptr would result ud behavior *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space -O(1).                                       *
*****************************************************/
bst_iterator_ty BstBegin(const bst_ty *bst);
/*****************************************************
* Description: finds the end of the BST              *
* PARARMS:                                           *
* 		 bst - bst to search the end in              *
* Return value: end of the BST                       *
*			upon failure : NULL                      *
*		Sending invalid ptr would result ud behavior *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
bst_iterator_ty BstEnd(const bst_ty *bst);
/*******************************************************
* Description:Find closest smaller data from the given *
* PARARMS:                                             *
* 		 iterator - the iterator to search from        *
* Return value: closest smaller data                   *
*			upon failure : NULL                        *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(logn).                                      *
* Space -O(1).                                         *
********************************************************/
bst_iterator_ty BstGetPrev(bst_iterator_ty iterator);
/*******************************************************
* Description:Find closest bigger data from the given  *
* PARARMS:                                             *
* 		 iterator - the iterator to search from        *
* Return value: closest bigger                         *
*			upon failure : NULL                        *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(logn).                                      *
* Space -O(1).                                         *
********************************************************/
bst_iterator_ty BstGetNext(bst_iterator_ty iterator);
/*******************************************************
* Description:Retriving the data from the iterator     *
* PARARMS:                                             *
* 		 iterator - the iterator to retrive the data   *
* Return value: the data                               *
*			upon failure : NULL                        *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(1).                                         *
* Space -O(1).                                         *
********************************************************/
void *BstGetData(bst_iterator_ty iterator);
/*******************************************************
* Description:Computing the size of the bst            *
* PARARMS:                                             *
* 		 bst - the bst to size                         *
* Return value: the number of data in the three        *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(n).                                         *
* Space -O(1).                                         *
********************************************************/
size_t BstSize(const bst_ty *bst);
/*******************************************************
* Description:Computing if the bst is empty            *
* PARARMS:                                             *
* 		 bst - the bst to check emptiness              *
* Return value: Upon Success: 1                        *
*			upon failure : 0                           *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(n).                                         *
* Space -O(1).                                         *
********************************************************/
int BstIsEmpty(const bst_ty *bst);
/*******************************************************
* Description:Computing if two iterators are the same  *
* PARARMS:                                             *
* 		 iterator 1,2 - the evaluated iterators        *
* Return value: Upon Success: 1                        *
*			upon failure : 0                           *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(1).                                         *
* Space -O(1).                                         *
********************************************************/
int BstIterIsEqual(bst_iterator_ty iterator1,
                   bst_iterator_ty iterator2);
/*******************************************************
* Description:executing a user function over the data  *
* PARARMS:                                             *
* 	 iterator from, to - range of data to execute task *
*    action_func - the action function                 *
*    params - user params                              *
* Return value: Upon Success: 1                        *
*			upon failure : 0                           *
*		Sending invalid ptr would result ud behavior   *
* Complexity:                                          *
* Time - O(n).                                         *
* Space -O(1).                                         *
********************************************************/
int BstForEach(bst_iterator_ty from,
               bst_iterator_ty to,
               action_func action,
               void *params);

#endif /* __ILRD_OL127_128_BST_H__ */
