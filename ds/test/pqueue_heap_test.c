#include <assert.h>	/*assert*/

#include "pqueue_heap.h" /*function decorations*/

int CompareData(const void *data1, const void *data2 , void *params);
bool_ty IsMatch(const void *data, const void *param);

#define UNUSED(params) (void)params
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
	
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data1));
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data2));
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data3));
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data4));
	
	assert(-3 == *(int *)PQueuePeek(prior_queue));
	PQueueDequeue(prior_queue);
	assert(-1 == *(int *)PQueuePeek(prior_queue));
	assert (3 == PQueueSize(prior_queue));
	PQueueClear(prior_queue);
	assert (1 == PQueueIsEmpty(prior_queue));
	
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data1));
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data2));
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data3));
	assert(SUCCESS == PQueueEnqueue(prior_queue, &data4));
	
	assert(66 == *(int *)PQueueErase(prior_queue, IsMatch, &data2));
	assert (3 == PQueueSize(prior_queue));
	
	assert(NULL == PQueueErase(prior_queue, IsMatch, &data7));
	PQueueDestroy(prior_queue);
	return (0);
}



bool_ty IsMatch(const void *data, const void *param)
{
	return (*(int*)data == *(int*)param);
}


int CompareData(const void *data1, const void *data2 , void *params)
{
	assert(NULL != data1);
	assert(NULL != data2);
	
	UNUSED (params);
	return (*(int*)data1 - *(int*)data2);
}
