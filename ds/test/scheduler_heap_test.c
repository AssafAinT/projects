/*****************************************************
 * Scheduler                                         *
 * Assaf Ainhoren                                    *
 * Reviewer:Eitan Akrish                             *
 * date: 19.06.2022                                  *
 *****************************************************/
 

#define UNUSED(param)  (void)param
/********************************libraries includes****************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /*malloc */

#include "scheduler_heap.h"

/********************************struct for removing tasks*********************/
typedef struct task_to_remove task_to_rem_ty;
struct task_to_remove 
{
	scheduler_ty *scheduler; 
	uid_ty task_uid;
};
/********************************functions declartions*************************/
int PrintTask(void *task_param);
int PrintNum(void *param);
int CallStop(void *scheduler);
int CallAdd(void *scheduler);
int PrintTheAdd(void *param);
int CallRemove(void *scheduler);
void CleanUp(void *cleanup_param);
void CleanUpStop(void *cleanup_param);
void CleanUpRemove(void *cleanup_param);

int main(void)
{
	
	task_to_rem_ty *task_to_rem = NULL;
	scheduler_ty *scheduler = SchedulerCreate();
	uid_ty uid_print_task = {0};
	uid_ty uid_print_num = {0};
	uid_ty uid_stop_it = {0};
	uid_ty uid_call_add = {0};
	uid_ty uid_call_remove = {0};
	
	int ret_status = 0;
	int num = 110;
	
	task_to_rem = (task_to_rem_ty *)malloc(sizeof(task_to_rem_ty));
	if (NULL == task_to_rem)
	{
		return 1;
	}
	
	assert(SchedulerIsEmpty(scheduler));
	assert(0 == SchedulerSize(scheduler));
	
	uid_print_task = SchedulerAddTask(scheduler,
					 PrintTask,
					 NULL,
					 CleanUp,
					 NULL,
					 6);
	
	
	uid_print_num = SchedulerAddTask(scheduler,
					 PrintNum,
					 &num,
					 CleanUp,
					 NULL,
					 1);
	
	task_to_rem->scheduler = scheduler;
	task_to_rem->task_uid = uid_print_num;
	
	uid_stop_it = SchedulerAddTask(scheduler,
					 CallStop,
					 scheduler,
					 CleanUpStop,
					 NULL,
					 4);

	uid_call_add = SchedulerAddTask(scheduler,
	                                CallAdd,
	                                scheduler,
	                                CleanUp,
	                                NULL,
	                                3);
	                                
	/* by adding this task we should only see 2 
	shows of the first task till it will be removed */
	uid_call_remove = SchedulerAddTask(scheduler,
	                                   CallRemove,
	                                   task_to_rem,
	                                   CleanUpRemove,
	                                   NULL,
	                                   2);
	                               
	assert(5 == SchedulerSize(scheduler));
	assert(!UidIsEqual(uid_print_task, bad_uid));
	assert(!UidIsEqual(uid_call_add, bad_uid));
	assert(!UidIsEqual(uid_call_remove, bad_uid));
	assert(!UidIsEqual(uid_stop_it, bad_uid));
	assert(!UidIsEqual(uid_print_num, bad_uid));
	/* run oper till stop func*/
	
	ret_status = SchedulerRun(scheduler);
	/* continue to run after stop */
	
	ret_status = SchedulerRun(scheduler);
	
	SchedulerDestroy(scheduler);
	free(task_to_rem);
	
	return (ret_status);
}


int PrintTask(void *task_param)
{
	UNUSED(task_param);
	
	printf("Hi i am here\n");
	return (1);
}

int PrintNum(void *param)
{
	int ret = 0;
	static size_t counter = 0;
	

	printf("now %d\n", *(int *)param);

	++counter;
	
	if (4 == counter)
	{
		ret = 1;
	}
	return ret;
}

int CallStop(void *scheduler)
{
	SchedulerStop(scheduler);
	printf("Stop?\n");
	return (1);
}


void CleanUp(void *cleanup_param)
{
	UNUSED(cleanup_param);
	printf("Your are all Clean\n");
}

void CleanUpStop(void *cleanup_param)
{
	UNUSED(cleanup_param);
	printf("Cleaned Stop\n");
}

int CallAdd(void *scheduler)
{
	SchedulerAddTask(scheduler,
					PrintTheAdd,
					NULL,
					CleanUp,
					NULL,
					2);
	return (1);
}

int PrintTheAdd(void *param)
{
	UNUSED(param);
	printf("i have been added by the user\n");
	
	return (1);
}


int CallRemove(void *scheduler)
{
	SchedulerRemoveTask(((task_to_rem_ty *)scheduler)->scheduler,
	 (((task_to_rem_ty *)scheduler)->task_uid));
	return (1);
}

void CleanUpRemove(void *clean_param)
{
	UNUSED(clean_param);
	printf("The Function has been removed \n");
}

