/*****************************************************
 * Task                                              *
 * Assaf Ainhoren                                    *
 * Reviewer:                                         *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "task.h" 


int PrintTask(void *task_param);
int CleanUp(void *cleanup_param);

int main(void)
{
	char param = 97;
	int ret_stat = 0;
	size_t timer = 0;
	task_func operate = NULL;
	task_ty *tasky = CreateTask(PrintTask, &param, &CleanUp, NULL, 10);
	uid_ty task_uid = {0};
	
	task_uid = GetUid(tasky);
	assert(!UidIsEqual(task_uid, bad_uid));
	
	timer = GetTaskTimeInterval(tasky);
	operate = GetTask(tasky);
	
	ret_stat = operate(GetTaskParam(tasky));
	printf("%ld\n", task_uid.time);
	printf("%ld\n", GetTaskPriorTime(tasky));
	
	while (timer)
	{
		--timer;
	}
	
	GetCleanUp(tasky)(&ret_stat);
	
	DestroyTask(tasky);
	
	
	return (0);
}

int PrintTask(void *task_param)
{
	printf("%c im here\n", *(char *)task_param);
	
	return (*(int *)task_param);
}

int CleanUp(void *cleanup_param)
{
	printf("%d is cleaned\n", *(int *)cleanup_param);
	
	return (0);
}
