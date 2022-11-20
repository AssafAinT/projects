#ifndef __ILRD_OL127_128_AVL_TREE_H__
#define __ILRD_OL127_128_AVL_TREE_H__
/*****************************************************
 * Avl                                               *
 * Assaf Ainhoren                                    *
 * Reviewer: Ofir Krisple                            *
 * date: 27.07.2022                                  *
 * Description:                                      *
 *     An AVL tree is a self-balancing               *
 *    binary search tree.                            *
 *    In an AVL tree, the heights of the             *
 *    two child subtrees of any node                 *
 *    node by at most one.                           *
 *    if at any time they differ by more             *
 *    than one, rebalancing is done.                 *
 *****************************************************/

/********************************libraries includes****************************/
#include <stddef.h> /* size_t */

typedef enum 
{
    INORDER     = 0,
    PREORDER    = 1,
    POST_ORDER  = 2
}trav_ty;

typedef enum
{
	SUCCESS = 0,
	FAIL    = 1
}status_ty;

typedef enum
{
	FALSE = 0,
	TRUE  = 1
}bool_ty;

typedef struct avl avl_ty;
/* typedef for user's compare function to manage the insert of avl      */
typedef int(*cmp_func)(const void *avl_data,
                       const void *user_data,
                       void *params);
/* typedef for user's action function to manipulate data in the avl:
	NOTE: any function that could change the balance of the tree would
	result undefined behaviour                                         */
typedef int(*action_func)(void *data, void *params);

/*****************************************************
* Description: Create AVL                            *
* Params: cmp - compare func for sort elements       *
*          params- user params                       *
* return value: a ptr to the new AVL                 *
			Upon failure: NULL                       *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1)                                       *
******************************************************/
avl_ty *AvlCreate(cmp_func cmp, void *params);
/*****************************************************
* Description: Destroy AVL                           *
* Params: avl - a ptr to the AVL                     *
* return value: void                                 *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(n)                                       *
******************************************************/
void AvlDestroy(avl_ty *avl);
/*****************************************************
* Description: Insert Element to the Avl             *
* Params: avl - a ptr to the AVL                     *
* 		  data - the data to insert                  *
* return value: SUCCESS if the element inserted      *
* 			   FAIL otherwise                        *
* 	   the tree does not support duplicates          *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space - O(logn)                                       *
******************************************************/
status_ty AvlInsert(avl_ty *avl, void *data);
/*****************************************************
* Description: Remove  Element from the Avl          *
* Params: avl - a ptr to the AVL                     *
* 		  data - the data to remove from the tree    *
* return value: void                                 *
* sending invalid ptr would result ud behavior       *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space - O(logn)                                       *
******************************************************/
void AvlRemove(avl_ty *avl, void *data);
/*****************************************************
* Description: Computing the height of the tree      *
* Params: avl - a ptr to the AVL                     *
* return value: longest path from root -no. of arches*
* sending invalid ptr would result ud behavior       *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1)                                       *
******************************************************/
long AvlHeight(const avl_ty *avl);
/*****************************************************
* Description: computing the tree size               *
* Params: avl - a ptr to the AVL                     *
* return value: the no. of element in the avl        *
* sending invalid ptr would result ud behavior       *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(n)                                       *
******************************************************/
size_t AvlSize(const avl_ty *avl);
/*****************************************************
* Description: computing if the tree is empty        *
* Params: avl - a ptr to the AVL                     *
* return value: TRUE - if empty                      *
*              FALSE - otherwise                     *
* sending invalid ptr would result ud behavior       *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1)                                       *
******************************************************/
bool_ty AvlIsEmpty(const avl_ty *avl);
/*****************************************************
* Description: Find Element in the Avl               *
* Params: avl - a ptr to the AVL                     *
* 		  data - the data to find                    *
* return value: SUCCESS if the element was found     *
* 			   FAIL otherwise                        *
* sending invalid ptr would result ud behavior       *
* Complexity:                                        *
* Time - O(logn).                                    *
* Space - O(logn)                                    *
******************************************************/
status_ty AvlFind(const avl_ty *avl, void *data);
/*****************************************************
* Description:Executing certain function over the avl*
* Params: avl - a ptr to the AVL                     *
* 	action - the function to be executed             *
* 	params - param to send to the function           *
* 	trav -the type of traverse the function executes *
* 	INORDER, PREORDER, POST_ORDER                    *
* return : SUCCESS if function finished normally     *
* 			   FAIL otherwise                        *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(n)                                       *
******************************************************/
status_ty AvlForEach(avl_ty *avl, action_func action,
						 void *params, trav_ty trav);
#ifndef NDEBUG
/*****************************************************
* Description:printing the tree (ONLY IN DEBUG MODE) *
* Params: avl - a ptr to the AVL                     *
* 			   FAIL otherwise                        *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(1)                                       *
******************************************************/
void TreePrint(avl_ty *avl);
#endif 
#endif /* __ILRD_OL127_128_AVLTREE_H__ */
