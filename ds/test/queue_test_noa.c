#include <assert.h>  	/* assert */

#include "queue.h"


int main(void)
{
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;

	int num11 = 11;
	int num22 = 22;
	int num33 = 33;

	int status = 0;
	queue_ty *queue = QueueCreate();
	queue_ty *queue2 = QueueCreate();

	status = QueueEnqueue(queue, &num1);
	
	assert (0 == status);

	assert (1 == QueuetSize(queue));

	assert(0 == QueueIsEmpty(queue));

	assert (1 == *(int *)QueuePeek(queue));

	QueueDequeue(queue);

	assert(1 == QueueIsEmpty(queue));

	status = QueueEnqueue(queue, &num1);
	status = QueueEnqueue(queue, &num2);
	status = QueueEnqueue(queue, &num3);
	status = QueueEnqueue(queue, &num4);
	status = QueueEnqueue(queue, &num5);

	status = QueueEnqueue(queue2, &num11);
	status = QueueEnqueue(queue2, &num22);
	status = QueueEnqueue(queue2, &num33);

	QueueAppend(queue, queue2);
	/*
	QueueDisplayQueue(queue);
	*/
	QueueDestroy(queue);
	QueueDestroy(queue2);	
	return 0;
}
