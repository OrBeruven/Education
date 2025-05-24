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

static void TestRemove();

static void TestHeapRemove(void);
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Help function declarations
*******************************************************************************/
static int CmpFunc(const void *lhs, const void *rhs);

static int IsMatch(const void *lhs, const void *rhs);

static void DrawSuccess(void);

static void DrawFailure(void);
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

	HEADER(Avivs Remove Test);
	TestRemove();
    printf("\n");

	HEADER(Yotams Remove Test);
	TestHeapRemove();
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

	HeapDestroy(heap);
}

static void TestRemove()
{
    heap_t *heap = HeapCreate(CmpFunc);
    int arr[] = {5, 2, 7, 1, 8, 3 };
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;
    int removed = 0;

    printf("Test HeapRemove\n");

    for (i = 0; i < size; ++i)
    {
        HeapPush(heap, &arr[i]);
    }

    removed = *(int *)HeapRemove(heap, IsMatch, &arr[1]);
    RESULT_STATUS(removed , 2, "Heap Remove");

    removed = *(int *)HeapRemove(heap, IsMatch, &arr[2]);
    RESULT_STATUS(removed , 7, "Heap Remove");

    removed = *(int *)HeapRemove(heap, IsMatch, &arr[3]);
    RESULT_STATUS(removed , 1, "Heap Remove");

    removed = *(int *)HeapRemove(heap, IsMatch, &arr[4]);
    RESULT_STATUS(removed , 8, "Heap Remove");

    removed = *(int *)HeapRemove(heap, IsMatch, &arr[0]);
    RESULT_STATUS(removed , 5, "Heap Remove");
    
    HeapDestroy(heap);
}

static void TestHeapRemove(void)
{
    heap_t *heap = HeapCreate(CmpFunc);
    int data1 = 5;
    int data2 = 2;
    int data3 = 7;
    int data4 = 1;
    int data5 = 8;
    int data6 = 3;
    int data7 = 10;
    int data8 = 4;
    int temp = 0;
    int temp2 = 0;
    int temp3 = 0;
    int temp4 = 0;
    int temp5 = 0;
    int temp6 = 0;
    int temp7 = 0;
    int data_to_remove = 2;
    int data_to_remove2 = 7;
    int data_to_remove3 = 1;
    int data_to_remove4 = 8;
    int data_to_remove5 = 5;
    int data_to_remove6 = 3;
    int data_to_remove7 = 20;
	void *temp8 = NULL;

    printf("HeapRemove:\n");

    HeapPush(heap, &data1);
    HeapPush(heap, &data2);
    HeapPush(heap, &data3);
    HeapPush(heap, &data4);
    HeapPush(heap, &data5);
    HeapPush(heap, &data6);
    HeapPush(heap, &data7);
    HeapPush(heap, &data8);

    
    temp = *(int *)HeapRemove(heap, IsMatch, &data_to_remove);
    (2 == temp && 7 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(7 == HeapSize(heap));
    assert(2 == temp);

    temp2 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove2);
    (7 == temp2) ? DrawSuccess() : DrawFailure();
    assert(7 == temp2);

    temp3 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove3);
    (1 == temp3) ? DrawSuccess() : DrawFailure();
    assert(1 == temp3);

    temp4 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove4);
    (8 == temp4) ? DrawSuccess() : DrawFailure();
    assert(8 == temp4);

    temp6 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove6);
    (3 == temp6) ? DrawSuccess() : DrawFailure();
    assert(3 == temp6);

    printf("HeapRemoveByKey:\n");
    
    temp8 = HeapRemoveByKey(heap,  &data_to_remove7);
    (NULL == temp8) ? DrawSuccess() : DrawFailure();

	temp8 = HeapRemoveByKey(heap,  &data_to_remove5);
    (5 == *(int *)temp8) ? DrawSuccess() : DrawFailure();
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

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}
