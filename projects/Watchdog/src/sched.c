/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for scheduler implementation

*****************************/

#include <stdlib.h> 	/*free, malloc*/
#include <assert.h> 	/*assert*/
#include <unistd.h>		/*sleep*/
#include <stdio.h>		/*perror*/	

#include "../include/sched.h" 	/*sch_t*/
#include "../include/task.h" 	/*task_t, TaskAPI*/
#include "../include/uid.h"	/*uid_t, UID API*/
#include "../include/pq_heap.h"		/*pq_t, PQ API - Data Stracture*/

#define RUN 0
#define STOP 1

#define SUCCESS 0
#define FAILURE 1
#define PQFAIL -1

struct scheduler
{
	pq_t *tasks;
	int stop;
};


/*******************************************************************************
						help function declarations
*******************************************************************************/

int PriorityFunc(const void *data1, const void *data2);

int MatchFunc(const void *data1, const void *data2);

/*******************************************************************************
*******************************************************************************/


sch_t *SchCreate(void)
{
	sch_t *new_sch = (sch_t *)malloc(sizeof(sch_t));
	
	if (NULL == new_sch)
	{
		perror("Allocation Failed\n");
		return NULL;
	}
	
	new_sch->tasks = PQCreate(PriorityFunc);
	
	if(NULL == new_sch->tasks)
	{
		free(new_sch);
		return NULL;
	}
	
	new_sch->stop = RUN;
	
	return new_sch;
}

void SchDestroy(sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	SchClear(scheduler);
	PQDestroy(scheduler->tasks);
	free(scheduler);
}

ilrd_uid_t SchAddTask(sch_t *scheduler ,int (*op_func)(void *), void *params, time_t exec_time , time_t interval)
{
	task_t *new_task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	assert(NULL != op_func);
	
	new_task = TaskCreate(op_func, params, exec_time, interval);
	
	if (NULL == new_task || PQEnqueue(scheduler->tasks, (void *)new_task))
	{
		return UIDGetBad();
	}
	
	return TaskGetUID(new_task);
}

void SchRemoveTask(sch_t *scheduler ,ilrd_uid_t task_uid)
{	
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	TaskDestroy((task_t *)PQErase(scheduler->tasks, MatchFunc, &task_uid));
}

int SchIsEmpty(const sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	return PQIsEmpty(scheduler->tasks);
}
	
size_t SchSize(const sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	return PQSize(scheduler->tasks);
}
	
int SchRun(sch_t *scheduler)
{
	int status = SUCCESS;
	double time_to_sleep = 0;
	
	task_t *task = NULL;
	time_t curr_interval = 0;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	scheduler->stop = RUN;
	
	while (RUN == scheduler->stop && SUCCESS == status && !SchIsEmpty(scheduler))
	{
		task = (task_t *)PQPeek(scheduler->tasks);
		time_to_sleep = difftime(TaskGetExecTime(task), time(NULL));
		
		if (0 < time_to_sleep)
		{
			while(sleep((unsigned int)time_to_sleep));
		}
		
		status = TaskRunTask(task);
		
		PQDequeue(scheduler->tasks);
		
		curr_interval = TaskGetInterval(task);
		
		if (0 != curr_interval && SUCCESS == status)
		{
			TaskSetExecTime(task, time(NULL) + curr_interval);
			if (PQEnqueue(scheduler->tasks, (void *)task))
			{
				status = PQFAIL;
			}
		}
		else
		{
			TaskDestroy(task);
		}
	}
	
	return status;
}

void SchStop(sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	scheduler->stop = STOP;
}

void SchClear(sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	while (!PQIsEmpty(scheduler->tasks))
	{
		TaskDestroy(PQPeek(scheduler->tasks));
		PQDequeue(scheduler->tasks);
	}
}


/**************************************************************************************
							Helper Functions
**************************************************************************************/

/*priority to compare func*/
int PriorityFunc(const void *data1, const void *data2)
{
	return (int)difftime(TaskGetExecTime((task_t *)data2), TaskGetExecTime((task_t *)data1));
}

int MatchFunc(const void *data1, const void *data2)
{
	return UIDIsSame(TaskGetUID((task_t *)data1), *(ilrd_uid_t *)data2);
}
