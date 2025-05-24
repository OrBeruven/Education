/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

#define BIGGER 0
#define SMALLER 1

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

static void SwapValues(node_t *n1, node_t *n2);
static void PrintSLL(node_t *head);

node_t *Rearrange(node_t *head)
{
	node_t *runner = head;
	node_t *next = runner->next;
	int sign = BIGGER;
	
	while (NULL != next)
	{
		if (BIGGER == sign)
		{
			sign = SMALLER;
			if (*(int *)runner->data < *(int *)next->data)
			{
				SwapValues(runner, next);
			}
		}
		else
		{
			sign = BIGGER;
			if (*(int *)runner->data > *(int *)next->data)
			{
				SwapValues(runner, next);
			}
		}
		
		runner = next;
		next = next->next;
	}
	
	return head;
}


static void SwapValues(node_t *n1, node_t *n2)
{
	void *temp = n1->data;
	n1->data = n2->data;
	n2->data = temp;
}


int main(void)
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
  	
  	PrintSLL(head);
  	
  	head = Rearrange(head);
	printf("\n");  	
	PrintSLL(head);
	return 0;
}

static void PrintSLL(node_t *head)
{
	if (NULL == head)
	{
		return;
	}
	
	printf("%d -> ", *(int *)head->data);
	
	PrintSLL(head->next);
}	








