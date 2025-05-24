/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <assert.h>

#include "../../ds/include/linked_list_exercises.h"

int IsLoop(node_t *head);

void OpenLoopOpen(node_t *head, node_t *in_loop);
void OpenLoop(node_t *head);

void PrintLoop(node_t *head);

#define GREEN_OUT_PUT printf("\033[0;32m");

#define RED_OUT_PUT printf("\033[0;31m");

#define NORMAL_OUT_PUT printf("\033[0m");

void PrintLoop(node_t *head)
{
	int temp = 10;
	
	while (NULL != head && temp)
	{
		printf("|%d| ->", *(int *) head->data);
		head = head->next;
		--temp;
	}
	printf("\n");
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

int main(void)
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
  	
  	
  	status = IsLoop(&node_1);
  	PrintLoop(&node_1);
  	ResultStatus(status, 0);
  	
  	node_5.next = &node_1;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 1);
    OpenLoop(&node_1);	
    PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 0);
  	
  	node_5.next = &node_2;

  	
  	status = IsLoop(&node_1);
  	PrintLoop(&node_1);
  	ResultStatus(status, 1);
  	OpenLoop(&node_1);	
  	status = IsLoop(&node_1);
  	PrintLoop(&node_1);
  	ResultStatus(status, 0);
  	
  	node_5.next = &node_3;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 1);
  	OpenLoop(&node_1);	
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 0);
  	
  	node_5.next = &node_4;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 1);
  	OpenLoop(&node_1);
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 0);
  	
  	node_5.next = &node_5;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 1);
  	OpenLoop(&node_1);	
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	ResultStatus(status, 0);

	return 0;
}

int IsLoop(node_t *head)
{
	node_t *fast_runner = NULL;
	int flag = 0;
	
	fast_runner = head->next;
	
	while (NULL != fast_runner && NULL != fast_runner->next)
	{
		if (head == fast_runner || head == fast_runner->next)
		{
			flag = 1;
			break;
		}
		
		fast_runner = fast_runner->next->next;
		head = head->next;
	}
	
	return flag;
}





void OpenLoop(node_t *head)
{
	node_t *fast_runner = NULL;
	node_t *slow_runner = NULL;
	
	fast_runner = head->next;
	slow_runner = head;
	
	while (NULL != fast_runner && NULL != fast_runner->next)
	{
		if (slow_runner == fast_runner || slow_runner == fast_runner->next)
		{
			OpenLoopOpen(head, slow_runner);
			break;
		}
		
		fast_runner = fast_runner->next->next;
		slow_runner = slow_runner->next;
	}
	
	return;
}


void OpenLoopOpen(node_t *head, node_t *in_loop)
{
	node_t *first_run = NULL;
	node_t *second_run = NULL;
	
	size_t  loop_size = 1;
	
	assert(NULL != head);
	
	first_run = in_loop->next;
	second_run = in_loop;
	
	while (first_run != second_run)
	{
		first_run = first_run->next;
		++loop_size;
	}
	
	first_run = head;
	second_run = head;
	
	while (loop_size)
	{
		first_run = first_run->next;
		--loop_size;
	}
	
	
	while (second_run != first_run)
	{
		first_run = first_run->next;
		second_run = second_run->next;
	}
	
	while (second_run->next != first_run)
	{
		second_run = second_run->next;
	}
	
	second_run->next = NULL;
	
	return;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
