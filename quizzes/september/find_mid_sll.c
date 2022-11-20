#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}node_ty;

node_ty *CreateNewNode(int data)
{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}

node_ty *NodeInsert(node_ty *position, int data)
{
	node_ty *new_node = CreateNewNode(data);
	
	assert(NULL != position);	
		
	new_node->next = position->next;
	position->next = new_node;
		
	return (position);
}



void FindMidElementSll(node_ty *node)
{
    node_ty *runner = node;
    node_ty *fast_runner = node;

    assert (NULL != node);

    while (NULL != fast_runner && NULL != fast_runner->next)
    {
        fast_runner = fast_runner->next->next;
        runner = runner->next;
    }

    printf("The mid element is %d\n", runner->data);
}

int main(void)
{
    int data1 = 1;
    int data2 = 3;
    int data3 = 7;
    int data4 = 8;
    int data5 = 9;

    node_ty *pt = CreateNewNode(data1);
    node_ty *iterator = pt;
    
    NodeInsert(iterator,data1);
    NodeInsert(iterator,data2);
    NodeInsert(iterator,data3);
    NodeInsert(iterator,data4);
    NodeInsert(iterator,data5);


    FindMidElementSll(pt);

    return 0;
}
