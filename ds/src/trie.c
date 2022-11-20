/*****************************************************
 * trie                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 7.08.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <stdlib.h>/* malloc, free */

#include "trie.h"
static const size_t g_root_size = 1;

struct trie
{
	node_ty *root;	
	void *params;
	size_t num_of_children;
	action_func action_func;
};


static node_ty *CreateNewNode(size_t number_of_childrens,
                              node_ty *node_parent, bool_ty is_fool_status);

static node_ty *TrieGetRoot(trie_ty *trie); 

static size_t GetNumOfChild(trie_ty *trie);

static void CountLeafsRecursive(trie_iterator_ty iter,
                            size_t num_of_children,
                            size_t *counter);

static void DestroyRecursive(node_ty *node, size_t number_of_children);

static void TrieRecursiveSize(node_ty *node,
                              size_t num_of_child,
							  size_t *o_counter);

trie_ty *TrieCreate(size_t num_of_children)
{
	trie_ty *new_trie = (trie_ty *)malloc(sizeof(trie_ty));
	if (NULL == new_trie)
	{
		return (NULL);
	}
	
	new_trie->num_of_children = num_of_children;

	new_trie->root = CreateNewNode(num_of_children, NULL, FALSE);
	if (NULL == new_trie->root)
	{
		free(new_trie);
		new_trie = NULL;	
		return (NULL);
	}

	return (new_trie);
}

void TrieDestroy(trie_ty *trie)
{
	assert(NULL != trie);

	DestroyRecursive(TrieGetRoot(trie), trie->num_of_children);
	
	free(trie);
	trie = NULL;
}

static void DestroyRecursive(node_ty *node, size_t number_of_children)
{
	size_t i = 0;

	if (NULL == node)
	{
		return;
	}

    for ( ; i < number_of_children ; ++i )
    {
		if (NULL != node->children[i])
		{
			DestroyRecursive(node->children[i], number_of_children);
		}
    }
	/* util function */
    free(node);
	node = NULL;
}
size_t TrieCountLeafs(trie_ty *trie, size_t num_of_children)
{
    size_t counter = 0;
    trie_iterator_ty iter = TrieBegin(trie);
	
	assert(NULL != trie);
	
    CountLeafsRecursive(iter, num_of_children, &counter);
    
	return (counter - g_root_size);
}
static void CountLeafsRecursive(trie_iterator_ty iter,
                                size_t num_of_children,
								size_t *counter)
{
	size_t i = 0;
	if (NULL == iter)
	{
		return ;
	}
	/* to change to count by depth and isfull flag */
    for(i = 0; i < num_of_children; ++i)
    {     
        if (NULL != TrieIterGetChildrenByIndex(iter, i))
        {
            CountLeafsRecursive(TrieIterGetChildrenByIndex(iter, i),
                                 num_of_children, counter);
        }
    }    
    if (IsLeaf(iter, num_of_children))
    {
        *counter += 1;
    }
}
trie_iterator_ty TrieInsert(trie_ty *trie,
                            trie_iterator_ty position,
							size_t index)

{	
	assert(NULL != trie);
	assert(NULL != position);

	if (NULL != TrieIterGetChildrenByIndex(position, index))
	{
		return (position);
	}
	position->children[index] = CreateNewNode(trie->num_of_children,
	                                          position,
										 	  FALSE);

	if (NULL == TrieIterGetChildrenByIndex(position, index))
	{
		return (NULL);
	}
	return (TrieIterGetChildrenByIndex(position, index));

}
bool_ty PathIsFull(trie_iterator_ty position)
{
	assert(NULL != position);
	
	return (TRUE == position->is_full);
}

bool_ty TrieIsEmpty(trie_ty *trie)
{	
	size_t i = 0;
	bool_ty is_empty = TRUE;
	size_t num_child = 0;

	assert(NULL != trie);

	num_child = trie->num_of_children;

	for ( ; TRUE == is_empty && 
	        i < num_child ; ++i)
	{
		if (NULL != trie->root->children[i])
		{
			is_empty = FALSE;
		}
	}

	return (is_empty);
}

size_t TrieSize(trie_ty *trie)
{
	size_t counter = 0;

	assert(NULL != trie);
		
	TrieRecursiveSize(TrieGetRoot(trie),GetNumOfChild(trie), &counter);

	return (counter);
}

static void TrieRecursiveSize(node_ty *node,
                              size_t num_of_child,
							  size_t *o_counter)
{
	size_t i = 0;
	*o_counter +=1;

	if (NULL == node)
	{
		return ;
	}

    for ( ; i < num_of_child ; ++i )
    {
		if (NULL != node->children[i])
		{
			TrieRecursiveSize(node->children[i], num_of_child,
			                     o_counter);
		}
    }
	
}

trie_iterator_ty TrieBegin(trie_ty *trie)
{
	assert(NULL != trie);
	
	return(TrieGetRoot(trie));
}

trie_iterator_ty TrieIterGetParent(trie_iterator_ty position)
{
	assert(NULL != position);

	return (position->parent);
}

trie_iterator_ty TrieIterGetChildrenByIndex(trie_iterator_ty position,
                                            size_t index)
{
	assert(NULL != position);

	return (position->children[index]);
}

bool_ty IsLeaf(trie_iterator_ty iter, size_t num_of_children)
{
    bool_ty is_leaf = TRUE;
    size_t i = 0;

    assert(NULL!= iter);

    for(i = 0; i < num_of_children && is_leaf; ++i)
    {
        if (NULL != TrieIterGetChildrenByIndex(iter, i))
        {
            is_leaf = FALSE;
        }
    } 

    return (is_leaf);
}

void TrieSetIsFullOnPath(trie_iterator_ty position)
{
	assert(NULL != position);

	position->is_full = TRUE;
}

void TrieUnsetIsFullOnPath(trie_iterator_ty position)
{
	assert(NULL != position);

	position->is_full = FALSE;
}

static node_ty *CreateNewNode(size_t number_of_childrens,
                              node_ty *node_parent,
							   bool_ty is_fool_status)
{
	size_t i = 0;
	size_t corrected_size = offsetof(node_ty, children) + 
	                       sizeof(node_ty *) * number_of_childrens;
	node_ty *ret = (node_ty *)malloc(corrected_size);
	if (NULL == ret)
	{
		return (NULL);
	}

	ret->parent = node_parent;
	ret->is_full = is_fool_status; 
	
	for ( ; i < number_of_childrens ; ++i)
	{
		ret->children[i] = NULL;
	}
	
	return (ret);
}
static size_t GetNumOfChild(trie_ty *trie)
{
	return (trie->num_of_children);
}
static node_ty *TrieGetRoot(trie_ty *trie)
{
	return (trie->root);
}
