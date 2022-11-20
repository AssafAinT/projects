#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_HEIGHT (5)

typedef enum
{
    LEFT,
    RIGHT,
    CHILD_NUM
}child_ty;

typedef struct  node
{
    void *data;
    long height;
    struct node *children[CHILD_NUM];
}node_ty;

static void TreePrint(node_ty *node);
static void TreePrintR(node_ty *node, int level);

void RecMirrorBt(node_ty *node);

int main (void)
{
    int first_data = 9;
	int sec_data = 4;
	int third_data = 8;
	int root_data = 19;
	int last_data = 7;

	node_ty *root = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node1 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node2 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node3 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node5 = (node_ty *)malloc(sizeof(node_ty));
	
	root->data = &root_data;
	node1->data = &first_data;
	node2->data = &sec_data;
	node3->data = &third_data;
	node5->data = &last_data;

	root->height = 3;
	node1->height = 0;
	node2->height = 1;
	node3->height = 0;
	node5->height = 0;

	root->children[LEFT] = node2;
	root->children[RIGHT] = node5;

	node2->children[LEFT] = node1;
	node2->children[RIGHT] = node3;

	node5->children[LEFT] = NULL;
	node5->children[RIGHT] = NULL;

	node1->children[LEFT] = NULL;
	node1->children[RIGHT] = NULL;

	node3->children[LEFT] = NULL;
	node3->children[RIGHT] = NULL;

    TreePrint(root);
    RecMirrorBt(root);
    TreePrint(root);

    free(root);
    free(node1);
    free(node2);
    free(node3);
    free(node5);

    return (0);

}
void RecMirrorBt(node_ty *node)
{
    node_ty *copy_node = NULL;

    if (NULL == node)
    {
        return ;
    }
     
    else
    {
        RecMirrorBt(node->children[LEFT]);
        RecMirrorBt(node->children[RIGHT]);

        copy_node = node->children[LEFT];
        node->children[LEFT] = node->children[RIGHT];
        node->children[RIGHT] = copy_node;
    }
}


static void TreePrint(node_ty *node)
{
    printf("\n----------------------------TREE-----------------------------\n");
    TreePrintR(node, 0);
    printf("\n-------------------------------------------------------------\n");
}


static void TreePrintR(node_ty *node, int level)
{
    int i = 0;
    if (node == NULL)
    {
        return;
	}
	 
    level += MAX_HEIGHT;
 
    TreePrintR(node->children[RIGHT], level);

    for (i = MAX_HEIGHT; i < level; i++)
    {
        printf("   ");
    }
    
    printf("Num: %d H:%ld\n",  *(int *)node->data, node->height);
 
    TreePrintR(node->children[LEFT], level);
}
