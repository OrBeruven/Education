/*****************************
	Name : Or Beruven

	Reviewed By : Oran

	Date Test: 22.03.2023

	Description : c file for binary search tree tests

*****************************/

#include <stdio.h>	/*printf*/
#include <string.h>	/*strlen*/
#include <stdlib.h>	/*free, malloc*/

#include "bst.h"
#include "utilitiestwo.h"

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void InsertRemoveTest(void);

static void IsEmptyTest(void);

static void SizeTest(void);

static void IteratorTest(void);

static void RemoveExpand(void);

static void FindTest(void);

static void ForEachTest(void);

static void HeightTest(void);
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Help function declarations
*******************************************************************************/
int CmpFunc(const void *a, const void *b);

int AuctionFunc(void *a, void *b);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Testing Create and Destroy);
	CreateDestroyTest();
	printf("\n");
	
	HEADER(Testing Insert And Remove);
	InsertRemoveTest();
	printf("\n");
	
	HEADER(Testing IsEmpty);
	IsEmptyTest();
	printf("\n");
	
	HEADER(Testing Size);
	SizeTest();
	printf("\n");
	
	HEADER(Testing Iterators);
	IteratorTest();
	printf("\n");
	
	HEADER(Testing Find);
	FindTest();
	printf("\n");
	
	HEADER(Testing ForEach);
	ForEachTest();
	printf("\n");
	
	HEADER(Testing Height);
	HeightTest();
	printf("\n");
	return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void CreateDestroyTest(void)
{	
	bst_t *bst = NULL;
	int num1 = 100;
	
	RESULT_STATUS(bst == NULL, 1, BeforeCreation);
	
	bst = BSTCreate(CmpFunc);
	
	RESULT_STATUS(bst == NULL, 0, Creation);
	
	
	BSTInsert(bst, &num1);
	
	
	BSTDestroy(bst);
}

static void InsertRemoveTest(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;

	bst_iter_t iter = NULL;
	
	bst = BSTCreate(CmpFunc);
	iter = BSTInsert(bst, &num1);
	
	RESULT_STATUS(BSTIsEmpty(bst), 0, Insert);
	BSTRemove(iter);
	RESULT_STATUS(BSTIsEmpty(bst), 1, Remove);
	
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	iter = BSTInsert(bst, &num4);

	RESULT_STATUS(BSTSize(bst), 3, Size);
	
	BSTRemove(iter);
	RESULT_STATUS(BSTSize(bst), 2, );
	
	BSTDestroy(bst);

	RemoveExpand();
}

static void RemoveExpand(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;
	int num5 = 120;
	int num6 = 27;
	int num7 = 32;
	int num8 = 55;
	int num9 = 26;
	int num10 = 115;
	int num11 = 130;
	int num12 = 116;
	bst_iter_t iter = NULL;
	
	bst = BSTCreate(CmpFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num9);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num11);
	BSTInsert(bst, &num12);
	
	iter = BSTBeginIter(bst);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 100, );
	
	BSTRemove(iter);
	
	iter = BSTBeginIter(bst);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);


	RESULT_STATUS(*(int *)BSTGetData(iter), 115, Removing Root);
	
	BSTDestroy(bst);
}

static void IsEmptyTest(void)
{
	bst_t *bst = NULL;
	int num = 1;
	bst_iter_t iter = NULL;
	
	bst = BSTCreate(CmpFunc);
	
	RESULT_STATUS(BSTIsEmpty(bst), 1, Empty);
	
	iter = BSTInsert(bst, &num);
	RESULT_STATUS(BSTIsEmpty(bst), 0, Not Empty);
	
	BSTRemove(iter);
	RESULT_STATUS(BSTIsEmpty(bst), 1, );
	
	BSTDestroy(bst);
}

static void SizeTest(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;
	int num5 = 120;
	int num6 = 27;
	int num7 = 32;
	int num8 = 55;
	int num9 = 26;
	int num10 = 115;
	int num11 = 130;
	
	bst = BSTCreate(CmpFunc);
	
	RESULT_STATUS(BSTSize(bst), 0, Size When empty);
	
	BSTInsert(bst, &num1);
	
	RESULT_STATUS(BSTSize(bst), 1, Size Each Insert);
	
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	RESULT_STATUS(BSTSize(bst), 3, );
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	RESULT_STATUS(BSTSize(bst), 7, );
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num9);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num11);
	
	RESULT_STATUS(BSTSize(bst), 11, );
	
	
	BSTDestroy(bst);
}

static void IteratorTest(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;
	int num5 = 120;
	int num6 = 27;
	int num7 = 32;
	int num8 = 55;
	int num9 = 26;
	int num10 = 115;
	int num11 = 130;
	bst_iter_t iter = NULL;
	bst_iter_t iter_prev = NULL;
	
	bst = BSTCreate(CmpFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num9);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num11);
	
	iter = BSTBeginIter(bst);
	RESULT_STATUS(*(int *)BSTGetData(iter), 17, Walking The Tree);
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 25, );
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 26, );
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 27, );
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 32, );
	
	iter_prev = BSTPrevIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter_prev), 27, );

	RESULT_STATUS(BSTIsSameIter(iter_prev, iter), 0, );
	iter = BSTPrevIter(iter);
	RESULT_STATUS(BSTIsSameIter(iter_prev, iter), 1, );
	
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 115, );
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);


	RESULT_STATUS(*(int *)BSTGetData(iter), 130, );
	RESULT_STATUS(*(int *)BSTGetData(BSTPrevIter(BSTEndIter(bst))), 130, );
	iter = BSTNextIter(iter);
	RESULT_STATUS(BSTIsSameIter(iter, BSTEndIter(bst)), 1, );	
	

	
	BSTDestroy(bst);
}
	
static void FindTest(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;
	int num5 = 120;
	int num6 = 27;
	int num7 = 32;
	int num8 = 55;
	int num9 = 26;
	int num10 = 115;
	int num11 = 130;
	bst_iter_t iter = NULL;
	bst_iter_t find = NULL;
	
	bst = BSTCreate(CmpFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num9);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num11);
	
	iter = BSTBeginIter(bst);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	
	find = BSTFind(bst, &num9);
	RESULT_STATUS(*(int *)BSTGetData(find), 26, Finding by Key);
	RESULT_STATUS(BSTIsSameIter(find, iter), 1, );
	
	find = BSTFind(bst, &num2);
	RESULT_STATUS(BSTIsSameIter(find, iter), 0, );
	RESULT_STATUS(*(int *)BSTGetData(find), 25, );

	iter = BSTPrevIter(iter);
	RESULT_STATUS(BSTIsSameIter(find, iter), 1, );	
	
	find = BSTFind(bst, &num11);
	RESULT_STATUS(*(int *)BSTGetData(find), 130, );
	BSTDestroy(bst);
}

static void ForEachTest(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;
	int num5 = 120;
	int num6 = 27;
	int num7 = 32;
	int num8 = 55;
	int num9 = 26;
	int num10 = 115;
	int num11 = 130;
	int add = 1;
	bst_iter_t iter = NULL;
	
	bst = BSTCreate(CmpFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num9);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num11);
	
	BSTForEach(BSTBeginIter(bst), BSTEndIter(bst), AuctionFunc, &add);

	iter = BSTBeginIter(bst);
	RESULT_STATUS(*(int *)BSTGetData(iter), 18, After For Each);
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 26, );
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 27, );
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 28, );
	
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 33, );

	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 116, );
	iter = BSTNextIter(iter);
	iter = BSTNextIter(iter);
	RESULT_STATUS(*(int *)BSTGetData(iter), 131, );
	
	BSTDestroy(bst);
}

static void HeightTest(void)
{
	bst_t *bst = NULL;
	int num1 = 100;
	int num2 = 25;
	int num3 = 45;
	int num4 = 17;
	int num5 = 120;
	int num6 = 27;
	int num7 = 32;
	int num8 = 55;
	int num9 = 26;
	int num10 = 115;
	int num11 = 130;
	
	bst = BSTCreate(CmpFunc);
	BSTInsert(bst, &num1);
	RESULT_STATUS(BSTHeight(bst), 1, Messuring the tree);	
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	RESULT_STATUS(BSTHeight(bst), 3, );	

	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	RESULT_STATUS(BSTHeight(bst), 4, );	
	
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	RESULT_STATUS(BSTHeight(bst), 5, );	
	
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num9);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num11);
	
	RESULT_STATUS(BSTHeight(bst), 5, );
	BSTDestroy(bst);	
}
/**************************************************************************************
								Help Functions
**************************************************************************************/
int CmpFunc(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int AuctionFunc(void *a, void *b)
{
	*(int *)a += *(int *)b;
	return 0;
}
