/*****************************
	Name : Or Beruven

	Reviewed By : Lilach

	Date Test: 18.03.2023

	Description : c file for

*****************************/

#include <stdio.h>	/*printf*/
#include <string.h>	/*strlen*/
#include <stdlib.h>	/*free, malloc*/

#include "recursion.h"
#include "utilitiestwo.h"
#include "stack.h"

#define SUCCESS 1
#define FAILURE 0

#define STACK_CAP 5

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void FiboIterTest(void);

static void FiboRecTest(void);

static void SLLFlipTest(void);

static void StackSortTest(void);

static void StrLenRecTest(void);

static void StrCmpRecTest(void);

static void StrCpyRecTest(void);

static void StrCatRecTest(void);

static void StrStrRecTest(void);
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Help function declarations
*******************************************************************************/
static void PrintSLL(node_t *head);

static void PrintStack(stack_t *stack);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Testing Fibonacci);
	FiboIterTest();
	FiboRecTest();
	printf("\n");
	
	HEADER(Testing SLLFlip);
	SLLFlipTest();
	printf("\n");
	
	HEADER(Testing Stack Sort);
	StackSortTest();
	printf("\n");
	
	HEADER(Testing StrLen);
	StrLenRecTest();
	printf("\n");
	
	HEADER(Testing StrCmp);
	StrCmpRecTest();
	printf("\n");
	
	HEADER(Testing StrCpy);
	StrCpyRecTest();
	printf("\n");
	
	HEADER(Testing StrCat);
	StrCatRecTest();
	printf("\n");
	
	HEADER(Testing StrStr);
	StrStrRecTest();
	printf("\n");
	return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void FiboIterTest(void)
{
	RESULT_STATUS(FiboIter(1), 0, Fibonacci Iteration :);
	RESULT_STATUS(FiboIter(2), 1, );
	RESULT_STATUS(FiboIter(3), 1, );
	RESULT_STATUS(FiboIter(4), 2, );
	RESULT_STATUS(FiboIter(8), 13,);
	RESULT_STATUS(FiboIter(12), 89,);
}
	
static void FiboRecTest(void)
{
	RESULT_STATUS(FiboRec(1), 0, Fibonacci Recursion :);
	RESULT_STATUS(FiboRec(2), 1, );
	RESULT_STATUS(FiboRec(3), 1, );
	RESULT_STATUS(FiboRec(4), 2, );
	RESULT_STATUS(FiboRec(8), 13,);
	RESULT_STATUS(FiboRec(12), 89,);
}
	
static void SLLFlipTest(void)
{
	node_t node_1;
	node_t node_2;
	node_t node_3;
	node_t node_4;
	node_t node_5;
	node_t *head = &node_1;
	
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;
	int num_5 = 5;
	
	node_1.data = (void *)&num_1;
  	node_1.next = &node_2;
  	
  	node_2.data = (void *)&num_2;
  	node_2.next = &node_3;
  	
  	node_3.data = (void *)&num_3;
  	node_3.next = &node_4;
  	
  	node_4.data = (void *)&num_4;
  	node_4.next = &node_5;
  	
  	node_5.data = (void *)&num_5;
  	node_5.next = NULL;
  	
  	head = SLLFlip(head);
  	RESULT_STATUS(*(int *)head->data, 5, SLL Reverse Recursion :);
  	RESULT_STATUS(*(int *)head->next->data, 4, );
  	RESULT_STATUS(*(int *)head->next->next->data, 3, );
   	RESULT_STATUS(*(int *)head->next->next->next->data, 2, );
	RESULT_STATUS(*(int *)head->next->next->next->next->data, 1, );
}

static void StackSortTest(void)
{
	stack_t *st1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	
	st1 = StackCreate(STACK_CAP, sizeof(int));
	
	StackPush(st1, &num2);
	StackPush(st1, &num5);
	StackPush(st1, &num1);
	StackPush(st1, &num3);
	StackPush(st1, &num4);

	st1 = StackSort(st1);
	
	RESULT_STATUS(*(int *)StackPeek(st1), 1, Stack Sort Recursion :);
	StackPop(st1);
	RESULT_STATUS(*(int *)StackPeek(st1), 2, );
	StackPop(st1);
	RESULT_STATUS(*(int *)StackPeek(st1), 3, );
	StackPop(st1);
	RESULT_STATUS(*(int *)StackPeek(st1), 4, );
	StackPop(st1);
	RESULT_STATUS(*(int *)StackPeek(st1), 5, );
	
	StackDestroy(st1);	
}

static void StrLenRecTest(void)
{
	char *str = "123456 89 ";
	char *str1 = "orberuven";
	char *str2 = "ashd;lkn;aoh  SKJDf o FPj gj SDIJf [j";
	
	RESULT_STATUS(StrLenRec(str), 10, StrLen Recursion :);
	RESULT_STATUS(StrLenRec(str) == strlen(str), 1, );
	RESULT_STATUS(StrLenRec(str1) == strlen(str1), 1, );
	RESULT_STATUS(StrLenRec(str2) == strlen(str2), 1, );
}

static void StrCmpRecTest(void)
{
	char *str = "Hello";
	char *str1 = "AbCdEf";
	char *str2 = "a";
	char *str3 = "b";
	
	RESULT_STATUS(StrCmpRec(str, str1), strcmp(str, str1), StrCmp Recursion :);
	RESULT_STATUS(StrCmpRec(str, str1), strcmp(str, str1),);
	RESULT_STATUS(StrCmpRec(str, str2), strcmp(str, str2),);
	RESULT_STATUS(StrCmpRec(str3, str1), strcmp(str3, str1),);
	RESULT_STATUS(StrCmpRec(str2, str3), strcmp(str2, str3),);
	RESULT_STATUS(StrCmpRec(str3, str2), strcmp(str3, str2),);
}

static void StrCpyRecTest(void)
{
	char *str = "Hello";
	char *str1 = "AbCdEf";
	char *dest = NULL;
	
	dest = (char *)calloc(10, sizeof(char));
	
	dest = StrCpyRec(dest, str);
	RESULT_STATUS(strlen(dest), 5, StrCpy Recursion :);
	RESULT_STATUS(strlen(dest) == strlen(str), 1, );
	
	dest = StrCpyRec(dest, str1);
	RESULT_STATUS(dest[0] == 'A', 1, );
	RESULT_STATUS(dest[1] == 'b', 1, );
	RESULT_STATUS(dest[4] == 'E', 1, );
	
	free(dest);
}

static void StrCatRecTest(void)
{
	char *str = "Hello";
	char *str1 = "AbCdEf";
	char *dest = NULL;
	
	dest = (char *)calloc(20, sizeof(char));
	
	dest = strcpy(dest, str);
	dest = StrCatRec(dest, str1);
	
	RESULT_STATUS(strlen(dest), strlen(str) + strlen(str1), StrCat Recursion :);

	RESULT_STATUS(dest[0] == 'H', 1, );
	RESULT_STATUS(dest[1] == 'e', 1, );
	RESULT_STATUS(dest[5] == 'A', 1, );
	RESULT_STATUS(dest[11] == '\0', 1, );
	
	free(dest);
}

static void StrStrRecTest(void)
{
	char *str = "Hello This Is A Test";
	char *c = "H";
	char *c2 = "i";
	char *dest = NULL;
	
	dest = StrStrRec(str, c);

	RESULT_STATUS(strlen(dest), strlen(str), StrStr Recursion :);
	
	dest = StrStrRec(str, c2);
	
	RESULT_STATUS(dest[0] == 'i', 1, );
	RESULT_STATUS(dest[1] == 's', 1, );
	RESULT_STATUS(dest[6] == 'A', 1, );
}

/**************************************************************************************
								Help Functions
**************************************************************************************/
static void PrintSLL(node_t *head)
{
	if (NULL == head)
	{
		return;
	}
	
	printf("%d -> ", *(int *)head->data);
	
	PrintSLL(head->next);
}	

static void PrintStack(stack_t *stack)
{
	int temp = 0;
	if (StackIsEmpty(stack))
	{
		return;
	}
	
	temp = *(int *)StackPeek(stack);
	printf("%d | ", temp);
	StackPop(stack);
	PrintStack(stack);
	
	StackPush(stack, &temp);
}	
