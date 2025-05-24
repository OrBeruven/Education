/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for Scheduler tests

*****************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 	/*system*/

#include "../include/utilities.h"
#include "sched.h"
#include "uid.h"

/*******************************************************************************
						Help function declarations
*******************************************************************************/
int StopIt(void *data);

int PrintHi(void *data);

int SleepOne(void *data);

int RickAstley(void *data);

int Loading(void *data);

int FailOnPurpose(void *data);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void AddTaskTest(void);

static void RemoveTaskTest(void);

static void RunTest(void);

static void StopTest(void);

static void SizeTest(void);

static void IsEmptyTest(void);

static void ClearTest(void);
/*******************************************************************************
*******************************************************************************/


int main(void)
{
	printf("Testing CreateDestroy\n");
	CreateDestroyTest();
	printf("\n");

	printf("Testing Add Task\n");
	AddTaskTest();
	printf("\n");
	
	printf("Testing Remove Task\n");
	RemoveTaskTest();
	printf("\n");
		
	printf("Testing Run\n");
	RunTest();
	printf("\n");
	
	printf("Testing Stop\n");
	StopTest();
	printf("\n");
	
	printf("Testing Size\n");
	SizeTest();
	printf("\n");
	
	printf("Testing IsEmpty\n");
	IsEmptyTest();
	printf("\n");
	
	printf("Testing Clear\n");
	ClearTest();
	printf("\n");
	return 0;
}


/*******************************************************************************
						Test function definitions
*******************************************************************************/
static void CreateDestroyTest(void)
{
	sch_t *sch = NULL;
	
	RESULTSTATUS(NULL == sch, 1);
	sch = SchCreate();
	RESULTSTATUS(NULL == sch, 0);
	
	SchDestroy(sch);
}

static void AddTaskTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	
	sch = SchCreate();
	RESULTSTATUS(NULL == sch, 0);
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	
	RESULTSTATUS(UIDIsSame(uid1, UIDGetBad()), 0);
	
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	
	RESULTSTATUS(UIDIsSame(uid2, UIDGetBad()), 0);
	RESULTSTATUS(UIDIsSame(uid2, uid1), 0);
	
	RESULTSTATUS(SchSize(sch), 2);	
	
	SchDestroy(sch);
}

static void RemoveTaskTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	
	sch = SchCreate();
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	
	RESULTSTATUS(SchSize(sch), 2);	
	SchRemoveTask(sch, uid1);
	RESULTSTATUS(SchSize(sch), 1);	
	SchRemoveTask(sch, uid2);
	RESULTSTATUS(SchIsEmpty(sch), 1);	
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	uid3 = SchAddTask(sch, StopIt, NULL, time(NULL), 0);
	
	SchRemoveTask(sch, uid1);
	SchRemoveTask(sch, uid2);
	RESULTSTATUS(SchSize(sch), 1);
	RESULTSTATUS(SchIsEmpty(sch), 0);
	
	SchRemoveTask(sch, uid3);
	
	SchDestroy(sch);
}

static void RunTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	
	int print_me = 7;
	
	(void)uid2;
	(void)uid3;
	
	sch = SchCreate();
	
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL) + 2, 0);
	uid3 = SchAddTask(sch, PrintHi, &print_me, time(NULL) + 3, 0);
	
	RESULTSTATUS(SchRun(sch), 0);
	
	uid2 = SchAddTask(sch, FailOnPurpose, NULL, time(NULL) + 2, 0);
	uid3 = SchAddTask(sch, PrintHi, &print_me, time(NULL) + 3, 0);
	
	RESULTSTATUS(SchRun(sch), 1);
	
	SchDestroy(sch);
}

static void StopTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	ilrd_uid_t uid4 = {0};
	
	int print_me = 7;
	
	(void)uid1;
	(void)uid2;
	(void)uid3;
	(void)uid4;
	
	sch = SchCreate();
	
	uid1 = SchAddTask(sch, PrintHi, &print_me, time(NULL) + 6, 0);
	uid2 = SchAddTask(sch, Loading, NULL, time(NULL), 1);
	uid3 = SchAddTask(sch, StopIt, (void *)sch, time(NULL) + 5, 0);
	uid4 = SchAddTask(sch, StopIt, (void *)sch, time(NULL) + 6, 0);
	
	RESULTSTATUS(SchRun(sch), 0);
	
	RESULTSTATUS(SchRun(sch), 0);
	
	SchDestroy(sch);
}

static void SizeTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	
	(void)uid3;
	
	sch = SchCreate();
	
	RESULTSTATUS(SchSize(sch), 0);	
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	
	RESULTSTATUS(SchSize(sch), 2);	
	SchRemoveTask(sch, uid1);
	RESULTSTATUS(SchSize(sch), 1);	
	SchRemoveTask(sch, uid2);
	RESULTSTATUS(SchSize(sch), 0);		
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	uid3 = SchAddTask(sch, StopIt, NULL, time(NULL), 0);
	
	RESULTSTATUS(SchSize(sch), 3);	
	SchRemoveTask(sch, uid1);
	SchRemoveTask(sch, uid2);
	RESULTSTATUS(SchSize(sch), 1);
	
	SchDestroy(sch);
}

static void IsEmptyTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	
	sch = SchCreate();
	
	RESULTSTATUS(SchIsEmpty(sch), 1);
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	RESULTSTATUS(SchIsEmpty(sch), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	RESULTSTATUS(SchIsEmpty(sch), 0);
	
	SchRemoveTask(sch, uid1);	
	SchRemoveTask(sch, uid2);
	RESULTSTATUS(SchIsEmpty(sch), 1);	
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	RESULTSTATUS(SchIsEmpty(sch), 0);
	
	
	SchDestroy(sch);
}

static void ClearTest(void)
{
	sch_t *sch = NULL;
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	
	(void)uid1;
	(void)uid2;
	sch = SchCreate();

	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	RESULTSTATUS(SchIsEmpty(sch), 0);
	
	
	SchClear(sch);
	RESULTSTATUS(SchIsEmpty(sch), 1);	
	
	uid1 = SchAddTask(sch, PrintHi, NULL, time(NULL), 0);
	uid2 = SchAddTask(sch, SleepOne, NULL, time(NULL), 0);
	RESULTSTATUS(SchIsEmpty(sch), 0);
	
	SchClear(sch);
	RESULTSTATUS(SchIsEmpty(sch), 1);	
	
	
	SchDestroy(sch);
}
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						Help function definitions
*******************************************************************************/
int StopIt(void *data)
{
	SchStop(((sch_t *)data));
	return 0;
}

int PrintHi(void *data)
{
	printf("Hi %d\n", *(int *)data);
	return 0;
}

int Loading(void *data)
{
	static int load = 1;
	(void)data;
	if (5 >= load)
	{
		printf("LOADING <%d/5>\n", load);
	}
	else
	{
		printf("Should print this\n");
	}
	++load;
	return 0;
}

int SleepOne(void *data)
{
	(void)data;
	printf("Sleeping 1 seconds\n");
	sleep(1);
	return 0;
}

int RickAstley(void *data)
{
	system((char *)data);
	
	return 0;
}

int FailOnPurpose(void *data)
{
	(void)data;
	
	return 1;
}
	
/*******************************************************************************
*******************************************************************************/
