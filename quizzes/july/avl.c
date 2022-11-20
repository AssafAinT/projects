/*****************************************************
 * Avl                                               *
 * Assaf Ainhoren                                    *
 * Reviewer: Ofir Krisple                            *
 * date: 27.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include "avl.h"

#define NO_OF_SPACES_FOR_PRINT 5

typedef struct node node_ty;

typedef enum 
{
	NADA = -1,
	LEFT,
	RIGHT,
	CHILDREN_NUM
} avl_params_ty;

struct node
{
	void *data;
	long height;
	struct node *children[CHILDREN_NUM];
};

struct avl
{
    cmp_func cmp_func;
    void *params;
    struct node *root;
};

typedef enum
{
	LL = 0,
	RR = 1,
	LR = 2,
	RL = 3,
	BALANCED = 4
}balance_status_ty;


static const size_t primarly_height = 0;
static const size_t size_of_tree_only_root = 0;
static const size_t size_of_leaf = 1;
static const size_t height_of_empty_root= -1;

static avl_ty *InitNewAvl(avl_ty *avl, cmp_func cmp_func, void *params);

static status_ty IsNodeHaveTwoChildren(node_ty *node);

static status_ty NodePostOrderForEach(node_ty *node, action_func action,
						 void *params, status_ty *ret_stat);

static status_ty NodeInOrderForEach(node_ty *node, action_func action,
						 void *params, status_ty *ret_stat);

static status_ty NodePreOrderForEach(node_ty *node, action_func action,
						 void *params, status_ty *ret_stat);

static void DestroyAvlPostOrder(node_ty *node);

static void NodeDataSwap(node_ty *node1, node_ty *node2);

static void *AvlGetParams(const avl_ty *avl);

static void *NodeGetData(node_ty *node);

static size_t GetSize(node_ty *root);

static int IsNodeLeaf(node_ty *node);

static int IsThereOneChildren(node_ty *node);

static long NodeGetHigh(const node_ty *node);

static long AvlGetMaxOfChildHeight(node_ty *node);

static long NodeComputeBalance(node_ty *node);

static node_ty *CreateNewNode(void *data,node_ty *left, node_ty *right);

static node_ty *FindPosition(const avl_ty *avl,node_ty *node,
                             void *data, avl_params_ty *which_child);

static node_ty *AvlGetRoot(const avl_ty *avl);

static node_ty *NodeGetMostLeftChild(node_ty *node);

static node_ty *ReBalancing(avl_ty *avl, node_ty *node, 
                          void *data);
static node_ty *NodeGetChildren(node_ty *node, int which_child);

static node_ty *FindPositionToRemove(const avl_ty *avl,node_ty *node,
                             void *data);
static node_ty *NodeGetNext(node_ty *node);
static node_ty *AvlReBalance(node_ty *node, balance_status_ty balance_status);

static node_ty *NodeRightRotate(node_ty *node);

static node_ty *NodeLeftRotate(node_ty *node);

static node_ty *WhichNodeToDelete(const avl_ty *avl, node_ty *node);

static balance_status_ty CheckBalanceType(avl_ty *avl, node_ty *node,
                                                long height_factor,
												void *data, cmp_func cmp);
#ifndef NDEBUG
static void TreePrintR(node_ty *node, int level);
#endif

/******************************Function definitons*****************************/
avl_ty *AvlCreate(cmp_func cmp_func, void *params)
{
	avl_ty *new_avl = NULL;
	assert(NULL != cmp_func);
	
	new_avl = InitNewAvl(new_avl, cmp_func, params);
	if (NULL == new_avl)
	{
		return (NULL);
	}
	return (new_avl);
}
void AvlDestroy(avl_ty *avl)
{
	DestroyAvlPostOrder(AvlGetRoot(avl));
	free(avl);
	avl = NULL;
}

status_ty AvlInsert(avl_ty *avl, void *data)
{
	node_ty *node_to_insert = NULL;
	avl_params_ty which_child = LEFT;
	
	assert(NULL != avl);
	node_to_insert = AvlGetRoot(avl);
	
	if (AvlIsEmpty(avl))
	{
		/* case its root */
		avl->root = CreateNewNode(data,NULL, NULL);
       	if (NULL == avl->root)
       	{
       		return (FAIL);
       	}
   		return (SUCCESS);
	}
	node_to_insert = FindPosition(avl , node_to_insert, data, &which_child);
	if (NADA == which_child)
	{
		return (FAIL);
	}
	
	node_to_insert->children[which_child] = CreateNewNode(data, NULL, NULL);
	if (NULL == node_to_insert->children[which_child])
   	{
		return (FAIL);
   	}

  	avl->root = ReBalancing(avl,AvlGetRoot(avl), data);
	return (SUCCESS);
}

void AvlRemove(avl_ty *avl, void *data)
{
	assert(NULL != avl);

	avl->root = FindPositionToRemove(avl , AvlGetRoot(avl),data);
	avl->root = ReBalancing(avl, AvlGetRoot(avl),data);
}

long AvlHeight(const avl_ty *avl)
{
	assert(NULL != avl);

	return (NodeGetHigh(AvlGetRoot(avl)));
}

size_t AvlSize(const avl_ty *avl)
{
	assert(NULL != avl);
	
	return (GetSize(AvlGetRoot(avl)));
}

bool_ty AvlIsEmpty(const avl_ty *avl)
{
	assert(NULL != avl);
	return (NULL == AvlGetRoot(avl));
}

status_ty AvlFind(const avl_ty *avl, void *data)
{
	void *found = NULL;
	avl_params_ty empty_param = NADA;

	assert(NULL != avl);
	
	found = NodeGetData((FindPosition((avl_ty *)avl, AvlGetRoot(avl),
	                                 data, &empty_param)));
	                           
	return !(SUCCESS == avl->cmp_func(found, data, AvlGetParams(avl)));
}

status_ty AvlForEach(avl_ty *avl, action_func action,
						    void *params, trav_ty trav)
{
	status_ty status = SUCCESS;

	assert(NULL != avl);
	assert(NULL != action);

	if (AvlIsEmpty(avl))
	{
		status = FAIL;
	}
	if (INORDER == trav)
	{
		status = NodeInOrderForEach(AvlGetRoot(avl), action, params, &status);
	}
	else if (POST_ORDER == trav)
	{
		status = NodePostOrderForEach(AvlGetRoot(avl), action, params, &status);
	}
	else
	{
		status = NodePreOrderForEach(AvlGetRoot(avl), action, params, &status);
	}

	return status;

}

/************************************static functions**************************/


static long AvlGetMaxOfChildHeight(node_ty *node)
{
	long left_height = NodeGetHigh(NodeGetChildren(node, LEFT));
	long right_height = NodeGetHigh(NodeGetChildren(node, RIGHT));
	
	return (left_height > right_height ? left_height : right_height);

}
static avl_ty *InitNewAvl(avl_ty *avl, cmp_func cmp_func, void *params)
{
	avl = (avl_ty *)malloc(sizeof(avl_ty ));
	if (NULL == avl)
	{
		return (NULL);
	}
	
	avl->cmp_func = cmp_func;
	avl->params = params;
	avl->root = NULL;
	return (avl);
}

static node_ty *CreateNewNode(void *data,node_ty *left,
                           node_ty *right)

{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	if(NULL == new_node)
	{
		return(NULL);
	}
	
	new_node->data = data;
	new_node->height = primarly_height;
	new_node->children[LEFT] = left;
	new_node->children[RIGHT] = right;
	return (new_node);
}

static size_t GetSize(node_ty *root)
{
	if (NULL == root)
	{
		return (size_of_tree_only_root);
	}
	if (IsNodeLeaf(root))
    {
    	return (size_of_leaf);
    }

	return (GetSize(NodeGetChildren(root, LEFT)) +
	        GetSize(NodeGetChildren(root, RIGHT)) + 1);

}
static node_ty *FindPositionToRemove(const avl_ty *avl,node_ty *node,
                                     void *data)
{
	int cmp_result = 0;
	if (NULL == node)
	{
		return (node);
	}
	cmp_result = avl->cmp_func(NodeGetData(node), data, AvlGetParams(avl));
	
	if (0 < cmp_result)
	{
		node->children[LEFT] = FindPositionToRemove(avl,
		                       NodeGetChildren(node, LEFT),
		                                             data);
	}
	else if (0 > cmp_result)
	{
		node->children[RIGHT] = FindPositionToRemove(avl,
		                       NodeGetChildren(node, RIGHT),
		                                             data);
	}
	else
	{
		return (WhichNodeToDelete(avl, node));
	}
	return (node);
}
static node_ty *WhichNodeToDelete(const avl_ty *avl, node_ty *node)
{
	if (IsNodeHaveTwoChildren(node))
	{
		node_ty *next_node = NodeGetNext(node);
		NodeDataSwap(next_node, node);
		node->children[RIGHT] = FindPositionToRemove(avl,
										NodeGetChildren(node, RIGHT),
										NodeGetData(next_node));
	}
	else if (IsThereOneChildren(node))
	{
		if (NULL != NodeGetChildren(node, LEFT))
		{
			node_ty *child_node = NodeGetChildren(node, LEFT);
			free(node);
			return(child_node);
		}
		else
		{
			node_ty *child_node = NodeGetChildren(node, RIGHT);
			free(node);
			return(child_node);
		}
	}
	else
	{
		free(node);
		node = NULL;
	}
	return (node);
}
static void DestroyAvlPostOrder(node_ty *node)
{
	if (NULL == node)
	{
		return;
	}
	
	if (IsNodeLeaf(node))
    {
    	free(node);
    	node = NULL;
    }
    else
    {
		DestroyAvlPostOrder(NodeGetChildren(node, LEFT));
		DestroyAvlPostOrder(NodeGetChildren(node, RIGHT));
    }
    free(node);
}

static void *NodeGetData(node_ty *node)
{
	return (node->data);
}

static node_ty *AvlGetRoot(const avl_ty *avl)
{
	return (avl->root);
}

static node_ty *NodeGetChildren(node_ty *node, int which_child)
{
	return(node->children[which_child]);
}

static int IsNodeLeaf(node_ty *node)
{
	return(NULL == node->children[LEFT] && 
	       NULL == node->children[RIGHT]);
}

static int IsThereOneChildren(node_ty *node)
{
	return ((NULL == NodeGetChildren(node, RIGHT) &&
	         NULL != NodeGetChildren(node, LEFT)) ||
	        (NULL != NodeGetChildren(node, RIGHT) &&
	         NULL == NodeGetChildren(node, LEFT))); 
}
static status_ty NodePostOrderForEach(node_ty *node, action_func action,
						 void *params, status_ty *ret_stat)
{
	
	if (NULL != NodeGetChildren(node, LEFT) && SUCCESS == *ret_stat)
	{
		*ret_stat = NodePostOrderForEach(NodeGetChildren(node, LEFT),
		                                 action, params, ret_stat);
	}
	
	if (NULL != NodeGetChildren(node, RIGHT) && SUCCESS == *ret_stat)
	{
		*ret_stat = NodePostOrderForEach(NodeGetChildren(node, RIGHT),
		                                action, params, ret_stat);
	}
	*ret_stat = action(NodeGetData(node), params);
	return (*ret_stat);
}

static status_ty NodeInOrderForEach(node_ty *node, action_func action,
						 void *params, status_ty *ret_stat)
{
	if (NULL != NodeGetChildren(node, LEFT) && SUCCESS == *ret_stat)
	{
		*ret_stat = NodeInOrderForEach(NodeGetChildren(node, LEFT),
		                               action, params, ret_stat);
	}
	
	*ret_stat = action(NodeGetData(node), params);
	
	if (NULL != NodeGetChildren(node, RIGHT)  && SUCCESS == *ret_stat)
	{
		*ret_stat =  NodeInOrderForEach(NodeGetChildren(node, RIGHT),
		                                action, params, ret_stat);
	}
	return (*ret_stat);
}

static status_ty NodePreOrderForEach(node_ty *node, action_func action,
						 void *params, status_ty *ret_stat)
{
	
	*ret_stat = action(NodeGetData(node), params);
	
	if (NULL != NodeGetChildren(node, LEFT) && SUCCESS == *ret_stat)
	{
		*ret_stat = NodePreOrderForEach(NodeGetChildren(node, LEFT),
		                                 action, params, ret_stat);
	}
	
	if (NULL != NodeGetChildren(node, RIGHT) && SUCCESS == *ret_stat)
	{
		*ret_stat =  NodePreOrderForEach(NodeGetChildren(node, RIGHT),
		                                  action, params, ret_stat);
	}
	return (*ret_stat);
}
static node_ty *FindPosition(const avl_ty *avl,node_ty *node,
                             void *data, avl_params_ty *which_child)
{
	
	int cmp_result = avl->cmp_func(NodeGetData(node), data, AvlGetParams(avl));
	
	if (0 == cmp_result)
	{
		*which_child = NADA;
		return (node);
	}
	else if (0 > cmp_result)
	{
		if (NULL == NodeGetChildren(node, RIGHT))
		{
			*which_child = RIGHT;
			return (node);
		}
		return (FindPosition(avl, NodeGetChildren(node, RIGHT),
		                    data, which_child));
	}
	
	else 
	{
		if (NULL == NodeGetChildren(node, LEFT))
		{
			*which_child = LEFT;
			return (node);
		}
		return (FindPosition(avl, NodeGetChildren(node, LEFT),
		                    data, which_child));
	}
}
static node_ty *ReBalancing(avl_ty *avl, node_ty *node, 
                          void *data)
{
	balance_status_ty balance = BALANCED;
	long height_factor = 0;
	int cmp_result = 0;

	if (NULL == node)
	{
		return NULL;
	}

	cmp_result = avl->cmp_func(NodeGetData(node), data, AvlGetParams(avl)); 
	if (0 < cmp_result)
	{
		node->children[LEFT] = ReBalancing(avl, NodeGetChildren(node, LEFT),
		              data);
	}
	
	else if (0 > cmp_result)
	{
		node->children[RIGHT] = ReBalancing(avl, NodeGetChildren(node, RIGHT),
		              data);
	}	
	
	node->height = AvlGetMaxOfChildHeight(node) + 1;
	height_factor = NodeComputeBalance(node);
	balance = CheckBalanceType(avl, node, height_factor, data, avl->cmp_func);
	return(AvlReBalance(node, balance));
}

static balance_status_ty CheckBalanceType(avl_ty *avl, node_ty *node,
                                                long height_factor,
												void *data, cmp_func cmp)
{
	if ((2 == height_factor) && 
	    (0 > cmp(data, node->children[LEFT]->data, AvlGetParams(avl))))
	{
		return LL;
	}
	
	if ((-2 == height_factor) && 
	    (0 < cmp(data, node->children[RIGHT]->data, AvlGetParams(avl))))
	{
		return RR;
	}
	
	if ((2 == height_factor) &&
	   (0 < cmp(data, node->children[LEFT]->data, AvlGetParams(avl))))
	{
		return LR;
	}
	
	if ((-2 == height_factor) &&
	   (0 > cmp(data, node->children[RIGHT]->data, AvlGetParams(avl))))
	{
		return RL;
	}
	return BALANCED;
}

static node_ty *AvlReBalance(node_ty *node, balance_status_ty balance_status)
{
	switch (balance_status)
	{
		case LL:
		{
			return (NodeRightRotate(node));
		}
		case RR:
		{
			return (NodeLeftRotate(node));
		}
		case LR:
		{
			node->children[LEFT] = NodeLeftRotate(NodeGetChildren(node, LEFT));
			return (NodeRightRotate(node));
		}
		case RL:
		{
			node->children[RIGHT] = NodeRightRotate(NodeGetChildren(node, RIGHT));
			return (NodeLeftRotate(node));
		}
		case BALANCED:
		{
			break;
		}
	}
	return (node);
}

static node_ty *NodeRightRotate(node_ty *node)
{
	node_ty *rotated_node = NodeGetChildren(node, LEFT);
	node_ty *right_child = rotated_node->children[RIGHT];

 	rotated_node->children[RIGHT] = node;
 	node->children[LEFT] = right_child;


	node->height = AvlGetMaxOfChildHeight(node) + 1;
	rotated_node->height = AvlGetMaxOfChildHeight(rotated_node) + 1; 
	
	return (rotated_node);
}

static node_ty *NodeLeftRotate(node_ty *node)
{
	node_ty *rotated_node = NodeGetChildren(node, RIGHT);
	node_ty *left_child = rotated_node->children[LEFT];

 	rotated_node->children[LEFT] = node;
 	node->children[RIGHT] = left_child;


	node->height = AvlGetMaxOfChildHeight(node) + 1;
	rotated_node->height = AvlGetMaxOfChildHeight(rotated_node) + 1; 
	return (rotated_node);
}
static status_ty IsNodeHaveTwoChildren(node_ty *node)
{
	return (NULL != NodeGetChildren(node, RIGHT) &&
	        NULL != NodeGetChildren(node, LEFT));
}
static void NodeDataSwap(node_ty *node1, node_ty *node2)
{
	void *tmp = NULL;
	
	tmp = NodeGetData(node1);
	node1->data = NodeGetData(node2);
	node2->data = tmp;
}

static node_ty *NodeGetMostLeftChild(node_ty *node)
{
	if (NULL == NodeGetChildren(node, LEFT))
	{
		return (node);
	}
	return (NodeGetMostLeftChild(NodeGetChildren(node, LEFT)));
}

static node_ty *NodeGetNext(node_ty *node)
{
	return (NodeGetMostLeftChild(NodeGetChildren(node, RIGHT)));
}

static void *AvlGetParams(const avl_ty *avl)
{
	return (avl->params);
}


static long NodeGetHigh(const node_ty *node)
{
	if (NULL == node)
	{
		return (height_of_empty_root);
	}
	else
	{	
		return (node->height);
	}
}
#ifndef NDEBUG
void TreePrint(avl_ty *avl)
{
    TreePrintR(AvlGetRoot(avl), 0);
}

static void TreePrintR(node_ty *node, int level)
{
	int i = 0;
	if (node == NULL)
		return;

	level += NO_OF_SPACES_FOR_PRINT;

	TreePrintR(node->children[RIGHT], level);


	for (i = NO_OF_SPACES_FOR_PRINT; i < level; i++)
	{
		printf(" ");
	}

	printf("%d\n",  *(int *)NodeGetData(node));

	TreePrintR(node->children[LEFT], level);
}
#endif
static long NodeComputeBalance(node_ty *node)
{
	if (NULL == node)
	{
		return (0);
	}
	return(NodeGetHigh(NodeGetChildren(node, LEFT)) - 
	       NodeGetHigh(NodeGetChildren(node, RIGHT)));
}

