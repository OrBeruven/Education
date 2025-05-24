/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

#include "../include/linked_list.h"



#define RED ("\x1B[31m") /* \x1B[<EFFECT>;<COLOR>m */
#define REDB ("\x1B[1;31m") /* red with bold effect */
#define GRN ("\x1B[0;32m")
#define YEL ("\x1B[33m")
#define BLU ("\x1B[34m")
#define MAG ("\x1B[4;35m") /* magenta with line effect */
#define CYN ("\x1B[36m")
#define WHT ("\x1B[37m")
#define RESET ("\x1B[0m") /* Resets effects and color */

/* printf will keep effects and colors if not reseted */



/*functions to is_match and action_fun*/
int AddNum(void *src, void *num);
int BiggerThanNum(const void *src, const void *num);


/*debbug function*/
static void PrintList(sll_t *sll)
{
	iterator_t iter = SLLBeginIter(sll);
	
	while (NULL != SLLNextIter(iter))
	{
		printf("|%d|-> ", *(int *)SLLGetData(iter));
		iter = SLLNextIter(iter);
	}
	
	printf("\n");
}


static void InsertTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	printf("Insert Tests :\n");
	iter_temp = SLLBeginIter(sll);
	*(int *)SLLGetData(iter_temp) == num3 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	iter_temp = SLLNextIter(iter_temp);
	*(int *)SLLGetData(iter_temp) == num2 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	iter_temp = SLLNextIter(iter_temp);
	*(int *)SLLGetData(iter_temp) == num ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}


static void RemoveTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	iter = SLLInsertBefore(iter, (void *)&num2);
	iter = SLLInsertBefore(iter, (void *)&num3);
	/*the list will be
		|5| -> |4| - > |3|*/
	
	iter_temp = SLLBeginIter(sll);
	iter_temp = SLLNextIter(iter_temp);
	iter_temp = SLLRemove(iter_temp);
	/*the list will be
		|5| -> |3|*/
	
	
	printf("Remove Tests :\n");
	iter_temp = SLLBeginIter(sll);
	*(int *)SLLGetData(iter_temp) == num3 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	/*num 2 was removed*/
	iter_temp = SLLNextIter(iter_temp);
	*(int *)SLLGetData(iter_temp) == num ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter = SLLEndIter(sll); /*saving the first dummy*/
	iter_temp = SLLEndIter(sll);
	
	/*trying to remove last node (dummy)*/
	iter_temp = SLLRemove(iter_temp);
	iter_temp = SLLEndIter(sll);
	iter_temp = SLLRemove(iter_temp);
	
	iter_temp == NULL ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	iter == SLLEndIter(sll) ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}

static void BeginNextEndTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	printf("BeginNextEnd Tests :\n");
	iter_temp = SLLBeginIter(sll);
	*(int *)SLLGetData(SLLBeginIter(sll)) == num3 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	iter_temp = SLLNextIter(iter_temp);
	*(int *)SLLGetData(iter_temp) == num2 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	iter_temp = SLLEndIter(sll);
	NULL == SLLNextIter(iter_temp) ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	sll == SLLGetData(iter_temp) ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}


static void CountTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	printf("Count Tests :\n");
	iter_temp = SLLBeginIter(sll);
	SLLCount(sll) == 3 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter_temp = SLLBeginIter(sll);
	iter_temp = SLLNextIter(iter_temp);
	iter_temp = SLLRemove(iter_temp);
	
	SLLCount(sll) == 2 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter_temp = SLLBeginIter(sll);
	iter_temp = SLLNextIter(iter_temp);
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	SLLCount(sll) == 3 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}

static void IsSameTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	printf("IsSame Tests :\n");
	iter_temp = SLLBeginIter(sll);
	SLLIsSameIter(iter_temp, iter) == 1 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter_temp = SLLNextIter(iter_temp);
	
	SLLIsSameIter(iter_temp, iter) == 0 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter = SLLEndIter(sll);
	iter_temp = SLLNextIter(iter_temp);
	iter_temp = SLLNextIter(iter_temp);
	
	SLLIsSameIter(iter_temp, iter) == 1 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}	



static void ForEachTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	action_func func = AddNum;
	
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	printf("ForEach Tests :\n");
	
	SLLForEach(SLLBeginIter(sll), SLLEndIter(sll), func, &num); 
	/*adds 3 to ever number in list*/

	iter_temp = SLLBeginIter(sll);
	*(int *)SLLGetData(iter_temp) == 8 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);

	iter_temp = SLLNextIter(iter_temp);
	*(int *)SLLGetData(iter_temp) == 7 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);

	iter_temp = SLLNextIter(iter_temp);
	*(int *)SLLGetData(iter_temp) == 6 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	num == 6 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}


static void GetSetTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	int set_to = 10;
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	
	printf("GetSet Tests :\n");
	iter_temp = SLLBeginIter(sll);
	*(int *)SLLGetData(iter_temp) == 5 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	SLLSetData(iter_temp, (void *)&set_to);
	*(int *)SLLGetData(iter_temp) == 10 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter_temp = SLLNextIter(iter_temp);
	set_to = 11;
	*(int *)SLLGetData(iter_temp) == 4 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	SLLSetData(iter_temp, &set_to);
	*(int *)SLLGetData(iter_temp) == 11 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	
	printf("\n\n");
	SLLDestroy(sll);
}	

static void IsEmptyTest()
{
	int num = 3;
	int num2 = 4;
	int num3 = 5;
	
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	printf("IsEmpty Tests :\n");
	SLLIsEmpty(sll) ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |3|*/
	
	SLLIsEmpty(sll) ? printf("%sFailure%s\n", REDB, RESET) : printf("%sSuccess!%s\n", GRN, RESET);
	
	iter_temp = SLLBeginIter(sll);
	iter_temp = SLLNextIter(iter_temp);
	iter_temp = SLLRemove(iter_temp);
	
	SLLIsEmpty(sll) ? printf("%sFailure%s\n", REDB, RESET) : printf("%sSuccess!%s\n", GRN, RESET);
	iter_temp = SLLRemove(iter_temp);
	iter_temp = SLLRemove(iter_temp);

	
	SLLIsEmpty(sll) ? printf("%sFailure%s\n", REDB, RESET) : printf("%sSuccess!%s\n", GRN, RESET);
	
	printf("\n\n");
	SLLDestroy(sll);
}	


static void FindTest()
{
	int num = 6;
	int num2 = 4;
	int num3 = 5;
	
	int bigger_than = 3;
	is_match func = BiggerThanNum;
	
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	iterator_t iter_temp = NULL;
	
	printf("Find Tests :\n");
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	/*the list will be
		|5| -> |4| - > |6|*/
	
	iter_temp = SLLFind(SLLBeginIter(sll), SLLEndIter(sll), func, (void *)&bigger_than);
	*(int *)SLLGetData(iter_temp) == 5 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	
	bigger_than = 5;
	iter_temp = SLLFind(SLLBeginIter(sll), SLLEndIter(sll), func, (void *)&bigger_than);
	*(int *)SLLGetData(iter_temp) == 6 ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	
	bigger_than = 8;
	iter_temp = SLLFind(SLLBeginIter(sll), SLLEndIter(sll), func, (void *)&bigger_than);
	iter_temp == SLLEndIter(sll) ? printf("%sSuccess!%s\n", GRN, RESET) : printf("%sFailure%s\n", REDB, RESET);
	
	
	printf("\n\n");
	SLLDestroy(sll);
}	


int main(void)
{
	InsertTest();
	
	RemoveTest();
	
	BeginNextEndTest();
	
	CountTest();
	
	IsSameTest();
	
	ForEachTest();
	
	GetSetTest();
	
	IsEmptyTest();
	
	FindTest();
	
	(void)PrintList;
	return 0;
}



int AddNum(void *src, void *num)
{
	*(int *)SLLGetData(src) += *(int *)num;
	
	return 0;
}

/*returns 1 if matching */
int BiggerThanNum(const void *src, const void *num)
{
	void *src_data = (void *)src;
	return (*(int *)SLLGetData(src_data) > *(int *)num);
}











