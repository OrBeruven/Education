/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for doubly linked list test

*****************************/
#include <stdio.h>	/*using - printf*/

#include "../include/dll.h"

/*******************************************************************************
Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void InsertRemoveTest(void);

static void PopPushBackFrontTest(void);

static void FindTest(void);
int BiggerThanNum(const void *src, const void *num);

static void ForEachTest(void);
int AddNum(void *src, void *num);

static void GetSetTest(void);

static void IsEmptyTest(void);

static void CountTest(void);

static void MultiFindTest(void);

static void SpliceTest(void);

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
	
	printf("Testing Insert Remove :\n");
	InsertRemoveTest();
	printf("\n");	
	
	printf("Testing Pop and Push :\n");
	PopPushBackFrontTest();
	printf("\n");
	
	printf("Testing Find :\n");
	FindTest();
	printf("\n");
	
	
	printf("Testing ForEach :\n");
	ForEachTest();
	printf("\n");
	
	
	printf("Testing Get and Set :\n");
	GetSetTest();
	printf("\n");
	
	printf("Testing IsEmpty :\n");
	IsEmptyTest();
	printf("\n");
	
	printf("Testing Count :\n");
	CountTest();
	printf("\n");
	
	printf("Testing Multi Found :\n");
	MultiFindTest();
	printf("\n");
	
	printf("Testing Splice :\n");
	SpliceTest();
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
	dll_t *d1 = NULL;
	dll_t *d2 = NULL;
	

	d1 = DLLCreate();
	ResultStatus(d1 == NULL, 0);
	
	DLLDestroy(d1);
	
	d1 = DLLCreate();
	ResultStatus(d1 == NULL, 0);
	
	d2 = DLLCreate();
	ResultStatus(d2 == NULL, 0);
	
	DLLDestroy(d1);
	DLLDestroy(d2);
}


static void InsertRemoveTest(void)
{
	dll_t *d = NULL;
	iterator_t iter = NULL;
	
	
	int num1 = 1;
	int num2 = 2;
	
	d = DLLCreate();
		
	iter = DLLBeginIter(d);
	iter = DLLInsert(iter, (void *)&num1);
	
	ResultStatus(iter == NULL, 0);
	ResultStatus(*(int *)DLLGetData(iter), 1);
	
	iter = DLLNextIter(iter);
	iter = DLLInsert(iter, (void *)&num2);
	ResultStatus(*(int *)DLLGetData(iter), 2);

	iter = DLLPrevIter(iter);
	iter = DLLRemove(iter);
	
	ResultStatus(*(int *)DLLGetData(iter), 2);
	
	iter = DLLRemove(iter);
	ResultStatus(DLLIsEmpty(d), 1);
	
	
	DLLDestroy(d);
}
	
	
	
static void PopPushBackFrontTest(void)
{
		
	dll_t *d = NULL;
	iterator_t iter = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	d = DLLCreate();
	
	iter = DLLBeginIter(d);
	
	iter = DLLPushBack(d, (void *)&num1);
	ResultStatus(*(int *)DLLGetData(iter), 1);
	
	iter = DLLPushBack(d, (void *)&num2);
	ResultStatus(*(int *)DLLGetData(iter), 2);
	
	iter = DLLEndIter(d);
	iter = DLLPrevIter(iter);
	
	ResultStatus(*(int *)DLLGetData(iter), 2);
	
	iter = DLLPopBack(d);
	iter = DLLEndIter(d);
	iter = DLLPrevIter(iter);
	ResultStatus(*(int *)DLLGetData(iter), 1);
	
	iter = DLLPushFront(d, (void *)&num3);
	iter = DLLPushFront(d, (void *)&num4);
	
	iter = DLLBeginIter(d);
	ResultStatus(*(int *)DLLGetData(iter), 4);
	
	iter = DLLPopFront(d);
	iter = DLLBeginIter(d);
	ResultStatus(*(int *)DLLGetData(iter), 3);
	
	
	DLLDestroy(d);
}
	

/*returns 1 if matching */
int BiggerThanNum(const void *src, const void *num)
{
	return (*(int *)src > *(int *)num);
}
static void FindTest(void)
{
	int num = 6;
	int num2 = 4;
	int num3 = 5;
	
	int bigger_than = 3;
	is_match_t func = BiggerThanNum;
	
	dll_t *d = DLLCreate();
	
	iterator_t iter_temp = NULL;
	
	DLLPushFront(d, (void *)&num);
	
	DLLPushFront(d, (void *)&num2);
	
	DLLPushFront(d, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |6|*/
	
	iter_temp = DLLFind(DLLBeginIter(d), DLLEndIter(d), func, (void *)&bigger_than);
	ResultStatus(*(int *)DLLGetData(iter_temp), 5);
	
	bigger_than = 5;
	iter_temp = DLLFind(DLLBeginIter(d), DLLEndIter(d), func, (void *)&bigger_than);
	ResultStatus(*(int *)DLLGetData(iter_temp), 6);
	
	bigger_than = 8;
	iter_temp = DLLFind(DLLBeginIter(d), DLLEndIter(d), func, (void *)&bigger_than);
	ResultStatus(DLLIsSameIter(iter_temp, DLLEndIter(d)), 1);	
	
	DLLDestroy(d);
}
	
	
	
int AddNum(void *src, void *num)
{
	*(int *)src += *(int *)num;
	
	return 0;
}
static void ForEachTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	action_func_t func = AddNum;
	
	dll_t *d = DLLCreate();
	
	iterator_t iter_temp = NULL;
	
	DLLPushFront(d, (void *)&num);
	
	DLLPushFront(d, (void *)&num2);
	
	DLLPushFront(d, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	DLLForEach(DLLBeginIter(d), DLLEndIter(d), func, &num); 
	/*adds 3 to ever number in list*/

	iter_temp = DLLBeginIter(d);
	ResultStatus(*(int *)DLLGetData(iter_temp), 8);

	iter_temp = DLLNextIter(iter_temp);
	ResultStatus(*(int *)DLLGetData(iter_temp), 7);

	iter_temp = DLLNextIter(iter_temp);
	ResultStatus(*(int *)DLLGetData(iter_temp), 6);
	
	ResultStatus(num, 6);
	
	DLLDestroy(d);
}	
	

static void GetSetTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	
	dll_t *d = DLLCreate();
	
	iterator_t iter = NULL;
	
	DLLPushFront(d, (void *)&num);
	
	DLLPushFront(d, (void *)&num2);
	
	DLLPushFront(d, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	

	iter = DLLBeginIter(d);
	DLLSetData(iter, (void *)&num4); 
	ResultStatus(*(int *)DLLGetData(iter), 4);
	
	iter = DLLNextIter(iter);
	DLLSetData(iter, (void *)&num5); 
	ResultStatus(*(int *)DLLGetData(iter), 5);

	iter = DLLNextIter(iter);
	DLLSetData(iter, (void *)&num6); 
	ResultStatus(*(int *)DLLGetData(iter), 6);
	
	
	DLLDestroy(d);
}	

static void IsEmptyTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	
	dll_t *d = DLLCreate();
	
	ResultStatus(DLLIsEmpty(d), 1);
	
	DLLPushFront(d, (void *)&num);
	ResultStatus(DLLIsEmpty(d), 0);
	
	DLLPopFront(d);
	ResultStatus(DLLIsEmpty(d), 1);
	
	DLLPushFront(d, (void *)&num2);
	DLLPushFront(d, (void *)&num3);
	
	ResultStatus(DLLIsEmpty(d), 0);
	/*the list will be
		|5| -> |4| - > |3|*/
	
	DLLDestroy(d);
}	
	

static void CountTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	
	dll_t *d = DLLCreate();
	
	ResultStatus((int)DLLCount(d), 0);
	
	DLLPushFront(d, (void *)&num);
	ResultStatus((int)DLLCount(d), 1);
	
	DLLPopFront(d);
	ResultStatus((int)DLLCount(d), 0);
	
	DLLPushFront(d, (void *)&num);
	DLLPushFront(d, (void *)&num2);
	DLLPushFront(d, (void *)&num3);
	
	ResultStatus((int)DLLCount(d), 3);
	/*the list will be
		|5| -> |4| - > |3|*/
	
	DLLDestroy(d);
}	

static void MultiFindTest(void)
{
	int num = 6;
	int num2 = 4;
	int num3 = 5;
	
	int bigger_than = 3;
	
	is_match_t func = BiggerThanNum;
	
	dll_t *d = DLLCreate();
	dll_t *d_dest = DLLCreate();
	
	iterator_t iter = NULL;
	
	DLLPushFront(d, (void *)&num);
	
	DLLPushFront(d, (void *)&num2);
	
	DLLPushFront(d, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |6|*/
	
	d_dest = DLLMultiFind(d_dest, DLLBeginIter(d), DLLEndIter(d), func, (void *)&bigger_than);
	ResultStatus((int)DLLCount(d_dest), 3);
	
	iter = DLLBeginIter(d_dest);
	ResultStatus(*(int *)DLLGetData(iter), 5);
	iter = DLLNextIter(iter);
	ResultStatus(*(int *)DLLGetData(iter), 4);
	iter = DLLNextIter(iter);
	ResultStatus(*(int *)DLLGetData(iter), 6);
	
	
	DLLDestroy(d_dest);	
	bigger_than = 5;
	d_dest = DLLCreate();
	
	d_dest = DLLMultiFind(d_dest, DLLBeginIter(d), DLLEndIter(d), func, (void *)&bigger_than);
	ResultStatus((int)DLLCount(d_dest), 1);
	iter = DLLBeginIter(d_dest);
	ResultStatus(*(int *)DLLGetData(iter), 6);
	
	
	DLLDestroy(d_dest);	
	bigger_than = 6;
	d_dest = DLLCreate();
	
	d_dest = DLLMultiFind(d_dest, DLLBeginIter(d), DLLEndIter(d), func, (void *)&bigger_than);
	ResultStatus((int)DLLCount(d_dest), 0);
	ResultStatus(DLLIsEmpty(d_dest), 1);
	
	DLLDestroy(d_dest);	
	DLLDestroy(d);
}

static void SpliceTest(void)
{
	int num = 1;
	int num2 = 2;
	int num3 = 3;
	
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	
	dll_t *d = DLLCreate();
	dll_t *d_to_splice = DLLCreate();
	
	iterator_t iter = NULL;
	
	DLLPushFront(d, (void *)&num);
	
	DLLPushFront(d, (void *)&num2);
	
	DLLPushFront(d, (void *)&num3);
	
	/*the list will be
		|3| -> |2| - > |1|*/
		
		
	DLLPushFront(d_to_splice, (void *)&num4);
	
	DLLPushFront(d_to_splice, (void *)&num5);
	
	DLLPushFront(d_to_splice, (void *)&num6);	
	/*the second list will be
		|6| -> |5| - > |4|*/	
		
	iter = DLLBeginIter(d);
	iter = DLLNextIter(iter);
	
	iter = DLLSplice(iter, DLLBeginIter(d_to_splice), DLLEndIter(d_to_splice));
	/*the list should be
		|3| -> |6| -> |5| -> |4| -> |2| -> |1|
		
	second list should be empty
		|dummy| -> |dummy|*/	
	ResultStatus(DLLIsEmpty(d_to_splice), 1);	
	
	
	iter = DLLBeginIter(d);
	ResultStatus(*(int *)DLLGetData(iter), 3);
	iter = DLLNextIter(iter);
	ResultStatus(*(int *)DLLGetData(iter), 6);
	iter = DLLNextIter(iter);
	ResultStatus(*(int *)DLLGetData(iter), 5);
	iter = DLLNextIter(iter);
	iter = DLLNextIter(iter);
	ResultStatus(*(int *)DLLGetData(iter), 2);
	
	
	DLLDestroy(d_to_splice);	
	DLLDestroy(d);
}

