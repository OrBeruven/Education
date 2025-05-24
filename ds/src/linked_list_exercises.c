/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 9.2.2023

	Description : c file for linked list exercises

*****************************/

#include <assert.h> /*using assert*/
#include <stddef.h> /*using - NULL*/

#include "../include/linked_list_exercises.h"


node_t *Flip(node_t *head)
{
	node_t *before = NULL;
	node_t *next = NULL;
	
	while (NULL != head->next)
	{
		next = head->next;
		head->next = before;
		before = head;
		head = next;
	}
	
	head->next = before;
	
	return head;
}

int HasLoop(node_t *head)
{
	node_t *two_jump = NULL;
	
	assert(NULL != head);
	
	two_jump = head->next;
	
	while (two_jump != NULL && two_jump->next != NULL)
	{
		if (two_jump->next == head ||
		two_jump == head)
		{
			return 1;
		}
	
		head = head->next;
		two_jump = two_jump->next->next;
	}
	
	return 0;
}

/*********************************************************/
/*my FindIntersection*/
node_t *FindIntersection1(node_t *head_1, node_t *head_2)
{
	node_t *runner_1 = head_1;
	node_t *runner_2 = head_2;
	
	assert(NULL != head_1);
	assert(NULL != head_2);
	
	while (runner_1 != runner_2)
	{
		runner_1 == NULL ? runner_1 = head_1 : (runner_1 = runner_1->next);
		runner_2 == NULL ? runner_2 = head_2 : (runner_2 = runner_2->next);
	}
	
	return runner_1;
}
/*************************************************************/

static size_t ListCount(node_t *head)
{
	size_t count = 0;
	
	assert(NULL != head);
	
	while (NULL != head->next)
	{
		++count;
		head = head->next;
	}
	
	return count;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	int remain = 0;
	
	remain = ListCount(head_1) - ListCount(head_2);
	
	if (0 > remain)
	{
		while (0 > remain)
		{
			head_2 = head_2->next;
			++remain;
		}
	}
	else
	{
		while (0 < remain)
		{
			head_1 = head_1->next;
			--remain;
		}
	}

	
	while (head_1 != head_2 && NULL != head_1 && NULL != head_2)
    {
            head_1 = head_1->next;
            head_2 = head_2->next;
    }
     
	return head_1;
}


