#include <stdio.h> /*printf */
#include <assert.h> /* assert */
#include <stdlib.h>
#include "queue.h" 

typedef struct node node_ty;
typedef struct tree tree_t;
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
	struct node *children[CHILDREN_NUM];
};

struct tree
{
    struct node *root;
};

static int NodeHasLeftChild(node_ty *node);
static int NodeHasRightChild(node_ty *node);
void LevelBLevelPrint(tree_t *tree, queue_ty *queue);

int main(void)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int data7 = 7;
    
    tree_t *tree_to_print = (tree_t *)malloc(sizeof(tree_t));
    queue_ty *queue = QueueCreate();
    node_ty *root = (node_ty *)malloc(sizeof(node_ty));
    node_ty *node_l_1 = (node_ty *)malloc(sizeof(node_ty));
    node_ty *node_r_1 = (node_ty *)malloc(sizeof(node_ty));
    node_ty *node_l_2 = (node_ty *)malloc(sizeof(node_ty));
    node_ty *node_r_2 = (node_ty *)malloc(sizeof(node_ty));
    node_ty *node_rr_2 = (node_ty *)malloc(sizeof(node_ty));
    node_ty *node_rl_2 = (node_ty *)malloc(sizeof(node_ty));
    root->data = &data1;
    node_l_1->data = &data2; /* 2 */
    node_r_1->data = &data3; /* 3 */
    node_l_2->data = &data4; /* 4 */
    node_r_2->data = &data5; /* 5 */
    node_rl_2->data = &data6; /* 6 */
    node_rr_2->data = &data7; /* 5 */

    tree_to_print->root = root;
    root = tree_to_print->root;
    root->children[LEFT] = node_l_1;
	root->children[RIGHT] = node_r_1;
    node_l_1->children[LEFT] = node_l_2;
    node_l_1->children[RIGHT] = node_r_2;
    node_r_1->children[RIGHT] = node_rr_2;
    node_r_1->children[LEFT] = node_rl_2;
    node_l_2->children[RIGHT] = NULL;
    node_l_2->children[LEFT] = NULL;
    node_r_2->children[RIGHT] = NULL;
    node_r_2->children[LEFT] = NULL;
    node_rl_2->children[RIGHT] = NULL;
    node_rl_2->children[LEFT] = NULL;
    node_rr_2->children[RIGHT] = NULL;
    node_rr_2->children[LEFT] = NULL;

    LevelBLevelPrint(tree_to_print, queue);
    QueueDestroy(queue);
    free(tree_to_print);
    free(root);
    free(node_l_1);
    free(node_r_1);
    free(node_l_2);
    free(node_r_2);
    free(node_rl_2);
    free(node_rr_2);

    return (0);
}
void LevelBLevelPrint(tree_t *tree, queue_ty *queue)
{
    node_ty *copy_print = NULL;

    assert(NULL != queue);
    assert(NULL != tree);

    copy_print = tree->root;
    QueueEnqueue(queue, copy_print);
    
    for ( ;QueuetSize(queue) != 0;
           copy_print = QueuePeek(queue))
    {
        printf("%d ", *(int *)copy_print->data);
        QueueDequeue(queue);
        if (NodeHasLeftChild(copy_print))
        {
            QueueEnqueue(queue, copy_print->children[LEFT]);
        }
        if (NodeHasRightChild(copy_print))
        {
            QueueEnqueue(queue, copy_print->children[RIGHT]);
        }
    }
    printf("\n");
}

static int NodeHasLeftChild(node_ty *node)
{
    return (NULL != node->children[LEFT]);
}
static int NodeHasRightChild(node_ty *node)
{
    return (NULL != node->children[RIGHT]);
}