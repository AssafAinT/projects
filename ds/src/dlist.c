/*****************************************************
 * dlist WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayan Sheraizin                        *
 * date: 19.06.22                                    *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stdlib.h> /*malloc, free */
#include <assert.h> /*assert */

#include "dlist.h" /* slist */

/********************************dlist defining********************************/


struct node 
{
    void *data;
    struct node *next;
    struct node *previous;
};

typedef struct node node_ty;

struct dlist 
{
    node_ty head;
    node_ty tail;
};




static node_ty *CreateNode(void *data, node_ty *next, node_ty *previous);
static void UpdateNodeNext(node_ty *current_node, node_ty *new_next_node);
static void UpdateNodePrev(node_ty *current_node, node_ty *new_prev_node);
/********************************function definitions**************************/

/*----------------------------------------------------------------------------*/
/*                               DlistCreate                                  */
/*----------------------------------------------------------------------------*/
dlist_ty *DlistCreate(void)
{

	dlist_ty *dlist = (dlist_ty *)malloc(sizeof(dlist_ty));
	if (NULL == dlist)
	{
		return NULL;
	}
	
	dlist->head.data = dlist;
	dlist->head.previous = NULL;
	dlist->head.next = &dlist->tail;
	
	dlist->tail.data = dlist;
	dlist->tail.next = NULL;
	dlist->tail.previous = &dlist->head;

	return (dlist);
}
/*----------------------------------------------------------------------------*/
/*                               CreateNode                                   */
/*----------------------------------------------------------------------------*/
static node_ty *CreateNode(void *data, node_ty *next, node_ty *previous)
{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	UpdateNodeNext(new_node, next);
	UpdateNodePrev(new_node, previous);
	return (new_node);
}
/*----------------------------------------------------------------------------*/
/*                               DlistDestroy                                 */
/*----------------------------------------------------------------------------*/
void DlistDestroy(dlist_ty *dlist)
{
	assert(NULL != dlist);
	
	while(!DlistIsEmpty(dlist))
	{
		DlistRemove(DlistBegin(dlist));
	}

	free(dlist);
	dlist = NULL;	
}
/*----------------------------------------------------------------------------*/
/*                               InsertBefore                                 */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistInsertBefore(dlist_iterator_ty position, void *data)
{
	node_ty *new_node = NULL;
	dlist_iterator_ty iter_prev = DlistPrev(position);
	
	assert (NULL != position);
	
	new_node = CreateNode(data, position, position->previous);
	if (NULL == new_node)
	{
		for ( ;NULL != DlistNext(position);position = DlistNext(position))
		{
			/*empty loop */
		}
		return (position);
	}
	
	UpdateNodeNext(iter_prev, new_node);
	UpdateNodePrev(position, new_node);
	
	return (new_node);
}
/*----------------------------------------------------------------------------*/
/*                               DlistRemove                                  */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistRemove(dlist_iterator_ty iterator)
{
	dlist_iterator_ty next_iter = NULL;
    dlist_iterator_ty prev_iter = NULL;
    
    assert(NULL != iterator);
    
    next_iter = DlistNext(iterator);
    prev_iter = DlistPrev(iterator);
    
    UpdateNodePrev(next_iter, prev_iter);
    UpdateNodeNext(prev_iter, DlistNext(iterator));
    
    free(iterator);
    iterator = NULL;
    
    return next_iter;
}
/*----------------------------------------------------------------------------*/
/*                               DlistBegin                                   */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistBegin(const dlist_ty *dlist)
{
	assert(NULL !=dlist);
	
	return(dlist->head.next);
}
/*----------------------------------------------------------------------------*/
/*                               DlistEnd                                   */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistEnd(const dlist_ty *dlist)
{
	assert(NULL !=dlist);

	return (dlist_iterator_ty)(&(dlist->tail));	
}
/*----------------------------------------------------------------------------*/
/*                               DlistNext                                   */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistNext(dlist_iterator_ty iterator)
{
	assert(NULL != iterator);

	return (iterator->next);
}
/*----------------------------------------------------------------------------*/
/*                               DlistPrev                                   */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistPrev(dlist_iterator_ty iterator)
{
	assert(NULL != iterator);

	return(iterator->previous);
}
/*----------------------------------------------------------------------------*/
/*                               DlistSetData                                 */
/*----------------------------------------------------------------------------*/
void DlistSetData(dlist_iterator_ty iterator, const void *data)
{
	iterator->data = (void *)data;
}
/*----------------------------------------------------------------------------*/
/*                               DlistGetData                                 */
/*----------------------------------------------------------------------------*/
void *DlistGetData(dlist_iterator_ty iterator)
{	
	return (iterator->data);
}
/*----------------------------------------------------------------------------*/
/*                               DlistSize                                    */
/*----------------------------------------------------------------------------*/
size_t DlistSize(const dlist_ty *dlist)
{
	size_t dlist_size = 0;
	node_ty *runner =NULL;
	
	assert(NULL != dlist);

	
	
	for ( runner = DlistBegin(dlist);
		  runner != &dlist->tail;
	      (runner = DlistNext(runner)))
	{
		++dlist_size;
	}
	
	return (dlist_size);
}
/*----------------------------------------------------------------------------*/
/*                               DlistIsEmpty                                 */
/*----------------------------------------------------------------------------*/
int DlistIsEmpty(const dlist_ty *dlist)
{
	assert(NULL !=dlist);
	return (DlistBegin(dlist) == DlistEnd(dlist));
}
/*----------------------------------------------------------------------------*/
/*                               DlistIterIsEqual                             */
/*----------------------------------------------------------------------------*/
int DlistIterIsEqual(dlist_iterator_ty iterator1, dlist_iterator_ty iterator2)
{
	assert (NULL != iterator1);
	assert (NULL != iterator2);
	
	return ((iterator1) == (iterator2));
}
/*----------------------------------------------------------------------------*/
/*                               DlistForEach                                 */
/*----------------------------------------------------------------------------*/
int DlistForEach(dlist_iterator_ty from,
                dlist_iterator_ty to,
                action_ty action_func,
                void *param)
{
	int action_status = 0;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);

	
	for ( ;!DlistIterIsEqual(from, to); from = DlistNext(from))
	{
		action_status = action_func(DlistGetData(from), param);
		if (0 != action_status)
		{
			return action_status;
		}
	}
	
	return action_status;

}
/*----------------------------------------------------------------------------*/
/*                               DlistFind                                    */
/*----------------------------------------------------------------------------*/
dlist_iterator_ty DlistFind(dlist_iterator_ty from,
                            dlist_iterator_ty to,
                            is_match_ty match_func,
                            void *param)
{
	int is_match = 0;

	assert (NULL != from);
	assert (NULL != to);
	
	for ( ; !DlistIterIsEqual(from, to); from = DlistNext(from))
	{
		is_match = match_func(from -> data, param);
		
		if( 1 == is_match)
		{
			return (from);
		}	
	}
	return (to);
}
/*----------------------------------------------------------------------------*/
/*                               DlistMultiFind                               */
/*----------------------------------------------------------------------------*/
int DlistMultiFind(dlist_iterator_ty from,
                  dlist_iterator_ty to,
                  dlist_ty *dest_list,
                  is_match_ty match_func,
                   void *param)
{
    dlist_iterator_ty runner = {0};
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != match_func);
    assert(NULL != dest_list);
    
    runner = DlistFind(from, to, match_func, param);
    
    for( ; !DlistIterIsEqual(runner, to); 
           runner =  DlistFind(runner, to, match_func, param))
    {
        DlistInsertBefore(DlistEnd(dest_list), DlistGetData(runner));
        runner = DlistNext(runner);
    }
    
    return (!DlistIsEmpty(dest_list));

}
/*----------------------------------------------------------------------------*/
/*                               DlistSplice                                  */
/*----------------------------------------------------------------------------*/
void DlistSplice(dlist_iterator_ty where,
                 dlist_iterator_ty from,
                 dlist_iterator_ty to)
{
	dlist_iterator_ty copy_of_to_prev = NULL;
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);
	
	copy_of_to_prev = to->previous;
	
	UpdateNodeNext(from->previous,to);
	UpdateNodePrev(to, from->previous);
	UpdateNodePrev(from, where->previous);
	
	UpdateNodeNext(copy_of_to_prev, where);
	UpdateNodeNext(where->previous, from);
	UpdateNodePrev(where, copy_of_to_prev);

}

static void UpdateNodeNext(node_ty *current_node, node_ty *new_next_node)
{
	assert(NULL != current_node);
	assert(NULL != new_next_node);
	
	current_node->next = new_next_node;
}
static void UpdateNodePrev(node_ty *current_node, node_ty *new_prev_node)
{
	assert(NULL != current_node);
	assert(NULL != new_prev_node);
	
	current_node->previous = new_prev_node;
}
