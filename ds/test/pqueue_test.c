/*****************************************************
 * Priority-Queue                                    *
 * Assaf Ainhoren                                    *
 * Reviewer: Eitan Akrish                            *
 * date: 22.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#define UNUSED(param)  (void)param

#include <assert.h> /* assert */

#include "pqueue.h"

int CompareData(void *data1, void *data2 , void *params);
int MatchFunc(const void *data, void *params);
int main (void)
{
	int data1 = 22;
	int data2 = 66;
	int data3 = -1;
	int data4 = -3;
	int data7 = 12;
	pqueue_ty *prior_queue = PQueueCreate(CompareData, NULL);
	
	assert (1 == PQueueIsEmpty(prior_queue));
	assert (0 == PQueueSize(prior_queue));
	
	assert(0 == PQueueEnqueue(prior_queue, &data1));
	assert(0 == PQueueEnqueue(prior_queue, &data2));
	assert(0 == PQueueEnqueue(prior_queue, &data3));
	assert(0 == PQueueEnqueue(prior_queue, &data4));
	
	assert(-3 == *(int *)PQueuePeek(prior_queue));
	PQueueDequeue(prior_queue);
	assert(-1 == *(int *)PQueuePeek(prior_queue));
	assert (3 == PQueueSize(prior_queue));
	PQueueClear(prior_queue);
	assert (1 == PQueueIsEmpty(prior_queue));
	
	assert(0 == PQueueEnqueue(prior_queue, &data1));
	assert(0 == PQueueEnqueue(prior_queue, &data2));
	assert(0 == PQueueEnqueue(prior_queue, &data3));
	assert(0 == PQueueEnqueue(prior_queue, &data4));
	
	assert(66 == *(int *)PQueueErase(prior_queue, MatchFunc, &data2));
	assert (3 == PQueueSize(prior_queue));
	
	assert(NULL == PQueueErase(prior_queue, MatchFunc, &data7));
	PQueueDestroy(prior_queue);
	return (0);
}



int CompareData(void *data1, void *data2 , void *params)
{
	UNUSED(params);
	
	return ((*(int *)(data1)) - (*(int *)data2));
}




int MatchFunc(const void *data, void *params)
{
	
	return (data == params);
}
