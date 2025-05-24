/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For Fixed Size Queue Implemantation

*****************************/
#include <stdio.h>  /*perror*/
#include <stdlib.h> /*malloc, calloc*/
#include <assert.h>	/*assert*/

#include "fsq.h"    /*fsq_t*/

#define SUCCESS (0)
#define FAIL (1)

#define EMPTY (0)
#define NOT_EMPTY (1)

struct fixed_size_queue
{
    size_t capacity;
    size_t current_size;
    int *arr;
};

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static void MoveQueue(fsq_t *fsq);
/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
fsq_t *FSQCreate(size_t capacity)
{
    fsq_t *new_fsq = (fsq_t *)malloc(sizeof(fsq_t));
    if (NULL == new_fsq)
    {
        perror("FSQCreate");
        return NULL;
    }
    
    new_fsq->arr = (int *)calloc(capacity, sizeof(int));
    if (NULL == new_fsq->arr)
    {
        free(new_fsq);
        perror("FSQCreate");
        return NULL;
    }

    new_fsq->capacity = capacity;
    new_fsq->current_size = 0;

    return new_fsq;
}

void FSQDestroy(fsq_t *fsq)
{
    assert(NULL != fsq);

    free(fsq->arr);
    free(fsq);
}

int FSQEnqueue(fsq_t *fsq, int element)
{
    assert(NULL != fsq);

    if (fsq->current_size >= fsq->capacity )
    {
        return FAIL;
    }

    fsq->arr[fsq->current_size] = element;
    ++(fsq->current_size);
    return SUCCESS;
}

void FSQDequeue(fsq_t *fsq)
{
    assert(NULL != fsq);

    if (EMPTY == fsq->current_size)
    {
        return;
    }

    MoveQueue(fsq);
}

int FSQPeek(fsq_t *fsq)
{
    assert(NULL != fsq);

    if (0 == fsq->current_size)
    {
        return PEEK_ERROR;
    }

    return fsq->arr[0];
}

int FSQIsEmpty(fsq_t *fsq)
{
    assert(NULL != fsq);

    return EMPTY == fsq->current_size;
}
/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
static void MoveQueue(fsq_t *fsq)
{
    size_t i = 0;

    for (i = 0; i < fsq->current_size - 1; ++i)
    {
        fsq->arr[i] = fsq->arr[i + 1];
    }

    --(fsq->current_size);
}

/*******************************************************************************

*******************************************************************************/