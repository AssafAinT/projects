/*
#################################################################
#	FILE: pq.c											#
#	Name: Ester													#
#	Reviewer: 	Assaf												#
#	PURPOSE: pq source									#	 
#################################################################
*/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "srtlist.h" /*sort list functions*/
#include "pq.h" /*API list functions*/

struct pqueue
{
	srtlist_ty *queue;
};

pqueue_ty *PQueueCreate(cmp_priority_func cmp_priority, void *param)
{
	pqueue_ty *new_queue = (pqueue_ty *)malloc(sizeof(pqueue_ty));
	if(!new_queue)
	{
		new_queue = NULL;
		return NULL;
	}
	
	new_queue->queue = SrtlistCreate(cmp_priority, param);
	if(!new_queue->queue)
	{
		free(new_queue);
		return NULL;
	}
	
	return (new_queue);
}



void PQueueDestroy(pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	SrtlistDestroy(pqueue->queue);
	free(pqueue);
	
	return;
}



int PQueueEnqueue(pqueue_ty *pqueue, void *data)
{
	srtlist_iterator_ty inserted_iter = {0};
	
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	inserted_iter = SrtlistInsert(pqueue->queue, data);
	
	return(SrtlistIterIsEqual(inserted_iter, SrtlistEnd(pqueue->queue)));
}

void PQueueDequeue(pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	SrtlistRemove(SrtlistBegin(pqueue->queue));
	
	return;
}

void *PQueuePeek(const pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	return (SrtlistGetData(SrtlistBegin(pqueue->queue)));

}

size_t PQueueSize(const pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	return (SrtlistSize(pqueue->queue));

}

int PQueueIsEmpty(const pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	return (SrtlistIsEmpty(pqueue->queue));
}

void PQueueClear(pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	while (!PQueueIsEmpty(pqueue))
	{
		PQueueDequeue(pqueue);
	}

	
	return;
}


void *PQueueErase(pqueue_ty *pqueue, is_data_match_ty is_match, void *param) /*data in temp*/
{
	srtlist_iterator_ty iter_to_rip = {0};
	
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	
	iter_to_rip = SrtlistFindIf(SrtlistBegin(pqueue->queue), 
                               			 SrtlistEnd(pqueue->queue),
                             							   is_match, param);
                                  
	if (NULL != iter_to_rip.dlist_iterator)
	{
		SrtlistRemove(iter_to_rip);	
	}
	else
	{
		param = NULL;
	}
	
	return param;

}
