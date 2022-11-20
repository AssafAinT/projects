/*
#################################################################
#	FILE: pqueue_test.c											#
#	Name: Ester													#
#	Reviewer: 	Assaf											#
#	PURPOSE: Priority queue test								#	 
#################################################################
*/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "pq.h" /* API functions */
#include "srtlist.h" /*API list functions*/






int CompareData(void *data1, void *data2 , void *params);
int IsMatch(const void *data, void *params);

int main()
{
	pqueue_ty *pq1 = NULL;
	
	int a =1;
	int b =2;
	int c =3;
	int d =4;

	
	/*Create check*/
	pq1 = PQueueCreate(CompareData, &a);
	
	/*Empty check*/
	assert(0 != PQueueIsEmpty(pq1));
	
	/*Enque Check*/
	assert(1 == PQueueEnqueue(pq1, &a));
	assert(1 == PQueueEnqueue(pq1, &b));
	assert(1 == PQueueEnqueue(pq1, &c));
	assert(1 == PQueueEnqueue(pq1, &d));
	
	/*size check*/
	assert(4 == PQueueSize(pq1));
	
	assert(2 == *(int *)PQueueErase(pq1, IsMatch, &b));
	assert(3 == PQueueSize(pq1));
	
	assert(1 == *(int *)PQueuePeek(pq1));

	PQueueDequeue(pq1);
	assert(2 == PQueueSize(pq1));
	
	
	
	

	PQueueClear(pq1);
	assert(0 == PQueueSize(pq1));

	
	
	PQueueDestroy(pq1);
	
	printf("If you didn't encounter any asserts, then you can go make your self a trophy coffee\n");
	
	return 0;
	
}

int IsMatch(const void *data, void *params)
{
	assert(NULL != data);
	assert(NULL != params);
	
	return (data == params);
}


int CompareData(void *data1, void *data2 , void *params)
{
	return ((*(int *)params) * (*(int *)data1) - 
											((*(int *)params) * (*(int *)data2)));
}

