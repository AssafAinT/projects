/****************************************************
* bst_to_dll                                        *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stdio.h> /*printf*/

typedef enum 
{
	LEFT = 0,
	RIGHT = 1,
	CHILDREN_NUM = 2
}params_ty;

typedef struct node
{
	void *data;
	struct node *children[CHILDREN_NUM];
}node_ty;


typedef enum
{
	SUCCESS = 0, 
    FAIL = 1,
	MALLOC_FAILURE = 2
}status_ty;

static status_ty QuizTest(void);
node_ty *BstToSrtDll(node_ty *root);
static void BstToSrtDllRec(node_ty *root, node_ty **head);
static void PrintList(node_ty *node);

int main (void)
{
    assert(SUCCESS == QuizTest());
    return (0);
}

static status_ty QuizTest(void)
{
    int tree_data[7] = {10, 6, 14, 4 ,8, 12, 16};
    
    node_ty *root =NULL;
    node_ty *node_left_1 = NULL;
    node_ty *node_right_1 = NULL;
    node_ty *node_left_2 = NULL;
    node_ty *node_right_2 = NULL;   
    node_ty *node_right_right_2 = NULL;
    node_ty *node_right_left_2 = NULL;

    root = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == root)
    {
        return MALLOC_FAILURE;
    }

    node_left_1 = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == node_left_1)
    {
        return MALLOC_FAILURE;
    }
    
    node_right_1 = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == node_right_1) 
    {
        return MALLOC_FAILURE;  
    }

    node_left_2 = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == node_left_2) 
    {
        return MALLOC_FAILURE;
    }

    node_right_1 = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == node_right_1)  
    {
        return MALLOC_FAILURE;
    }

    node_right_2 = (node_ty *)malloc(sizeof(node_ty));  
    if (NULL == node_right_2) 
    {
        return MALLOC_FAILURE;
    }


    node_right_right_2 = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == node_right_right_2)
    {
    	return MALLOC_FAILURE;
    }
    
    node_right_left_2 = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == node_right_left_2)
    {
    	return MALLOC_FAILURE;
    }

    root->data = &tree_data[0];
    node_left_1->data = &tree_data[1]; 
    node_right_1->data = &tree_data[2]; 
    node_left_2->data = &tree_data[3]; 
    node_right_2->data = &tree_data[4]; 
    node_right_left_2->data = &tree_data[5];
    node_right_right_2->data = &tree_data[6];

    root->children[LEFT] = node_left_1;
	root->children[RIGHT] = node_right_1;
    node_left_1->children[LEFT] = node_left_2;
    node_left_1->children[RIGHT] = node_right_2;
    node_right_1->children[RIGHT] = node_right_right_2;
    node_right_1->children[LEFT] = node_right_left_2;
    node_left_2->children[RIGHT] = NULL;
    node_left_2->children[LEFT] = NULL;
    node_right_2->children[RIGHT] = NULL;
    node_right_2->children[LEFT] = NULL;
    node_right_left_2->children[RIGHT] = NULL;
    node_right_left_2->children[LEFT] = NULL;
    node_right_right_2->children[RIGHT] = NULL;
    node_right_right_2->children[LEFT] = NULL;

    root = BstToSrtDll(root);
    PrintList(root);
    
   	free(root);
    root = NULL;
    free(node_left_1);
    node_left_1 = NULL;
    free(node_left_2);
    node_left_2 = NULL;
    free(node_right_2);
    node_right_2 = NULL;
    free(node_right_1);
    node_right_1 = NULL;
    free(node_right_right_2);
    node_right_right_2 = NULL;
    free(node_right_left_2);
    node_right_left_2 = NULL;

    return SUCCESS;
}

node_ty *BstToSrtDll(node_ty *root)
{
	node_ty *head = NULL;
    assert(root != NULL);
	
    BstToSrtDllRec(root, &head);
	return head;
}

static void BstToSrtDllRec(node_ty *root, node_ty **head)
{	
    static node_ty *prev = NULL;
	if (NULL == root)
	{
		return;
	}
	
	BstToSrtDllRec(root->children[LEFT], head);
	
	if (NULL == prev)
	{
		*head = root;
	}
	else
	{
		root->children[LEFT] = prev;
		prev->children[RIGHT] = root;
	}
	
    prev = root;
	
	BstToSrtDllRec(root->children[RIGHT], head);
}

static void PrintList(node_ty *node)
{
	while (NULL != node)
	{
		printf("%d\n", *(int *)node->data);
		node = node->children[RIGHT];
	}
}
