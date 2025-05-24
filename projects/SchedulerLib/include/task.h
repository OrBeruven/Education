/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : header file for task module

*****************************/

#ifndef __ILRD_OL139_40_TASK_H__
#define __ILRD_OL139_40_TASK_H__

#include <time.h> /*time_t*/

#include "uid.h" /*ilrd_uid_t*/

typedef struct task task_t;
typedef int (*op_func_t)(void *);

/*
* TaskCreate Description:
*	Creates a new task structure and adds Unique ID	
*				 											
* @params:
*	op_func - Pointer to a operation function
*	params - params to be executed with op_func
*	exec_time - time to execute in time_t format
*	interval - in seconds, when to repeat task
*
* @returns:
*	Pointer to task. If error occured - returns null.
*
* @Complexity
*	O(1)
*/
task_t *TaskCreate(int (*op_func)(void *), void *params, time_t exec_time , time_t interval);


/*
* TaksDestroy Description:
* 	Deallocates a given task from memory.
* 
* @params:
*	task - pointer to task to be freed from memory
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	None
*
* @Complexity
*	O(1)
*/
void TaskDestroy(task_t *task);

/*
* TaksRunTask Description:
* 	Execute the proccess of the task.
* 
* @params:
*	task - pointer to the task containing operation func to execute
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	returns task's operation function status.
*	in general, 0 for successm otherwise for failure
*
* @Complexity
*	O(1)
*/
int TaskRunTask(task_t *task);

/*
* TaskGetExecTime Description:
* 	get the time to execute in time_t format.
* 
* @params:
*	task - pointer to the task containing time to execute
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	returns task's time to execute in time_t format
*
* @Complexity
*	O(1)
*/
time_t TaskGetExecTime(task_t *task);

/*
* TaskGetInterval Description:
* 	get the time interval to the next execute in time_t format.
* 
* @params:
*	task - pointer to the task containing interval time to execute
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	returns task's interval time to execute in time_t format
*
* @Complexity
*	O(1)
*/
time_t TaskGetInterval(task_t *task);

/*
* TaskGetUID Description:
* 	get the task's uid.
* 
* @params:
*	task - pointer to the task containing uid
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	returns task's uis int ilrd_uid_t format
*
* @Complexity
*	O(1)
*/
ilrd_uid_t TaskGetUID(task_t *task);

/*
* TaskGetFunc Description:
* 	get the task's pointer to function.
* 
* @params:
*	task - pointer to the task containing pointer to function
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	returns task's function pointer in int (*op_func)(void *) format
*
* @Complexity
*	O(1)
*/
op_func_t TaskGetFunc(task_t *task);

/*
* TaskGetParams Description:
* 	get the task's pointer to function's parameters.
* 
* @params:
*	task - pointer to the task containing parameters
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	returns task's function parameters in void * format
*
* @Complexity
*	O(1)
*/
void *TaskGetParams(task_t *task);

/*
* TaskSetExecTime Description:
* 	change the execution time of a given task.
* 
* @params:
*	task - pointer to the wanted task to change 
* 	If the pointer is invalid - behavior is undefined.
*	exec_time - execution value in time_t format to be changed in task
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetExecTime(task_t *task, time_t exec_time);


/*
* TaskSetInterval Description:
* 	change the interval time of a given task.
* 
* @params:
*	task - pointer to the wanted task to change 
* 	If the pointer is invalid - behavior is undefined.
*	interval - interval value in time_t format to be changed in task
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetInterval(task_t *task, time_t interval);

/*
* TaskSetFunc Description:
* 	change the function pointer of a given task.
* 
* @params:
*	task - pointer to the wanted task to change 
* 	If the pointer is invalid - behavior is undefined.
*	op_func - pointer to function to be changed in task
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetFunc(task_t *task, int (*op_func)(void *));

/*
* TaskSetParams Description:
* 	change the parameters to function of a given task.
* 
* @params:
*	task - pointer to the wanted task to change 
* 	If the pointer is invalid - behavior is undefined.
*	params - params to be changed in task in void* format
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetParams(task_t *task, void *params);

#endif
