/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

#include "/home/beru/BeruEnv/or.beruven/ds/include/queue.h"
#include "../../ds/include/utilitiestwo.h"

#define SUCCESS 0
#define FAILURE 1

typedef struct stack_queue st_t;

struct stack_queue
{
	queue_t *q1;
	queue_t *q2;
};

/*******************************************************************************
						Or function Decl
*******************************************************************************/
int StackQueuePushOr(st_t *st, void *data);
void *StackQueuePeekOr(st_t *st);
void StackQueuePopOr(st_t *st);

static int PushTo(queue_t *to, queue_t *from);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						Internet function Decl
*******************************************************************************/
void StackPushA(st_t *stack, void *data);
void StackPopA(st_t *stack);
void *StackPeekA(const st_t *stack);
/*******************************************************************************
*******************************************************************************/

static void OrTest(void);
static void InternetTest(void);

int main(void)
{
	OrTest();
	printf("\n\n");
	/*InternetTest();*/
	return 0;
}	

static void OrTest(void)
{
	queue_t *q1 = NULL;
	queue_t *q2 = NULL;
	st_t stack = {0};
	
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	
	
	
	q1 = QueueCreate();
	q2 = QueueCreate();
	
	stack.q1 = q1;
	stack.q2 = q2;
	
	RESULT_STATUS(StackQueuePushOr(&stack, &a1), SUCCESS, );
	RESULT_STATUS(StackQueuePushOr(&stack, &a3), SUCCESS, );
	RESULT_STATUS(*(int *)StackQueuePeekOr(&stack), 3, );
	
	RESULT_STATUS(StackQueuePushOr(&stack, &a4), SUCCESS, );
	RESULT_STATUS(*(int *)StackQueuePeekOr(&stack), 4, );
	
	RESULT_STATUS(StackQueuePushOr(&stack, &a2), SUCCESS, );
	RESULT_STATUS(*(int *)StackQueuePeekOr(&stack), 2, );
	
	StackQueuePopOr(&stack);
	RESULT_STATUS(*(int *)StackQueuePeekOr(&stack), 4, );
	
	StackQueuePopOr(&stack);
	StackQueuePopOr(&stack);
	RESULT_STATUS(*(int *)StackQueuePeekOr(&stack), 1, );
	
	RESULT_STATUS(StackQueuePushOr(&stack, &a5), SUCCESS, );
	RESULT_STATUS(*(int *)StackQueuePeekOr(&stack), 5, );
	
	QueueDestroy(q1);
	QueueDestroy(q2);
}

static void InternetTest(void)
{
	queue_t *q1 = NULL;
	queue_t *q2 = NULL;
	st_t stack = {0};
	
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	
	q1 = QueueCreate();
	q2 = QueueCreate();
	
	stack.q1 = q1;
	stack.q2 = q2;
	
	StackPushA(&stack, &a1);
	StackPushA(&stack, &a3);
	RESULT_STATUS(*(int *)StackPeekA(&stack), 3, );
	
	StackPushA(&stack, &a4);
	RESULT_STATUS(*(int *)StackPeekA(&stack), 4, );
	
	StackPushA(&stack, &a2);
	RESULT_STATUS(*(int *)StackPeekA(&stack), 2, );
	/*printf("%d\n", *(int *)StackPeekA(&stack));*/
	
	StackPopA(&stack);
	RESULT_STATUS(*(int *)StackPeekA(&stack), 4, );
/*	printf("%d\n", *(int *)StackPeekA(&stack));*/
	
	StackPopA(&stack);
	StackPopA(&stack);
	RESULT_STATUS(*(int *)StackPeekA(&stack), 1, );
	/*printf("%d\n", *(int *)StackPeekA(&stack));
	*/
	StackPushA(&stack, &a5);
	RESULT_STATUS(*(int *)StackPeekA(&stack), 5, );
	/*printf("%d\n", *(int *)StackPeekA(&stack));*/
	
	QueueDestroy(q1);
	QueueDestroy(q2);
}



/*******************************************************************************
						Or function Impl
*******************************************************************************/
int StackQueuePushOr(st_t *st, void *data)
{
	int status = SUCCESS;
	
	if (QueueIsEmpty(st->q1))
	{
		QueueEnqueue(st->q1, data);
		status = PushTo(st->q1, st->q2);
	}
	else
	{
		QueueEnqueue(st->q2, data);
		status = PushTo(st->q2, st->q1);
	}
	
	return status;
}

static int PushTo(queue_t *to, queue_t *from)
{
	int status = SUCCESS;
	
	while (SUCCESS == status && !QueueIsEmpty(from))
	{
		status = QueueEnqueue(to, QueuePeek(from));
		QueueDequeue(from);
	}
	
	return status;
}

void *StackQueuePeekOr(st_t *st)
{
	void *data_to_return = NULL;
	
	if (QueueIsEmpty(st->q1))
	{
		data_to_return = QueuePeek(st->q2);
	}
	else
	{
		data_to_return = QueuePeek(st->q1);
	}
	
	return data_to_return;
}

void StackQueuePopOr(st_t *st)
{
	if (QueueIsEmpty(st->q1))
	{
		QueueDequeue(st->q2);
	}
	else
	{
		QueueDequeue(st->q1);
	}
}
	
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Internet function Impl
*******************************************************************************/
void StackPushA(st_t *stack, void *data)
{
    if(0 == QueueIsEmpty(stack->q1))
    {
        QueueEnqueue(stack->q2, data);
        QueueAppend(stack->q2, stack->q1);
    }
    else
    {
        QueueEnqueue(stack->q1, data);
        QueueAppend(stack->q1, stack->q2);    
    }
}

void StackPopA(st_t *stack)
{
    if(0 == QueueIsEmpty(stack->q1))
    {
        QueueDequeue(stack->q1);
    }
    else
    {
        QueueDequeue(stack->q2);
    }
}

void *StackPeekA(const st_t *stack)
{
    if(0 == QueueIsEmpty(stack->q1))
    {
    	printf("p1 = (%d)\n", *(int *)QueuePeek(stack->q1));
	    return QueuePeek(stack->q1);
    }
    else
    {
    	printf("p2 = (%d)\n", *(int *)QueuePeek(stack->q2));
    	return QueuePeek(stack->q2);
	}
}
/*******************************************************************************
*******************************************************************************/	
	
	
	
	
	
	
