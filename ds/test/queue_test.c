/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for queue

*****************************/
#include <stdio.h>	/*using - printf*/

#include "../include/queue.h"

/*******************************************************************************
Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void EnqueueDequeueTest(void);

static void PeekTest(void);

static void IsEmptyTest(void);

static void SizeTest(void);

static void AppendTest(void);

static void ResultStatus(int status, int expected_status);

#define GREEN_OUT_PUT printf("\033[0;32m");

#define RED_OUT_PUT printf("\033[0;31m");

#define NORMAL_OUT_PUT printf("\033[0m");

/*******************************************************************************
*******************************************************************************/


int main()
{
	printf("Testing Create and Destroy : \n");
	CreateDestroyTest();
	printf("\n");	
	
	printf("Testing Enqueue and Dequeue :\n");
	EnqueueDequeueTest();
	printf("\n");	
	
	printf("Testing Peek :\n");
	PeekTest();
	printf("\n");
	
	printf("Testing IsEmpty :\n");
	IsEmptyTest();
	printf("\n");
	
	printf("Testing Size :\n");
	SizeTest();
	printf("\n");
	
	printf("Testing Append :\n");
	AppendTest();
	printf("\n");
	return 0;
}


/**************************************************************************************
			Test Functions
**************************************************************************************/



static void ResultStatus(int status, int expected_status)
{
	if (status == expected_status)
	{
		GREEN_OUT_PUT
		printf("Success\n");
		NORMAL_OUT_PUT
	}
	else
	{
		RED_OUT_PUT
		printf("Failure\n");
		NORMAL_OUT_PUT
	}
}


static void CreateDestroyTest(void)
{
	queue_t *q1 = NULL;
	queue_t *q2 = NULL;
	

	q1 = QueueCreate();
	ResultStatus(q1 == NULL, 0);
	
	QueueDestroy(q1);
	
	q1 = QueueCreate();
	ResultStatus(q1 == NULL, 0);
	
	q2 = QueueCreate();
	ResultStatus(q2 == NULL, 0);
	
	QueueDestroy(q1);
	QueueDestroy(q2);
}


static void EnqueueDequeueTest(void)
{
	queue_t *q1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	q1 = QueueCreate();
	
	ResultStatus(QueueEnqueue(q1, (void *)&num1), 0);
	
	
	ResultStatus(QueueEnqueue(q1, (void *)&num2), 0);	
	ResultStatus(QueueEnqueue(q1, (void *)&num3), 0);
	ResultStatus(QueueEnqueue(q1, (void *)&num4), 0);
	
	QueueDequeue(q1);
	QueueDestroy(q1);
}

static void PeekTest(void)
{
	queue_t *q1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	q1 = QueueCreate();
	QueueEnqueue(q1, (void *)&num1);
	/*1*/
	ResultStatus(*(int *)QueuePeek(q1), num1);
	
	QueueEnqueue(q1, (void *)&num2);
	/*1 . 2*/
	ResultStatus(*(int *)QueuePeek(q1), num1);
	
	QueueDequeue(q1);
	/*2*/
	ResultStatus(*(int *)QueuePeek(q1), num2);
	
	QueueEnqueue(q1, (void *)&num3);
	/*2.3*/
	ResultStatus(*(int *)QueuePeek(q1), num2);
		
	QueueDequeue(q1);
	/*3*/
	ResultStatus(*(int *)QueuePeek(q1), num3);	
	QueueEnqueue(q1, (void *)&num1);
	/*3 . 1*/
	QueueEnqueue(q1, (void *)&num4);
	/*3 . 1 . 4*/
	QueueDequeue(q1);
	/*1 . 4*/
	QueueDequeue(q1);
	/*4*/
	ResultStatus(*(int *)QueuePeek(q1), num4);
	
	QueueDestroy(q1);
}


static void IsEmptyTest(void)
{
	queue_t *q1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	/*assert
	ResultStatus(QueueIsEmpty(q1), 1);
	*/
	
	q1 = QueueCreate();
	QueueEnqueue(q1, (void *)&num1);
	/*1*/
	ResultStatus(QueueIsEmpty(q1), 0);
	
	QueueEnqueue(q1, (void *)&num2);
	/*1 . 2*/
	
	QueueDequeue(q1);
	/*2*/
	ResultStatus(QueueIsEmpty(q1), 0);
	QueueEnqueue(q1, (void *)&num3);
	/*2.3*/
		
	ResultStatus(QueueIsEmpty(q1), 0);
	
	QueueDequeue(q1);
	/*3*/
	QueueDequeue(q1);
	/*empty*/
	
	ResultStatus(QueueIsEmpty(q1), 1);
	
	QueueDestroy(q1);
}


static void SizeTest(void)
{
	queue_t *q1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	
	q1 = QueueCreate();
	ResultStatus(QueueSize(q1), 0);
	QueueEnqueue(q1, (void *)&num1);
	/*1*/
	ResultStatus(QueueSize(q1), 1);
	
	QueueEnqueue(q1, (void *)&num2);
	/*1 . 2*/
	
	QueueDequeue(q1);
	/*2*/
	ResultStatus(QueueSize(q1), 1);
	QueueEnqueue(q1, (void *)&num3);
	/*2.3*/
		
	ResultStatus(QueueSize(q1), 2);
	
	QueueEnqueue(q1, (void *)&num1);
	/*2.3.1*/
	ResultStatus(QueueSize(q1), 3);
	QueueDequeue(q1);
	QueueDequeue(q1);
	QueueDequeue(q1);
	/*empty*/
	ResultStatus(QueueSize(q1), 0);
	
	QueueDestroy(q1);
}



static void AppendTest(void)
{
	queue_t *q1 = NULL;
	queue_t *q2 = NULL;
	
	/*q1*/
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	
	/*q2*/
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;

	/*q1*/
	q1 = QueueCreate();
	QueueEnqueue(q1, (void *)&num1);
	QueueEnqueue(q1, (void *)&num2);
	QueueEnqueue(q1, (void *)&num3);
	
	/*q2*/
	q2 = QueueCreate();
	QueueEnqueue(q2, (void *)&num4);
	QueueEnqueue(q2, (void *)&num5);
	QueueEnqueue(q2, (void *)&num6);
	
	
	QueueAppend(q1, q2);
	/*now i should have
	1.2.3.4.5.6	*/
	
	ResultStatus(QueueIsEmpty(q2), 1);
	ResultStatus(*(int *)QueuePeek(q1), 1);
	QueueDequeue(q1);
	/*2.3.4.5.6	*/
	QueueDequeue(q1);
	/*3.4.5.6	*/
	ResultStatus(*(int *)QueuePeek(q1), 3);
	
	QueueDequeue(q1);
	/*4.5.6	*/
	ResultStatus(*(int *)QueuePeek(q1), 4);
	QueueDequeue(q1);
	/*5.6	*/
	QueueDequeue(q1);
	/*6	*/
	ResultStatus(*(int *)QueuePeek(q1), 6);
	
	QueueDequeue(q1);
	/*empty*/
	ResultStatus(QueueIsEmpty(q1), 1);
	
	
	
	QueueDestroy(q1);
	QueueDestroy(q2);
}










