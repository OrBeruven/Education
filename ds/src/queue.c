/*****************************
	Name : Or Beruven

	Reviewed By : Harel

	Date Test: 12.2.2023

	Description : c file for Queue

*****************************/

#include <stdio.h> /*using - perror*/
#include <stdlib.h> /*using - malloc, free*/
#include <assert.h> /*using - assert*/

#include "../include/queue.h"
#include "../src/linked_list.c"


struct queue /*c file*/
{
    sll_t *queue;
};

/************************************functions **********************/

queue_t *QueueCreate(void)
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == new_queue)
	{
		perror("Fail to malloc memory for new list \n");
		return NULL;
	}
	
	new_queue->queue = SLLCreate();
	if (NULL == new_queue->queue)
	{
		/*perror is sent by SLLCreate fucntion*/
		free(new_queue);
		return NULL;
	}
	return new_queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);

	SLLDestroy(queue->queue);
	
	free(queue);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	return SLLInsertBefore(SLLEndIter(queue->queue), data) == SLLEndIter(queue->queue) ? 1 : 0;
}
	
void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLRemove(SLLBeginIter(queue->queue));
}


void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLGetData(SLLBeginIter(queue->queue));
}


int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLIsEmpty(queue->queue);
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLCount(queue->queue);
}
	


queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->queue = SLLAppend(dest->queue, src->queue);
	
	return dest;
}
















