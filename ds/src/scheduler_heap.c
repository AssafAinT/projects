/*****************************************************
* Scheduler                                         *
* Assaf Ainhoren                                    *
* Reviewer:Eitan Akrish                             *
* date: 19.06.2022                                  *
*****************************************************/

/********************************libraries includes****************************/
#include <stdlib.h> /* malloc, free */ 
#include <assert.h> /* assert */
#include <stdio.h> 

#include "scheduler_heap.h"
#include "pqueue_heap.h"
#include "task.h"

/********************************macros defines********************************/
#define UNUSED(param)  (void)param
#define FAILURE_IN_TIME -1
#define TO_CYCLE 0
#define SUCCESS 0
#define FAIL 1
#define NOT_RUNNING 0
#define RUNNING 1
#define GET_SCHEDULER(scheduler)  scheduler->scheduler
/********************************struct defines********************************/
struct scheduler
{
    pqueue_ty *scheduler;
    int is_run;
};
/**********************Static Functions Declarations***************************/
static int CompareData(const void *data1, const void *data2 , void *params);

static bool_ty IsMatchUid(const void *uid_to_remove, const void *current_task);

static time_t SetDelta(task_ty *mission, time_t current_time);

static void SchedulerReEnqueue(scheduler_ty *scheduler, task_ty *task);

/********************************Function declarations*************************/
scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *scheduler = (scheduler_ty *)malloc(sizeof(scheduler_ty));
	if (NULL == scheduler)
	{
		return (NULL);
	}
	scheduler->scheduler = PQueueCreate(CompareData, NULL);
	if (NULL == scheduler->scheduler)
	{
		free(scheduler);
		scheduler = NULL;
		return (NULL);
	}
	
	return(scheduler);
}

void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(NULL!=scheduler);
	
	assert(NULL!=scheduler);

	SchedulerClear(scheduler);
	
	PQueueDestroy(GET_SCHEDULER(scheduler));
	scheduler->scheduler = NULL;

	free(scheduler);
	scheduler = NULL;
}

uid_ty SchedulerAddTask(scheduler_ty *scheduler,
						operation_func task,
                        void *task_param, cleanup_func cleanup,
                        void *cleanup_param, size_t time_interval)
{
	task_ty *task_to_send = NULL;
	
	task_to_send = CreateTask(task,
	                          task_param,
	                          cleanup,
	                          cleanup_param,
	                          time_interval);
	
	if (NULL == task_to_send)
	{
		return (bad_uid);
	}
	
	if (FAIL == PQueueEnqueue(GET_SCHEDULER(scheduler), task_to_send))
	{
		DestroyTask(task_to_send);
		return (bad_uid);
	}
	return (GetUid(task_to_send));
}

int SchedulerRemoveTask(scheduler_ty *scheduler, uid_ty uid)
{
	task_ty *task_found = NULL;
	int ret_stat = SUCCESS;
	assert(NULL != scheduler);
	assert(!UidIsEqual(bad_uid, uid));
	
	task_found = PQueueErase(scheduler->scheduler, IsMatchUid, &uid);
	if (NULL == task_found)
	{
		ret_stat = FAIL;
	}
	DestroyTask(task_found);
	
	return (ret_stat);
}

static bool_ty IsMatchUid(const void *uid_p, const void *task)
{
	return (UidIsEqual(*(uid_ty *)uid_p, 
			 GetUid((task_ty *)task)));

}

int SchedulerRun(scheduler_ty *scheduler)
{
	int ret_status = SUCCESS;
	time_t delta = 0;
	time_t time_to_send =0;
	task_ty *to_run = NULL;
	
	assert(NULL != scheduler);
	scheduler->is_run = RUNNING;
	while ((RUNNING == scheduler->is_run) && 
		  !SchedulerIsEmpty(scheduler))
	{
		time_to_send = time(NULL);
		to_run = (task_ty *)(PQueuePeek(GET_SCHEDULER(scheduler)));
		PQueueDequeue(GET_SCHEDULER(scheduler));
		delta = SetDelta(to_run, time_to_send); 
		
		if (FAILURE_IN_TIME == delta)
		{
			puts("you here?");
			DestroyTask(to_run);
			return (FAILURE_IN_TIME);
		}
		while (0 != sleep(delta));
		
	 	ret_status = RunTask(to_run);
	 	
		if(TO_CYCLE == ret_status)
		{
			SchedulerReEnqueue(scheduler, to_run);
		}
		else
		{
			RunClean(to_run);
			DestroyTask(to_run);
		}	
	}
	return ret_status;
}



void SchedulerStop(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != GET_SCHEDULER(scheduler));

	scheduler->is_run = NOT_RUNNING;

}

size_t SchedulerSize(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	
	return(PQueueSize(GET_SCHEDULER(scheduler)));
}

int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQueueIsEmpty(GET_SCHEDULER(scheduler)));
}

void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *task_to_clear = NULL;
	
	assert(NULL != scheduler);
	
	while (!SchedulerIsEmpty(scheduler))
	{
		task_to_clear = PQueuePeek(GET_SCHEDULER(scheduler));
		SchedulerRemoveTask(scheduler,GetUid(task_to_clear));
	}
}



/********************************static func declaration***********************/
static int CompareData(const void *data1, const void *data2 , void *params)
{
	UNUSED(params);
	
	return (GetTaskPriorTime((task_ty *)(data1)) - 
	       (GetTaskPriorTime((task_ty *)(data2))));
}

static time_t SetDelta(task_ty *mission, time_t current_time)
{
	time_t ret = 0;

	
	if (FAILURE_IN_TIME == current_time )
	{
		ret = FAILURE_IN_TIME;
	}
	else
	{
		UpdateTaskRunTime(mission);
		ret = GetTaskPriorTime(mission)- (current_time);		
	}
	return (ret);
}

static void SchedulerReEnqueue(scheduler_ty *scheduler, task_ty *task)
{
	assert(NULL != scheduler);
	assert(NULL != task);
	
	UpdateTaskRunTime(task);
	if (FAIL == PQueueEnqueue(GET_SCHEDULER(scheduler), task))
	{
		DestroyTask(task);
	}
	
}

