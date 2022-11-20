#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
	void *data;
	struct node *next;
}node_ty;

node_ty *Create_List();
node_ty *Flip(node_ty *head);
int HasLoops(const node_ty *head);
node_ty *FindIntersection(node_ty *head1, node_ty *head2);


int main(void)
{
	int x = 20;
	int y = 22;
	int z = 35;
	
	return (0);
}

node_ty *CreateNode(void *data)
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
	assert(NULL != node);
	
	runner = node;
	copy_of_node = node;
	while(NULL != runner_node -> next)
	{
		runner = runner -> next;
		free(node_to_free);
		copy_of_node = runner;
	}
	
	free(runner);	
}
/*
void SlistInsertBegin(node_ty *head, void *data)
{
	
}*/
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
	
	head = prev;
	return (head);
}

int HasLoops(const node_ty *head)
{
	assert(NULL != head);
	assert(NULL != head -> next);
	
	node_ty *slow_runner = head;
	node_ty *fast_runner = head;
	
	while((NULL != slow_runner && NULL != fast_runner) && NULL != fast_runner->next)
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
/*
node_ty FindIntersection(node_ty *head1, node_ty *head2)
{
	
}*/
