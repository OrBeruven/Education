/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include "../../ds/src/linked_list.c"

static void FindTest();


iterator_t NthElement(sll_t *sll, int n)
{
	int i = 0;
	iterator_t iterator = SLLBeginIter(sll);
	
	while (NULL != SLLNextIter(iterator))
	{
		++i;
		iterator = SLLNextIter(iterator);
	}

	n = i - n;
	iterator = SLLBeginIter(sll);

	for (i = 1; i < n; ++i)
	{
		iterator = SLLNextIter(iterator);
	}
	
	return iterator;
}


int main(void)
{
	FindTest();
	return 0;
}

static void FindTest()
{
	int num = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int num7 = 7;
	
	sll_t *sll = SLLCreate();
	iterator_t iter = SLLBeginIter(sll);
	
	printf("Find Tests :\n");
	
	iter = SLLInsertBefore(iter, (void *)&num);
	
	iter = SLLInsertBefore(iter, (void *)&num2);
	
	iter = SLLInsertBefore(iter, (void *)&num3);
	
	iter = SLLInsertBefore(iter, (void *)&num4);
	
	iter = SLLInsertBefore(iter, (void *)&num5);
	
	iter = SLLInsertBefore(iter, (void *)&num6);
	
	iter = SLLInsertBefore(iter, (void *)&num7);
	
	/*the list will be
		|7| -> |6| -> |5| -> |4| -> |3| -> |2| - > |1|*/
	
	iter = NthElement(sll, 2);
	
	printf("Element %d\n", *(int *)SLLGetData(iter));
	
	printf("\n\n");
	SLLDestroy(sll);
}	
