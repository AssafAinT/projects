/*****************************************************
 * Binary_Search_Tree                                *
 * Assaf Ainhoren                                    *
 * Reviewer: Ahron Cohen                             *
 * date: 19.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "bst.h"

#define FOUND_POSITION 0
typedef struct node node_ty;

typedef enum 
{
	NADA = -1,
	LEFT,
	RIGHT,
	CHILDREN_NUM
} bst_params_ty;


struct bst
{
    node_ty *dummy_root; 
    cmp_func cmp;
    void *params;
};

struct node
{
    void *data;
    node_ty *children[CHILDREN_NUM];
    node_ty *parent;
};


static node_ty *CreateNewNode(void *data, node_ty *left,
                           node_ty *right, node_ty *parent);
static node_ty *BstGetRootNode(bst_ty *bst);

static node_ty *BstGetParent(node_ty *node);

static int FindInsertPosition(bst_iterator_ty *runner,
						      bst_iterator_ty *parent_keeper,
						      bst_ty *bst,
						      int which_child,
						      void *data);

static node_ty *BstGetChildren(bst_iterator_ty iterator, int which_child);

static int IsIterRightChildren(bst_iterator_ty iterator);

static int IsIterHaveRIghtChildren(bst_iterator_ty iterator);

static bst_iterator_ty GetLeftLeaf(bst_iterator_ty iterator);

static int IsThereTwoChildren(bst_iterator_ty iterator);

static int IsThereOneChildren(bst_iterator_ty iterator);

static void SwapNodes(bst_iterator_ty iterator, bst_iterator_ty iterator2);

static int IsIterLeftChildren(bst_iterator_ty iterator);

static int IsIterHaveLeftChildren(bst_iterator_ty iterator);

static bst_iterator_ty GetRightLeaf(bst_iterator_ty iterator);

static void BstDisConnectLeaf(bst_iterator_ty position);

static bst_iterator_ty SwapWithPrevNode(bst_iterator_ty position);

/**************************function declarations*******************************/
bst_ty *BstCreate(cmp_func cmp, void *params)
{
	bst_ty *new_bs_tree = NULL;
	assert(NULL != cmp);
	
	new_bs_tree = (bst_ty *)malloc(sizeof(bst_ty ));
	if (NULL == new_bs_tree)
	{
		return (NULL);
	}
	
	new_bs_tree->cmp = cmp;
	new_bs_tree->params = params;
	new_bs_tree->dummy_root = CreateNewNode(NULL,NULL,NULL,NULL);
	
	if (NULL == new_bs_tree->dummy_root)
	{
		free(new_bs_tree);
		new_bs_tree = NULL;
		return (NULL);
	}
	return (new_bs_tree);
}


void BstDestroy(bst_ty *bst)
{
	assert(NULL != bst);
	while(!BstIsEmpty(bst))
	{
		BstRemove(bst->dummy_root->children[LEFT]);
	}

	free(bst->dummy_root);
	bst->dummy_root= NULL;
	free(bst);
	bst = NULL;	
}

bst_iterator_ty BstInsert(bst_ty *bst, void *data)
{
	bst_iterator_ty runner = NULL;
	bst_iterator_ty parent_keeper = NULL;
	bst_iterator_ty iter_to_ret = NULL;
	
	int which_child = 0;
	
	assert(NULL != bst);
	
	runner = BstGetRootNode(bst);
	parent_keeper = bst->dummy_root;
	
	which_child = FindInsertPosition(&runner, &parent_keeper,
	                                 bst, which_child, data);
	
	if (NADA == which_child)
	{
		return (NULL);
	}
	iter_to_ret = CreateNewNode(data, NULL, NULL, parent_keeper);
	parent_keeper->children[which_child] = iter_to_ret; 
	
	return(iter_to_ret);
}

void *BstRemove(bst_iterator_ty position)
{
	int which_child = 0;
	void *position_data = NULL;	
	assert(NULL != position);

	position_data = BstGetData(position);	
	if (IsThereTwoChildren(position))
	{
		position = SwapWithPrevNode(position);
	}
	if (IsThereOneChildren(position))
	{
		which_child = IsIterRightChildren(position);
		if (NULL == BstGetChildren(position, RIGHT))
		{
			BstGetParent(position)->children[which_child] =
			BstGetChildren(position, LEFT);
			BstGetChildren(position,LEFT)->parent = BstGetParent(position);
		}
		else
		{
			BstGetParent(position)->children[which_child] =
			BstGetChildren(position, RIGHT);
			BstGetChildren(position,RIGHT)->parent = BstGetParent(position);
		}
	}
	else
	{
		BstDisConnectLeaf(position);
	}
	free(position);
	position = NULL;
	return(position_data);
}

bst_iterator_ty BstFind(const bst_ty *bst, void *data)
{
	bst_iterator_ty runner = NULL;
	
	int func_res = 1;
	int which_child = 0;
	
	assert(NULL != bst);
	
	runner = BstGetRootNode((bst_ty *)bst);
	
	while((FOUND_POSITION != func_res) && (NULL != runner))
	{
		func_res = bst->cmp(BstGetData(runner), data, bst->params); 
		if ((FOUND_POSITION != func_res))
		{
			/* if the result is negetive the node will be in the left side */
			which_child = (FOUND_POSITION > func_res);
			runner = BstGetChildren(runner, which_child);
		}
	}
	
	return (runner);
}

bst_iterator_ty BstBegin(const bst_ty *bst)
{
	bst_iterator_ty runner = NULL;
	bst_iterator_ty runner_parent = NULL;
	
	runner = BstGetRootNode((bst_ty *)bst);
	runner_parent = bst->dummy_root;
	
	for ( ; NULL != runner;runner_parent = runner,
		runner = BstGetChildren(runner, LEFT))
	{
		/* empty for */
	}
	
	return (runner_parent);
}

bst_iterator_ty BstEnd(const bst_ty *bst)
{

	assert(NULL != bst);
	return (bst->dummy_root);
}

bst_iterator_ty BstGetPrev(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	
	if (IsIterHaveLeftChildren(iterator))
	{
		iterator = BstGetChildren(iterator, LEFT);
		iterator = GetRightLeaf(iterator);
	}
	else if (NULL != BstGetParent(iterator))
	{
      	for ( ; NULL != BstGetParent(iterator) &&
      	       IsIterLeftChildren(iterator);
      	       iterator = BstGetParent(iterator))
      	{
      		/* empty for */
      	}
  		iterator = BstGetParent(iterator);
	}	
	
	return (iterator);
}

bst_iterator_ty BstGetNext(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	
	if (IsIterHaveRIghtChildren(iterator))
	{
		iterator = BstGetChildren(iterator, RIGHT);
		iterator = GetLeftLeaf(iterator);
	}
	else if (NULL != BstGetParent(iterator))
	{
      	for ( ;NULL != BstGetParent(iterator) &&
      	       IsIterRightChildren(iterator);
      	       iterator = BstGetParent(iterator))
      	{
      		/*empty function */
      	}
  		iterator = BstGetParent(iterator);
	}	
	
	return (iterator);
}

void *BstGetData(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	
	return(iterator->data);
}

size_t BstSize(const bst_ty *bst)
{
	size_t counter = 0;
	bst_iterator_ty runner = NULL;
	assert(NULL != bst);
	
	for (runner = BstBegin(bst); !BstIterIsEqual(runner, BstEnd(bst)); 
	                             ++counter,
	                             runner = BstGetNext(runner))
	{
		/* empty for*/
	}
	/* for counting the last node itself */
	return (counter);
}

int BstIsEmpty(const bst_ty *bst)
{
	assert(NULL != bst);
	return(NULL == bst->dummy_root->children[LEFT]);
}

int BstIterIsEqual(bst_iterator_ty iterator1, bst_iterator_ty iterator2)
{
	assert (NULL != iterator1);
	assert (NULL != iterator2);
	
	return (iterator1 == iterator2);
}

int BstForEach(bst_iterator_ty from, bst_iterator_ty to,
               action_func action, void *params)
{
	int action_status = 0;
	
	for ( ;!BstIterIsEqual(from, to) &&
	     0 == action_status;
	     from = BstGetNext(from))
	{
		action_status = action(BstGetData(from), params);
	}
	
	return action_status;

}

static node_ty *CreateNewNode(void *data, node_ty *left,
                           node_ty *right, node_ty *parent)
{
	node_ty *new_node = malloc(sizeof(node_ty));
	
	if(NULL == new_node)
	{
		return(NULL);
	}
	
	new_node->parent = parent;
	new_node->children[LEFT] = left;
	new_node->children[RIGHT] = right;
	new_node->data = data;
	
	return (new_node);
}

static node_ty *BstGetRootNode(bst_ty *bst)
{
	assert(NULL != bst);
	
	return (bst->dummy_root->children[LEFT]);
}


static node_ty *BstGetParent(node_ty *node)
{
	
	return (node->parent);
}

static int FindInsertPosition(bst_iterator_ty *runner,
						      bst_iterator_ty *parent_keeper,
						      bst_ty *bst,
						      int which_child,
						      void *data)
{
	int func_res = 0;
	while(NULL != *runner && which_child != NADA)
	{
		*parent_keeper = *runner;
		func_res = bst->cmp(BstGetData(*runner), data, bst->params); 
		if ( 0 != func_res)
		{
			/* if the result is negetive the node will be in the left side */
			which_child = (0 > func_res);
			*runner = BstGetChildren(*runner, which_child);
		}
		else
		{
			which_child = NADA;
		}
	}
	return(which_child);
}



static node_ty *BstGetChildren(bst_iterator_ty iterator, int which_child)
{
	assert(NULL!= iterator);
	
	return(iterator->children[which_child]);
}

static int IsIterRightChildren(bst_iterator_ty iterator)
{
	return((iterator == BstGetChildren(BstGetParent(iterator), RIGHT)));
}


static int IsIterHaveRIghtChildren(bst_iterator_ty iterator)
{
	return (NULL != BstGetChildren(iterator, RIGHT));
}


static bst_iterator_ty GetLeftLeaf(bst_iterator_ty iterator)
{
	bst_iterator_ty runner = NULL;
	
	
	for ( runner = iterator ; NULL != BstGetChildren(runner, LEFT);
	                          runner = BstGetChildren(runner, LEFT))
	{
		/* empty for */
	}
	
	return (runner);	
}


static int IsThereTwoChildren(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	return ((NULL != BstGetChildren(iterator, RIGHT)) &&
	        (NULL != BstGetChildren(iterator, LEFT)));
}
static int IsThereOneChildren(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	
	return (((NULL == BstGetChildren(iterator, RIGHT)) &&
	        (NULL != BstGetChildren(iterator, LEFT))) ||
	        ((NULL != BstGetChildren(iterator, RIGHT)) &&
	        (NULL == BstGetChildren(iterator, LEFT))));
}	



static void SwapNodes(bst_iterator_ty iterator, bst_iterator_ty iterator2)
{
	void *tmp = NULL;
	assert(NULL != iterator);
	assert(NULL != iterator2);
	
	tmp = BstGetData(iterator);
	iterator->data = BstGetData(iterator2);
	iterator2->data = tmp;
	
}

static int IsIterLeftChildren(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	return ((iterator == BstGetChildren(BstGetParent(iterator), LEFT)));
}

static int IsIterHaveLeftChildren(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	return (NULL != BstGetChildren(iterator, LEFT));
}


static bst_iterator_ty GetRightLeaf(bst_iterator_ty iterator)
{
	bst_iterator_ty runner = NULL;
	
	runner = iterator;
	
	for (runner = iterator; NULL != BstGetChildren(runner, RIGHT);
							runner = BstGetChildren(runner, RIGHT))
	{
		/* empty for loop */
	}
	
	return (runner);	
}

static void BstDisConnectLeaf(bst_iterator_ty position)
{
	int which_child = 0;
	
	assert(NULL != position);
	
	which_child = IsIterRightChildren(position);
	BstGetParent(position)->children[which_child] = NULL;
}
static bst_iterator_ty SwapWithPrevNode(bst_iterator_ty position)
{
	bst_iterator_ty prev_position = NULL;
	assert(NULL != position);
	
	prev_position = BstGetPrev(position);
	SwapNodes(position, prev_position);
	return (prev_position);
}
