/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <stdlib.h>

#include "../../ds/include/stack.h"


typedef struct queue queue_t;

struct queue
{
	stack_t *st1;
	stack_t *st2;
};

void QueueEnqueue(queue_t *que, const void *data);
void *QueueDequeue(queue_t *que);

int main(void)
{
	stack_t *st1 = NULL;
	stack_t *st2 = NULL;
	
	queue_t *que = (queue_t *)malloc(sizeof(queue_t));
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	
	void *p1 = *(void **)&num1;
	st1 = StackCreate(10, 4);
	st2 = StackCreate(10, 4);
	
	que->st1 = st1;
	que->st2 = st2;
	
	QueueEnqueue(que, (void *)&num1);
	QueueEnqueue(que, (void *)&num3);
	QueueEnqueue(que, (void *)&num5);
	QueueEnqueue(que, (void *)&num2);
	QueueEnqueue(que, (void *)&num4);
	QueueEnqueue(que, (void *)&num6);
	
	printf("|%d| <-", *(int *)QueueDequeue(que));
	printf("|%d| <-", *(int *)QueueDequeue(que));
	printf("|%d| <-", *(int *)QueueDequeue(que));
	printf("|%d| <-", *(int *)QueueDequeue(que));
	printf("|%d| <-", *(int *)QueueDequeue(que));
	printf("|%d| <-", *(int *)QueueDequeue(que));
	
	
	return 0;
}


void QueueEnqueue(queue_t *que, const void *data)
{
	StackPush(que->st1, data);
}

void *QueueDequeue(queue_t *que)
{
	void *to_ret = NULL;
	
	if (StackIsEmpty(que->st2))
	{
		while (!StackIsEmpty(que->st1))
		{
			StackPush(que->st2, StackPeek(que->st1));
			StackPop(que->st1);
		}
	}
	
	to_ret = StackPeek(que->st2);
	StackPop(que->st2);
	
	return to_ret;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
