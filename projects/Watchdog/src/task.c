/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for task module implementation

*****************************/

#include <stdio.h> /*perror*/
#include <stdlib.h>/*free, malloc*/
#include <assert.h> /*assert*/

#include "../include/task.h"

#define SUCCESS 0

struct task
{
	time_t exec_time;
	int (*op_func)(void *);
	void *params;
	time_t interval;
	ilrd_uid_t uid;
};

task_t *TaskCreate(int (*op_func)(void *), void *params, time_t exec_time , time_t interval)
{
	task_t *new_task = NULL;
	
	assert(NULL != op_func);
	
	new_task = (task_t *)malloc(sizeof(task_t));
	if(NULL == new_task)
	{
		perror("Allocation Failed\n");
		return NULL;
	}
	
	new_task->op_func = op_func;
	new_task->params = params;
	new_task->exec_time = exec_time;
	new_task->interval = interval;
	new_task->uid = UIDCreate();
	
	if (UIDIsSame(new_task->uid, UIDGetBad()))
	{
		return NULL;
	}
	
	return new_task;
}

void TaskDestroy(task_t *task)
{
	free(task);
	task = NULL;
}
	
int TaskRunTask(task_t *task)
{
	assert(NULL != task);
	
	return task->op_func(TaskGetParams(task));
}

time_t TaskGetExecTime(task_t *task)
{
	assert(NULL != task);
	
	return task->exec_time;
}

time_t TaskGetInterval(task_t *task)
{
	assert(NULL != task);
	
	return task->interval;
}

ilrd_uid_t TaskGetUID(task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

op_func_t TaskGetFunc(task_t *task)
{
	assert(NULL != task);
	
	return task->op_func;
}

void *TaskGetParams(task_t *task)
{
	assert(NULL != task);
	
	return task->params;
}

void TaskSetExecTime(task_t *task, time_t exec_time)
{
	assert(NULL != task);
	
	task->exec_time = exec_time;
}

void TaskSetInterval(task_t *task, time_t interval)
{
	assert(NULL != task);
	
	task->interval = interval;
}

void TaskSetFunc(task_t *task, int (*op_func)(void *))
{
	assert(NULL != task);
	
	task->op_func = op_func;
}

void TaskSetParams(task_t *task, void *params)
{
	assert(NULL != task);
	
	task->params = params;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
