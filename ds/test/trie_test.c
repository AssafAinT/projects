/*****************************************************
 * trie_test                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 18.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "trie.h"


static const size_t g_digit_ascii = 48;

int ExtractIndex(void *data, void *params);
char *AsciiToBinary(char *expression);
static void TrieCreateAndDestroyTest(void);
static void TrieSizeTest(void);
static void TrieIsEmptyTest(void);
static void TrieInsertTest(void);
static void TrieRemoveTest(void);
int main(void)
{
	TrieCreateAndDestroyTest();
	TrieSizeTest();
	TrieIsEmptyTest();
	TrieInsertTest();
	TrieRemoveTest();
	return (0);
}

static void TrieCreateAndDestroyTest(void)
{
	trie_ty *new_trie = TrieCreate(2);

	TrieDestroy(new_trie);
}
static void TrieSizeTest(void)
{
	trie_ty *new_trie = TrieCreate(2);
	assert(0 == TrieSize(new_trie));
	TrieDestroy(new_trie);
}
static void TrieIsEmptyTest(void)
{
	trie_ty *new_trie = TrieCreate(2);
	assert(TRUE == TrieIsEmpty(new_trie));
	TrieDestroy(new_trie);
}

static void TrieInsertTest(void)
{
    trie_ty *new_trie = TrieCreate(2);
	trie_ty *another_trie = TrieCreate(2);
    trie_iterator_ty iter = TrieBegin(new_trie);
    trie_iterator_ty iter2 = TrieBegin(new_trie);
    trie_iterator_ty iter3  = NULL;
	trie_iterator_ty iter4 = TrieBegin(another_trie);
    int ip_path[] = {0, 1, 1, 0, 1};
    size_t i = 0;
	assert(TRUE == TrieIsEmpty(new_trie));
	assert(TRUE == TrieIsEmpty(another_trie));

	for ( ; i < 5; ++i)
	{
		iter4 = TrieInsert(another_trie, iter4,ip_path[i]);
	}
    
    iter = TrieInsert(new_trie ,iter ,0);
    iter = TrieInsert(new_trie ,iter ,0);
    iter3 = iter;
    iter = TrieInsert(new_trie ,iter ,1);
    iter = TrieInsert(new_trie ,iter ,0);
    
    iter3 = TrieInsert(new_trie ,iter3 ,0);
    iter3 = TrieInsert(new_trie ,iter3 ,0);
    
    iter2 = TrieInsert(new_trie ,iter2 ,1);
    iter2 = TrieInsert(new_trie ,iter2 ,0);
    iter2 = TrieInsert(new_trie ,iter2 ,1);
    iter2 = TrieInsert(new_trie ,iter2 ,0);
    
    assert(FALSE == TrieIsEmpty(new_trie));
	assert(10 == TrieSize(new_trie));

	iter = TrieBegin(new_trie);
	assert (NULL != TrieIterGetNext(iter)); /* 0 */
	assert (NULL != TrieIterGetNext(iter)); /* 0 */
	assert (NULL != TrieIterGetPrev(iter)); /* 1 */
	assert (NULL != TrieIterGetNext(iter)); /* 0 */
	assert (NULL != TrieIterGetNext(iter)); /* 0 */
	assert (NULL != TrieIterGetPrev(iter)); /* 0 */
	
	iter2 = TrieBegin(new_trie);
	assert (NULL != TrieIterGetPrev(iter2)); /* 1 */
	assert (NULL != TrieIterGetNext(iter2)); /* 0 */
	assert (NULL != TrieIterGetPrev(iter2)); /* 1 */
	assert (NULL != TrieIterGetNext(iter2)); /* 0 */
	printf("%ld is path size\n", TrieSize(new_trie));
	iter2 = TrieBegin(new_trie);
	iter = TrieIterGetPrev(iter);
	iter = TrieIterGetNext(iter);
	printf("is num of leafs: %d\n", TrieCountLeafs(new_trie, 2));
	TrieDeleteNode(new_trie, iter);
	printf("%ld is path size\n", TrieSize(new_trie));
	
    TrieDestroy(new_trie);
	TrieDestroy(another_trie);
}

static void TrieRemoveTest(void)
{
	trie_ty *new_trie = TrieCreate(2);	
	int ip_path[] = {0, 1, 1, 0, 1};
    size_t i = 0;
	trie_iterator_ty iter = TrieBegin(new_trie);
	assert(TRUE == TrieIsEmpty(new_trie));

	for ( ; i < 5; ++i)
	{
		iter = TrieInsert(new_trie, iter,ip_path[i]);
	}
	iter = TrieBegin(new_trie);
	iter = TrieIterGetNext(iter);
	iter = TrieIterGetPrev(iter);
	printf("%ld is path size\n", TrieSize(new_trie));
	TrieDeleteNode(new_trie, iter);
	printf("%ld is path size\n", TrieSize(new_trie));
	
	TrieDestroy(new_trie);
}

int ExtractIndex(void *data, void *params)
{
	int index_ret = 0;
	if ('\0' == *(char *)data)
	{
		return (-1);
	}
	index_ret = *(char *)data - 48;
	++*(char *)data;
	return (index_ret);


}
