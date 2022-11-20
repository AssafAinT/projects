/*****************************************************
 * Slisr WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Haggai Newman                           *
 * date: 05.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stddef.h> /* size_t */ 
#include <stdlib.h> /*malloc */
#include <assert.h> /*assert */

#include "slist.h" /* slist */

/********************************slist defining********************************/
typedef struct node node_ty;

struct node
{
    void *data;
    struct node *next;
};

struct slist 
{
    node_ty *head;
    node_ty *tail;
};


/********************************function definitions**************************/

slist_ty *SlistCreate(void)
{
	node_ty *dummy = NULL;
	
	slist_ty *new_list = (slist_ty *)malloc(sizeof(slist_ty));
	if (NULL == new_list)
	{
		return NULL;
	}
	dummy = (node_ty *)malloc(sizeof(node_ty));
	if (NULL == new_list)
	{
		free(new_list);
		return NULL;
	}
	
	dummy -> data = (void *)new_list; 
	dummy -> next = (node_ty *)0xDEADBEEF;
	
	new_list -> head = dummy;
	new_list -> tail = dummy;
	
	return (new_list);
}


void SlistDestroy(slist_ty *slist)
{
	
	assert(NULL != slist);
	assert(NULL != slist -> head);
	assert(NULL != slist -> tail);
	
	while(!SlistIsEmpty(slist))
	{
		SlistRemove(slist -> head);
	}
	
	free(slist->tail);
	free(slist);	

}


slist_iterator_ty SlistInsertBefore(slist_iterator_ty position, void *data)
{
	node_ty *new_node = NULL;
	
	assert (NULL != position);
	new_node = (node_ty *)malloc(sizeof(node_ty));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	if (0xDEADBEEF == (size_t)(position->next))
	{
		((slist_ty *)(position -> data))->tail = new_node;
	}
	
	new_node->data = position->data;
	new_node->next = position->next;
	
	position->data = data;
	position->next = new_node;
	
	return (position);
} 

slist_iterator_ty SlistBegin(const slist_ty *slist)
{
	assert(NULL != slist);
	assert(NULL != slist->head);
	
	
	return (slist->head);
}
slist_iterator_ty SlistEnd(const slist_ty *slist)
{
	assert(NULL != slist);
	assert(NULL != slist->tail);

	return(slist->tail);
}

slist_iterator_ty SlistNext(const slist_iterator_ty iterator) 
{
	assert (NULL != iterator);
	
	return (iterator->next);	
}


slist_iterator_ty SlistRemove(slist_iterator_ty iterator)
{
	node_ty *copy_of_next = iterator->next; 
	
	assert (NULL != iterator);
	assert (NULL != iterator -> next);
	
	
	/* checking if iterator is one before the dummy */
	if (0xDEADBEEF == (size_t)(iterator -> next -> next))  
	{
		((slist_ty *)(iterator ->next-> data)) -> tail = iterator;	
	}
	
	/* the iterator is being switched to be the dummy */
	iterator -> data = iterator -> next->data;
	iterator -> next = iterator -> next->next;
	
	free(copy_of_next);
	
	return (iterator);
}

void SlistSetData(slist_iterator_ty iterator, void *data)
{
	assert (NULL != iterator);
	
	iterator->data = data;
	
}

void *SlistGetData(const slist_iterator_ty iterator)
{
	assert (NULL != iterator->next);
	
	return (iterator -> data);
}

size_t SlistSize(const slist_ty *slist)
{
	size_t counter = 0;
	node_ty *runner =NULL;
	
	assert(NULL != slist);
	assert(NULL != slist -> head);
	assert(NULL != slist -> tail);
	
	runner= slist -> head;
	
	for ( ; (slist -> tail) != (runner ) ; (runner =SlistNext(runner)))
	{
		++counter;
	}
	
	return (counter);
}

int SlistIsEmpty(const slist_ty *slist)
{
	return (slist -> head == slist -> tail);
}


int SlistIterIsEqual(const slist_iterator_ty iterator1, const slist_iterator_ty iterator2)
{
	assert (NULL != iterator1);
	assert (NULL != iterator2);
	
	return ((iterator1) == (iterator2));
}

/* not include iterator to */ 
int SlistForEach(slist_iterator_ty from, slist_iterator_ty to, action_ty action_func, void *param)
{
	int action_result = 0;

	assert (NULL != from);
	assert (NULL != to);
	
	for ( ; from -> next != to ; from = SlistNext(from))
	{
		action_result = action_func(from -> data, param);
		
		if(0 != action_result)
		{
			return action_result;
		}	
	}
	return 0;
}



slist_iterator_ty SlistFind(slist_iterator_ty from, slist_iterator_ty to,
 is_match_ty match_func, void *param)
{
	int action_result = 0;

	assert (NULL != from);
	assert (NULL != to);
	
	for ( ; from -> next != to ; from = SlistNext(from))
	{
		action_result = match_func(from -> data, param);
		
		if( 1 == action_result)
		{
			return (from);
		}	
	}
	return (to);
}


void SlistAppend(slist_ty *dest, slist_ty *src)
{
	
    assert(NULL != dest);
    assert(NULL != src);
    
    dest->tail->data = src->head->data;
    dest->tail->next = src->head->next;

    src->tail->data = dest;
    dest->tail=src->tail;

    src->head->next = NULL;
    src->tail=src->head;
    
    SlistDestroy(src);

}
