/*****************************
	Name : Or Beruven

	Reviewed By : 

	Date Test: 00.00.2023

	Description : c file for Fixed Size Queue

*****************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#include "../include/fsq.h"
#include "../include/utilitiestwo.h"

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void QueueTest(void);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Create. Destroy Test);
    CreateDestroyTest();
    printf("\n");

    HEADER(Queue Test);
    QueueTest();
    printf("\n");
    return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void CreateDestroyTest(void)
{	
    size_t capacity = 4;
	fsq_t *fsq = NULL;
	
	RESULT_STATUS(fsq == NULL, 1, BeforeCreation);
	
	fsq = FSQCreate(capacity);
	RESULT_STATUS(fsq == NULL, 0, Creation);

	FSQDestroy(fsq);
}

static void QueueTest(void)
{
    size_t capacity = 4;
	fsq_t *fsq = NULL;
	
	fsq = FSQCreate(capacity);
    RESULT_STATUS(FSQIsEmpty(fsq), 1, IsEmpty);
	RESULT_STATUS(FSQEnqueue(fsq, 1), 0, Enqueue);
    RESULT_STATUS(FSQIsEmpty(fsq), 0, IsEmpty);
    RESULT_STATUS(FSQEnqueue(fsq, 2), 0, );
    RESULT_STATUS(FSQEnqueue(fsq, 3), 0, );
    RESULT_STATUS(FSQEnqueue(fsq, 4), 0, );
    RESULT_STATUS(FSQEnqueue(fsq, 5) == 0, 0, No More Space);

    RESULT_STATUS(FSQPeek(fsq), 1, Peek And Pop);
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 2, );
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 3, );
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 4, );
    FSQDequeue(fsq);
    RESULT_STATUS(FSQIsEmpty(fsq), 1, IsEmpty);
    RESULT_STATUS(FSQPeek(fsq), PEEK_ERROR, PEEK_ERROR);

	FSQDestroy(fsq);
}