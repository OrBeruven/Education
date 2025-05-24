/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 20.2.2023

	Description : c file for sorted link tests

*****************************/

#include <stdio.h>

#include "sorted_list.h"
#include "utilities.h"

/*******************************************************************************
help function declarations
*******************************************************************************/

int CmpFunc(const void *data1, const void *data2);
int IsNum(const void *src, const void *num);
int AddNum(void *src, void *num);

/*******************************************************************************
Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void IsEmptyTest(void);

static void InsertRemoveTest(void);

static void SizeTest(void);

static void PopBackFrontTest(void);

static void FindTest(void);

static void FindIfTest(void);

static void ForEachTest(void);

static void GetTest(void);

static void MergeTest(void);

/*******************************************************************************
*******************************************************************************/


int main()
{
	printf("Testing Create and Destroy : \n");
	CreateDestroyTest();
	printf("\n");
	
	printf("Testing IsEmpty :\n");
	IsEmptyTest();
	printf("\n");	
	
	printf("Testing Insert Remove :\n");
	InsertRemoveTest();
	printf("\n");	
	
	printf("Testing Size :\n");
	SizeTest();
	printf("\n");
	
	
	printf("Testing Pop Back and Front :\n");
	PopBackFrontTest();
	printf("\n");
	
	printf("Testing Find :\n");
	FindTest();
	printf("\n");
	
	
	printf("Testing Find If:\n");
	FindIfTest();
	printf("\n");
	
	
	printf("Testing ForEach :\n");
	ForEachTest();
	printf("\n");
	
	printf("Testing Get :\n");
	GetTest();
	printf("\n");

	printf("Testing Merge :\n");
	MergeTest();
	printf("\n");
	
	return 0;
}


/**************************************************************************************
			Test Functions
**************************************************************************************/

static void PrintList(sol_t *sol)
{
	sol_iterator_t iter = SortedListBeginIter(sol);

	while (!SortedListIsSameIter(iter, SortedListEndIter(sol)))
	{
		printf("%d -> ", *(int *)SortedListGetData(iter));
		iter = SortedListNextIter(iter);
	}
	
	printf("\n");
}

static void CreateDestroyTest(void)
{
	sol_t *s1 = NULL;
	sol_t *s2 = NULL;
	
	cmp_func_st func = CmpFunc;

	s1 = SortedListCreate(func);
	RESULTSTATUS(s1 == NULL, 0);
	
	SortedListDestroy(s1);
	
	s1 = SortedListCreate(func);
	RESULTSTATUS(0, s1 == NULL);
	
	s2 = SortedListCreate(func);
	RESULTSTATUS(s2 == NULL, 0);
	
	SortedListDestroy(s1);
	SortedListDestroy(s2);
}

static void IsEmptyTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	sol_iterator_t iter = {NULL};
	
	cmp_func_st func = CmpFunc;
	
	sol_t *s = SortedListCreate(func);
	
	RESULTSTATUS(SortedListIsEmpty(s), 1);
	
	iter = SortedListInsert(s, (void *)&num);
	
	RESULTSTATUS(SortedListIsEmpty(s), 0);
	
	iter = SortedListRemove(iter);
	
	RESULTSTATUS(SortedListIsEmpty(s), 1);
	
	iter = SortedListInsert(s, (void *)&num3);
	iter = SortedListInsert(s, (void *)&num2);
	iter = SortedListInsert(s, (void *)&num);
	
	RESULTSTATUS(SortedListIsEmpty(s), 0);
	SortedListDestroy(s);
}
	
static void InsertRemoveTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;

	sol_iterator_t iter = {NULL};
	
	cmp_func_st func = CmpFunc;
	
	sol_t *s = SortedListCreate(func);
	
	RESULTSTATUS(SortedListIsEmpty(s), 1);
	
	iter = SortedListInsert(s, (void *)&num);
	
	RESULTSTATUS(SortedListIsEmpty(s), 0);
	
	iter = SortedListRemove(iter);
	
	RESULTSTATUS(SortedListIsEmpty(s), 1);
	
	SortedListInsert(s, (void *)&num3);
	SortedListInsert(s, (void *)&num2);
	SortedListInsert(s, (void *)&num);
	
	/*list will be
		|3| -> |4| -> |5|*/
	
	iter = SortedListBeginIter(s);
	
	RESULTSTATUS(*(int *)SortedListGetData(iter), 3);
	
	iter = SortedListRemove(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 4);
	
	iter = SortedListEndIter(s);
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 5);
	
	iter = SortedListRemove(iter);
	iter = SortedListEndIter(s);
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 4);
	
	SortedListDestroy(s);
}
	
static void SizeTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	cmp_func_st func = CmpFunc;
	sol_iterator_t iter = {NULL};
	sol_t *sol = SortedListCreate(func);
	
	RESULTSTATUS((int)SortedListSize(sol), 0);
	
	SortedListInsert(sol, (void *)&num);
	RESULTSTATUS((int)SortedListSize(sol), 1);
	
	iter = SortedListBeginIter(sol);
	SortedListRemove(iter);
	RESULTSTATUS((int)SortedListSize(sol), 0);
	
	SortedListInsert(sol, (void *)&num);
	SortedListInsert(sol, (void *)&num2);
	SortedListInsert(sol, (void *)&num3);
	
	RESULTSTATUS((int)SortedListSize(sol), 3);
	/*the list will be
		|5| -> |4| - > |3|*/
	
	SortedListDestroy(sol);
}


static void PopBackFrontTest(void)
{
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	cmp_func_st func = CmpFunc;
	sol_iterator_t iter = {NULL};
	sol_t *sol = SortedListCreate(func);
	
	iter = SortedListBeginIter(sol);
	
	SortedListInsert(sol, (void *)&num1);
	SortedListInsert(sol, (void *)&num2);
	
	iter = SortedListEndIter(sol);
	iter = SortedListPrevIter(iter);
	
	RESULTSTATUS(*(int *)SortedListGetData(iter), 2);
	RESULTSTATUS(*(int *)SortedListPopBack(sol), 2);
	iter = SortedListEndIter(sol);
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 1);
	
	SortedListInsert(sol, (void *)&num3);
	SortedListInsert(sol, (void *)&num4);
	
	iter = SortedListEndIter(sol);
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 4);
	
	RESULTSTATUS(*(int *)SortedListPopFront(sol), 1);
	iter = SortedListBeginIter(sol);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 3);
	
	
	SortedListDestroy(sol);
}


static void FindTest(void)
{
	int num = 1;
	int num2 = 4;
	int num3 = 3;
	int num4 = 2;
	int numzero = 0;
	int numbig = 28;
	
	int bigger_than = 3;
	
	cmp_func_st func = CmpFunc;
	sol_iterator_t iter_temp = {NULL};
	sol_t *sol = SortedListCreate(func);
	
	SortedListInsert(sol, (void *)&numzero);
	SortedListInsert(sol, (void *)&num2);
	SortedListInsert(sol, (void *)&num3);
	SortedListInsert(sol, (void *)&numbig);
	SortedListInsert(sol, (void *)&num4);
	SortedListInsert(sol, (void *)&num);
	
	
	/*the list will be
		|0| -> |1| -> |2| - > |3| -> |4| -> |28|*/
	
	iter_temp = SortedListFind(sol, SortedListBeginIter(sol), SortedListEndIter(sol), (void *)&bigger_than);
	RESULTSTATUS(*(int *)SortedListGetData(iter_temp), 3);
	
	bigger_than = 1;
	iter_temp = SortedListFind(sol, SortedListBeginIter(sol), SortedListEndIter(sol), (void *)&bigger_than);
	RESULTSTATUS(*(int *)SortedListGetData(iter_temp), 1);
	
	bigger_than = 8;
	iter_temp = SortedListFind(sol, SortedListBeginIter(sol), SortedListEndIter(sol), (void *)&bigger_than);
	RESULTSTATUS(SortedListIsSameIter(iter_temp, SortedListEndIter(sol)), 1);
	
	bigger_than = 30;
	iter_temp = SortedListFind(sol, SortedListBeginIter(sol), SortedListEndIter(sol), (void *)&bigger_than);
	RESULTSTATUS(SortedListIsSameIter(iter_temp, SortedListEndIter(sol)), 1);
	
	SortedListDestroy(sol);
}


static void FindIfTest(void)
{
	int num = 1;
	int num2 = 4;
	int num3 = 3;
	int num4 = 2;
	int numzero = 0;
	int numbig = 28;
	
	int bigger_than = 3;
	
	cmp_func_st func = CmpFunc;
	is_match_t match_func = IsNum;
	sol_iterator_t iter_temp = {NULL};
	sol_t *sol = SortedListCreate(func);
	
	SortedListInsert(sol, (void *)&numzero);
	SortedListInsert(sol, (void *)&num2);
	SortedListInsert(sol, (void *)&num3);
	SortedListInsert(sol, (void *)&numbig);
	SortedListInsert(sol, (void *)&num4);
	SortedListInsert(sol, (void *)&num);
	
	(void)match_func;/*get rid of warning*/
	
	/*the list will be
		|0| -> |1| -> |2| - > |3| -> |4| -> |28|*/
	
	
	iter_temp = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsNum, (void *)&bigger_than);
	RESULTSTATUS(*(int *)SortedListGetData(iter_temp), 3);
	
	bigger_than = 1;
	iter_temp = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsNum, (void *)&bigger_than);
	RESULTSTATUS(*(int *)SortedListGetData(iter_temp), 1);
	
	bigger_than = 8;
	iter_temp = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsNum, (void *)&bigger_than);
	/*doesnt find 8*/
	RESULTSTATUS(SortedListIsSameIter(iter_temp, SortedListEndIter(sol)), 1);
	
	bigger_than = -1;
	iter_temp = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsNum, (void *)&bigger_than);
	/*doesnt find 8*/
	RESULTSTATUS(SortedListIsSameIter(iter_temp, SortedListEndIter(sol)), 1);
	
	bigger_than = 4;
	iter_temp = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsNum, (void *)&bigger_than);
	RESULTSTATUS(*(int *)SortedListGetData(iter_temp), 4);
	
	SortedListDestroy(sol);
}

static void ForEachTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	int add = 10;
	action_func_t act_func = AddNum;
	cmp_func_st func = CmpFunc;
	sol_iterator_t iter = {NULL};
	sol_t *sol = SortedListCreate(func);
	
	SortedListInsert(sol, (void *)&num3);
	
	SortedListInsert(sol, (void *)&num);
	
	SortedListInsert(sol, (void *)&num2);
	
	/*the list will be
		|3| -> |4| - > |5|*/
	
	
	SortedListForEach(SortedListBeginIter(sol), SortedListEndIter(sol), act_func, &add); 
	/*adds 10 to ever number in list*/
	
	iter = SortedListBeginIter(sol);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 13);

	iter = SortedListNextIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 14);

	iter = SortedListNextIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 15);
	
	SortedListForEach(SortedListBeginIter(sol), SortedListEndIter(sol), act_func, &add); 
	/*adds 10 to ever number in list*/
	
	iter = SortedListBeginIter(sol);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 23);

	iter = SortedListNextIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 24);

	iter = SortedListNextIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 25);
	
	RESULTSTATUS(num, 23);
	
	SortedListDestroy(sol);
}	



static void GetTest(void)
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	
	cmp_func_st func = CmpFunc;
	sol_iterator_t iter = {NULL};
	sol_t *sol = SortedListCreate(func);
	
	SortedListInsert(sol, (void *)&num3);
	SortedListInsert(sol, (void *)&num);
	SortedListInsert(sol, (void *)&num2);
	
	
	/*PrintList(sol);*/
	/*the list will be
		|3| -> |4| - > |5|*/
	

	iter = SortedListBeginIter(sol);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 3);
	
	iter = SortedListNextIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 4);

	iter = SortedListNextIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 5);
	
	
	SortedListDestroy(sol);
}	

static void MergeTest(void)
{
	/*list 1*/
	int num = 10;
	int num2 = 20;
	int num3 = 30;
	
	/*list 2*/
	int num4 = 11;
	int num5 = 12;
	int num6 = 21;
	int num7 = 22;
	int num8 = 32;
	int num9 = 42;
	
	
	cmp_func_st func = CmpFunc;
	
	/*list 1*/
	sol_iterator_t iter = {NULL};
	sol_t *sol1 = SortedListCreate(func);
	
	/*list 2*/
	sol_t *sol2 = SortedListCreate(func);
	
	
	SortedListInsert(sol1, (void *)&num2);
	SortedListInsert(sol1, (void *)&num3);
	SortedListInsert(sol1, (void *)&num);
	/*list will be
		|10| -> |20| -> |30|*/
	
	
	SortedListInsert(sol2, (void *)&num6);
	SortedListInsert(sol2, (void *)&num4);
	SortedListInsert(sol2, (void *)&num5);
	SortedListInsert(sol2, (void *)&num7);
	SortedListInsert(sol2, (void *)&num9);
	SortedListInsert(sol2, (void *)&num8);
	/*list will be
		|11| -> |12| -> |21| -> |22| -> |32| -> |42|*/
	
	PrintList(sol1);
	PrintList(sol2);
	
	sol1 = SortedListMerge(sol1, sol2);
	printf("\n");
	PrintList(sol1);
	
	/*list will be
		|10| -> |11| -> |12| -> |20| -> |21| -> |22| -> |30| -> |32| -> |42|*/
	
	RESULTSTATUS(SortedListIsEmpty(sol2), 1);
	
	iter = SortedListBeginIter(sol1);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 10);
	
	iter = SortedListEndIter(sol1);
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 42);
	
	iter = SortedListPrevIter(iter);
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 30);
	
	iter = SortedListPrevIter(iter);
	RESULTSTATUS(*(int *)SortedListGetData(iter), 22);
	
	
	
	SortedListDestroy(sol1);
	SortedListDestroy(sol2);
}

/**************************************************************************************
			help Functions
**************************************************************************************/

/*compare func*/
int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

/*is match func*/
/*returns 1 if matching */
int IsNum(const void *src, const void *num)
{
	return (*(int *)src == *(int *)num);
}

/*auction func*/
int AddNum(void *src, void *num)
{
	*(int *)src += *(int *)num;
	
	return 0;
}
