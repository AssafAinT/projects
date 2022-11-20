#include <stdio.h> /*printf, size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

typedef struct node node_ty;
struct node
{
	void *data;
	struct node *next;
};

node_ty *FindIntersection(node_ty *list1, node_ty *list2); 
void SaparateIntersection(node_ty *head1, node_ty *head2);
static size_t SlistSize(const node_ty *slist);



node_ty *FindIntersection(node_ty *list1, node_ty *list2)
{
	node_ty *runner1 = NULL;
	node_ty *runner2 = NULL;
	
	size_t size_list1 = 0;
	size_t size_list2 = 0;
	size_t offset_lists = 0;
	
	assert(NULL !=list1);
	assert(NULL !=list2);
	
	size_list1 = SlistSize(list1);
	size_list2 = SlistSize(list2);
	
	runner1 = list1;
	runner2 = list2;
	
	if (size_list1 > size_list2)
	{
		offset_lists = size_list1 - size_list2;
		
		for ( ; 0 != offset_lists;
		     runner1= runner1->next,
		     --offset_lists)
		{
			/* empty loop */
		}
	}
	if (size_list2 > size_list1)
	{
		offset_lists = size_list2 - size_list1;
		
		for ( ; 0 != offset_lists;
		     runner2= runner2->next,
		     --offset_lists)
		{
			/* empty loop */
		}
	}
	
	for ( ; (NULL != runner1)&&
		 (NULL != runner2) &&
		 runner1 != runner2;
		 runner1= runner1->next,
		 runner2= runner2->next)
		 {
		 /* empty loop */
		 }
	return (runner1);

}

void SaparateIntersection(node_ty *head1, node_ty *head2)
{
	node_ty *saparate = NULL;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	saparate = FindIntersection(head1, head2);
	
	if (NULL != saparate)
	{
		saparate->next = NULL;
	}
}
static size_t SlistSize(const node_ty *slist)
{
	size_t counter = 0;
	const node_ty *runner =NULL;
	
	assert(NULL != slist);
	runner= slist;
	
	for ( ; NULL != (runner ) ; (runner = runner->next))
	{
		++counter;
	}
	
	return (counter);
}





int main(void)
{
	node_ty *head = NULL;
	node_ty *another_head = NULL;

	node_ty *node1 = NULL;
	node_ty *node2 = NULL;
	node_ty *node3 = NULL;
	node_ty *node4 = NULL;
	node_ty *node5 = NULL;
	node_ty *node6 = NULL;
	node_ty *node7 = NULL;
	node_ty *node22 = NULL;
	node_ty *node11 = NULL;
	
	node_ty *intersection_node = NULL;

	node_ty *temp_node = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int num7 = 7;
	int num11 = 8;
	int num22 = 9;

	
	node1 = (node_ty *)malloc(sizeof(node_ty));
	node2 = (node_ty *)malloc(sizeof(node_ty));
	node3 = (node_ty *)malloc(sizeof(node_ty));
	node4 = (node_ty *)malloc(sizeof(node_ty));
	node5 = (node_ty *)malloc(sizeof(node_ty));
	node6 = (node_ty *)malloc(sizeof(node_ty));
	node7 = (node_ty *)malloc(sizeof(node_ty));
	node11 = (node_ty *)malloc(sizeof(node_ty));
	node22 = (node_ty *)malloc(sizeof(node_ty));

	node1->data = &num1;
	node2->data = &num2;
	node3->data = &num3;
	node4->data = &num4;
	node5->data = &num5;
	node6->data = &num6;
	node7->data = &num7;
	node11->data = &num11;
	node22->data = &num22;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = NULL;
	
	node11->next = node22;
	node22->next = node5;

	head = node1;
	another_head = node11;
	
	SaparateIntersection(head, another_head);

	intersection_node = FindIntersection(head, another_head);


	if (NULL == intersection_node)
	{
		printf("\n\nThere is no itersection node\n\n");
	}
	else
	{
		printf("\n\nThere is itersection node\n\n");

	}
	
	return (0);
}


