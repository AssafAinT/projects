#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */


typedef struct node node_ty;
struct node
{
	void *data;
	struct node *next;
};

node_ty *FindNElemFromLastSll(node_ty *head, size_t n);

int main(void)
{
	node_ty *node1 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node2 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node3 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node4 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node5 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node6 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node7 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *node8 = (node_ty *)malloc(sizeof(node_ty));
	node_ty *found = NULL;
	node_ty *head = NULL;

	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int num7 = 7;
	int num8 = 8;

	node1->data = &num1;
	node2->data = &num2;
	node3->data = &num3;
	node4->data = &num4;
	node5->data = &num5;
	node6->data = &num6;
	node7->data = &num7;
	node8->data = &num8;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = NULL;

	head = node1;

	found = FindNElemFromLastSll(head, 3);

	assert(6 == *(int *)found->data);
	found = FindNElemFromLastSll(head, 1);
	assert(8 == *(int *)found->data);
	
	found = FindNElemFromLastSll(head, 10);
	assert(NULL == found);
	
	found = FindNElemFromLastSll(head, 8);
	assert(1 == *(int *)found->data);
	return 0;
}



node_ty *FindNElemFromLastSll(node_ty *head, size_t n)
{
	node_ty *runner = head;
	size_t len = 0;
	size_t i = 0;
	
	assert(NULL != runner);
	
	while (NULL != runner)
	{
		runner = runner->next;
		++len;
	}
	
	if (len < n)
	{
		return (NULL);
	}
	
	
	for ( ; i< (len - n); ++i)
	{
		head = head->next;
		
	}
	
	return (head);
}
