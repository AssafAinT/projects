#ifndef __ILRD_127_128_TRIE_H__
#define __ILRD_127_128_TRIE_H__

#include "utils.h"

typedef struct trie trie_ty; 
typedef struct node *trie_iterator_ty;
typedef struct node node_ty;

struct node
{
	bool_ty is_full;
	node_ty *parent;
	node_ty *children[1];	
};

/****************************************************
* description: Creates a new Trie                   *
* params: num_of_children - maximum width           *
*        of every level                             *
* Return: Upon successful creation,                 *
*            a ptr to the new Trie                  *
*         Otherwise NULL                            *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
trie_ty *TrieCreate(size_t num_of_children);
/****************************************************
* description: destroy Trie                         *
* params:  trie - Trie to destroy                   *
* Return:         void                              *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
void TrieDestroy(trie_ty *trie);
/****************************************************
* description: creating path in Trie                *                                           
* params:                                           *
*	   trie - the trie to insert path               *
*      position - the current position in trie path *
*      index - the index of the path to be created  *
* Return: position of next place in path            *                                          
* Complexity:                                       *
   Time: O(logn)                                    *
   Space: O(1)                                      *
****************************************************/
trie_iterator_ty TrieInsert(trie_ty *trie,
                           trie_iterator_ty position,
						   size_t index);
/****************************************************
* description: counting nodes in the trie           *                                           
* params:                                           *
*	   trie - the trie to size                       *
* Return: number of nodes in the trie               *                                       
* Complexity:                                       *
   Time: O(logn)                                    *
   Space: O(1)                                      *
****************************************************/
size_t TrieSize(trie_ty *trie);
/****************************************************
* Check if current position is full                 *
* params:  position - position to check             *
* Return:   if full - TRUE                          *
*           OTHERWISE - FALSE                       *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
bool_ty PathIsFull(trie_iterator_ty position);
/****************************************************
* Check if trie is empty                            *
* params: trie -  trie to check                     *
* Return:   if empty - TRUE                         *
*           OTHERWISE - FALSE                       *
* Complexity:                                       *
   Time: O(logn)                                    *
   Space: O(1)                                      *
****************************************************/
bool_ty TrieIsEmpty(trie_ty *trie);
/****************************************************
* Check if current position leaf                    *
* params:  position - position to check             *
* Return:   if leaf - TRUE                          *
*           OTHERWISE - FALSE                       *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
bool_ty IsLeaf(trie_iterator_ty iter, size_t num_of_children);
/****************************************************
* count leafs in the trie                           *
* params:  trie - trie to check leafs               *
* num_of_children -num_of_children in trie node     *
* Return:   number of leafs                         *
* Complexity:                                       *
   Time: O(logn)                                    *
   Space: O(logn)                                   *
****************************************************/
size_t TrieCountLeafs(trie_ty *trie, size_t num_of_children);
/****************************************************
* retrive the beginning of the trie                 *
* params:  trie - trie to get beginning of          *
* Return:   beginning of the trie                   *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
trie_iterator_ty TrieBegin(trie_ty *trie);
/****************************************************
* retrive the parent of current node in the trie    *
* params:  position - the position to get parent    *
* Return:   if there is parent - iterator to parent *
*           otherwise - NULL                        *
*      sending invalid ptr would result ud behavior *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
trie_iterator_ty TrieIterGetParent(trie_iterator_ty position);
/****************************************************
* retrive the children of current node in the trie  *
* params:  position - the position to get parent    *
* params:  index - children index                   *
* Return:   if there is children - iter to children *
*           otherwise - NULL                        *
*      sending invalid ptr would result ud behavior *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
trie_iterator_ty TrieIterGetChildrenByIndex(trie_iterator_ty position, size_t index);
/****************************************************
* mark the current iterator as full                 *
* params:     position - position to set full       *
* Return:                                           *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
void TrieSetIsFullOnPath(trie_iterator_ty position);
/****************************************************
* mark the current iterator as not full             *
* params:     position - position to unset full     *
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
void TrieUnsetIsFullOnPath(trie_iterator_ty position);

 
#endif /* __ILRD_127_128_TRIE_H__ */
