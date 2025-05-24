/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 13.04.2023

	Description : c file for Binary Heap Test

*****************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#include "../include/heap.h"
#include "../include/utilitiestwo.h"

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void PushTest(void);

static void PopTest(void);

static void PeekTest(void);

static void IsEmptyTest(void);

static void RemoveTest(void);

static void RemoveByKeyTest(void);
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Help function declarations
*******************************************************************************/
static int CmpFunc(const void *lhs, const void *rhs);

static int IsMatch(const void *lhs, const void *rhs);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Create. Destroy and Size Test);
    CreateDestroyTest();
    printf("\n");

    HEADER(Push Test);
    PushTest();
    printf("\n");

	HEADER(Pop Test);
    PopTest();
    printf("\n");
    
	HEADER(Peek Test);
    PeekTest();
    printf("\n");

	HEADER(Is Empty Test);
    IsEmptyTest();
    printf("\n");

	HEADER(Remove Test);
	RemoveTest();
    printf("\n");

	HEADER(Remove By Key Test);
	RemoveByKeyTest();
    printf("\n");
    return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void CreateDestroyTest(void)
{	
	heap_t *heap = NULL;
	
	RESULT_STATUS(heap == NULL, 1, BeforeCreation);
	
	heap = HeapCreate(CmpFunc);
	RESULT_STATUS(heap == NULL, 0, Creation);

	HeapDestroy(heap);
}

static void PushTest(void)
{
    heap_t *heap = NULL;
	int num1 = 1;
    int num2 = 2;
	int num3 = 3;
	int num0 = 0;
	int num4 = 4;
	
	heap = HeapCreate(CmpFunc);
    RESULT_STATUS(HeapPush(heap, &num1), 0, Push);
	RESULT_STATUS(HeapPush(heap, &num3), 0,);
    RESULT_STATUS(HeapPush(heap, &num2), 0,);
	RESULT_STATUS(HeapPush(heap, &num0), 0,);
    RESULT_STATUS(HeapSize(heap), 4, Size);

	HeapPop(heap);
	RESULT_STATUS(HeapPush(heap, &num4), 0,);
	RESULT_STATUS(*(int *)HeapPeek(heap), 4,);

	HeapDestroy(heap);
}

static void PopTest(void)
{
	heap_t *heap = NULL;
	int num1 = 1;
    int num2 = 2;
	int num3 = 3;
	int num0 = 0;
	
	heap = HeapCreate(CmpFunc);
    HeapPush(heap, &num1);
	HeapPush(heap, &num3);
    HeapPush(heap, &num2);
	HeapPush(heap, &num0);
    
	HeapPop(heap);
	RESULT_STATUS(*(int *)HeapPeek(heap), 2, After Pop);
	RESULT_STATUS(HeapSize(heap), 3, Size);
	HeapPop(heap);
	RESULT_STATUS(*(int *)HeapPeek(heap), 1, );
	RESULT_STATUS(HeapSize(heap), 2, );
	HeapPop(heap);
	RESULT_STATUS(*(int *)HeapPeek(heap), 0, );
	RESULT_STATUS(HeapSize(heap), 1, );

	HeapDestroy(heap);
}

static void PeekTest(void)
{
	heap_t *heap = NULL;
	int num1 = 1;
    int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	heap = HeapCreate(CmpFunc);
    RESULT_STATUS(HeapPush(heap, &num1), 0, Push);
	RESULT_STATUS(HeapPush(heap, &num3), 0,);
    RESULT_STATUS(HeapPush(heap, &num2), 0,);
    RESULT_STATUS(*(int *)HeapPeek(heap), 3, Peek);

	RESULT_STATUS(HeapPush(heap, &num4), 0,);
	RESULT_STATUS(*(int *)HeapPeek(heap), 4, );


	HeapDestroy(heap);
}

static void IsEmptyTest(void)
{
	heap_t *heap = NULL;
	int num1 = 1;
    int num2 = 2;
	
	heap = HeapCreate(CmpFunc);
	RESULT_STATUS(HeapIsEmpty(heap), 1, Before Push);

    RESULT_STATUS(HeapPush(heap, &num1), 0, Push);
	RESULT_STATUS(HeapIsEmpty(heap), 0, After Push);
	RESULT_STATUS(HeapPush(heap, &num2), 0, );
	RESULT_STATUS(HeapIsEmpty(heap), 0, After Push);

	HeapDestroy(heap);
}

static void RemoveTest(void)
{
	heap_t *heap = NULL;
	int num1 = 1;
    int num2 = 2;
	int num3 = 3;
	int num0 = 0;
	
	heap = HeapCreate(CmpFunc);
    HeapPush(heap, &num1);
	HeapPush(heap, &num3);
    HeapPush(heap, &num2);
	HeapPush(heap, &num0);
    
	RESULT_STATUS(IsMatch(HeapRemove(heap,IsMatch, &num1), &num1), 1, Remove);

	RESULT_STATUS(HeapSize(heap), 3, );

	/*PrintHeap(heap);*/
	HeapDestroy(heap);
}

static void RemoveByKeyTest(void)
{
	heap_t *heap = NULL;
	int num1 = 1;
    int num2 = 2;
	int num3 = 3;
	int num0 = 0;
	
	heap = HeapCreate(CmpFunc);
    HeapPush(heap, &num1);
	HeapPush(heap, &num3);
    HeapPush(heap, &num2);
	HeapPush(heap, &num0);
    
	RESULT_STATUS(IsMatch(HeapRemoveByKey(heap, &num1), &num1), 1, Remove);

	RESULT_STATUS(HeapSize(heap), 3, );

	/*PrintHeap(heap);*/
	HeapDestroy(heap);
}
/*******************************************************************************
						Help function declarations
*******************************************************************************/
static int CmpFunc(const void *lhs, const void *rhs)
{
    return *(int *)lhs - *(int *)rhs;
}

static int IsMatch(const void *lhs, const void *rhs)
{
    return *(int *)lhs == *(int *)rhs;
}

/*******************************************************************************
*******************************************************************************/