/*************************************
*  llex1                             *
*  Assaf Ainhoren                    *
*  Reviewer: Maayan                  *
*   13.06.22                         *
***************************************/

/*************************************Libraries Include************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

/*************************************struct definition************************/
typedef struct node
{
	void *data;
	struct node *next;
}node_ty;

/*************************************function declaration*********************/

node_ty *CreateHead(void *data);
node_ty *Flip(node_ty *head);
node_ty *LastNode(node_ty *head);

int HasLoops(const node_ty *head);
node_ty *FindIntersection(node_ty *head1, node_ty *head2);
node_ty *SlistInsertBegin(node_ty *head, void *data);
void DestroyNode(node_ty *head);
size_t ListSize(node_ty *head);
int TestExercise();
/****************************************main function*************************/
int main(void)
{
	TestExercise();
	
	return (0);
}

node_ty *CreateHead(void *data)
{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node -> data = data;
	new_node -> next = NULL;
	
	return (new_node);		
}

void DestroyNode(node_ty *head)
{
	node_ty *runner = NULL;
	node_ty *copy_of_node = NULL;
	assert(NULL != head);
	
	runner = head;
	copy_of_node = head;
	while(NULL != runner -> next)
	{
		runner = runner -> next;
		free(copy_of_node);
		copy_of_node = runner;
	}
	
	free(runner);
}

node_ty *SlistInsertBegin(node_ty *head, void *data)
{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node -> data = data;
	new_node -> next = head;
	
	return (new_node);
	
}
node_ty *LastNode(node_ty *head)
{
	assert (NULL != head);
	
	while (NULL != head -> next)
	{
		head = head -> next;
	}
	return (head);
}
node_ty *Flip(node_ty *head)
{
	node_ty *prev = NULL;
	node_ty *curr = head;
	node_ty *next = NULL;
	
	while (curr!=NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;

	}
	
	
	return (prev);
}

int HasLoops(const node_ty *head)
{
	const node_ty *slow_runner = head;
	const node_ty *fast_runner = head;
	
	assert(NULL != head);
	assert(NULL != head -> next);
	
	while((NULL != slow_runner && NULL != fast_runner) && 
		  (NULL != fast_runner->next))
	{
		slow_runner = slow_runner -> next; 
		fast_runner = fast_runner -> next -> next; 
		if(slow_runner == fast_runner)
		{
			return (1);
		}
	}
	return 0;
}

node_ty *FindIntersection(node_ty *head1, node_ty *head2)
{
	size_t size_head1 = 0;
	size_t size_head2 = 0;
	size_t differ = 0;
	
	assert(NULL != head1);
	assert(NULL != head2);
	

	size_head1 = ListSize(head1);
	size_head2 = ListSize(head2);
	
	if (size_head1 > size_head2)
	{
		differ = size_head1 - size_head2;
		for ( ; 0 != differ; --differ)
		{
			head1 = head1->next;
		}
	}
	else if (size_head2 > size_head1)
	{
		differ = size_head2 - size_head1;
		for ( ; 0 != differ; --differ)
		{
			head2 = head2->next;
		}
	}
	
	while(NULL != head1)
	{
		if (head1 == head2)
		{
			return head1;
		}
		head1 = head1->next;
		head2 = head2->next;
	}
	
	return (NULL);
}

size_t ListSize(node_ty *head)
{
	size_t size = 0;
	assert(NULL != head);
	
	while(NULL != head)
	{
		++size;
		head = head->next;
	}
	return size;
}

int TestExercise()
{
	int x = 20;
	int y = 22;
	int z = 35;
	int w = 88;
	int first_data = 2121;
	int second_data = 77;
	
	node_ty *list = CreateHead(&x);
	node_ty *inter = CreateHead(&first_data);
	
	
	node_ty *list_copy = list;
	node_ty *end_of_list = list;
	node_ty *copy_of_inter = inter;
	node_ty *temp_inter = inter;
	
	list = SlistInsertBegin(list, &y);
	list = SlistInsertBegin(list, &z);
	list = SlistInsertBegin(list, &w);
	
	inter = SlistInsertBegin(inter, &second_data);
	inter->next->next = list->next;
	

	temp_inter = FindIntersection(copy_of_inter, list);
	assert(35 == *(int *)temp_inter->data);
	inter->next->next = NULL;
	
	list_copy = list;

	assert(4 == ListSize(list));
	
	while (NULL != list_copy)
	{
		printf("%d\n", *(int *)list_copy -> data);
		list_copy = list_copy -> next;
	}
	printf("\n");
	
	list = Flip(list);
	list_copy = list;

	
	while (NULL != list_copy)
	{
		printf("%d\n", *(int *)list_copy -> data);
		list_copy = list_copy -> next;
	}
	printf("\n");
	
	list_copy = list;
	end_of_list = LastNode(list_copy);
	end_of_list -> next = list->next->next;
	assert(1 == HasLoops(list));
	end_of_list -> next = NULL;
	
	
	DestroyNode(list);
	DestroyNode(inter);	
	
	return (0);
}
