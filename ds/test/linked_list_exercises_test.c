/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 9.2.2023

	Description : c file for linked list exercises tests

*****************************/
#include <stdio.h>	/*using - printf*/

#include "../include/linked_list_exercises.h"

/*******************************************************************************
Test function declarations
*******************************************************************************/
static void TestFlip(void);

static void ComperSLL(node_t *node);

static void ComperFlipedSLL(node_t *node);

static void TestHasLoop(void);

static void TestFindIntersection(void);

static void ResultStatus(int status, int expected_status);

#define GREEN_OUT_PUT printf("\033[0;32m");

#define RED_OUT_PUT printf("\033[0;31m");

#define NORMAL_OUT_PUT printf("\033[0m");

/*******************************************************************************
*******************************************************************************/


int main()
{
	printf("Testing flip\n");
	TestFlip();
	printf("Testing has loops\n");
	TestHasLoop();
	printf("Testing has intersection\n");
	TestFindIntersection();
	
	
	return 0;
}

/*******************************************************************************
Test function
*******************************************************************************/
static void TestFlip(void)
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
  	
  	printf("Pre-flip\n");
  	ComperSLL(head);
  	
  	head = Flip(&node_1);

	printf("after flip\n");
  	ComperFlipedSLL(head);
}


static void ComperSLL(node_t *node)
{
	int i = 0;
	
	for(i = 1; 6 > i; ++i)
	{
		ResultStatus(*(int *)(node->data), i);
		node = node->next;
	}
}

static void ComperFlipedSLL(node_t *node)
{
	int i = 0;
	
	for(i = 5; 0 < i; --i)
	{
		ResultStatus(*(int *)(node->data), i);
		node = node->next;
	}
}

static void TestHasLoop(void)
{
	node_t node_1;
	node_t node_2;
	node_t node_3;
	node_t node_4;
	node_t node_5;
	
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;
	int num_5 = 5;
	
	int status = 0;
	
	
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
  	
  	
  	status = HasLoop(&node_1);
  	ResultStatus(status, 0);
  	
  	node_5.next = &node_1;
  	
  	status = HasLoop(&node_1);
  	ResultStatus(status, 1);
  	
  	node_5.next = &node_2;
  	
  	status = HasLoop(&node_1);
  	ResultStatus(status, 1);
  	
  	node_5.next = &node_3;
  	
  	status = HasLoop(&node_1);
  	ResultStatus(status, 1);
  	
  	node_5.next = &node_4;
  	
  	status = HasLoop(&node_1);
  	ResultStatus(status, 1);
  	
  	node_5.next = &node_5;
  	
  	status = HasLoop(&node_1);
  	ResultStatus(status, 1);
}

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

static void TestFindIntersection(void)
{
	node_t node_1_1;
	node_t node_1_2;
	node_t node_1_3;
	node_t node_1_4;
	node_t node_1_5;
	
	node_t node_2_1;
	node_t node_2_2;
	node_t node_2_3;
	node_t node_2_4;
	node_t node_2_5;
	
	node_t *intersection = NULL;
	
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;
	int num_5 = 5;
	
	node_1_1.data = (void *)&num_1;
  	node_1_1.next = &node_1_2;
  	
  	node_1_2.data = (void *)&num_2;
  	node_1_2.next = &node_1_3;
  	
  	node_1_3.data = (void *)&num_3;
  	node_1_3.next = &node_1_4;
  	
  	node_1_4.data = (void *)&num_4;
  	node_1_4.next = &node_1_5;
  	
  	node_1_5.data = (void *)&num_5;
  	node_1_5.next = NULL;
  	
  	node_2_1.data = (void *)&num_5;
  	node_2_1.next = &node_2_2;
  	
  	node_2_2.data = (void *)&num_4;
  	node_2_2.next = &node_2_3;
  	
  	node_2_3.data = (void *)&num_3;
  	node_2_3.next = &node_2_4;
  	
  	node_2_4.data = (void *)&num_2;
  	node_2_4.next = &node_2_5;
  	
  	node_2_5.data = (void *)&num_1;
  	node_2_5.next = NULL;
  	
  	printf("Testing with no intersection:\n");
  	intersection = FindIntersection(&node_1_1, &node_2_1);
  	
  	if (NULL == intersection)
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
	
	printf("Testing with intersection from 2 to 1:\n");
	node_2_4.next = &node_1_5;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_5);
	
	node_2_4.next = &node_1_4;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_4);
	
	node_2_4.next = &node_1_3;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_3);
	
	node_2_2.next = &node_1_3;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_3);
	
	node_2_2.next = &node_1_1;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_1);
	
	node_2_2.next = &node_2_3;
	node_2_4.next = &node_2_5;
	
	printf("Testing with intersection from 1 to 2:\n");
	node_1_4.next = &node_2_5;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_1);
	
	node_1_4.next = &node_2_4;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_2);
	
	node_1_4.next = &node_2_3;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_3);
	
	node_1_2.next = &node_2_3;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_3);
	
	node_1_2.next = &node_2_1;
	
	intersection = FindIntersection(&node_1_1, &node_2_1);
	ResultStatus(*(int *)(intersection->data), num_5);
}















