/*****************************
	Name : Or Beruven

	Reviewed By : 

	Date Test: 00.00.2023

	Description : c file for Fixed Size Queue 5

*****************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <stdio.h> /*print*/

#include "./fsq5.h"

struct fsq
{
    int front;
    int rear;
    size_t max_size;
    int *array;
};

/************************ Functions ************************/

fsq_t *FSQCreate(size_t size)
{
    fsq_t *fsq = malloc(sizeof(fsq_t));

    if (NULL == fsq)
    {
        return NULL;
    }

    fsq->max_size = size;
    fsq->rear = 0;
    fsq->front = 0;
    fsq->array = calloc(size, sizeof(int));

    if (NULL == fsq->array)
    {
        free(fsq);
        return NULL;
    }
    return fsq;
}

void FSQDestroy(fsq_t *fsq)
{
    assert(NULL != fsq);

    free(fsq->array);
    free(fsq);
}

void FSQEnqueue(fsq_t *fsq, int input)
{
    assert(NULL != fsq);
    
    if ((int)fsq->max_size == fsq->front)
    {
        fsq->front = 0;
    }

    fsq->array[fsq->front] = input;
    ++fsq->front;
}

void FSQDequeue(fsq_t *fsq)
{
    assert(NULL != fsq);
    
    if ((int)fsq->max_size == fsq->rear)
    {
        fsq->rear = 0;
    }

    ++fsq->rear;
}

int FSQPeek(fsq_t *fsq)
{
    assert(NULL != fsq);
    
    return fsq->rear == (int)fsq->max_size ? fsq->array[0] : fsq->array[fsq->rear];
}
