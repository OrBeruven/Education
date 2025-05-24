/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <stddef.h>

#include "../../ds/include/linked_list_exercises.h"


#define GREEN_OUT_PUT printf("\033[0;32m");

#define RED_OUT_PUT printf("\033[0;31m");

#define NORMAL_OUT_PUT printf("\033[0m");

size_t ListLength(node_t *head)
{
	size_t count = 0;
	
	while (NULL != head)
	{
		head = head->next;
		++count;
	}
	
	return count;
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

int IsIntersect(node_t *head1, node_t *head2)
{
	int diff = (int)ListLength(head1) - (int)ListLength(head2);
	
	if (0 < diff)
	{
		while (diff)
		{
			head1 = head1->next;
			--diff;
		}
	}
	else
	{
		while (diff)
		{
			head2 = head2->next;
			++diff;
		}
	}
	
	while (head1 != head2)
	{
		head1 = head1->next;
		head2 = head2->next;
	}
	
	return NULL != head1;
}

void SeperateIntersection(node_t *head1, node_t *head2)
{
	node_t *before_inter = head2;
	int diff = (int)ListLength(head1) - (int)ListLength(head2);
	
	if (0 < diff)
	{
		while (diff)
		{
			head1 = head1->next;
			--diff;
		}
	}
	else
	{
		while (diff)
		{
			head2 = head2->next;
			++diff;
		}
	}
	
	while (head1 != head2)
	{
		before_inter = head2;
		head1 = head1->next;
		head2 = head2->next;
	}
	
	before_inter->next = NULL;
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
	
	node_t node_6;
	node_t node_7;
	node_t node_8;
	node_t node_9;
	
	int num_6 = 6;
	int num_7 = 7;
	int num_8 = 8;
	int num_9 = 9;
	
	
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
  	
  	
  	
  	
  	node_6.data = (void *)&num_6;
  	node_6.next = &node_7;
  	
  	node_7.data = (void *)&num_7;
  	node_7.next = &node_8;
  	
  	node_8.data = (void *)&num_8;
  	node_8.next = &node_9;
  	
  	node_9.data = (void *)&num_9;
  	node_9.next = NULL;

  	
  	
  	ResultStatus(IsIntersect(&node_1, &node_6), 0);
  	node_9.next = &node_3;
  	ResultStatus(IsIntersect(&node_1, &node_3), 1);
  	
  	SeperateIntersection(&node_1, &node_6);
  	ResultStatus(IsIntersect(&node_1, &node_6), 0);
	
	return 0;
}
