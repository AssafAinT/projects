/****************************************/
/*										*/
/*			node1						*/
/*			Name : ofir krisple			*/
/*										*/
/****************************************/

/************Libraries Includes************/
#include <assert.h>	/*assert*/
#include <stdlib.h>	/*malloc, free*/

#include "node.h" 

/************CreateNewNode************/

node_ty *CreateNewNode(void *data)
{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->data = data;
	new_node->next = NULL;
	
	return (new_node);
}

/************DestroyNodeList************/

void DestroyNodeList(node_ty *head_node)
{
	node_ty *runner = NULL;
	node_ty *node_to_free = NULL;
		
	assert(NULL != head_node);
	
	runner = head_node;
	
	while (NULL != runner )
	{
		node_to_free = runner;
		runner = NextNode(runner);
		free(node_to_free);
	}
}

/************InsertNode************/

node_ty *InsertNode(node_ty *position, void *data)
{
	node_ty *new_node = CreateNewNode(data);
	
	new_node->next = position->next;
	
	position->next = new_node;
	
	return (position);
}

/************EndNode************/

node_ty *EndNode(node_ty *node)
{
	assert(NULL != node);

	while (NULL != node->next)
	{
		node = node->next;
	}
	
	return (node);
}

/************NextNode************/

node_ty *NextNode(node_ty *node)
{
	assert(NULL != node);
	
	return (node->next);
}

/************NodeSetData************/

void NodeSetData(node_ty *node, void *data)
{
	assert (NULL != node);
	
	node->data = data; 
}

/************NodeGetData************/

void *NodeGetData(const node_ty *node)
{
	assert(NULL != node);
	
	return (node->data);
}

/************ListSize************/

size_t ListSize(const node_ty *head_node)
{
	size_t count = 0;
	
	assert(NULL != head_node);
	
	while (NULL != head_node)
	{
		head_node = head_node->next;
		++count;
	}
	
	return (count);
}

/************listIsEmpty************/

int listIsEmpty(node_ty *head_node)
{
	assert(NULL != head_node);
	
	return (0 == ListSize(head_node));
}

/************listIterIsEqual************/

int listIterIsEqual(const node_ty *node1, const node_ty *node2)
{
	assert(NULL != node1);
	assert(NULL != node2);
	
	return (node1 == node2);
}


/************Flip************/

node_ty *Flip(node_ty *head_node)
{
	node_ty *prev_node = NULL;
	node_ty *next_node = NULL;
	
	assert(NULL != head_node);
		
	while (NULL != head_node)
	{	
		next_node = head_node->next;
		head_node->next = prev_node;
		prev_node = head_node;
		head_node = next_node;
	}
	return (prev_node);
}

/************HasLoop************/

int HasLoop(const node_ty *head_node)
{
	const node_ty *runner = head_node;
	const node_ty *runner_pi_2 = head_node->next;
	
	assert(NULL != head_node);
	
	while (runner != runner_pi_2 &&
		   NULL != runner_pi_2 &&
		   NULL != runner_pi_2->next)
	{
		runner = runner->next;
		runner_pi_2 = runner_pi_2->next->next;
	}

	return (listIterIsEqual(runner , runner_pi_2));
}

/************FinedIntersection************/

node_ty *FinedIntersection(node_ty *head1, node_ty *head2)
{
	size_t size1 = ListSize(head1);
	size_t size2 = ListSize(head2);
	size_t distance = 0;

	assert(NULL != head1);
	assert(NULL != head2);
	
	if (size1 > size2)
	{
		distance = size1 - size2;
		while (0 < distance)
		{
			head1 = NextNode(head1);
			--distance;
		}
	}
	else
	{
		distance = size2 - size1;
		while (0 < distance)
		{
			head2 = NextNode(head2);
			--distance;
		}
	}
	
	while (NULL != head1->next)
	{
		if (head1 == head2)
		{
			return (head1);
		}
		head1 = NextNode(head1);
		head2 = NextNode(head2);
	}
	return (NULL);
}




