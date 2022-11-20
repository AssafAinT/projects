/*****************************************************
 * Ds Exam                                           *
 * Assaf Ainhoren                                    *
 * Reviewer: Ofir - Kispel                           *
 * date: 09.07.21                                    *
 *****************************************************/
#include <stdio.h> /* printf, size_t */
#include <limits.h> /* CHAR_BIT */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc */


#define SIZE_OF_ARR_TO_SEND(arr) (sizeof(arr))/(sizeof(int))
#define Q_SIZE 12
#define Q_EMPTY 0
#define FAIL -1
#define SUCCESS 0


typedef struct node node_ty;
struct node
{
	void *data;
	struct node *next;
};
typedef struct dlnode dlnode_ty;
struct dlnode
{
	void *data;
	struct dlnode *next_node;
	struct dlnode *prev_node;
};

typedef struct cir_queue cirqueue_ty;
struct cir_queue
{
	char m_queue[Q_SIZE];
	size_t m_elements_in_q;
	size_t m_first_element_index;
};

static void TestFindNodeIntersect(void);
static size_t SlistSize(const node_ty *slist);
static void TestSlistRemove(void);
static void TestFindMissingNum(void);
static void TestQueue(void);


int main(void)
{
	/*TestSlistRemove();*/
	TestFindNodeIntersect();	
	TestFindMissingNum();
	TestQueue();	
	return (0);
}
/*----------------------------------------------------------------------------*/
/*                               2. FlipNode                                  */
/*----------------------------------------------------------------------------*/

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

 
/*----------------------------------------------------------------------------*/
/*                               3. SLL Time complexity                       */
/*----------------------------------------------------------------------------*/

/*          
   find O(n)
   insert O(n)
   delete O(n)
              */ 
/*----------------------------------------------------------------------------*/
/*                               4.HasLoop &Un-tie                             */
/*----------------------------------------------------------------------------*/
size_t FindLoops(node_ty *head)
{
	node_ty *slow_runner = head;
	node_ty *fast_runner = head;
	size_t size_to_ret = 0;
	assert(NULL != head);
	assert(NULL != head -> next);
	
	while((NULL != slow_runner && NULL != fast_runner) && 
		  (NULL != fast_runner->next))
	{
		slow_runner = slow_runner -> next; 
		fast_runner = fast_runner -> next -> next; 

	}
	
	if(slow_runner == fast_runner)
	{
			++size_to_ret;
			while (slow_runner->next != fast_runner)
			{
				slow_runner = slow_runner->next;
				++size_to_ret; 
			}
	}
	return (size_to_ret);
}

void UnTieLoop(node_ty *head, size_t loop_size)
{
	size_t iter = 0; 
	node_ty *loop_runner = NULL;
	node_ty *runner = head;
	
	for ( ; iter<loop_size +1; ++iter)
	{
		loop_runner = loop_runner->next;
	}
	
	while (runner != loop_runner)
	{
	
		for (iter = 0; iter < loop_size && runner != loop_runner; ++iter)
		{
			loop_runner = loop_runner->next;
		}
		runner = runner->next;
	}
	
	for (iter = 1; iter<loop_size; ++iter)
	{
		runner = runner->next;
	}
	runner->next = NULL;
}




/*----------------------------------------------------------------------------*/
/*                               5.intersection                               */
/*----------------------------------------------------------------------------*/
node_ty *FindNodeIntersect(node_ty *list1, node_ty *list2)
{
	node_ty *head_runner = NULL;
	node_ty *head2_runner = NULL;
	
	size_t size_list1 = 0;
	size_t size_list2 = 0;
	size_t offset_lists = 0;
	
	assert(NULL !=list1);
	assert(NULL !=list2);
	
	size_list1 = SlistSize(list1);
	size_list2 = SlistSize(list2);
	
	head_runner = list1;
	head2_runner = list2;
	
	if (size_list1 > size_list2)
	{
		offset_lists = size_list1 - size_list2;
		
		for ( ; 0 != offset_lists;
		     head_runner= head_runner->next,
		     --offset_lists)
		{
			/* empty loop */
		}
	}
	if (size_list2 > size_list1)
	{
		offset_lists = size_list2 - size_list1;
		
		for ( ; 0 != offset_lists;
		     head2_runner= head2_runner->next,
		     --offset_lists)
		{
			/* empty loop */
		}
	}
	
	for ( ; (NULL != head_runner)&&
		 (NULL != head2_runner) &&
		 head_runner != head2_runner;
		 head_runner= head_runner->next,
		 head2_runner= head2_runner->next)
		 {
		 /* empty loop */
		 }
	return (head_runner);

}

void SaparateIntersection(node_ty *head1, node_ty *head2)
{
	node_ty *saparate = NULL;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	saparate = FindNodeIntersect(head1, head2);
	
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



/*----------------------------------------------------------------------------*/
/*                               6.SlistRemove                                */
/*----------------------------------------------------------------------------*/
node_ty *SlistRemove(node_ty *slist)
{
	node_ty *node_to_remove = slist;
	
	if (NULL == slist->next->next)
	{
		((node_ty *)(slist->next->data))->next = slist;
	}
	
	slist->data = slist->next->data;
	slist->next = slist->next->next;
	
	free(node_to_remove);
	
	return(slist);
}


/*----------------------------------------------------------------------------*/
/*                               7.DlistInsetBefore                           */
/*----------------------------------------------------------------------------*/
dlnode_ty *DlistInsetBefore(dlnode_ty *dlist, void *data)
{
	dlnode_ty *new_node = NULL;
	
	new_node = malloc(sizeof(dlnode_ty));
	if (NULL == new_node)
	{
		return (NULL);
	}
	new_node->data = data;
	new_node->next_node = dlist;
	new_node->prev_node = dlist->prev_node;
	
	dlist->prev_node->next_node = new_node;
	dlist->prev_node = new_node;
}

/*----------------------------------------------------------------------------*/
/*                               7.DlistRemove                                */
/*----------------------------------------------------------------------------*/
dlnode_ty *DlistRemove(dlnode_ty *dlist)
{
	dlnode_ty *to_remove = dlist;


	dlist->prev_node->next_node = to_remove->next_node;
	dlist->next_node->prev_node = to_remove->prev_node;
	
	free(to_remove);
	return (dlist);
}
/*----------------------------------------------------------------------------*/
/*                               8.FindMissingNum                             */
/*----------------------------------------------------------------------------*/
unsigned int FindMissingNum(int *arr, unsigned int arr_size)
{
	unsigned int seq_sum = (((arr_size) * (arr_size + 1))/2);
	size_t i = 0;
	
	for ( ;i<arr_size; ++i)
	{
		seq_sum -= arr[i];
	}
	
	return (seq_sum);
}


/*----------------------------------------------------------------------------*/
/*                               10.CirQueue                                  */
/*----------------------------------------------------------------------------*/

int QueuePushChar(cirqueue_ty *cir_que, char data)
{
	size_t push_ind = 0;
	if (Q_SIZE == cir_que->m_elements_in_q)
	{
		return (FAIL);
	}
	push_ind = ((cir_que->m_first_element_index )+
				 (cir_que->m_elements_in_q)) % Q_SIZE;
	cir_que->m_queue[push_ind] = data;
	++(cir_que->m_elements_in_q);
	
	return (SUCCESS);
}

int QueuePopChar(cirqueue_ty *cir_que)
{
	if (Q_EMPTY == cir_que->m_elements_in_q)
	{
		return (FAIL);
	}
	cir_que->m_first_element_index += 1 % Q_SIZE;
	--(cir_que->m_elements_in_q);
	
	return (SUCCESS);
}
/*----------------------------------------------------------------------------*/
/*                               7.Tests                                      */
/*----------------------------------------------------------------------------*/

static void TestSlistRemove(void)
{
	node_ty *head = NULL;

	node_ty *node1 = NULL;
	node_ty *node2 = NULL;
	node_ty *node3 = NULL;
	node_ty *node4 = NULL;
	node_ty *node5 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	
	node1 = (node_ty *)malloc(sizeof(node_ty));
	node2 = (node_ty *)malloc(sizeof(node_ty));
	node3 = (node_ty *)malloc(sizeof(node_ty));
	node4 = (node_ty *)malloc(sizeof(node_ty));
	node5 = (node_ty *)malloc(sizeof(node_ty));
	
	
	node1->data = &num1;
	node2->data = &num2;
	node3->data = &num3;
	node4->data = &num4;
	node5->data = &num5;
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	
	head = node1;
	/*printf("slist size before remove: %ld\n", SlistSize(head));*/
	SlistRemove(node4);
	printf("node4 holds after remove: %ld\n", SlistSize(head));
}
static void TestFindNodeIntersect(void)
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

	intersection_node = FindNodeIntersect(head, another_head);


	if (NULL == intersection_node)
	{
		printf("\n\nThere is no itersection node\n\n");
	}
	else
	{
		printf("\n\nThere is itersection node\n\n");

	}
	
}

static void TestFindMissingNum(void)
{
	int arr[]= {0,1,5,3,2,6};
	int arr1[] = {0,2,3,4,5,6,7,8,9,10,11,12,13};
	int arr2[] = {1,2,4,3,5,6,7,8,9,10,11,12,13};
	size_t size = SIZE_OF_ARR_TO_SEND(arr);
	int miss_num = FindMissingNum(arr, size);
	assert(4 == miss_num);
	size = SIZE_OF_ARR_TO_SEND(arr1);
	miss_num = FindMissingNum(arr1, size);
	assert(1 == miss_num);
	size = SIZE_OF_ARR_TO_SEND(arr2);
	miss_num = FindMissingNum(arr2, size);
	assert(0 == miss_num);
	
	printf("Missing num successesed!!!\n");
}

static void TestQueue(void)
{
	cirqueue_ty cqueue = {{0}, 0, 0};
	char c1 = 'h';
	char c2 = 'e';
	char c3 = 'l';
	char c4 = 'l';
	char c5 = 'o';
	char c6 = 'a';
	char c7 = 's';
	char c8 = 's';
	char c9 = 'a';
	char c10 = 'f';
	size_t i = 0;

	QueuePushChar(&cqueue, c1);
	QueuePushChar(&cqueue, c2);
	QueuePushChar(&cqueue, c3);
	QueuePushChar(&cqueue, c4);
	QueuePushChar(&cqueue, c5);

	for (; i < cqueue.m_elements_in_q; ++i)
	{
		printf("%c", cqueue.m_queue[i]);
	}
	printf("\n");

	QueuePopChar(&cqueue);
	QueuePopChar(&cqueue);
	QueuePopChar(&cqueue);
	QueuePopChar(&cqueue);
	QueuePopChar(&cqueue);

	
	QueuePushChar(&cqueue, c6);
	QueuePushChar(&cqueue, c7);
	QueuePushChar(&cqueue, c8);
	QueuePushChar(&cqueue, c9);
	QueuePushChar(&cqueue, c10);

	for (i = 0; i < cqueue.m_elements_in_q; ++i)
	{
	}
		printf("%c", cqueue.m_queue[i]);
	printf("\n");

}
