/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for Task tests

*****************************/

#include <stdio.h>
#include <time.h>

#include "utilities.h"
#include "task.h"
#include "uid.h"

/*******************************************************************************
						Help function declarations
*******************************************************************************/
int PrintToScreen(void *params);

int PrintToScreenFail(void *params);

int DoNothing(void *params);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void RunTaskTest(void);

static void GetExecTimeTest(void);

static void GetIntervalTest(void);

static void GetUIDTest(void);

static void GetFuncTest(void);

static void GetParamsTest(void);

static void SetExecTimeTest(void);

static void SetIntervalTest(void);

static void SetFuncTest(void);

static void SetParamsTest(void);
/*******************************************************************************
*******************************************************************************/
int main()
{
	printf("Testing Create\n");
	CreateDestroyTest();
	printf("\n");

	printf("Testing Run Task\n");
	RunTaskTest();
	printf("\n");
		
	printf("Testing GetExecTime\n");
	GetExecTimeTest();
	printf("\n");
	
	printf("Testing GetInterval\n");
	GetIntervalTest();
	printf("\n");
	
	printf("Testing GetUID\n");
	GetUIDTest();
	printf("\n");
	
	printf("Testing GetFunc\n");
	GetFuncTest();
	printf("\n");
	
	printf("Testing GetParams\n");
	GetParamsTest();
	printf("\n");
	
	printf("Testing SetExecTime\n");
	SetExecTimeTest();
	printf("\n");
	
	printf("Testing SetInterval\n");
	SetIntervalTest();
	printf("\n");
	
	printf("Testing SetFunc\n");
	SetFuncTest();
	printf("\n");
	
	printf("Testing SetParams\n");
	SetParamsTest();
	printf("\n");
	
	return 0;
}

/*******************************************************************************
						Test function definitions
*******************************************************************************/
static void CreateDestroyTest(void)
{
	task_t *task = NULL;
	
	RESULTSTATUS(NULL == task, 1);
	task = TaskCreate(PrintToScreen, NULL, 0, 0);
	RESULTSTATUS(NULL == task, 0);
	
	TaskDestroy(task);
}

static void RunTaskTest(void)
{
	task_t *task = NULL;
	task_t *failed_success = NULL;
	task = TaskCreate(PrintToScreen, NULL, 0, 0);
	RESULTSTATUS(NULL == task, 0);
	printf("Should Print 'TESTESTEST' : ");
	RESULTSTATUS(TaskRunTask(task), 0);
	
	failed_success = TaskCreate(PrintToScreenFail, NULL, 0, 0);
	printf("Should Print 'FAILED SUCCESFULLY' : ");
	RESULTSTATUS(TaskRunTask(failed_success), 1);
	
	TaskDestroy(failed_success);
	TaskDestroy(task);
}

static void GetExecTimeTest(void)
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;
	strptime("6 Dec 2001 12:33:45", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, t, 0);
	
	RESULTSTATUS(t == TaskGetExecTime(task), 1);
	
	t = time(0);
	
	RESULTSTATUS(t == TaskGetExecTime(task), 0);
	
	TaskDestroy(task);
}

static void GetIntervalTest(void)
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;
	strptime("6 Dec 2001 12:33:45", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, 0, t);
	
	RESULTSTATUS(t == TaskGetInterval(task), 1);
	
	t = time(0);
	
	RESULTSTATUS(t == TaskGetInterval(task), 0);
	
	TaskDestroy(task);
	
	task = TaskCreate(DoNothing, NULL, 0, 1);
	RESULTSTATUS(1 == TaskGetInterval(task), 1);
	TaskDestroy(task);
}

static void GetUIDTest(void)
{
	task_t *task = NULL;
	task_t *task2 = NULL;
	ilrd_uid_t uid;
	ilrd_uid_t bad;
	task = TaskCreate(DoNothing, NULL, 1, 1);
	
	bad = UIDGetBad();
	
	RESULTSTATUS(UIDIsSame(TaskGetUID(task), bad), 0);
	
	
	RESULTSTATUS(UIDIsSame(TaskGetUID(task), TaskGetUID(task)), 1);
	
	uid = TaskGetUID(task);
	task2 = TaskCreate(DoNothing, NULL, 1, 1);
	RESULTSTATUS(UIDIsSame(uid, TaskGetUID(task)), 1);
	RESULTSTATUS(UIDIsSame(uid, TaskGetUID(task2)), 0);
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void GetFuncTest(void)
{
	task_t *task = NULL;
	task_t *task2 = NULL;
	int (*func_pointer)(void *) = NULL;
	int (*func_pointer2)(void *) = NULL;
	
	task = TaskCreate(DoNothing, NULL, 0, 0);
	func_pointer = TaskGetFunc(task);
	
	RESULTSTATUS(func_pointer == DoNothing, 1);
	RESULTSTATUS(func_pointer == PrintToScreenFail, 0);
	
	task2 = TaskCreate(PrintToScreenFail, NULL, 0, 0);
	func_pointer2 = TaskGetFunc(task2);
	
	
	RESULTSTATUS(func_pointer2 == PrintToScreenFail, 1);
	RESULTSTATUS(func_pointer == func_pointer2, 0);
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void GetParamsTest(void)
{
	task_t *task = NULL;
	task_t *task2 = NULL;
	void *param1 = NULL;
	void *param2 = NULL;
	
	int a = 5;
	
	task = TaskCreate(DoNothing, NULL, 0, 0);
	param1 = TaskGetParams(task);

	RESULTSTATUS(NULL == param1, 1);
	RESULTSTATUS(&a == param1, 0);
	
	task2 = TaskCreate(PrintToScreenFail, &a, 0, 0);
	param2 = TaskGetParams(task2);
	
	
	RESULTSTATUS(*(int *)param2 == a, 1);
	RESULTSTATUS(param2 == &a, 1);
	RESULTSTATUS(param2 == param1, 0);
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void SetExecTimeTest(void)
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;
	strptime("6 Dec 2001 12:33:45", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, t, 0);
	
	RESULTSTATUS(t == TaskGetExecTime(task), 1);
	
	t = time(0);
	
	RESULTSTATUS(t == TaskGetExecTime(task), 0);
	TaskSetExecTime(task, t);
	RESULTSTATUS(t == TaskGetExecTime(task), 1);
	
	TaskDestroy(task);
}

static void SetIntervalTest(void)
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;
	strptime("6 Dec 2001 12:33:45", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, 0, t);
	
	RESULTSTATUS(t == TaskGetInterval(task), 1);
	
	t = time(0);
	
	RESULTSTATUS(t == TaskGetInterval(task), 0);
	
	TaskSetInterval(task, t);
	RESULTSTATUS(t == TaskGetInterval(task), 1);
	
	TaskDestroy(task);
	
	task = TaskCreate(DoNothing, NULL, 0, 1);
	TaskSetInterval(task, 2);
	RESULTSTATUS(2 == TaskGetInterval(task), 1);
	TaskDestroy(task);
}

static void SetFuncTest(void)
{
	task_t *task = NULL;
	int (*func_pointer)(void *) = NULL;
	
	task = TaskCreate(DoNothing, NULL, 0, 0);
	func_pointer = TaskGetFunc(task);
	
	RESULTSTATUS(func_pointer == DoNothing, 1);
	RESULTSTATUS(func_pointer == PrintToScreenFail, 0);
	
	TaskSetFunc(task, PrintToScreenFail);
	func_pointer = TaskGetFunc(task);
	
	RESULTSTATUS(func_pointer == DoNothing, 0);
	RESULTSTATUS(func_pointer == PrintToScreenFail, 1);
	
	
	TaskDestroy(task);
}

static void SetParamsTest(void)
{
	task_t *task = NULL;
	void *param1 = NULL;
	
	int a = 5;
	
	task = TaskCreate(DoNothing, NULL, 0, 0);
	param1 = TaskGetParams(task);

	RESULTSTATUS(NULL == param1, 1);
	RESULTSTATUS(&a == param1, 0);
	
	TaskSetParams(task, &a);
	param1 = TaskGetParams(task);
	
	RESULTSTATUS(NULL == param1, 0);
	RESULTSTATUS(&a == param1, 1);
	RESULTSTATUS(a == *(int *)param1, 1);	
	
	
	TaskDestroy(task);
}
/*******************************************************************************
*******************************************************************************/



/*******************************************************************************
						Help function definitions
*******************************************************************************/
int PrintToScreen(void *params)
{
	(void)params;
	printf("TESTESTEST\n");
	
	return 0;
}
int PrintToScreenFail(void *params)
{
	(void)params;
	printf("FAILED SUCCESFULLY\n");
	
	return 1;
}
int DoNothing(void *params)
{
	(void)params;
	return 0;
}
/*******************************************************************************
*******************************************************************************/
	
	
	
	
	
	
	
	
	
	
	
	
