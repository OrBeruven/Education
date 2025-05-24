/*****************************
	Name : Or Beruven

	Reviewed By : 

	Date Test: 00.00.2023

	Description : test file for Fixed Size Queue 5

    Compile with : gd fsq5.c fsq5_test.c 

*****************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#include "./fsq5.h"
#include "../../ds/include/utilitiestwo.h"

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
	FSQEnqueue(fsq, 1);
    FSQEnqueue(fsq, 2);
    FSQEnqueue(fsq, 3);
    FSQEnqueue(fsq, 4);
    

    RESULT_STATUS(FSQPeek(fsq), 1, Peek And Pop);
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 2, );
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 3, );
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 4, );
    FSQDequeue(fsq);

    FSQEnqueue(fsq, 5);
    FSQEnqueue(fsq, 6);

    RESULT_STATUS(FSQPeek(fsq), 5, );
    FSQDequeue(fsq);
    RESULT_STATUS(FSQPeek(fsq), 6, );
    FSQDequeue(fsq);

	FSQDestroy(fsq);
}