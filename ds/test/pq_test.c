/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 20.2.2023

	Description : c file for Priority Queue

*****************************/

#include <stdio.h>

#include "../include/pq_heap.h"
#include "../include/utilities.h"

/*******************************************************************************
						help function declarations
*******************************************************************************/
int PriorityFunc(const void *data1, const void *data2);

int IsMatch(const void *data1, const void *data2);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void InsertRemoveTest(void);

static void IsEmptyTest(void);

static void SizeTest(void);

static void PeekTest(void);

static void EraseTest(void);

static void ClearTest(void);

static void MergeTest(void);
/*******************************************************************************
*******************************************************************************/

int main()
{

	printf("Testing Create and Destroy : \n");
	CreateDestroyTest();
	printf("\n");

	printf("Testing Insert Remove :\n");
	InsertRemoveTest();
	printf("\n");

	printf("Testing IsEmpty :\n");
	IsEmptyTest();
	printf("\n");	
	
	printf("Testing Size :\n");
	SizeTest();
	printf("\n");
	
	printf("Testing Peek :\n");
	PeekTest();
	printf("\n");
	
	printf("Testing Erase :\n");
	EraseTest();
	printf("\n");
	
	printf("Testing Clear :\n");
	ClearTest();
	printf("\n");
	
	printf("Testing Merge :\n");
	MergeTest();
	printf("\n");
	
	return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/

static void CreateDestroyTest(void)
{
	pq_t *q1 = NULL;
	pq_t *q2 = NULL;
	
	int (*func)(const void *, const void *) = PriorityFunc;

	q1 = PQCreate(func);
	RESULTSTATUS(q1 == NULL, 0);
	
	PQDestroy(q1);
	
	RESULTSTATUS(q1 != NULL, 1);
	
	q1 = PQCreate(func);
	RESULTSTATUS(q1 == NULL, 0);
	
	q2 = PQCreate(func);
	RESULTSTATUS(q2 == NULL, 0);
	
	PQDestroy(q1);
	PQDestroy(q2);
}

static void InsertRemoveTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	int (*func)(const void *, const void *) = PriorityFunc;
	
	pq_t *pq = PQCreate(func);
	
	RESULTSTATUS(PQIsEmpty(pq), 1);
	
	RESULTSTATUS(PQEnqueue(pq, (void *)&num), 0);
	
	RESULTSTATUS(PQIsEmpty(pq), 0);
	
	PQDequeue(pq);
	
	RESULTSTATUS(PQIsEmpty(pq), 1);
	
	PQEnqueue(pq, (void *)&num3);
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num);
	
	/*queue will be
		|3| <- |4| <- |5|*/
	
	
	RESULTSTATUS(*(int *)PQPeek(pq), 3);
	
	PQDequeue(pq);
	RESULTSTATUS(*(int *)PQPeek(pq), 4);
	
	PQDequeue(pq);
	
	RESULTSTATUS(*(int *)PQPeek(pq), 5);
	
	PQDestroy(pq);
}

static void IsEmptyTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	int (*func)(const void *, const void *) = PriorityFunc;
	
	pq_t *pq = PQCreate(func);
	
	RESULTSTATUS(PQIsEmpty(pq), 1);
	
	PQEnqueue(pq, (void *)&num);
	
	RESULTSTATUS(PQIsEmpty(pq), 0);
	
	PQDequeue(pq);
	
	RESULTSTATUS(PQIsEmpty(pq), 1);
	
	PQEnqueue(pq, (void *)&num3);
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num);
	
	RESULTSTATUS(PQIsEmpty(pq), 0);
	PQDestroy(pq);
}

static void SizeTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	int (*func)(const void *, const void *) = PriorityFunc;
	pq_t *pq = PQCreate(func);
	
	RESULTSTATUS((int)PQSize(pq), 0);
	
	PQEnqueue(pq, (void *)&num);
	RESULTSTATUS((int)PQSize(pq), 1);
	
	PQDequeue(pq);
	RESULTSTATUS((int)PQSize(pq), 0);
	
	PQEnqueue(pq, (void *)&num);
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num3);
	
	RESULTSTATUS((int)PQSize(pq), 3);
	/*the list will be
		|5| -> |4| - > |3|*/
	
	PQDestroy(pq);
}

static void PeekTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	int (*func)(const void *, const void *) = PriorityFunc;
	pq_t *pq = PQCreate(func);
	
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num);
	PQEnqueue(pq, (void *)&num3);
	
	RESULTSTATUS(*(int *)PQPeek(pq), 3);
	PQDequeue(pq);
	
	PQEnqueue(pq, (void *)&num);
	RESULTSTATUS(*(int *)PQPeek(pq), 3);
	PQDequeue(pq);
	
	RESULTSTATUS(*(int *)PQPeek(pq), 4);
	PQDequeue(pq);
	
	RESULTSTATUS(*(int *)PQPeek(pq), 5);
	/*the list will be
		|5| -> |4| - > |3|*/
	
	PQDestroy(pq);
}

static void EraseTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	int (*func)(const void *, const void *) = PriorityFunc;
	pq_t *pq = PQCreate(func);
	
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num);
	PQEnqueue(pq, (void *)&num3);
	
	PQErase(pq, IsMatch, (void *)&num);
	RESULTSTATUS(*(int *)PQPeek(pq), 4);
	
	
	PQEnqueue(pq, (void *)&num);
	RESULTSTATUS(*(int *)PQPeek(pq), 3);
	PQErase(pq, IsMatch, (void *)&num2);
	
	RESULTSTATUS(*(int *)PQPeek(pq), 3);
	PQDequeue(pq);
	
	RESULTSTATUS(*(int *)PQPeek(pq), 5);
	/*the queue will be
		|5| -> |4| - > |3|*/
	
	PQDestroy(pq);
}

static void ClearTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	int (*func)(const void *, const void *) = PriorityFunc;
	pq_t *pq = PQCreate(func);
	
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num);
	PQEnqueue(pq, (void *)&num3);
	
	RESULTSTATUS(PQIsEmpty(pq), 0);
	
	PQClear(pq);
	RESULTSTATUS(PQIsEmpty(pq), 1);
	
	
	PQEnqueue(pq, (void *)&num3);
	PQEnqueue(pq, (void *)&num2);
	PQEnqueue(pq, (void *)&num);
	RESULTSTATUS(*(int *)PQPeek(pq), 3);
	
	RESULTSTATUS(PQIsEmpty(pq), 0);
	
	PQClear(pq);
	RESULTSTATUS(PQIsEmpty(pq), 1);
	/*the queue will be
		|5| -> |4| - > |3|*/
	
	PQDestroy(pq);
}

static void MergeTest(void)
{
	/*for dest queue*/
	int num1 = 1;
	int num3 = 3;
	int num5 = 5;
	
	/*for src queue*/
	int num2 = 2;
	int num4 = 4;
	int num6 = 6;

	int (*func)(const void *, const void *) = PriorityFunc;
	pq_t *pq_dest = PQCreate(func);
	pq_t *pq_src = PQCreate(func);
	
	PQEnqueue(pq_dest, (void *)&num3);
	PQEnqueue(pq_dest, (void *)&num5);
	PQEnqueue(pq_dest, (void *)&num1);
	/*dest will be
		|1| <- |3| <- |5|*/
	
	PQEnqueue(pq_src, (void *)&num4);
	PQEnqueue(pq_src, (void *)&num2);
	PQEnqueue(pq_src, (void *)&num6);
	/*src will be
		|2| <- |4| <- |6|*/
	
	
	RESULTSTATUS(PQIsEmpty(pq_src), 0);
	PQMerge(pq_dest, pq_src);
	RESULTSTATUS(PQIsEmpty(pq_src), 1);
	/*dest need to be
		|1| <- |2| <- |3| <- |4| <- |5| <- |6|*/
	
	RESULTSTATUS(PQIsEmpty(pq_dest), 0);
	
	RESULTSTATUS(*(int *)PQPeek(pq_dest), 1);
	PQDequeue(pq_dest);
	
	RESULTSTATUS(*(int *)PQPeek(pq_dest), 2);
	PQDequeue(pq_dest);
	
	RESULTSTATUS(*(int *)PQPeek(pq_dest), 3);
	PQDequeue(pq_dest);
	
	RESULTSTATUS(*(int *)PQPeek(pq_dest), 4);
	PQDequeue(pq_dest);
	
	RESULTSTATUS(*(int *)PQPeek(pq_dest), 5);
	PQDequeue(pq_dest);
	
	RESULTSTATUS(*(int *)PQPeek(pq_dest), 6);
	PQDequeue(pq_dest);
	
	RESULTSTATUS(PQIsEmpty(pq_dest), 1);
	
	
	PQDestroy(pq_src);
	PQDestroy(pq_dest);
}


/**************************************************************************************
							Helper Functions
**************************************************************************************/

/*priority to compare func*/
int PriorityFunc(const void *data1, const void *data2)
{
	return (*(int *)data2 - *(int *)data1);
}

int IsMatch(const void *data1, const void *data2)
{
	return (*(int *)data1 == *(int *)data2);
}

